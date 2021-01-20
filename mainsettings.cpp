#include "mainsettings.h"

MainSettings::MainSettings(Game *game, QWidget *parent)
    : QWidget(parent), game(game)
{
    delaySpinBox = new QSpinBox(this);
    inputButton = new QPushButton(QIcon(":/img/Icons/PNG/White/2x/plus.png"), "", this);
    volumeSlider = new QSlider(Qt::Horizontal, this);
    pathWidget = new PathWidget(this);
    returnButton = new QPushButton(QIcon(":/img/Icons/PNG/White/2x/arrowLeft.png"), "", this);

    inputButton->setIconSize(QSize(40, 40));
    returnButton->setIconSize(QSize(40, 40));

    QFormLayout *layout = new QFormLayout();
    layout->addRow(tr("delay"), delaySpinBox);
    layout->addRow(tr("controls"), inputButton);
    layout->addRow(tr("volume"), volumeSlider);
    layout->addRow(tr("musics directory"), pathWidget);

    QHBoxLayout *spacerFormLayout = new QHBoxLayout();
    spacerFormLayout->addStretch(2);
    spacerFormLayout->addLayout(layout, 8);
    spacerFormLayout->addStretch(2);

    QHBoxLayout *spacerButtonLayout = new QHBoxLayout();
    spacerButtonLayout->addWidget(returnButton, 1);
    spacerButtonLayout->addStretch(9);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(spacerButtonLayout, 1);
    mainLayout->addStretch(1);
    mainLayout->addLayout(spacerFormLayout, 1);
    mainLayout->addStretch(3);
    this->setLayout(mainLayout);

    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet("MainSettings { background-image: url(\":/img/Background2.png\"); }");

    connect(delaySpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainSettings::setNewDelay);
    connect(inputButton, &QPushButton::clicked, this, &MainSettings::displayControlSettings);
    connect(volumeSlider, &QSlider::valueChanged, this, &MainSettings::setNewVolume);
    connect(pathWidget->mapPathText, &QLineEdit::textChanged, this, &MainSettings::validateAndSetNewDirectory);
    connect(pathWidget->mapPathButton, &QPushButton::clicked, this, &MainSettings::openModalFileExplorer);
    connect(returnButton, &QPushButton::clicked, this, &MainSettings::displayMainMenu);
}

void MainSettings::setNewDelay()
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
