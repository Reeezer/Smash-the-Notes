#include "game.h"

#include <QFontDatabase>

bool loadRessources(Game *game)
{
    /* Fonts */
    QFontDatabase::addApplicationFont(":/font/foo.ttf");
    QFontDatabase::addApplicationFont(":/font/karen.otf");

    game->fonts[FontType::NORMAL_SMALL] = QFont("Foo", 18, QFont::Normal);
    game->fonts[FontType::NORMAL_LARGE] = QFont("Foo", 70, QFont::Normal);
    game->fonts[FontType::ACCURACY] = QFont("karen", 22, QFont::Normal);

    /* Animatables */

    game->player[RUN] = Animatable(":/img/Character/Run/run%d.png", 15, 30);
    game->player[DOWN] = Animatable(":/img/Character/Down/down%d.png", 1, 30);
    game->player[REGENERATE] = Animatable(":/img/Character/Regenerate/regenerate%d.png", 16, 30);
    game->player[FEVER] = Animatable(":/img/Character/Fever/fever%d.png", 13, 30);
    game->player[DAMAGED] = Animatable(":/img/Character/Damage/damage%d.png", 11, 30);
    game->player[HIT] = Animatable(":/img/Character/Hit/hit%d.png", 15, 30);
    game->player[JUMP] = Animatable(":/img/Character/Jump/jump%d.png", 24, 30);

    return true;
}
