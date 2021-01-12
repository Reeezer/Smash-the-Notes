#ifndef MAINSETTINGS_H
#define MAINSETTINGS_H

#include <QWidget>
#include <QSpinBox>
#include <QPushButton>
#include <QSlider>
#include <QLineEdit>
#include <QFormLayout>
#include <QObject>

#include "pathwidget.h"
#include "game.h"

class MainSettings : public QWidget
{
public:
    MainSettings(Game *game, QWidget *parent = nullptr);

private:
    Game *game;

    QSpinBox *delaySpinBox;
    QPushButton *inputButton;
    QSlider *volumeSlider;
    PathWidget *pathWidget;

public slots:
    void setNewDelay();
    void displayControlSettings();
    void setNewVolume();
    void validateAndSetNewDirectory();
    void openModalFileExplorer();
};

#endif // MAINSETTINGS_H
