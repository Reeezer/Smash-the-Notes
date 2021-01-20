#pragma once

#include "animatable.h"
#include "gameitems/character.h"

#include <QFont>

class QPixmap;
class QString;
class QSoundEffect;

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
    int _delay;
    int _volume;

    QFont _fonts[FONT_ESIZE];
};

bool loadRessources(Game *);
