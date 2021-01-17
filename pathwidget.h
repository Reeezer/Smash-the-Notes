#ifndef PATHWIDGET_H
#define PATHWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

class PathWidget : public QWidget
{
    Q_OBJECT
public:
    PathWidget(QWidget *parent = nullptr);
    QLineEdit *mapPathText;
    QPushButton *mapPathButton;
};

#endif // PATHWIDGET_H
