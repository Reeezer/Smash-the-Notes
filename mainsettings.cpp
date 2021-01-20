#include "mainsettings.h"

#include <QSpinBox>
#include <QPushButton>
#include <QSlider>
#include <QLineEdit>
#include <QFormLayout>
#include <QVBoxLayout>

MainSettings::MainSettings(Game *game, QWidget *parent)
    : QWidget(parent), _game(game)
{
    _delaySpinBox = new QSpinBox(this);
    _inputButton = new QPushButton(QIcon(":/img/Icons/PNG/White/2x/plus.png"), "", this);
    _volumeSlider = new QSlider(Qt::Horizontal, this);
    _pathWidget = new PathWidget(this);
    _returnButton = new QPushButton(QIcon(":/img/Icons/PNG/White/2x/arrowLeft.png"), "", this);

    _inputButton->setIconSize(QSize(40, 40));
    _returnButton->setIconSize(QSize(40, 40));

    QFormLayout *layout = new QFormLayout();
    layout->addRow(tr("delay"), _delaySpinBox);
    layout->addRow(tr("controls"), _inputButton);
    layout->addRow(tr("volume"), _volumeSlider);
    layout->addRow(tr("musics directory"), _pathWidget);

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
    connect(_pathWidget->_mapPathText, &QLineEdit::textChanged, this, &MainSettings::validateAndUpdateSongDirectory);
    connect(_pathWidget->_mapPathButton, &QPushButton::clicked, this, &MainSettings::openModalFileExplorer);
    connect(_returnButton, &QPushButton::clicked, this, &MainSettings::displayMainMenu);
}

void MainSettings::updateDelay()
{

}

void MainSettings::updateVolume()
{

}

void MainSettings::validateAndUpdateSongDirectory()
{

}

void MainSettings::openModalFileExplorer()
{

}
