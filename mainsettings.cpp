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
}
