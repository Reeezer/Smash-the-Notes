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
#include <QElapsedTimer>
#include <QRandomGenerator>
#include <QPushButton>

GameView::GameView(Game *game, Character *player, QWidget *parent)
    : QGraphicsView(parent), game(game), player(player)
{
    //QGraphicsView & QGraphicsScene
    resize(1000, 600);
    XLINE = this->width() / 5;
    UPLINE = this->height() / 3;
    DOWNLINE = this->height() * 2 / 3;
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene = new QGraphicsScene();
    setScene(scene);
    scene->setSceneRect(0, 0, this->width(), this->height());

    //Set up the music & sound effect
    music = new QMediaPlayer(this);

    timer = new QElapsedTimer();

    hitEffect = new QSoundEffect(this);
    hitEffect->setSource(QUrl("qrc:/audio/hit-normal.wav"));

    //Background
    _ratio = 0.0032;
    backgroundFever = scene->addPixmap(QPixmap(":/img/Background/Fever.png").scaled(QSize(this->width(), this->height())));
    backgroundList = new QList<QGraphicsPixmapItem *>();

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

    combo->setFont(game->fonts[FontType::NORMAL_18]);
    comboLabel->setFont(game->fonts[FontType::NORMAL_18]);
    score->setFont(game->fonts[FontType::NORMAL_18]);
    scoreLabel->setFont(game->fonts[FontType::NORMAL_18]);
    highScore->setFont(game->fonts[FontType::NORMAL_18]);
    highScoreLabel->setFont(game->fonts[FontType::NORMAL_18]);
    upLabel->setFont(game->fonts[FontType::ACCURACY]);
    downLabel->setFont(game->fonts[FontType::ACCURACY]);

    combo->setZValue(30);
    comboLabel->setZValue(30);
    score->setZValue(30);
    scoreLabel->setZValue(30);
    highScore->setZValue(30);
    highScoreLabel->setZValue(30);
    upLabel->setZValue(30);
    downLabel->setZValue(30);

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
    _rotationCrossHair = _countCross = 0;

    crosshairList = new QList<QPixmap>();
    for(int i = 1; i <= 3; i++)
        crosshairList->push_back(QPixmap(":/img/Crosshair/Crosshair" + QString::asprintf("%d", i) + ".png").scaled(QSize(50, 50)));

    pixUpCross = scene->addPixmap(crosshairList->first());
    pixUpCross->setPos(XLINE + 16, UPLINE + 25);
    pixUpCross->setZValue(250);
    pixDownCross = scene->addPixmap(crosshairList->first());
    pixDownCross->setPos(XLINE + 16, DOWNLINE + 25);
    pixDownCross->setZValue(250);

    //CHANGER PAR DES QPROGRESSBAR MAIS VOIR COMMENT MARCHE LES STYLESSHEETS
    //Rect : life, fever, progress
    QGraphicsRectItem *rect1 = scene->addRect(this->width() / 10, this->height() * 57 / 60, this->width() / 2 - this->width() / 10, this->height() * 2 / 60, QPen(Qt::white), QBrush(QColor(46, 64, 83)));
    QGraphicsRectItem *rect2 = scene->addRect(this->width() / 2, this->height() * 57 / 60, this->width() / 2 - this->width() / 10, this->height() * 2 / 60, QPen(Qt::white), QBrush(QColor(46, 64, 83)));
    QGraphicsRectItem *rect3 = scene->addRect(0, this->height() * 59 / 60, this->width(), this->height() / 60, QPen(Qt::white), QBrush(QColor(46, 64, 83)));
    lifeRect = scene->addRect(this->width() / 10, this->height() * 57 / 60, this->width() / 2, this->height() * 2 / 60, QPen(Qt::white), QBrush(QColor(204, 0, 0)));
    feverRect = scene->addRect(this->width() / 2, this->height() * 57 / 60, this->width() / 2 - this->width() / 10, this->height() * 2 / 60, QPen(Qt::white), QBrush(QColor(68, 201, 228)));
    durationRect = scene->addRect(0, this->height() * 59 / 60, this->width(), this->height() / 60, QPen(Qt::white), QBrush(Qt::white));

    rect1->setZValue(200);
    rect2->setZValue(200);
    rect3->setZValue(200);
    lifeRect->setZValue(200);
    feverRect->setZValue(200);
    durationRect->setZValue(200);

    //Set up
    upNotes = new QList<Note *>();
    downNotes = new QList<Note *>();

    //Game Over label & Pause label with buttons (at first invisible)
    gameOverLabel = new QGraphicsSimpleTextItem("Game Over");
    gameOverLabel->setFont(game->fonts[NORMAL_70]);
    gameOverLabel->setZValue(1000);
    scene->addItem(gameOverLabel);
    gameOverLabel->setPos(this->width() / 4, this->height() / 3);

    pauseLabel = new QGraphicsSimpleTextItem("Pause");
    pauseLabel->setFont(game->fonts[NORMAL_70]);
    pauseLabel->setZValue(1000);
    scene->addItem(pauseLabel);
    pauseLabel->setPos(this->width() / 3, this->height() / 3);

    restartButton = new QPushButton("Restart");
    scene->addWidget(restartButton);

    restartButton->setGeometry(this->width() / 4 + 80, this->height() / 2 + 30, 100, 50);
    quitButton = new QPushButton("Quit");
    scene->addWidget(quitButton);

    quitButton->setGeometry(this->width() / 4 + 280, this->height() / 2 + 30, 100, 50);

    //Start
    scene->addItem(player);
    player->setPos(XLINE - 110, DOWNLINE);

    this->startTimer(1);

    //Connect
    QObject::connect(restartButton, &QPushButton::clicked, this, &GameView::initialize);
    QObject::connect(music, &QMediaPlayer::stateChanged, this, &GameView::musicEnd);
}

