#include "gamewindow.h"

#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow w;
    w.show();

    a.setStyleSheet("* { font-family: \"Foo\"; font-size: 32px; }\
                    QWidget { background-color : DarkOliveGreen; }\
                    QPushButton { color: white; background-color: DarkGreen; border-radius: 4px; border: 2px solid black; }\
                    QListWidget { background-color : OliveDrab; }\
                    QPushButton:hover { border: 3px solid lightBlue; }\
                    QPushButton:disabled { background-color: grey; color: lightgrey; }\
                    ");

    return a.exec();
}
