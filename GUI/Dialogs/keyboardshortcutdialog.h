
#ifndef KEYBOARDSHORTCUTDIALOG_H
#define KEYBOARDSHORTCUTDIALOG_H

#include <QDialog>

class KeyboardShortcutDialog : public QDialog
{
    Q_OBJECT
public:
    explicit KeyboardShortcutDialog(QWidget *parent = nullptr); 

protected:
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // KEYBOARDSHORTCUTDIALOG_H
