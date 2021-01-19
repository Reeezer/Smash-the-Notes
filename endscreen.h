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
    void returnToMenu();

private:
    Game *game;
    Character *player;

    QLabel *scoreLabel, *highScoreLabel, *perfectLabel, *greatLabel, *missLabel, *passLabel, *accuracyLabel, *noteLabel;
};

