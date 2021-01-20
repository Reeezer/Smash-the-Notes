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

GameView::GameView(GameData *game, Character *player, QWidget *parent)
    : QGraphicsView(parent), _game(game), _player(player)
{
    //QGraphicsView & QGraphicsScene
    resize(1000, 600);
    XLINE = this->width() / 5;
    UPLINE = this->height() / 3;
    DOWNLINE = this->height() * 2 / 3;
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    _scene = new QGraphicsScene();
    setScene(_scene);
    _scene->setSceneRect(0, 0, this->width(), this->height());

    //Set up the music & sound effect
    _music = new QMediaPlayer(this);

    _timer = new QElapsedTimer();

    _hitEffect = new QSoundEffect(this);
    _hitEffect->setSource(QUrl("qrc:/audio/hit-normal.wav"));

    //Background
    _ratio = 0.0032;
    _backgroundFever = _scene->addPixmap(QPixmap(":/img/Background/Fever.png").scaled(QSize(this->width(), this->height())));
    _backgroundList = new QList<QGraphicsPixmapItem *>();

    //Display
    //Texts
    QGraphicsSimpleTextItem *comboLabel = new QGraphicsSimpleTextItem("Combo");
    _combo = new QGraphicsSimpleTextItem();
    QGraphicsSimpleTextItem *scoreLabel = new QGraphicsSimpleTextItem("Score");
    _score = new QGraphicsSimpleTextItem();
    QGraphicsSimpleTextItem *highScoreLabel = new QGraphicsSimpleTextItem("HighScore");
    _highScoreTextItem = new QGraphicsSimpleTextItem();
    _upLabel = new QGraphicsSimpleTextItem();
    _downLabel = new QGraphicsSimpleTextItem();

    _combo->setFont(game->_fonts[FontType::NORMAL_18]);
    comboLabel->setFont(game->_fonts[FontType::NORMAL_18]);
    _score->setFont(game->_fonts[FontType::NORMAL_18]);
    scoreLabel->setFont(game->_fonts[FontType::NORMAL_18]);
    _highScoreTextItem->setFont(game->_fonts[FontType::NORMAL_18]);
    highScoreLabel->setFont(game->_fonts[FontType::NORMAL_18]);
    _upLabel->setFont(game->_fonts[FontType::ACCURACY]);
    _downLabel->setFont(game->_fonts[FontType::ACCURACY]);

    _combo->setZValue(30);
    comboLabel->setZValue(30);
    _score->setZValue(30);
    scoreLabel->setZValue(30);
    _highScoreTextItem->setZValue(30);
    highScoreLabel->setZValue(30);
    _upLabel->setZValue(30);
    _downLabel->setZValue(30);

    _scene->addItem(comboLabel);
    _scene->addItem(_combo);
    _scene->addItem(scoreLabel);
    _scene->addItem(_score);
    _scene->addItem(_highScoreTextItem);
    _scene->addItem(highScoreLabel);
    _scene->addItem(_upLabel);
    _scene->addItem(_downLabel);

    comboLabel->setPos(this->width() / 2 - 40, this->height() / 60);
    _combo->setPos(this->width() / 2 - 40, this->height() * 4 / 60);
    scoreLabel->setPos(this->width() / 5 - 40, this->height() / 60);
    _score->setPos(this->width() / 5 - 40, this->height() * 4 / 60);
    highScoreLabel->setPos(this->width() * 4 / 5 - 40, this->height() / 60);
    _highScoreTextItem->setPos(this->width() * 4 / 5 - 40, this->height() * 4 / 60);
    _upLabel->setPos(XLINE - 100, UPLINE - 100);
    _downLabel->setPos(XLINE - 100, DOWNLINE - 100);

    //Crosshair
    _rotationCrossHair = _countCross = 0;

    _crosshairList = new QList<QPixmap>();
    for(int i = 1; i <= 3; i++)
        _crosshairList->push_back(QPixmap(":/img/Crosshair/Crosshair" + QString::asprintf("%d", i) + ".png").scaled(QSize(50, 50)));

    _pixUpCross = _scene->addPixmap(_crosshairList->first());
    _pixUpCross->setPos(XLINE + 16, UPLINE + 25);
    _pixUpCross->setZValue(250);
    _pixDownCross = _scene->addPixmap(_crosshairList->first());
    _pixDownCross->setPos(XLINE + 16, DOWNLINE + 25);
    _pixDownCross->setZValue(250);

    //CHANGER PAR DES QPROGRESSBAR MAIS VOIR COMMENT MARCHE LES STYLESSHEETS
    //Rect : life, fever, progress
    QGraphicsRectItem *rect1 = _scene->addRect(this->width() / 10, this->height() * 57 / 60, this->width() / 2 - this->width() / 10, this->height() * 2 / 60, QPen(Qt::white), QBrush(QColor(46, 64, 83)));
    QGraphicsRectItem *rect2 = _scene->addRect(this->width() / 2, this->height() * 57 / 60, this->width() / 2 - this->width() / 10, this->height() * 2 / 60, QPen(Qt::white), QBrush(QColor(46, 64, 83)));
    QGraphicsRectItem *rect3 = _scene->addRect(0, this->height() * 59 / 60, this->width(), this->height() / 60, QPen(Qt::white), QBrush(QColor(46, 64, 83)));
    _lifeRect = _scene->addRect(this->width() / 10, this->height() * 57 / 60, this->width() / 2, this->height() * 2 / 60, QPen(Qt::white), QBrush(QColor(204, 0, 0)));
    _feverRect = _scene->addRect(this->width() / 2, this->height() * 57 / 60, this->width() / 2 - this->width() / 10, this->height() * 2 / 60, QPen(Qt::white), QBrush(QColor(68, 201, 228)));
    _durationRect = _scene->addRect(0, this->height() * 59 / 60, this->width(), this->height() / 60, QPen(Qt::white), QBrush(Qt::white));

    rect1->setZValue(200);
    rect2->setZValue(200);
    rect3->setZValue(200);
    _lifeRect->setZValue(200);
    _feverRect->setZValue(200);
    _durationRect->setZValue(200);

    //Set up
    _upNotes = new QList<Note *>();
    _downNotes = new QList<Note *>();

    //Game Over label & Pause label with buttons (at first invisible)
    _gameOverLabel = new QGraphicsSimpleTextItem("Game Over");
    _gameOverLabel->setFont(game->_fonts[NORMAL_70]);
    _gameOverLabel->setZValue(1000);
    _scene->addItem(_gameOverLabel);
    _gameOverLabel->setPos(this->width() / 4, this->height() / 3);

    _pauseLabel = new QGraphicsSimpleTextItem("Pause");
    _pauseLabel->setFont(game->_fonts[NORMAL_70]);
    _pauseLabel->setZValue(1000);
    _scene->addItem(_pauseLabel);
    _pauseLabel->setPos(this->width() / 3, this->height() / 3);

    _restartButton = new QPushButton(QIcon(":/img/Icons/PNG/White/2x/return.png"), "Restart");
    _restartButton->setIconSize(QSize(40, 40));
    _scene->addWidget(_restartButton);

    _restartButton->setGeometry(this->width() / 4 + 80, this->height() / 2 + 30, 100, 50);
    _quitButton = new QPushButton(QIcon(":/img/Icons/PNG/White/2x/home.png"), "Quit");
    _quitButton->setIconSize(QSize(40, 40));
    _scene->addWidget(_quitButton);

    _quitButton->setGeometry(this->width() / 4 + 280, this->height() / 2 + 30, 100, 50);

    //Start
    _scene->addItem(player);
    player->setPos(XLINE - 110, DOWNLINE);

    this->startTimer(1);

    //Connect
    QObject::connect(_restartButton, &QPushButton::clicked, this, &GameView::restartGame);
    QObject::connect(_music, &QMediaPlayer::stateChanged, this, &GameView::musicEnd);
    QObject::connect(_quitButton, &QPushButton::clicked, this, &GameView::displayMainMenu);
}

