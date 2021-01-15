#include "mainsettings.h"

MainSettings::MainSettings(Game *game, QWidget *parent)
    : QWidget(parent), game(game)
{
    delaySpinBox = new QSpinBox(this);
    inputButton = new QPushButton(this);
    volumeSlider = new QSlider(Qt::Horizontal, this);
    pathWidget = new PathWidget(this);

    QFormLayout *layout = new QFormLayout(this);
    layout->addRow(tr("delay"), delaySpinBox);
    layout->addRow(tr("controls"), inputButton);
    layout->addRow(tr("volume"), volumeSlider);
    layout->addRow(tr("musics directory"), pathWidget);

    connect(delaySpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainSettings::setNewDelay);
    connect(inputButton, &QPushButton::clicked, this, &MainSettings::displayControlSettings);
    connect(volumeSlider, &QSlider::valueChanged, this, &MainSettings::setNewVolume);
    connect(pathWidget->mapPathText, &QLineEdit::textChanged, this, &MainSettings::validateAndSetNewDirectory);
    connect(pathWidget->mapPathButton, &QPushButton::clicked, this, &MainSettings::openModalFileExplorer);
}

void MainSettings::setNewDelay()
{

}

void MainSettings::displayControlSettings()
{

}

void MainSettings::setNewVolume()
{

}

void MainSettings::validateAndSetNewDirectory()
{

}

void MainSettings::openModalFileExplorer()
{

}
