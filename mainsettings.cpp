#include "mainsettings.h"
#include "fileutils.h"

#include <QSpinBox>
#include <QPushButton>
#include <QSlider>
#include <QLineEdit>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QMediaPlayer>

MainSettings::MainSettings(GameData *game, QMediaPlayer *mediaPlayer, QWidget *parent)
    : QWidget(parent), _game(game), _mediaPlayer(mediaPlayer)
{
    _delaySpinBox = new QSpinBox(this);
    _inputButton = new QPushButton(QIcon(":/img/Icons/PNG/White/2x/plus.png"), "", this);
    _volumeSlider = new QSlider(Qt::Horizontal, this);
    _returnButton = new QPushButton(QIcon(":/img/Icons/PNG/White/2x/arrowLeft.png"), "", this);

    _inputButton->setIconSize(QSize(40, 40));
    _returnButton->setIconSize(QSize(40, 40));

    _volumeSlider->setRange(0, 100);
    _volumeSlider->setValue(_game->_volume);

    _delaySpinBox->setRange(-100, 100);
    _delaySpinBox->setValue(_game->_delay);

    QFormLayout *layout = new QFormLayout();
    layout->addRow(tr("delay"), _delaySpinBox);
    layout->addRow(tr("volume"), _volumeSlider);
    layout->addRow(tr("controls"), _inputButton);

    QHBoxLayout *spacerFormLayout = new QHBoxLayout();
    spacerFormLayout->addStretch(2);
    spacerFormLayout->addLayout(layout, 8);
    spacerFormLayout->addStretch(2);

    QHBoxLayout *spacerButtonLayout = new QHBoxLayout();
    spacerButtonLayout->addWidget(_returnButton, 1);
    spacerButtonLayout->addStretch(9);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(spacerButtonLayout, 1);
    mainLayout->addStretch(1);
    mainLayout->addLayout(spacerFormLayout, 1);
    mainLayout->addStretch(3);
    this->setLayout(mainLayout);

    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet("MainSettings { background-image: url(\":/img/Background2.png\"); }");

    connect(_delaySpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainSettings::updateDelay);
    connect(_inputButton, &QPushButton::clicked, this, &MainSettings::displayControlSettings);
    connect(_volumeSlider, &QSlider::valueChanged, this, &MainSettings::updateVolume);
    connect(_returnButton, &QPushButton::clicked, this, &MainSettings::displayMainMenu);
}

void MainSettings::updateDelay()
{
    _game->_delay = _delaySpinBox->value();
    qDebug() << "setting delay to " << _game->_delay;
    saveSettings();
}

void MainSettings::updateVolume()
{
    _mediaPlayer->setVolume(_volumeSlider->value());
    _game->_volume = _volumeSlider->value(); /* pour pouvoir les enregistrer dans les paramètres */
    qDebug() << "setting volume to " << _game->_volume;
    saveSettings();
}

void MainSettings::saveSettings(void)
{
    // FIXME corriger le chemin d'accès
    QString path("C:\\Users\\lucadavi.meyer\\Desktop\\songdir\\settings.json");
    writeSettingsFile(path, _game);
}
