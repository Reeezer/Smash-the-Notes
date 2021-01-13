#pragma once

#include "animatable.h"
#include "GameItems/character.h"

#include <QFont>

class QPixmap;
class QString;
class QSoundEffect;

enum SoundEffectIndex {

};

enum SpriteIndex {

};

enum FontType {
    NORMAL_18,
    NORMAL_70,
    NORMAL_40,
    NORMAL_50,
    ACCURACY,
    FONT_ESIZE
};

struct Game
{
    int delay;
    int volume;

    QFont fonts[FONT_ESIZE];
};

bool loadRessources(Game *);