void GameView::newGame(Song *song)
{
    _currentSong = song;

    //Background
    if(backgroundList->size() > 0)
    {
        for(QGraphicsPixmapItem *element : *backgroundList)
            scene->removeItem(element);
        scene->removeItem(backLayer);
        backgroundList->clear();
    }
    backgroundDisplay();

    initialize();

    //Notes
    for (Note *note : *upNotes)
        removeFirstNote(upNotes);
    for (Note *note : *downNotes)
        removeFirstNote(downNotes);

    QString path = _currentSong->getPath();

    loadOsuFile(path, upNotes, downNotes);
    for (Note *note : *upNotes)
    {
        if (note->getNoteType() == NoteType::SMASH)
            note->setY((UPLINE + DOWNLINE) / 2);
        else
            note->setY(UPLINE);
        scene->addItem(note);
    }
    for (Note *note : *downNotes)
    {
        if (note->getNoteType() == NoteType::SMASH)
            note->setY((UPLINE + DOWNLINE) / 2);
        else
            note->setY(DOWNLINE);
        scene->addItem(note);
    }

    qDebug() << "new game with audio file: " + _currentSong->getAudioFilePath();

    timer->restart();
    music->stop();
    music->setMedia(QUrl::fromLocalFile(_currentSong->getAudioFilePath()));
    music->play();
}

void GameView::initialize()
{
    _pause = false;
    _lastBackgroundElapsed = _lastSmashElapsed = _lastJumpElapsed = 0;

    //Set up
    backgroundFever->setVisible(false);
    gameOverLabel->setVisible(false);
    pauseLabel->setVisible(false);
    quitButton->setVisible(false);
    restartButton->setVisible(false);

    player->initialize();
    player->setY(DOWNLINE);
    player->setZValue(300);

    update();
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

//Check if the player has missed the note but it was close the character hitbox meet the note hitbox
void GameView::checkPass(QList<Note *> *Notes, bool high)
{
    if (!Notes->isEmpty() && XLINE - NOTPASSED < getNextNote(Notes)->x() && XLINE - PIXMAPHALF > getNextNote(Notes)->x())
    {
        //If the player is at the same line that the note
        if (player->getJump() == high)
        {
            getNextNote(Notes)->hit();
            if (getNextNote(Notes)->getNoteType() == NoteType::NORMALUP || getNextNote(Notes)->getNoteType() == NoteType::NORMALDOWN || (getNextNote(Notes)->getNoteType() == NoteType::TRAP && getNextNote(Notes)->getHit() == 1)) //We don't remove it, then it must not hit us more than one time)
            {
                player->setState(CharacterAction::DAMAGED);
                if (getNextNote(Notes)->getNoteType() == NoteType::NORMALUP || getNextNote(Notes)->getNoteType() == NoteType::NORMALDOWN)
                    removeFirstNote(Notes);
                player->damage();
                player->increaseMiss();
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
                removeFirstNote(Notes);
                player->regenerate();
                player->increaseScore();
            }
        }
        //If he is not
        else
        {
            if (getNextNote(Notes)->getNoteType() == NoteType::TRAP)
                changeLabel("PASS", false);
            else
            {
                changeLabel("MISS", false);
                player->comboBreak();
            }
        }
    }
}

void GameView::gamePause()
{
    _pause = !_pause;
    if (!_pause)
    {
        music->play();
        pauseLabel->setVisible(false);
        restartButton->setVisible(false);
        quitButton->setVisible(false);
    }
    else
    {
        music->pause();
        pauseLabel->setVisible(true);
        restartButton->setVisible(true);
        quitButton->setVisible(true);
    }
}

void GameView::keyPressEvent(QKeyEvent *event)
{
    //The pause mode
    if (event->key() == Qt::Key_Escape && player->getAlive())
        gamePause();

    if (player->getAlive() && !_pause)
    {
        //Use the time of the music to know when to hit
        if (event->key() == Qt::Key_F || event->key() == Qt::Key_J)
        {
            hitEffect->play();

            //If it's a SMASH note we can smash our keyboard to hit more & quicker
            if ((!downNotes->isEmpty() && getNextNote(downNotes)->getNoteType() == NoteType::SMASH) || (!upNotes->isEmpty() && getNextNote(upNotes)->getNoteType() == NoteType::SMASH))
            {
                if (!downNotes->isEmpty() && getNextNote(downNotes)->getNoteType() == NoteType::SMASH)
                    hitSmash(downNotes);
                if (!upNotes->isEmpty() && getNextNote(upNotes)->getNoteType() == NoteType::SMASH)
                    hitSmash(upNotes);
            }
            //If it's not, we have to check which kind of note it is
            else if (event->key() == Qt::Key_F)
            {
                _lastJumpElapsed = timer->elapsed();
                if (!player->getJump())
                {
                    player->setState(CharacterAction::JUMP);
                    player->setY(UPLINE);
                    player->setJump(true);
                }
                if (!upNotes->isEmpty() && getNextNote(upNotes)->getNoteType() != NoteType::SMASH)
                    hitNormal(upNotes);
            }
            else if (event->key() == Qt::Key_J)
            {
                if (player->getJump())
                {
                    player->setY(DOWNLINE);
                    player->setJump(false);
                }
                if (!downNotes->isEmpty() && getNextNote(downNotes)->getNoteType() != NoteType::SMASH)
                    hitNormal(downNotes);
            }
        }
        update();
    }
}

//Check for every notes what to do with
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
            //If the player missed a note, we don't want to errase the first one of the list but the one we can hit
            removeNoteHitten(Notes);
            hit();
        }
    }
}

