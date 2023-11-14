
#ifndef SETTHRESHOLDSDIALOG_H
#define SETTHRESHOLDSDIALOG_H

#include <QtWidgets>
#include <QDialog>

class SetThresholdsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SetThresholdsDialog(bool absoluteThreshold_, int threshold_, double rmsMultiple_, bool negativeRelativeThreshold_,
                                 QWidget *parent);
    bool absoluteThreshold() const;
    double threshold() const;
    double rmsMultiple() const;

private slots:
    void updateThresholdType();

private:
    QSpinBox *thresholdSpinBox;
    QComboBox *rmsSignComboBox;
    QDoubleSpinBox *rmsMultipleSpinBox;
    QDialogButtonBox *buttonBox;

    QButtonGroup *buttonGroup;
    QRadioButton *absoluteThresholdButton;
    QRadioButton *relativeThresholdButton;
};

#endif // SETTHRESHOLDSDIALOG_H
