#pragma once

#include <QWidget>
#include <QObject>

class QLabel;

#include "game.h"
#include "gameitems/character.h"

class EndScreen : public QWidget
{
    Q_OBJECT

public:
    EndScreen(Game *game, Character *player, QWidget *parent = nullptr);
    ~EndScreen();
    void initialize();

signals:
    void restartGame();
    void displayMainMenu();

private:
    Game *_game;
    Character *_player;

    QLabel *_scoreLabel;
    QLabel *_highScoreLabel;
    QLabel *_perfectLabel;
    QLabel *_greatLabel;
    QLabel *_missLabel;
    QLabel *_passLabel;
    QLabel *_accuracyLabel;
    QLabel *_noteLabel;
};

