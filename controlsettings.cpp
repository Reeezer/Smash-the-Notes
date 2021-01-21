#include "controlsettings.h"
#include "keydialog.h"
#include "keybindbutton.h"
#include "fileutils.h"

#include <QDebug>
#include <QKeyEvent>
#include <QFormLayout>

ControlSettings::ControlSettings(GameData *game, QWidget *parent)
    : QWidget(parent), _game(game)
{
    _topNote1 = new KeyBindButton(&game->_topNote1Key, this);
    _topNote2 = new KeyBindButton(&game->_topNote2Key, this);
    _bottomNote1 = new KeyBindButton(&game->_bottomNote1Key, this);
    _bottomNote2 = new KeyBindButton(&game->_bottomNote2Key, this);
    _pauseButton = new KeyBindButton(&game->_pauseButtonKey, this);
    _resetButton = new KeyBindButton(&game->_resetButtonKey, this);
    _returnButton = new QPushButton(QIcon(":/img/Icons/PNG/White/2x/arrowLeft.png"), "", this);

    _returnButton->setIconSize(QSize(40, 40));

    QFormLayout *layout = new QFormLayout();
    layout->addRow(tr("top note 1"), _topNote1);
    layout->addRow(tr("top note 2"), _topNote2);
    layout->addRow(tr("bottom note 1"), _bottomNote1);
    layout->addRow(tr("bottom note 2"), _bottomNote2);
    layout->addRow(tr("pause button"), _pauseButton);
    layout->addRow(tr("reset button"), _resetButton);

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
    connect(_topNote1, &KeyBindButton::clicked, this, &ControlSettings::changeKeyBinding);
    connect(_topNote2, &KeyBindButton::clicked, this, &ControlSettings::changeKeyBinding);
    connect(_bottomNote1, &KeyBindButton::clicked, this, &ControlSettings::changeKeyBinding);
    connect(_bottomNote2, &KeyBindButton::clicked, this, &ControlSettings::changeKeyBinding);
    connect(_pauseButton, &KeyBindButton::clicked, this, &ControlSettings::changeKeyBinding);
    connect(_resetButton, &KeyBindButton::clicked, this, &ControlSettings::changeKeyBinding);
}
void ControlSettings::changeKeyBinding()
{
    KeyBindButton *button = (KeyBindButton *) QObject::sender();
    int key = KeyDialog::getKey();
    qDebug() << "reading key from dialog: " << key;
    button->setKey(key);

    // FIXME corriger le chemin d'accès
    QString path("C:\\Users\\lucadavi.meyer\\Desktop\\songdir\\settings.json");
    writeSettingsFile(path, _game);
}

