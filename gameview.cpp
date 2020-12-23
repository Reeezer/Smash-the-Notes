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
#include <QElapsedTimer>
#include <QRandomGenerator>

GameView::GameView(Game *game, QWidget *parent)
    : QGraphicsView(parent), game(game)
{
    _pause = false;

    //Custom font
    QFontDatabase::addApplicationFont("qrc:/font/foo.ttf");
    QFont Foo("Foo", 18, QFont::Normal);

    QFontDatabase::addApplicationFont("qrc:/font/foo.ttf");
    QFont BigFoo("Foo", 70, QFont::Normal);

    QFontDatabase::addApplicationFont("qrc:/font/karen.otf");
    QFont Karen("karen", 22, QFont::Normal);

    //QGraphicsView & QGraphicsScene
    resize(1000, 600);
    XLINE = this->width() / 5;
    UPLINE = this->height() / 3;
    DOWNLINE = this->height() * 2 / 3;
    this->setBackgroundBrush(Qt::black);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene = new QGraphicsScene();
    setScene(scene);
    scene->setSceneRect(0, 0, this->width(), this->height());

    //Set up the music & sound effect
    music = new QMediaPlayer(this);
    music->setMedia(QUrl("qrc:/music/test.mp3"));

    timer = new QElapsedTimer();

    hitEffect = new QSoundEffect(this);
    hitEffect->setSource(QUrl("qrc:/music/hit-normal.wav"));

    //Background
    _lastElapsed = 0;
    _ratio = 0.0032;
    backgroundDisplay();

    //Display
        //Texts
    QGraphicsSimpleTextItem *comboLabel = new QGraphicsSimpleTextItem("Combo");
    combo = new QGraphicsSimpleTextItem();
    QGraphicsSimpleTextItem *scoreLabel = new QGraphicsSimpleTextItem("Score");
    score = new QGraphicsSimpleTextItem();
    QGraphicsSimpleTextItem *highScoreLabel = new QGraphicsSimpleTextItem("HighScore");
    highScore = new QGraphicsSimpleTextItem();
    upLabel = new QGraphicsSimpleTextItem();
    downLabel = new QGraphicsSimpleTextItem();

    combo->setFont(Foo);
    comboLabel->setFont(Foo);
    score->setFont(Foo);
    scoreLabel->setFont(Foo);
    highScore->setFont(Foo);
    highScoreLabel->setFont(Foo);
    upLabel->setFont(Karen);
    downLabel->setFont(Karen);

    scene->addItem(comboLabel);
    scene->addItem(combo);
    scene->addItem(scoreLabel);
    scene->addItem(score);
    scene->addItem(highScore);
    scene->addItem(highScoreLabel);
    scene->addItem(upLabel);
    scene->addItem(downLabel);

    comboLabel->setPos(this->width() / 2 - 40, this->height() / 60);
    combo->setPos(this->width() / 2 - 40, this->height() * 4 / 60);
    scoreLabel->setPos(this->width() / 5 - 40, this->height() / 60);
    score->setPos(this->width() / 5 - 40, this->height() * 4 / 60);
    highScoreLabel->setPos(this->width() * 4 / 5 - 40, this->height() / 60);
    highScore->setPos(this->width() * 4 / 5 - 40, this->height() * 4 / 60);
    upLabel->setPos(XLINE - 100, UPLINE - 100);
    downLabel->setPos(XLINE - 100, DOWNLINE - 100);

        //Crosshair
    _rotationCrossHair = 1;
    _countCross = 0;
    pixUpCross = scene->addPixmap(QPixmap(":/img/Crosshair/Crosshair1.png").scaled(50,50));
    pixUpCross->setPos(XLINE + 16, UPLINE + 25);
    pixDownCross = scene->addPixmap(QPixmap(":/img/Crosshair/Crosshair1.png").scaled(50,50));
    pixDownCross->setPos(XLINE + 16, DOWNLINE + 25);

        //Rect : life, fever, progress
    scene->addRect(this->width() / 10, this->height() * 57 / 60, this->width() / 2 - this->width() / 10, this->height() * 2 / 60, QPen(Qt::white), QBrush(QColor(46, 64, 83)));
    scene->addRect(this->width() / 2, this->height() * 57 / 60, this->width() / 2 - this->width() / 10, this->height() * 2 / 60, QPen(Qt::white), QBrush(QColor(46, 64, 83)));
    scene->addRect(0, this->height() * 59 / 60, this->width(), this->height() / 60, QPen(Qt::white), QBrush(QColor(46, 64, 83)));
    lifeRect = scene->addRect(this->width() / 10, this->height() * 57 / 60, this->width() / 2, this->height() * 2 / 60, QPen(Qt::white), QBrush(QColor(204, 0, 0)));
    feverRect = scene->addRect(this->width() / 2, this->height() * 57 / 60, this->width() / 2 - this->width() / 10, this->height() * 2 / 60, QPen(Qt::white), QBrush(QColor(68, 201, 228)));
    durationRect = scene->addRect(0, this->height() * 59 / 60, this->width(), this->height() / 60, QPen(Qt::white), QBrush(Qt::white));

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

    //Game Over label & Pause label (at first invisible)
    gameOverLabel = new QGraphicsSimpleTextItem("Game Over");
    gameOverLabel->setFont(BigFoo);
    scene->addItem(gameOverLabel);
    gameOverLabel->setPos(this->width() / 4, this->height() / 3);
    gameOverLabel->setVisible(false);

    pauseLabel = new QGraphicsSimpleTextItem("Pause");
    pauseLabel->setFont(BigFoo);
    scene->addItem(pauseLabel);
    pauseLabel->setPos(this->width() / 3, this->height() / 3);
    pauseLabel->setVisible(false);

    //Start
    player = new Character();
    scene->addItem(player);
    player->setPos(XLINE - 110, DOWNLINE);

    music->play();
    update();
    timer->start();
    this->startTimer(1);
}

