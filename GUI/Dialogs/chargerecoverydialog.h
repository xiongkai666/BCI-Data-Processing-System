
#ifndef CHARGERECOVERYDIALOG_H
#define CHARGERECOVERYDIALOG_H

#include <QDialog>
#include "rhxregisters.h"

class QDialogButtonBox;
class QLineEdit;
class QLabel;
class QComboBox;

class ChargeRecoveryDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ChargeRecoveryDialog(bool chargeRecoveryMode,
                                  RHXRegisters::ChargeRecoveryCurrentLimit currentLimit,
                                  double targetVoltage, QWidget *parent);

    QLineEdit *targetVoltageLineEdit;
    QComboBox *chargeRecoveryModeComboBox;

    RHXRegisters::ChargeRecoveryCurrentLimit getCurrentLimit();

private slots:
    void onLineEditTextChanged();
    void setChargeRecoveryMode(int index);

private:
    QLabel *targetVoltageRangeLabel;
    QComboBox *currentLimitComboBox;
    QDialogButtonBox *buttonBox;
};

#endif // CHARGERECOVERYDIALOG_H