void GameView::newGame(Song *song)
{
    _currentSong = song;

    //Background
    if(_backgroundList->size() > 0)
    {
        for(QGraphicsPixmapItem *element : *_backgroundList)
            _scene->removeItem(element);
        _scene->removeItem(_backLayer);
        _backgroundList->clear();
    }
    backgroundDisplay();

    restartGame();
}

void GameView::restartGame()
{
    _pause = false;
    _lastBackgroundElapsed = _lastSmashElapsed = _lastJumpElapsed = 0;
    _highScore = 0;

    //Notes
    for (Note *note : *_upNotes)
    {
        Q_UNUSED(note)
        removeFirstNote(_upNotes);
    }
    for (Note *note : *_downNotes)
    {
        Q_UNUSED(note)
        removeFirstNote(_downNotes);
    }

    QString path = _currentSong->getPath();

    loadOsuFile(path, _upNotes, _downNotes);
    for (Note *note : *_upNotes)
    {
        if (note->getNoteType() == NoteType::SMASH)
            note->setY((UPLINE + DOWNLINE) / 2);
        else
            note->setY(UPLINE);
        _scene->addItem(note);
    }
    for (Note *note : *_downNotes)
    {
        if (note->getNoteType() == NoteType::SMASH)
            note->setY((UPLINE + DOWNLINE) / 2);
        else
            note->setY(DOWNLINE);
        _scene->addItem(note);
    }

    qDebug() << "new game with audio file: " + _currentSong->getAudioFilePath();

    _timer->restart();
    _music->stop();
    _music->setMedia(QUrl::fromLocalFile(_currentSong->getAudioFilePath()));
    _music->play();

    //Set up
    _backgroundFever->setVisible(false);
    _gameOverLabel->setVisible(false);
    _pauseLabel->setVisible(false);
    _quitButton->setVisible(false);
    _restartButton->setVisible(false);

    _player->resetCharacter();
    _player->setY(DOWNLINE);
    _player->setZValue(300);

    update();
}

