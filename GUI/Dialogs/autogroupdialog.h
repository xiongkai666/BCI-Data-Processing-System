
#ifndef AUTOGROUPDIALOG_H
#define AUTOGROUPDIALOG_H

#include <QtWidgets>
#include <QDialog>

class AutoGroupDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AutoGroupDialog(QWidget *parent);
    int groupSize() const { return groupSizeSpinBox->value(); }

private:
    QSpinBox *groupSizeSpinBox;
    QDialogButtonBox *buttonBox;
};

#endif // AUTOGROUPDIALOG_H
