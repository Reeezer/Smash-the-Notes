#include "gameview.h"

#include <QtWidgets>
#include <QMediaPlayer>

#define PERFECT 20
#define GREAT 80
#define NOTPASSED 300

GameView::GameView(Game *game, QWidget *parent)
    : QGraphicsView(parent), game(game)
{
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
    musicPosition = music->position();

    //When the note has not been hitten and it arrives on the player
    checkPass(upNotes);
    checkPass(downNotes);
    _update();
}

void GameView::checkPass(QList<Note *> Notes)
{
    if (!Notes.isEmpty() && Notes.first()->timeStamp() < musicPosition)
    {
        if(player->getJump() && (Notes.first()->_type() == NORMAL || Notes.first()->_type() == TRAP))
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
    musicPosition = music->position();

    if (event->key() == Qt::Key_F)
    {
        player->setJump(true);
        playerHit(upNotes);
    }
    if (event->key() == Qt::Key_J)
    {
        player->setJump(false);
        playerHit(downNotes);
    }
    _update();
}

//Check for the different notes what to do with the character
void GameView::playerHit(QList<Note *> Notes)
{
    if(!Notes.isEmpty())
    {
        if(Notes.first()->_type() == NORMAL)
        {
            if (musicPosition <= Notes.first()->timeStamp() + PERFECT && musicPosition >= Notes.first()->timeStamp() - PERFECT)
                player->increaseScorePerfect();
            else if (musicPosition <= Notes.first()->timeStamp() + GREAT && musicPosition >= Notes.first()->timeStamp() - GREAT)
                player->increaseScoreGreat();
            else
                return;
            Notes.removeFirst();
            player->increaseCombo();
            player->increaseFever();
        }
        else if(Notes.first()->_type() == BONUS)
        {
            if(musicPosition <= Notes.first()->timeStamp() + NOTPASSED && musicPosition >= Notes.first()->timeStamp() - NOTPASSED)
                player->regenerate();
        }
        else if(Notes.first()->_type() == TRAP)
        {
            if(musicPosition <= Notes.first()->timeStamp() + NOTPASSED && musicPosition >= Notes.first()->timeStamp() - NOTPASSED)
            {
                player->damage();
                player->comboBreak();
            }
            else
                player->increasePass();
        }
        else if(Notes.first()->_type() == SMASH)
        {
            player->increaseCombo();
            player->increaseFever();
            player->increaseScore();
        }
    }
}

//Update the diplay
void GameView::_update()
{
    timeLabel->setText("Time : " + QString::asprintf("%lld", musicPosition));
    lifeLabel->setText("Life : " + QString::asprintf("%d", player->getLife()));
    feverLabel->setText("Fever : " + QString::asprintf("%d", player->getFever()));
    comboLabel->setText("Combo : " + QString::asprintf("%d", player->getCombo()));
    scoreLabel->setText("Score : " + QString::asprintf("%d", player->getScore()));
}
