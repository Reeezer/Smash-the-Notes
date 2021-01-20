#ifndef PATHWIDGET_H
#define PATHWIDGET_H

#include <QWidget>

class QLineEdit;
class QPushButton;

class PathWidget : public QWidget
{
    Q_OBJECT

public:
    PathWidget(QWidget *parent = nullptr);

    QLineEdit *_mapPathText;
    QPushButton *_mapPathButton;
};

#endif // PATHWIDGET_H
