
#ifndef AUTOCOLORDIALOG_H
#define AUTOCOLORDIALOG_H

#include <QtWidgets>
#include <QDialog>

class AutoColorDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AutoColorDialog(QWidget *parent);
    int numColors() const { return numColorsSpinBox->value(); }
    int numChannelsSameColor() const { return numChannelsSameColorSpinBox->value(); }

private:
    QSpinBox *numColorsSpinBox;
    QSpinBox *numChannelsSameColorSpinBox;
    QDialogButtonBox *buttonBox;
};

#endif // AUTOCOLORDIALOG_H