//update of the display
void GameView::timerEvent(QTimerEvent *)
{
    //When the note has not been hitten and it arrives on the player
    checkPass(_upNotes, true);
    checkPass(_downNotes, false);

    //Update the display
    update();
}

//Check if the player has missed the note but it was close the character hitbox meet the note hitbox
void GameView::checkPass(QList<Note *> *Notes, bool high)
{
    if (!Notes->isEmpty() && XLINE - NOTPASSED < getNextNote(Notes)->x() && XLINE - PIXMAPHALF > getNextNote(Notes)->x())
    {
        //If the player is at the same line that the note
        if (_player->getJump() == high)
        {
            getNextNote(Notes)->hit();
            if (getNextNote(Notes)->getNoteType() == NoteType::NORMALUP || getNextNote(Notes)->getNoteType() == NoteType::NORMALDOWN || (getNextNote(Notes)->getNoteType() == NoteType::TRAP && getNextNote(Notes)->getHit() == 1)) //We don't remove it, then it must not hit us more than one time)
            {
                _player->setState(CharacterAction::DAMAGED);
                if (getNextNote(Notes)->getNoteType() == NoteType::NORMALUP || getNextNote(Notes)->getNoteType() == NoteType::NORMALDOWN)
                    removeFirstNote(Notes);
                _player->damage();
                _player->increaseMiss();
                if (_player->getLife() <= 0)
                {
                    _player->setState(CharacterAction::DOWN);
                    _music->pause();
                    _gameOverLabel->setVisible(true);
                    _restartButton->setVisible(true);
                    _quitButton->setVisible(true);
                }
                _player->comboBreak();
            }
            else if (getNextNote(Notes)->getNoteType() == NoteType::BONUS)
            {
                _player->setState(CharacterAction::REGENERATE);
                removeFirstNote(Notes);
                _player->regenerate();
                _player->increaseScore();
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
                _player->comboBreak();
            }
        }
    }
}

void GameView::gamePause()
{
    _pause = !_pause;
    if (!_pause)
    {
        _music->play();
        _pauseLabel->setVisible(false);
        _restartButton->setVisible(false);
        _quitButton->setVisible(false);
    }
    else
    {
        _music->pause();
        _pauseLabel->setVisible(true);
        _restartButton->setVisible(true);
        _quitButton->setVisible(true);
    }
}

