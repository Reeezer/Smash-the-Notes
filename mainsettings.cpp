#include "mainsettings.h"

MainSettings::MainSettings(Game *game, QWidget *parent)
    : QWidget(parent), game(game)
{
    delaySpinBox = new QSpinBox(this);
    inputButton = new QPushButton(QIcon(":/img/Icons/PNG/Black/1x/plus.png"), "", this);
    volumeSlider = new QSlider(Qt::Horizontal, this);
    pathWidget = new PathWidget(this);
    returnButton = new QPushButton(QIcon(":/img/Icons/PNG/Black/1x/arrowLeft.png"), "", this);

    QFormLayout *layout = new QFormLayout();
    layout->addRow(tr("delay"), delaySpinBox);
    layout->addRow(tr("controls"), inputButton);
    layout->addRow(tr("volume"), volumeSlider);
    layout->addRow(tr("musics directory"), pathWidget);

    QHBoxLayout *spacerLayout = new QHBoxLayout();
    spacerLayout->addWidget(returnButton, 1);
    spacerLayout->addStretch(9);

    QVBoxLayout *returnButtonLayout = new QVBoxLayout();
    returnButtonLayout->addLayout(spacerLayout);
    returnButtonLayout->addLayout(layout);
    this->setLayout(returnButtonLayout);

    connect(delaySpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainSettings::setNewDelay);
    connect(inputButton, &QPushButton::clicked, this, &MainSettings::displayControlSettings);
    connect(volumeSlider, &QSlider::valueChanged, this, &MainSettings::setNewVolume);
    connect(pathWidget->mapPathText, &QLineEdit::textChanged, this, &MainSettings::validateAndSetNewDirectory);
    connect(pathWidget->mapPathButton, &QPushButton::clicked, this, &MainSettings::openModalFileExplorer);
    connect(returnButton, &QPushButton::clicked, this, &MainSettings::returnButtonPressed);
}

void MainSettings::setNewDelay()
{

}

void MainSettings::displayControlSettings()
{
    emit controlSettingsCall();
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

void MainSettings::returnButtonPressed()
{
    emit mainMenuCall();
}