void GameView::applyParallax(float ratio, QList<QGraphicsPixmapItem *> *background)
{
    int i = 0;
    for(QGraphicsPixmapItem *layer : *background)
    {
        i++;
        layer->setX(layer->x() - ratio * (layer->boundingRect().width()));
        if(layer->x() <= - this->width() + 1)
            layer->setX(this->width() - 4);
        if(i % 2 == 0 && ratio > 0.0005)
            ratio -= 0.0005;
    }
}

//update of the display
void GameView::timerEvent(QTimerEvent *)
{
    //When the note has not been hitten and it arrives on the player
    checkPass(upNotes, true);
    checkPass(downNotes, false);

    //Update the display
    update();
}

//Check if the player has missed the note but it was close
void GameView::checkPass(QList<Note *> *Notes, bool high)
{
    if (!Notes->isEmpty() && XLINE - NOTPASSED < getNextNote(Notes)->x() && XLINE - PIXMAPHALF > getNextNote(Notes)->x())
    {
        if (player->getJump() == high)
        {
            getNextNote(Notes)->hit();
            if (getNextNote(Notes)->getNoteType() == NoteType::NORMALUP || getNextNote(Notes)->getNoteType() == NoteType::NORMALDOWN || (getNextNote(Notes)->getNoteType() == NoteType::TRAP && getNextNote(Notes)->getHit() == 1)) //We don't remove it, then it must not hit us more than one time)
            {
                player->setState(CharacterAction::DAMAGED);
                if(getNextNote(Notes)->getNoteType() == NoteType::NORMALUP || getNextNote(Notes)->getNoteType() == NoteType::NORMALDOWN)
                    removeNotePassed(Notes);
                player->damage();
                if (player->getLife() <= 0)
                {
                    player->setState(CharacterAction::DOWN);
                    music->pause();
                    gameOverLabel->setVisible(true);
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
        }
        else
        {
            if (getNextNote(Notes)->getNoteType() == NoteType::TRAP)
            {
                changeLabel("PASS", false);
                player->increasePass();
            }
            else
            {
                changeLabel("MISS", false);
                player->increaseMiss();
            }
        }
    }
}

void GameView::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        _pause = !_pause;
        if(!_pause)
        {
            music->play();
            pauseLabel->setVisible(false);
        }
        else
        {
            music->pause();
            pauseLabel->setVisible(true);
        }
    }

    if(player->getLife() > 0 && !_pause)
    {
        //Use the time of the music to know when to hit
        //If it's a SMASH note we can destroy our keyboard
        if (event->key() == Qt::Key_F || event->key() == Qt::Key_J)
        {
            hitEffect->play();
            if (!upNotes->isEmpty() && getNextNote(upNotes)->getNoteType() == NoteType::SMASH && getNextNote(upNotes)->getHit() < getNextNote(upNotes)->getMaxHits())
                hitSmash(upNotes);
            else if (!downNotes->isEmpty() && getNextNote(downNotes)->getNoteType() == NoteType::SMASH && getNextNote(downNotes)->getHit() < getNextNote(downNotes)->getMaxHits())
                hitSmash(downNotes);
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
}

//Check for the different notes what to do with the character
void GameView::hitNormal(QList<Note *> *Notes)
{
    if (!Notes->isEmpty())
    {
        if (getNextNote(Notes)->getNoteType() == NoteType::NORMALUP || getNextNote(Notes)->getNoteType() == NoteType::NORMALDOWN)
        {
            if (XLINE - PERFECT <= getNextNote(Notes)->x() && XLINE + PERFECT >= getNextNote(Notes)->x())
            {
                changeLabel("PERFECT", true);
                player->increaseScorePerfect();
            }
            else if (XLINE - GREAT <= getNextNote(Notes)->x() && XLINE + GREAT >= getNextNote(Notes)->x())
            {
                changeLabel("GREAT", true);
                player->increaseScoreGreat();
            }
            else
                return;
            //If the player didn't hit a note, we don't want to errase the first one of the list
            player->setState(CharacterAction::HIT);
            removeNoteHitten(Notes);
            player->increaseCombo();
            if (!player->getFevered())
                player->increaseFever();
            if (player->getFever() >= player->getMaxFever() && !player->getFevered())
                player->setState(CharacterAction::FEVER);
        }
    }
}

void GameView::hitSmash(QList<Note *> *Notes)
{
    player->setState(CharacterAction::HIT);

    player->increaseCombo();
    if (!player->getFevered())
        player->increaseFever();
    player->increaseScore();

    getNextNote(Notes)->hit();
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
            if (x <= -2 * PIXMAPHALF)
                removeNotePassed(Notes);
        }
    }
}

