
#ifndef AMPSETTLEDIALOG_H
#define AMPSETTLEDIALOG_H

#include <QDialog>

class QDialogButtonBox;
class QLineEdit;
class QLabel;
class QCheckBox;
class QComboBox;

class AmpSettleDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AmpSettleDialog(double lowerSettleBandwidth, bool useFastSettle, bool headstageGlobalSettle,
                             QWidget *parent);

    QLineEdit *lowFreqSettleLineEdit;
    QCheckBox *settleHeadstageCheckBox;
    QComboBox *ampSettleModeComboBox;
    QDialogButtonBox *buttonBox;

private slots:
    void onLineEditTextChanged();
    void setAmpSettleMode(int index);

private:
    QLabel *lowRangeSettleLabel;
};

#endif // AMPSETTLEDIALOG_H
