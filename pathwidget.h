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

    QLineEdit *_mapPathText;
    QPushButton *_mapPathButton;
};

#endif // PATHWIDGET_H
