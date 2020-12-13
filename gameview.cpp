#include "gameview.h"

#include <QTime>
#include <QMediaPlayer>
#include <QGraphicsSimpleTextItem>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsScene>

GameView::GameView(Game *game, QWidget *parent)
    : QGraphicsView(parent), game(game)
{
    resize(800,400);
    scene = new QGraphicsScene();
    setScene(scene);

    this->setVerticalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);

    //Appel la musique en fond pour récupérer le timing
    music = new QMediaPlayer(this);
    music->setMedia(QUrl("qrc:/music/test.mp3"));
    timer = new QTime();

    //Display
    lifeLabel = new QGraphicsSimpleTextItem("lifeLabel");
    feverLabel = new QGraphicsSimpleTextItem("feverLabel");
    comboLabel = new QGraphicsSimpleTextItem("comboLabel");
    scoreLabel = new QGraphicsSimpleTextItem("scoreLabel");
    timeLabel = new QGraphicsSimpleTextItem("timeLabel");

    scene->addItem(timeLabel);
    scene->addItem(feverLabel);
    scene->addItem(lifeLabel);
    scene->addItem(comboLabel);
    scene->addItem(scoreLabel);

    feverLabel->setPos(10,10);
    lifeLabel->setPos(10,30);
    comboLabel->setPos(150,10);
    scoreLabel->setPos(150,30);
    timeLabel->setPos(650,10);

    scene->addLine(XLINE, 0, XLINE, this->height());

    //Set up
    upNotes = new QList<Note *>();

    Note *note1 = new Note;
    note1->_timestamp = 2000;
    note1->_noteType = NoteType::NORMAL;
    note1->setY(100);
    Note *note2 = new Note();
    note2->_timestamp = 3000;
    note2->_noteType = NoteType::BONUS;
    note2->setY(100);
    Note *note3 = new Note();
    note3->_timestamp = 5000;
    note3->_noteType = NoteType::NORMAL;
    note3->setY(100);
    Note *note4 = new Note();
    note4->_timestamp = 8000;
    note4->_noteType = NoteType::TRAP;
    note4->setY(100);
    Note *note5 = new Note();
    note5->_timestamp = 12000;
    note5->_noteType = NoteType::NORMAL;
    note5->setY(100);
    Note *note6 = new Note();
    note6->_timestamp = 15000;
    note6->_noteType = NoteType::TRAP;
    note6->setY(100);
    Note *note7 = new Note();
    note7->_timestamp = 20000;
    note7->_noteType = NoteType::BONUS;
    note7->setY(100);
    upNotes->append(note1);
    upNotes->append(note2);
    upNotes->append(note3);
    upNotes->append(note4);
    upNotes->append(note5);
    upNotes->append(note6);
    upNotes->append(note7);

    for(Note* note:*upNotes)
        scene->addItem(note);

    downNotes = new QList<Note *>();

    Note *note12 = new Note();
    note12->_timestamp = 1800;
    note12->_noteType = NoteType::NORMAL;
    note12->setY(300);
    Note *note22 = new Note();
    note22->_timestamp = 2000;
    note22->_noteType = NoteType::BONUS;
    note22->setY(300);
    Note *note32 = new Note();
    note32->_timestamp = 3600;
    note32->_noteType = NoteType::NORMAL;
    note32->setY(300);
    Note *note42 = new Note();
    note42->_timestamp = 7000;
    note42->_noteType = NoteType::TRAP;
    note42->setY(300);
    Note *note52 = new Note();
    note52->_timestamp = 10000;
    note52->_noteType = NoteType::NORMAL;
    note52->setY(300);
    Note *note62 = new Note();
    note62->_timestamp = 11000;
    note62->_noteType = NoteType::TRAP;
    note62->setY(300);
    Note *note72 = new Note();
    note72->_timestamp = 16000;
    note72->_noteType = NoteType::BONUS;
    note72->setY(300);
    downNotes->append(note12);
    downNotes->append(note22);
    downNotes->append(note32);
    downNotes->append(note42);
    downNotes->append(note52);
    downNotes->append(note62);
    downNotes->append(note72);

    for(Note* note:*downNotes)
        scene->addItem(note);

    //Start
    player = new Character();
    scene->addItem(player);
    player->setY(300);

    music->play();
    this->startTimer(0);
}

//update of the display
void GameView::timerEvent(QTimerEvent *)
{
    //When the note has not been hitten and it arrives on the player
    checkPass(upNotes, true);
    checkPass(downNotes, false);

    update();
}

