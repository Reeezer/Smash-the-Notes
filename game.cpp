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

    return true;
}
