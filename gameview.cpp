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
#include <QSoundEffect>
#include <QFontDatabase>

GameView::GameView(Game *game, QWidget *parent)
    : QGraphicsView(parent), game(game)
{
    //Custom font
    QFontDatabase::addApplicationFont("qrc:/music/foo.ttf");
    QFont Foo("Foo", 18, QFont::Normal);
    QFont FooTiny("Foo", 18, QFont::Normal);

    resize(1000, 600);
    XLINE = this->width() / 5;
    UPLINE = this->height() / 3;
    DOWNLINE = this->height() * 2 / 3;
    this->setBackgroundBrush(Qt::black);
    scene = new QGraphicsScene();
    setScene(scene);
    scene->addRect(0, 0, this->width(), this->height(), QPen(Qt::black), QBrush(Qt::white));

    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //Appel la musique en fond pour récupérer le timing
    music = new QMediaPlayer(this);
    music->setMedia(QUrl("qrc:/music/test.mp3"));
    timer = new QTime();

    hitEffect = new QSoundEffect(this);
    hitEffect->setSource(QUrl("qrc:/music/hit-normal.wav"));

    //Display
    QGraphicsSimpleTextItem *comboLabel = new QGraphicsSimpleTextItem("Combo");
    combo = new QGraphicsSimpleTextItem();
    QGraphicsSimpleTextItem *scoreLabel = new QGraphicsSimpleTextItem("Score");
    score = new QGraphicsSimpleTextItem();
    QGraphicsSimpleTextItem *highScoreLabel = new QGraphicsSimpleTextItem("HighScore");
    highScore = new QGraphicsSimpleTextItem();

    combo->setFont(Foo);
    comboLabel->setFont(Foo);
    score->setFont(Foo);
    scoreLabel->setFont(Foo);
    highScore->setFont(Foo);
    highScoreLabel->setFont(Foo);

    scene->addItem(comboLabel);
    scene->addItem(combo);
    scene->addItem(scoreLabel);
    scene->addItem(score);
    scene->addItem(highScore);
    scene->addItem(highScoreLabel);

    comboLabel->setPos(this->width() / 2 - 40, this->height() * 2 / 60);
    combo->setPos(this->width() / 2 - 40, this->height() * 5 / 60);
    scoreLabel->setPos(this->width() / 5 - 40, this->height() / 60);
    score->setPos(this->width() / 5 - 40, this->height() * 3 / 60);
    highScoreLabel->setPos(this->width() * 4 / 5 - 40, this->height() / 60);
    highScore->setPos(this->width() * 4 / 5 - 40, this->height() * 3 / 60);

    scene->addLine(XLINE + PIXMAPHALF, 0, XLINE + PIXMAPHALF, this->height()); //XLINE + half of pixmap width
    scene->addRect(0, this->height() * 57 / 60, this->width() / 2, this->height() * 2 / 60, QPen(Qt::black), QBrush(Qt::lightGray));
    scene->addRect(this->width() / 2, this->height() * 57 / 60, this->width() / 2, this->height() * 2 / 60, QPen(Qt::black), QBrush(Qt::lightGray));
    scene->addRect(0, this->height() * 59 / 60, this->width(), this->height() / 60, QPen(Qt::black), QBrush(Qt::lightGray));
    lifeRect = scene->addRect(0, this->height() * 57 / 60, this->width() / 2, this->height() * 2 / 60, QPen(Qt::black), QBrush(QColor(204,0,0)));
    feverRect = scene->addRect(this->width() / 2, this->height() * 57 / 60, this->width() / 2, this->height() * 2 / 60, QPen(Qt::black), QBrush(QColor(68,201,228)));
    durationRect = scene->addRect(0, this->height() * 59 / 60, this->width(), this->height() / 60, QPen(Qt::black), QBrush(QColor(64,64,64)));

    //Set up
    upNotes = new QList<Note *>();
    downNotes = new QList<Note *>();

    QString path = "C:\\Users\\leon.muller\\Desktop\\.Projet\\jeu-de-rythme\\LFZ_-_Popsicle_Easy.osu";
    loadFromFile(path, upNotes, downNotes);

    for (Note *note : *upNotes)
    {
        note->setY(UPLINE);
        scene->addItem(note);
    }

    for (Note *note : *downNotes)
    {
        note->setY(DOWNLINE);
        scene->addItem(note);
    }

    //Start
    player = new Character();
    scene->addItem(player);
    player->setPos(XLINE - 110, DOWNLINE);

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
Note *GameView::getNextNote(QList<Note *> *Notes)
{
    int i = 0;
    while (Notes->at(i)->x() < XLINE - NOTPASSED && Notes->last() != Notes->at(i))
        i++;
    return Notes->at(i);
}

//Check if the player has missed the note but it was close
void GameView::checkPass(QList<Note *> *Notes, bool high)
{
    if (!Notes->isEmpty() && (XLINE - NOTPASSED) <= getNextNote(Notes)->x() && (XLINE - PIXMAPHALF) >= getNextNote(Notes)->x())
    {
        if (player->getJump() == high)
        {
            getNextNote(Notes)->hit();
            if (getNextNote(Notes)->getNoteType() == NoteType::NORMAL)
            {
                player->setState(CharacterAction::DAMAGED);
                removeNotePassed(Notes);
                player->damage();
                if(player->getLife() <= 0)
                {
                    player->setState(CharacterAction::DOWN);
                    music->pause();
                }
                player->comboBreak();
            }
            else if (getNextNote(Notes)->getNoteType() == NoteType::BONUS)
            {
                player->setState(CharacterAction::REGENERATE);
                removeNotePassed(Notes);
                player->regenerate();
                player->increaseScore();
            }
            else if (getNextNote(Notes)->getNoteType() == NoteType::TRAP && getNextNote(Notes)->getHit() == 0) //We don't remove it, then it must not hit us more than one time
            {
                qDebug() << "trap";
                player->setState(CharacterAction::DAMAGED);
                player->damage();
                if(player->getLife() <= 0)
                {
                    player->setState(CharacterAction::DOWN);
                    music->pause();
                }
                player->comboBreak();
            }
        }
        else
        {
            if (getNextNote(Notes)->getNoteType() == NoteType::TRAP)
            {
                //                //TEST
                //                if(!player->getJump())
                //                    upHit->setText("PASS");
                //                else
                //                    downHit->setText("PASS");
                //                //FIN TEST
                player->increasePass();
            }
            else
            {
                //                //TEST
                //                if(!player->getJump())
                //                    upHit->setText("MISS");
                //                else
                //                    downHit->setText("MISS");
                //                //FIN TEST
                player->increaseMiss();
            }
        }
    }
}

void GameView::keyPressEvent(QKeyEvent *event)
{
    //Use the time of the music to know when to hit
    //If it's a SMASH note we can destroy our keyboard
    if (event->key() == Qt::Key_F || event->key() == Qt::Key_J)
    {
        hitEffect->play();
        if (!upNotes->isEmpty() && getNextNote(upNotes)->getNoteType() == NoteType::SMASH)
        { //rajouter les hits max
            player->setState(CharacterAction::HIT);
            hitSmash();
            getNextNote(upNotes)->hit();
        }
        else if (!downNotes->isEmpty() && getNextNote(downNotes)->getNoteType() == NoteType::SMASH)
        {
            player->setState(CharacterAction::HIT);
            hitSmash();
            getNextNote(downNotes)->hit();
        }
    }
    //If it's not, we have to check what it is and to do something in consequence
    if (event->key() == Qt::Key_F)
    {
        if (!player->getJump())
        {
            player->setState(CharacterAction::JUMP);
            player->setY(UPLINE);
            player->setJump(true);
        }
        if (!upNotes->isEmpty() && getNextNote(upNotes)->getNoteType() != NoteType::SMASH)
            hitNormal(upNotes);
    }
    if (event->key() == Qt::Key_J)
    {
        if (player->getJump())
        {
            player->setState(CharacterAction::JUMP);
            player->setY(DOWNLINE);
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
    if (!Notes->isEmpty())
    {
        if (getNextNote(Notes)->getNoteType() == NoteType::NORMAL)
        {
            if (XLINE - PERFECT <= getNextNote(Notes)->x() && XLINE + PERFECT >= getNextNote(Notes)->x())
            {
                //                //TEST
                //                if(player->getJump())
                //                    upHit->setText("PERFECT");
                //                else
                //                    downHit->setText("PERFECT");
                //                //FIN TEST
                player->increaseScorePerfect();
            }
            else if (XLINE - GREAT <= getNextNote(Notes)->x() && XLINE + GREAT >= getNextNote(Notes)->x())
            {
                //                //TEST
                //                if(player->getJump())
                //                    upHit->setText("GREAT");
                //                else
                //                    downHit->setText("GREAT");
                //                //FIN TEST
                player->increaseScoreGreat();
            }
            else
                return;
            //If the player didn't hit a note, we don't want to errase the first one of the list
            player->setState(CharacterAction::HIT);
            removeNoteHitten(Notes);
            player->increaseCombo();
            if(!player->getFevered())
                player->increaseFever();
            if(player->getFever() >= player->getMaxFever())
                player->setState(CharacterAction::FEVER);
        }
    }
}

void GameView::hitSmash()
{
    player->increaseCombo();
    if(!player->getFevered())
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
    if (!Notes->isEmpty())
    {
        for (int i = 0; i < Notes->count(); i++)
        {
            int x = XLINE + ((Notes->at(i)->getTimestamp() - music->position()) * ((double)(this->width() - XLINE) / (double)3000));
            Notes->at(i)->setX(x);
            if (x <= 0)
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

    combo->setText(QString::asprintf("%d", player->getCombo()));
    score->setText(QString::asprintf("%d", player->getScore()));
    highScore->setText(QString::asprintf("%d", this->_highScore));
    lifeRect->setRect(0, this->height() * 57 / 60, (this->width() / 2) * player->getLife() / player->getMaxLife(), this->height() * 2 / 60);
    feverRect->setRect(this->width() - ((this->width() / 2) * player->getFever() / player->getMaxFever()), this->height() * 57 / 60, (this->width() / 2) * player->getFever() / player->getMaxFever(), this->height() * 2 / 60);
    if(music->duration() > 0)
        durationRect->setRect(0, this->height() * 59 / 60, this->width() * (float)music->position() / (float)music->duration(), this->height() / 60);

    if(player->getFevered())
        player->feverModeDecrease();
    scene->update();
}
