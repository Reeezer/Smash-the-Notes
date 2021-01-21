#ifndef KEYBINDBUTTON_H
#define KEYBINDBUTTON_H

#include <QPushButton>

class KeyBindButton : public QPushButton
{
    Q_OBJECT
public:
    KeyBindButton(int *, QWidget *parent = nullptr);

    void setKey(int);

private:
    int *_keyptr;
};

#endif // KEYBINDBUTTON_H
