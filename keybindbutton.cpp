#include "keybindbutton.h"

#include <QKeySequence>

KeyBindButton::KeyBindButton(int *keyptr, QWidget *parent)
    : QPushButton(parent), _keyptr(keyptr)
{
    setKey(*keyptr);
}

void KeyBindButton::setKey(int key)
{
    *_keyptr = key;
    setText(QKeySequence(key).toString());
}
