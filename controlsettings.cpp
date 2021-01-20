#include "controlsettings.h"

#include <QPushButton>
#include <QFormLayout>

ControlSettings::ControlSettings(Game *game, QWidget *parent)
    : QWidget(parent), _game(game)
{
    _topNote1 = new QPushButton("J", this);
    _topNote2 = new QPushButton(this);
    _bottomNote1 = new QPushButton("F", this);
    _bottomNote2 = new QPushButton(this);
    _pauseButton = new QPushButton("Esc", this);
    _resetButton = new QPushButton("Del", this);
    _validationButton = new QPushButton("Enter", this);
    _returnButton = new QPushButton(QIcon(":/img/Icons/PNG/White/2x/arrowLeft.png"), "", this);

    _returnButton->setIconSize(QSize(40, 40));

    QFormLayout *layout = new QFormLayout();
    layout->addRow(tr("top note 1"), _topNote1);
    layout->addRow(tr("top note 2"), _topNote2);
    layout->addRow(tr("bottom note 1"), _bottomNote1);
    layout->addRow(tr("bottom note 2"), _bottomNote2);
    layout->addRow(tr("pause button"), _pauseButton);
    layout->addRow(tr("reset button"), _resetButton);
    layout->addRow(tr("validation button"), _validationButton);

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
    setStyleSheet("ControlSettings { background-image: url(\":/img/Background2.png\"); }");

    connect(_returnButton, &QPushButton::clicked, this, &ControlSettings::displayMainSettings);
}
