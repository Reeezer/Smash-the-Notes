#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>

class Display : public QWidget
{
    Q_OBJECT

public:
    Display(QWidget *parent = nullptr);
    ~Display();
};
#endif // DISPLAY_H
