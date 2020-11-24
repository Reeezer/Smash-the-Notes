#include "gamewindow.h"

GameWindow::GameWindow(QWidget *parent)
    : QStackedWidget(parent)
{
    setWindowTitle("Smash The Notes");
}

GameWindow::~GameWindow()
{
}

