#ifndef MAINSETTINGS_H
#define MAINSETTINGS_H

#include <QWidget>

class QSpinBox;
class QPushButton;
class QSlider;
class QLineEdit;
class QMediaPlayer;

#include "gamedata.h"

class MainSettings : public QWidget
{
    Q_OBJECT

public:
    MainSettings(GameData *game, QMediaPlayer *, QWidget *parent = nullptr);

public slots:
    void saveSettings(void);

signals:
    void displayMainMenu();
    void displayControlSettings();

protected:
    void validateAndUpdateSongDirectory();
    void openModalFileExplorer();

    void updateDelay();
    void updateVolume();

private:
    GameData *_game;

    QMediaPlayer *_mediaPlayer;

    QSpinBox *_delaySpinBox;
    QPushButton *_inputButton;
    QPushButton *_mapPathButton;
    QSlider *_volumeSlider;
    QPushButton *_returnButton;
};

#endif // MAINSETTINGS_H