void GameView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
        _music->stop();

    //The pause mode
    if (event->key() == Qt::Key_Escape && _player->getAlive())
        gamePause();

    if (_player->getAlive() && !_pause)
    {
        //Use the time of the music to know when to hit
        if (event->key() == Qt::Key_F || event->key() == Qt::Key_J)
        {
            _hitEffect->play();

            //If it's a SMASH note we can smash our keyboard to hit more & quicker
            if ((!_downNotes->isEmpty() && getNextNote(_downNotes)->getNoteType() == NoteType::SMASH) || (!_upNotes->isEmpty() && getNextNote(_upNotes)->getNoteType() == NoteType::SMASH))
            {
                if (!_downNotes->isEmpty() && getNextNote(_downNotes)->getNoteType() == NoteType::SMASH && getNextNote(_downNotes)->x() <= 600)
                    hitSmash(_downNotes);
                if (!_upNotes->isEmpty() && getNextNote(_upNotes)->getNoteType() == NoteType::SMASH && getNextNote(_upNotes)->x() <= 600)
                    hitSmash(_upNotes);
            }
            //If it's not, we have to check which kind of note it is
            else if (event->key() == Qt::Key_F)
            {
                _lastJumpElapsed = _timer->elapsed();
                if (!_player->getJump())
                {
                    _player->setState(CharacterAction::JUMP);
                    _player->setY(UPLINE);
                    _player->setJump(true);
                }
                if (!_upNotes->isEmpty() && getNextNote(_upNotes)->getNoteType() != NoteType::SMASH)
                    hitNormal(_upNotes);
            }
            else if (event->key() == Qt::Key_J)
            {
                if (_player->getJump())
                {
                    _player->setY(DOWNLINE);
                    _player->setJump(false);
                }
                if (!_downNotes->isEmpty() && getNextNote(_downNotes)->getNoteType() != NoteType::SMASH)
                    hitNormal(_downNotes);
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
                _player->increaseScorePerfect();
            }
            else if (XLINE - GREAT <= getNextNote(Notes)->x() && XLINE + GREAT >= getNextNote(Notes)->x())
            {
                changeLabel("GREAT", true);
                _player->increaseScoreGreat();
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
    _player->setY((UPLINE + DOWNLINE) / 2);
    _player->setX(500);
    _lastSmashElapsed = _timer->elapsed();

    hit();

    _player->increaseScore();
    getNextNote(Notes)->hit();

    //If we hit the smash a number of times, we want to erase it.
    if (getNextNote(Notes)->getHit() == NBSMASHHIT)
        removeFirstNote(Notes);
}

void GameView::hit()
{
    _player->setState(CharacterAction::HIT);
    _player->increaseCombo();
    if (!_player->getFevered())
        _player->increaseFever();
    if (_player->getFever() == _player->getMaxFever())
    {
        _backgroundFever->setVisible(true);
        _player->setState(CharacterAction::FEVER);
    }
}

void GameView::removeFirstNote(QList<Note *> *Notes)
{
    _scene->removeItem(Notes->first());
    Note *note = Notes->takeFirst();
    delete note;
}

void GameView::removeNoteHitten(QList<Note *> *Notes)
{
    _scene->removeItem(getNextNote(Notes));
    Note *note = getNextNote(Notes);
    Notes->removeOne(note);
    delete note;
}

//Change the note position
void GameView::changeNotePosition(QList<Note *> *Notes)
{
    if (!Notes->isEmpty())
    {
        if(Notes->first()->getNoteType() == NoteType::SMASH && Notes->first()->getTimeOut() < _music->position())
            removeFirstNote(Notes);

        for (int i = 0; i < Notes->count(); i++)
        {
            int x = XLINE + ((Notes->at(i)->getTimeStamp() - _music->position()) * ((double)(this->width() - XLINE) / (double)3000));
            if ((Notes->at(i)->getNoteType() != NoteType::SMASH) || (Notes->at(i)->getNoteType() == NoteType::SMASH && (Notes->at(i)->x() >= 600 || Notes->at(i)->x() <= 10)))
                Notes->at(i)->setX(x);
            if (Notes->at(i)->x() <= 0)
            {
                if(Notes->first()->getNoteType() == NoteType::TRAP)
                    _player->increasePass();
                else if(Notes->first()->getNoteType() != NoteType::TRAP && Notes->first()->getNoteType() != NoteType::BONUS)
                    _player->increaseMiss();
                removeFirstNote(Notes);
            }
        }
    }
}

//Change the text PERFECT, GREAT, MISS, PASS
void GameView::changeLabel(QString string, bool high)
{
    if ((_player->getJump() && high) || (!_player->getJump() && !high))
    {
        _upLabel->setText(string);
        _upLabel->setOpacity(1);
    }
    else
    {
        _downLabel->setText(string);
        _downLabel->setOpacity(1);
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
    _backLayer = _scene->addPixmap(QPixmap(":/img/Background/" + QString::asprintf("%d", rand) + "/Layer" + QString::asprintf("%d", max) + ".png").scaled(QSize(this->width(), this->height())));
    _backLayer->setZValue(-1000);
    for (int i = max - 1; i > 0; i--)
    {
        pix1 = _scene->addPixmap(QPixmap(":/img/Background/" + QString::asprintf("%d", rand) + "/Layer" + QString::asprintf("%d", i) + ".png").scaled(QSize(this->width(), this->height())));
        pix2 = _scene->addPixmap(QPixmap(":/img/Background/" + QString::asprintf("%d", rand) + "/Layer" + QString::asprintf("%d", i) + ".png").scaled(QSize(this->width(), this->height())));
        pix2->setPos(this->width(), 0);
        _backgroundList->push_front(pix1);
        _backgroundList->push_front(pix2);
    }

    for(int i = 0; i < _backgroundList->size(); i++)
        _backgroundList->at(i)->setZValue(-10 * (i + 1));
}

//Crosshair animation
void GameView::rotateCrossHair()
{
    _countCross++;
    if (_countCross >= 15) //15 times 10ms (to be prettier & smoother)
    {
        _pixUpCross->setPixmap(_crosshairList->at(_rotationCrossHair));
        _pixDownCross->setPixmap(_crosshairList->at(_rotationCrossHair));
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
    if(_music->state() == QMediaPlayer::StoppedState && _timer->elapsed() > 100) {//When we restart the game, we stop the music and we don't want to see the end screen at this moment
        Rank rank;

        if(_player->getAccuracy() > 99)      rank = Rank::SSS;
        else if(_player->getAccuracy() > 95) rank = Rank::SS;
        else if(_player->getAccuracy() > 90) rank = Rank::S;
        else if(_player->getAccuracy() > 80) rank = Rank::A;
        else if(_player->getAccuracy() > 70) rank = Rank::B;
        else if(_player->getAccuracy() > 50) rank = Rank::C;
        else                                rank = Rank::D;

        _currentSong->addHighscore(rank, _player->getScore());

        emit displayEndScreen();
    }
}

//Update the display
void GameView::update()
{  
    if (!_pause)
    {
        //Update of note position
        changeNotePosition(_upNotes);
        changeNotePosition(_downNotes);

        if ((_timer->elapsed() - _lastSmashElapsed > 150 || _timer->elapsed() - _lastSmashElapsed < 0) && _player->getAlive())
        {
            _lastSmashElapsed = _timer->elapsed();

            if (_player->x() >= 500)
            {
                _player->setX(100);
                _player->setY(DOWNLINE);
            }
        }

        //Background animation & Crosshair animation
        if ((_timer->elapsed() - _lastBackgroundElapsed > 10 || _timer->elapsed() - _lastBackgroundElapsed < 0) && _player->getAlive()) //The timer->elapsed() at the first call returns a very big number
        {
            _lastBackgroundElapsed = _timer->elapsed();

            applyParallax(_ratio, _backgroundList);
            rotateCrossHair();
        }

        //The character returns down after he jumped
        if ((_timer->elapsed() - _lastJumpElapsed > 700 || _timer->elapsed() - _lastJumpElapsed < 0) && _player->getAlive())
        {
            _lastJumpElapsed = _timer->elapsed();

            if ((!_downNotes->isEmpty() && getNextNote(_downNotes)->getNoteType() != NoteType::SMASH) && (!_upNotes->isEmpty() && getNextNote(_upNotes)->getNoteType() != NoteType::SMASH))
            {
                _player->setJump(false);
                _player->setY(DOWNLINE);
            }
        }

        //Labels actualisation
        if (_player->getScore() > _highScore)
            _highScore = _player->getScore();
        _combo->setText(QString::asprintf("%d", _player->getCombo()));
        _score->setText(QString::asprintf("%d", _player->getScore()));
        _highScoreTextItem->setText(QString::asprintf("%d", _highScore));

        //GREAT, PERFECT, MISS, PASS texts animation
        if (_downLabel->opacity() > 0)
            _downLabel->setOpacity(_downLabel->opacity() - 0.003);
        if (_upLabel->opacity() > 0)
            _upLabel->setOpacity(_upLabel->opacity() - 0.003);

        //Rectangle of life, fever, and progression animation
        _lifeRect->setRect(this->width() / 10, this->height() * 57 / 60, (this->width() / 2 - this->width() / 10) * _player->getLife() / _player->getMaxLife(), this->height() * 2 / 60);
        _feverRect->setRect((this->width() - this->width() / 10) - ((this->width() / 2 - this->width() / 10) * _player->getFever() / _player->getMaxFever()), this->height() * 57 / 60, (this->width() / 2 - this->width() / 10) * _player->getFever() / _player->getMaxFever(), this->height() * 2 / 60);
        if (_music->duration() > 0)
            _durationRect->setRect(0, this->height() * 59 / 60, this->width() * (float)_music->position() / (float)_music->duration(), this->height() / 60);

        //Mode fever
        if (_player->getFevered())
            _player->feverModeDecrease();
        if (!_player->getFever() && _backgroundFever->isVisible())
            _backgroundFever->setVisible(false);

        _scene->update();
    }
}

Song * GameView::getCurrentSong()
{
    return _currentSong;
}
