#include "pathwidget.h"

PathWidget::PathWidget(QWidget *parent) : QWidget(parent)
{
    mapPathText = new QLineEdit(this);
    mapPathButton = new QPushButton(tr("Browse"), this);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(mapPathText, 1);
    layout->addWidget(mapPathButton);
}
