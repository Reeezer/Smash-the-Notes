#include "gameview.h"

#include <QTime>
#include <QMediaPlayer>
#include <QLabel>
#include <QVBoxLayout>
#include <QKeyEvent>

GameView::GameView(Game *game, QWidget *parent)
    : QGraphicsView(parent), game(game)
{
    this->setScene(scene);
    this->setVerticalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    
    //Appel la musique en fond pour récupérer le timing
    music = new QMediaPlayer(this);
    music->setMedia(QUrl("qrc:/music/test.mp3"));
    timer = new QTime();

    //Display
    lifeLabel = new QLabel();
    feverLabel = new QLabel();
    comboLabel = new QLabel();
    scoreLabel = new QLabel();
    timeLabel = new QLabel();
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(timeLabel);
    layout->addWidget(lifeLabel);
    layout->addWidget(feverLabel);
    layout->addWidget(comboLabel);
    layout->addWidget(scoreLabel);

    //Start
    player = new Character();
    music->play();
    startTimer(0);
}

//Actualisation of the display
void GameView::timerEvent(QTimerEvent *)
{
    //When the note has not been hitten and it arrives on the player
    checkPass(&upNotes, true);
    checkPass(&downNotes, false);
    update();
}

void GameView::checkPass(QList<Note *> *Notes, bool high)
{
    if (!Notes->isEmpty() && Notes->first()->timestamp() < music->position())
    {
        if(player->getJump() == high && (Notes->first()->type() == NoteType::NORMAL || Notes->first()->type() == NoteType::TRAP))
        {
            player->damage();
            player->increaseMiss();
            player->comboBreak();
        }
        removeNote(Notes);
    }
}

void GameView::keyPressEvent(QKeyEvent *event)
{
    //Use the time of the music to know when to hit
    if (event->key() == Qt::Key_F)
    {
        if (upNotes.first()->type() == NoteType::SMASH || downNotes.first()->type() == NoteType::SMASH)
            hitSmash();
        else
        {
            player->setJump(true);
            playerHit(&upNotes);
        }
    }
    if (event->key() == Qt::Key_J)
    {
        if (upNotes.first()->type() == NoteType::SMASH || downNotes.first()->type() == NoteType::SMASH)
            hitSmash();
        else
        {
            player->setJump(false);
            playerHit(&downNotes);
        }
    }
    update();
}

//Check for the different notes what to do with the character
void GameView::playerHit(QList<Note *> *Notes)
{
    if(!Notes->isEmpty())
    {
        if(Notes->first()->type() == NoteType::NORMAL)
        {
            if (music->position() <= Notes->first()->timestamp() + PERFECT && music->position() >= Notes->first()->timestamp() - PERFECT)
                player->increaseScorePerfect();
            else if (music->position() <= Notes->first()->timestamp() + GREAT && music->position() >= Notes->first()->timestamp() - GREAT)
                player->increaseScoreGreat();
            else
                return;
            removeNote(Notes);
            player->increaseCombo();
            player->increaseFever();
        }
        else if(Notes->first()->type() == NoteType::BONUS)
        {
            if(music->position() <= Notes->first()->timestamp() + NOTPASSED && music->position() >= Notes->first()->timestamp() - NOTPASSED)
                player->regenerate();
        }
        else if(Notes->first()->type() == NoteType::TRAP)
        {
            if(music->position() <= Notes->first()->timestamp() + NOTPASSED && music->position() >= Notes->first()->timestamp() - NOTPASSED)
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

void GameView::removeNote(QList<Note *> *list)
{
    scene->removeItem(list->first());
    Note *temp = list->takeFirst();
    delete temp;
}

void GameView::changeNotePosition(QList<Note *> *list)
{
    for (int i = 0; i < list->count(); i++)
    {
        list->at(i)->setX(100 + ((list->at(i)->timestamp()-music->position()) * ((double)(this->width()-100)/(double)3000)));
        if(list->at(i)->x() <= 0)
            removeNote(list);
    }
}

//Update the diplay
void GameView::update()
{
    changeNotePosition(&upNotes);
    changeNotePosition(&downNotes);

    timeLabel->setText("Time : " + QString::asprintf("%lld", music->position()));
    lifeLabel->setText("Life : " + QString::asprintf("%d", player->getLife()));
    feverLabel->setText("Fever : " + QString::asprintf("%d", player->getFever()));
    comboLabel->setText("Combo : " + QString::asprintf("%d", player->getCombo()));
    scoreLabel->setText("Score : " + QString::asprintf("%d", player->getScore()));
}
