#include "gamewindow.h"

#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow w;
    w.show();
                      //EndScreen { background-color: black; }
    a.setStyleSheet("* { font-family: \"Foo\"; font-size: 32px; }\
                    QWidget { background-color : DarkOliveGreen; }\
                    QPushButton { color: white; background-color: DarkGreen; border-radius: 4px; border: 2px solid black; }\
                    QListWidget { background-color : OliveDrab; }");

    return a.exec();
}