void GameView::hitSmash(QList<Note *> *Notes)
{
    player->setY((UPLINE + DOWNLINE) / 2);
    player->setX(500);
    _lastSmashElapsed = timer->elapsed();

    hit();

    player->increaseScore();
    getNextNote(Notes)->hit();

    //If we hit the smash a number of times, we wan't to erase it.
    if (getNextNote(Notes)->getHit() == NBSMASHHIT)
        removeFirstNote(Notes);
}

void GameView::hit()
{
    player->setState(CharacterAction::HIT);
    player->increaseCombo();
    if (!player->getFevered())
        player->increaseFever();
    if (player->getFever() == player->getMaxFever())
    {
        backgroundFever->setVisible(true);
        player->setState(CharacterAction::FEVER);
    }
}

void GameView::removeFirstNote(QList<Note *> *Notes)
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

//Change the note position
void GameView::changeNotePosition(QList<Note *> *Notes)
{
    if (!Notes->isEmpty())
    {
        if(Notes->first()->getNoteType() == NoteType::SMASH && Notes->first()->getTimeOut() < music->position())
            removeFirstNote(Notes);

        for (int i = 0; i < Notes->count(); i++)
        {
            int x = XLINE + ((Notes->at(i)->getTimeStamp() - music->position()) * ((double)(this->width() - XLINE) / (double)3000));
            if ((Notes->at(i)->getNoteType() != NoteType::SMASH) || (Notes->at(i)->getNoteType() == NoteType::SMASH && (Notes->at(i)->x() >= 600 || Notes->at(i)->x() <= 10)))
                Notes->at(i)->setX(x);
            if (Notes->at(i)->x() <= 0)
            {
                if(Notes->first()->getNoteType() == NoteType::TRAP)
                    player->increasePass();
                else if(Notes->first()->getNoteType() != NoteType::TRAP && Notes->first()->getNoteType() != NoteType::BONUS)
                    player->increaseMiss();
                removeFirstNote(Notes);
            }
        }
    }
}

//Change the text PERFECT, GREAT, MISS, PASS
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

//Add all the layer in the QList to be able to apply parallax after
void GameView::backgroundDisplay()
{
    QGraphicsPixmapItem *pix1 = new QGraphicsPixmapItem();
    QGraphicsPixmapItem *pix2 = new QGraphicsPixmapItem();
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
        max = 7;
        break;
    default:
        qDebug() << "Not in range " << rand;
        break;
    }

    //The last layer (the sky) does not move, then we don't add it in the List
    backLayer = scene->addPixmap(QPixmap(":/img/Background/" + QString::asprintf("%d", rand) + "/Layer" + QString::asprintf("%d", max) + ".png").scaled(QSize(this->width(), this->height())));
    backLayer->setZValue(-1000);
    for (int i = max - 1; i > 0; i--)
    {
        pix1 = scene->addPixmap(QPixmap(":/img/Background/" + QString::asprintf("%d", rand) + "/Layer" + QString::asprintf("%d", i) + ".png").scaled(QSize(this->width(), this->height())));
        pix2 = scene->addPixmap(QPixmap(":/img/Background/" + QString::asprintf("%d", rand) + "/Layer" + QString::asprintf("%d", i) + ".png").scaled(QSize(this->width(), this->height())));
        pix2->setPos(this->width(), 0);
        backgroundList->push_front(pix1);
        backgroundList->push_front(pix2);
    }

    for(int i = 0; i < backgroundList->size(); i++)
        backgroundList->at(i)->setZValue(-10 * (i + 1));
}

