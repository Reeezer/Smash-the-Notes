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
    lifeLabel = new QGraphicsSimpleTextItem();
    feverLabel = new QGraphicsSimpleTextItem();
    comboLabel = new QGraphicsSimpleTextItem();
    scoreLabel = new QGraphicsSimpleTextItem();
    timeLabel = new QGraphicsSimpleTextItem();

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

    scene->addLine(XLINE + PIXMAPHALF, 0, XLINE + PIXMAPHALF, this->height()); //XLINE + half of pixmap width

    //Set up
    upNotes = new QList<Note *>();
    downNotes = new QList<Note *>();

    QString path = "C:\\Users\\ethan.millet\\Desktop\\Niveau 2\\P2\\git\\LFZ_-_Popsicle_Easy.osu";
    loadFromFile(path, upNotes, downNotes);

    for(Note* note:*upNotes)
    {
        scene->addItem(note);
        note->setY(100);
    }

    for(Note* note:*downNotes)
    {
        scene->addItem(note);
        note->setY(300);
    }

    //Start
    player = new Character();
    scene->addItem(player);
    player->setY(300);

    music->play();
    update();
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

//If we miss a note but we don't hit it with the body of the character, we want to be able to hit the next note while the note we have missed is still on the screen but gone after the player
Note* GameView::getNextNote(QList<Note *> *Notes)
{
    int i = 0;
    while(Notes->at(i)->x() < XLINE - PIXMAPHALF - 10 && Notes->last() != Notes->at(i))
    {
        i++;
    }
    return Notes->at(i);
}

//Check if the player has missed the note but it was close
void GameView::checkPass(QList<Note *> *Notes, bool high)
{
    if (!Notes->isEmpty() && XLINE - NOTPASSED <= getNextNote(Notes)->x() && XLINE - PIXMAPHALF >= getNextNote(Notes)->x())
    {
        if(player->getJump() == high)
        {
            getNextNote(Notes)->hit();
            if(getNextNote(Notes)->getNoteType() == NoteType::NORMAL)
            {
                removeNotePassed(Notes);
                player->damage();
                player->comboBreak();
            }
            else if(getNextNote(Notes)->getNoteType() == NoteType::BONUS)
            {
                removeNotePassed(Notes);
                player->regenerate();
                player->increaseScore();
            }
            else if(getNextNote(Notes)->getNoteType() == NoteType::TRAP && getNextNote(Notes)->getHit() == 0)//We don't remove it, then it must not hit us more than one time
            {
                player->damage();
                player->comboBreak();
            }
        }
        else
        {
            if (getNextNote(Notes)->getNoteType() == NoteType::TRAP)
                player->increasePass();
            else
                player->increaseMiss();
        }
    }
}

void GameView::keyPressEvent(QKeyEvent *event)
{
    //Use the time of the music to know when to hit
    //If it's a SMASH note we can destroy our keyboard
    if(event->key() == Qt::Key_F || event->key() == Qt::Key_J)
    {
        if(!upNotes->isEmpty() && getNextNote(upNotes)->getNoteType() == NoteType::SMASH)
        { //rajouter les hits max
            hitSmash();
            getNextNote(upNotes)->hit();
        }
        else if(!downNotes->isEmpty() && getNextNote(downNotes)->getNoteType() == NoteType::SMASH)
        {
            hitSmash();
            getNextNote(downNotes)->hit();
        }
    }
    //If it's not, we have to check what it is and to do something in consequence
    if(event->key() == Qt::Key_F)
    {
        if(!player->getJump())
        {
            player->setY(100);
            player->setJump(true);
        }
        if (!upNotes->isEmpty() && getNextNote(upNotes)->getNoteType() != NoteType::SMASH)
            hitNormal(upNotes);
    }
    if(event->key() == Qt::Key_J)
    {
        if(player->getJump())
        {
            player->setY(300);
            player->setJump(false);
        }
        if (!downNotes->isEmpty() && getNextNote(downNotes)->getNoteType() != NoteType::SMASH)
            hitNormal(downNotes);
    }
    update();
}

//Check for the different notes what to do with the character
void GameView::hitNormal(QList<Note *> *Notes)
{
    if(!Notes->isEmpty())
    {
        if(getNextNote(Notes)->getNoteType() == NoteType::NORMAL)
        {
            if (XLINE - PERFECT <= getNextNote(Notes)->x() && XLINE + PERFECT >= getNextNote(Notes)->x())
                player->increaseScorePerfect();
            else if (XLINE - GREAT <= getNextNote(Notes)->x() && XLINE + GREAT >= getNextNote(Notes)->x())
                player->increaseScoreGreat();
            else
                return;
            //If the player didn't hit a note, we don't want to errase the first one of the list
            removeNoteHitten(Notes);
            player->increaseCombo();
            player->increaseFever();
        }
    }
}

void GameView::hitSmash()
{
    player->increaseCombo();
    player->increaseFever();
    player->increaseScore();
}

void GameView::removeNotePassed(QList<Note *> *Notes)
{
    scene->removeItem(Notes->first());
    Note *note = Notes->takeFirst();
    delete note;
}

void GameView::removeNoteHitten(QList<Note *> *Notes)
{
    scene->removeItem(getNextNote(Notes));
    Note *note = getNextNote(Notes);
    Notes->removeOne(note);
    delete note;
}

void GameView::changeNotePosition(QList<Note *> *Notes)
{
    if(!Notes->isEmpty())
    {
        for(int i = 0; i < Notes->count(); i++)
        {
            int x = XLINE + ((Notes->at(i)->getTimestamp() - music->position()) * ((double)(this->width() - XLINE) / (double)3000));
            Notes->at(i)->setX(x);
            if(x <= 0)
                removeNotePassed(Notes);
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
