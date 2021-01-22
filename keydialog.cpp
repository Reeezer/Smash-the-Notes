#include "keydialog.h"

#include <QKeyEvent>
#include <QVBoxLayout>
#include <QLabel>

KeyDialog::KeyDialog(int *key)
    : _key(key)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(new QLabel("Press a key..."));
}

/* static */
int KeyDialog::getKey()
{
    int key;
    KeyDialog dialog(&key);
    dialog.exec();
    return key;
}

void KeyDialog::keyPressEvent(QKeyEvent *event)
{
    *_key = event->key();
    close();
}
