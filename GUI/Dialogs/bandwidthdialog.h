
#ifndef BANDWIDTHDIALOG_H
#define BANDWIDTHDIALOG_H

#include <QDialog>

class QDialogButtonBox;
class QLineEdit;
class QLabel;
class QCheckBox;

class SimpleBandwidthDialog : public QDialog{
    Q_OBJECT
public:
    explicit SimpleBandwidthDialog(double lowerBandwidth, double upperBandwidth, double sampleRate,
                                   QWidget *parent = nullptr);

    QLineEdit *lowFreqLineEdit;
    QLineEdit *highFreqLineEdit;
    QDialogButtonBox *buttonBox;

private slots:
    void onLineEditTextChanged();

private:
    double nyquistFrequency;

    QLabel *lowRangeLabel;
    QLabel *highRangeLabel;
    QLabel *nyquistWarningLabel;
};

class AdvancedBandwidthDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AdvancedBandwidthDialog(double lowerBandwidth, double upperBandwidth, double dspCutoffFreq, bool dspEnabled,
                                     double sampleRate, QWidget *parent = nullptr);

    QLineEdit *dspFreqLineEdit;
    QLineEdit *lowFreqLineEdit;
    QLineEdit *highFreqLineEdit;
    QCheckBox *dspEnableCheckBox;
    QDialogButtonBox *buttonBox;

private slots:
    void onLineEditTextChanged();
    void onDspCheckBoxChanged(bool enable);

private:
    double nyquistFrequency;

    QLabel *dspRangeLabel;
    QLabel *lowRangeLabel;
    QLabel *highRangeLabel;
    QLabel *nyquistWarningLabel;
};

#endif // BANDWIDTHDIALOG_H
