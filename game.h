#ifndef GAME_H
#define GAME_H

#include <QString>
#include <QPixmap>
#include <QSoundEffect>

enum SoundEffectIndex {

};

enum SpriteIndex {

};


class Game
{
public:
    Game();

    bool loadRessources(void);

private:
    int delay;
    int volume;

    QPixmap **sprites;
    QSoundEffect **soundEffects;
};

#endif // GAME_H
