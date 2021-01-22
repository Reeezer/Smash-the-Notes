#ifndef KEYDIALOG_H
#define KEYDIALOG_H

#include <QDialog>

class KeyDialog : public QDialog
{
    Q_OBJECT

public:
    KeyDialog(int *);

    static int getKey();

protected:
    void keyPressEvent(QKeyEvent *) override;

private:
    int *_key;
};

#endif // KEYDIALOG_H