//Crosshair animation
void GameView::rotateCrossHair()
{
    _countCross++;
    if (_countCross >= 15) //15 times 10ms (to be prettier & smoother)
    {
        pixUpCross->setPixmap(crosshairList->at(_rotationCrossHair));
        pixDownCross->setPixmap(crosshairList->at(_rotationCrossHair));
        _rotationCrossHair++;
        if (_rotationCrossHair >= 3)
            _rotationCrossHair = 0;
        _countCross = 0;
    }
}

//Background parallax animation
void GameView::applyParallax(float ratio, QList<QGraphicsPixmapItem *> *background)
{
    int i = 0;
    for (QGraphicsPixmapItem *layer : *background)
    {
        i++;
        layer->setX(layer->x() - ratio * (layer->boundingRect().width()));
        if (layer->x() <= -this->width() + 1)
            layer->setX(this->width() - 4);
        if (i % 2 == 0 && ratio > 0.0005) //The same layer is twice in the list, then the ratio as to be decreased on every new layer
            ratio -= 0.0005;
    }
}

void GameView::musicEnd()
{
    if(music->state() == QMediaPlayer::StoppedState && timer->elapsed() > 100) //When we restart the game, we stop the music and we don't want to see the end screen at this moment
        emit gameFinished();
}

//Update the display
void GameView::update()
{  
    if (!_pause)
    {
        //Update of note position
        changeNotePosition(upNotes);
        changeNotePosition(downNotes);

        if ((timer->elapsed() - _lastSmashElapsed > 150 || timer->elapsed() - _lastSmashElapsed < 0) && player->getAlive())
        {
            _lastSmashElapsed = timer->elapsed();

            if (player->x() >= 500)
            {
                player->setX(100);
                player->setY(DOWNLINE);
            }
        }

        //Background animation & Crosshair animation
        if ((timer->elapsed() - _lastBackgroundElapsed > 10 || timer->elapsed() - _lastBackgroundElapsed < 0) && player->getAlive()) //The timer->elapsed() at the first call returns a very big number
        {
            _lastBackgroundElapsed = timer->elapsed();

            applyParallax(_ratio, backgroundList);
            rotateCrossHair();
        }

        //The character returns down after he jumped
        if ((timer->elapsed() - _lastJumpElapsed > 700 || timer->elapsed() - _lastJumpElapsed < 0) && player->getAlive())
        {
            _lastJumpElapsed = timer->elapsed();

            if ((!downNotes->isEmpty() && getNextNote(downNotes)->getNoteType() != NoteType::SMASH) && (!upNotes->isEmpty() && getNextNote(upNotes)->getNoteType() != NoteType::SMASH))
            {
                player->setJump(false);
                player->setY(DOWNLINE);
            }
        }

        //Labels actualisation
        if (player->getScore() > _highScore)
            _highScore = player->getScore();
        combo->setText(QString::asprintf("%d", player->getCombo()));
        score->setText(QString::asprintf("%d", player->getScore()));
        highScore->setText(QString::asprintf("%d", this->_highScore));

        //GREAT, PERFECT, MISS, PASS texts animation
        if (downLabel->opacity() > 0)
            downLabel->setOpacity(downLabel->opacity() - 0.003);
        if (upLabel->opacity() > 0)
            upLabel->setOpacity(upLabel->opacity() - 0.003);

        //Rectangle of life, fever, and progression animation
        lifeRect->setRect(this->width() / 10, this->height() * 57 / 60, (this->width() / 2 - this->width() / 10) * player->getLife() / player->getMaxLife(), this->height() * 2 / 60);
        feverRect->setRect((this->width() - this->width() / 10) - ((this->width() / 2 - this->width() / 10) * player->getFever() / player->getMaxFever()), this->height() * 57 / 60, (this->width() / 2 - this->width() / 10) * player->getFever() / player->getMaxFever(), this->height() * 2 / 60);
        if (music->duration() > 0)
            durationRect->setRect(0, this->height() * 59 / 60, this->width() * (float)music->position() / (float)music->duration(), this->height() / 60);

        //Mode fever
        if (player->getFevered())
            player->feverModeDecrease();
        if (!player->getFever() && backgroundFever->isVisible())
            backgroundFever->setVisible(false);

        scene->update();
    }
}