void GameView::changeLabel(QString string, bool high)
{
    if ((player->getJump() && high) || (!player->getJump() && !high))
    {
        upLabel->setText(string);
        upLabel->setOpacity(1);
    }
    else
    {
        downLabel->setText(string);
        downLabel->setOpacity(1);
    }
}

//If we miss a note but we don't hit it with the body of the character, we want to be able to hit the next note while the note we have missed is still on the screen but gone after the player
Note *GameView::getNextNote(QList<Note *> *Notes)
{
    int i = 0;
    while (Notes->at(i)->x() < XLINE - NOTPASSED && Notes->last() != Notes->at(i))
        i++;
    return Notes->at(i);
}

void GameView::backgroundDisplay()
{
    QGraphicsPixmapItem *pix1 = new QGraphicsPixmapItem();
    QGraphicsPixmapItem *pix2 = new QGraphicsPixmapItem();
    backgroundList = new QList<QGraphicsPixmapItem *>();
    int max = 0;

    quint32 rand = QRandomGenerator::global()->bounded(1, 5);
    switch (rand)
    {
    case 1:
        max = 5;
        break;
    case 2:
        max = 6;
        break;
    case 3:
        max = 7;
        break;
    case 4:
        max  = 7;
        break;
    default:
        qDebug() << "Not in range " << rand;
        break;
    }

    scene->addPixmap(QPixmap(":/img/Background/" + QString::asprintf("%d", rand) + "/Layer" + QString::asprintf("%d", max) + ".png").scaled(QSize(this->width(), this->height())));
    for(int i = max; i > 0; i--)
    {
        pix1 = scene->addPixmap(QPixmap(":/img/Background/" + QString::asprintf("%d", rand) + "/Layer" + QString::asprintf("%d", i) + ".png").scaled(QSize(this->width(), this->height())));
        pix2 = scene->addPixmap(QPixmap(":/img/Background/" + QString::asprintf("%d", rand) + "/Layer" + QString::asprintf("%d", i) + ".png").scaled(QSize(this->width(), this->height())));
        pix2->setPos(this->width(), 0);
        backgroundList->push_front(pix1);
        backgroundList->push_front(pix2);
    }
}

void GameView::rotateCrossHair()
{
    _countCross++;
    if(_countCross >= 15) //15 times 10ms (to be prettier)
    {
        pixUpCross->setPixmap(QPixmap(":/img/Crosshair/Crosshair" + QString::asprintf("%d",_rotationCrossHair) + ".png").scaled(50,50));
        pixDownCross->setPixmap(QPixmap(":/img/Crosshair/Crosshair" + QString::asprintf("%d",_rotationCrossHair) + ".png").scaled(50,50));
        _rotationCrossHair++;
        if(_rotationCrossHair > 3)
            _rotationCrossHair = 1;
        _countCross = 0;
    }
}

//Update the diplay
void GameView::update()
{
    changeNotePosition(upNotes);
    changeNotePosition(downNotes);

    if(timer->elapsed() - _lastElapsed > 10 && timer->elapsed()  - _lastElapsed < 5000 && player->getAlive() && !_pause) //The timer->elapsed() at the first call returns a very big number
    {
        _lastElapsed = timer->elapsed();

        applyParallax(_ratio, backgroundList);
        rotateCrossHair();
    }

    combo->setText(QString::asprintf("%d", player->getCombo()));
    score->setText(QString::asprintf("%d", player->getScore()));
    highScore->setText(QString::asprintf("%d", this->_highScore));

    downLabel->setOpacity(downLabel->opacity() - 0.003);
    upLabel->setOpacity(upLabel->opacity() - 0.003);

    lifeRect->setRect(this->width() / 10, this->height() * 57 / 60, (this->width() / 2 - this->width() / 10) * player->getLife() / player->getMaxLife(), this->height() * 2 / 60);
    feverRect->setRect((this->width() - this->width() / 10) - ((this->width() / 2 - this->width() / 10) * player->getFever() / player->getMaxFever()), this->height() * 57 / 60, (this->width() / 2 - this->width() / 10) * player->getFever() / player->getMaxFever(), this->height() * 2 / 60);
    if (music->duration() > 0)
        durationRect->setRect(0, this->height() * 59 / 60, this->width() * (float)music->position() / (float)music->duration(), this->height() / 60);

    if (player->getFevered())
        player->feverModeDecrease();

    scene->update();
}
