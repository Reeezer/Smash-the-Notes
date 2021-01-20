#include "controlsettings.h"

ControlSettings::ControlSettings(Game *game, QWidget *parent)
    : QWidget(parent), game(game)
{
    topNote1 = new QPushButton("J", this);
    topNote2 = new QPushButton(this);
    bottomNote1 = new QPushButton("F", this);
    bottomNote2 = new QPushButton(this);
    pauseButton = new QPushButton("Esc", this);
    resetButton = new QPushButton("Del", this);
    validationButton = new QPushButton("Enter", this);
    returnButton = new QPushButton(QIcon(":/img/Icons/PNG/White/2x/arrowLeft.png"), "", this);

    returnButton->setIconSize(QSize(40, 40));

    QFormLayout *layout = new QFormLayout();
    layout->addRow(tr("top note 1"), topNote1);
    layout->addRow(tr("top note 2"), topNote2);
    layout->addRow(tr("bottom note 1"), bottomNote1);
    layout->addRow(tr("bottom note 2"), bottomNote2);
    layout->addRow(tr("pause button"), pauseButton);
    layout->addRow(tr("reset button"), resetButton);
    layout->addRow(tr("validation button"), validationButton);

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
    setStyleSheet("ControlSettings { background-image: url(\":/img/Background2.png\"); }");

    connect(returnButton, &QPushButton::clicked, this, &ControlSettings::displayMainSettings);
}
