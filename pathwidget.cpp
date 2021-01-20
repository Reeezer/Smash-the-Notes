#include "pathwidget.h"

#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

PathWidget::PathWidget(QWidget *parent) : QWidget(parent)
{
    _mapPathText = new QLineEdit(this);
    _mapPathButton = new QPushButton(tr("Browse"), this);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(_mapPathText, 1);
    layout->addWidget(_mapPathButton);
}