void GameView::checkPass(QList<Note *> *Notes, bool high)
{
    if (!Notes->isEmpty() && Notes->first()->getTimestamp() < music->position())
    {
        if(player->getJump() == high)
        {
            if(Notes->first()->getNoteType() == NoteType::NORMAL || Notes->first()->getNoteType() == NoteType::TRAP)
            {
                player->damage();
                player->comboBreak();
            }
            else if(Notes->first()->getNoteType() == NoteType::BONUS)
            {
                player->regenerate();
                player->increaseScore();
            }
        }
        if(player->getJump() != high && Notes->first()->getNoteType() != NoteType::TRAP)
            player->increaseMiss();
        removeNote(Notes);
    }
}

void GameView::keyPressEvent(QKeyEvent *event)
{
    //Use the time of the music to know when to hit
    //If it's a SMASH note we can destroy our keyboard
    if(event->key() == Qt::Key_F || event->key() == Qt::Key_J)
    {
        if(!upNotes->isEmpty() && upNotes->first()->getNoteType() == NoteType::SMASH)
        {
            hitSmash();
            upNotes->first()->hit();
        }
        else if(!downNotes->isEmpty() && downNotes->first()->getNoteType() == NoteType::SMASH)
        {
            hitSmash();
            downNotes->first()->hit();
        }
    }
    //If it's not, we have to check what it is and to do something in consequence
    if(event->key() == Qt::Key_F)
    {
        if(player->getJump() == false)
        {
            player->setY(100);
            player->setJump(true);
        }
        if (!upNotes->isEmpty() && upNotes->first()->getNoteType() != NoteType::SMASH)
            playerHit(upNotes);
    }
    if(event->key() == Qt::Key_J)
    {
        if(player->getJump() == true)
        {
            player->setY(300);
            player->setJump(false);
        }
        if (!downNotes->isEmpty() && downNotes->first()->getNoteType() != NoteType::SMASH)
            playerHit(downNotes);
    }
    update();
    scene->update();
}

//Check for the different notes what to do with the character
void GameView::playerHit(QList<Note *> *Notes)
{
    if(!Notes->isEmpty())
    {
        if(Notes->first()->getNoteType() == NoteType::NORMAL)
        {
            if (music->position() <= Notes->first()->getTimestamp() + PERFECT && music->position() >= Notes->first()->getTimestamp() - PERFECT)
                player->increaseScorePerfect();
            else if (music->position() <= Notes->first()->getTimestamp() + GREAT && music->position() >= Notes->first()->getTimestamp() - GREAT)
                player->increaseScoreGreat();
            else
                return;
            //If the player didn't hit a note, we don't want to errase the first one of the list
            removeNote(Notes);
            player->increaseCombo();
            player->increaseFever();
        }
        else if(Notes->first()->getNoteType() == NoteType::BONUS)
        {
            if(music->position() <= Notes->first()->getTimestamp() + NOTPASSED && music->position() >= Notes->first()->getTimestamp() - NOTPASSED)
                player->regenerate();
        }
        else if(Notes->first()->getNoteType() == NoteType::TRAP)
        {
            if(music->position() <= Notes->first()->getTimestamp() + NOTPASSED && music->position() >= Notes->first()->getTimestamp() - NOTPASSED)
            {
                player->damage();
                player->comboBreak();
            }
            else
                player->increasePass();
        }
    }
}

void GameView::hitSmash()
{
    player->increaseCombo();
    player->increaseFever();
    player->increaseScore();
}

void GameView::removeNote(QList<Note *> *Notes)
{
    scene->removeItem(Notes->first());
    Note *note = Notes->takeFirst();
    delete note;
}

void GameView::changeNotePosition(QList<Note *> *Notes)
{
    if(!Notes->isEmpty())
    {
        for(int i = 0; i < Notes->count(); i++)
        {
            int x = XLINE + ((Notes->at(i)->getTimestamp() - music->position()) * ((double)(this->width() - XLINE) / (double)6000));
            Notes->at(i)->setX(x);
            if(x <= -XLINE)
                removeNote(Notes);
        }
    }
}

//Update the diplay
void GameView::update()
{
    changeNotePosition(upNotes);
    changeNotePosition(downNotes);
    //afficher le joueur et les différentes notes

    timeLabel->setText("Time : " + QString::asprintf("%lld", music->position()));
    lifeLabel->setText("Life : " + QString::asprintf("%d", player->getLife()));
    feverLabel->setText("Fever : " + QString::asprintf("%d", player->getFever()));
    comboLabel->setText("Combo : " + QString::asprintf("%d", player->getCombo()));
    scoreLabel->setText("Score : " + QString::asprintf("%d", player->getScore()));
    scene->update();
}
