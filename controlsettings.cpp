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
    returnButton = new QPushButton(this);

    QFormLayout *layout = new QFormLayout();
    layout->addRow(tr("top note 1"), topNote1);
    layout->addRow(tr("top note 2"), topNote2);
    layout->addRow(tr("bottom note 1"), bottomNote1);
    layout->addRow(tr("bottom note 2"), bottomNote2);
    layout->addRow(tr("pause button"), pauseButton);
    layout->addRow(tr("reset button"), resetButton);
    layout->addRow(tr("validation button"), validationButton);

    QHBoxLayout *spacerLayout = new QHBoxLayout();
    spacerLayout->addWidget(returnButton, 1);
    spacerLayout->addStretch(9);

    QVBoxLayout *returnButtonLayout = new QVBoxLayout();
    returnButtonLayout->addLayout(spacerLayout);
    returnButtonLayout->addLayout(layout);
    this->setLayout(returnButtonLayout);

    connect(returnButton, &QPushButton::clicked, this, &ControlSettings::displayMainSettings);
}
