
#ifndef IMPEDANCEFREQDIALOG_H
#define IMPEDANCEFREQDIALOG_H

#include <QDialog>

class QDialogButtonBox;
class QLineEdit;
class QLabel;

class ImpedanceFreqDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ImpedanceFreqDialog(double desiredImpedanceFreq, double lowerBandwidth, double upperBandwidth,
                                 double dspCutoffFreq, bool dspEnabled, double sampleRate, QWidget *parent = nullptr);

    QLineEdit *impedanceFreqLineEdit;
    QDialogButtonBox *buttonBox;
    
private slots:
    void onLineEditTextChanged();

private:
    double lowerLimitSample;
    double upperLimitSample;
    double lowerLimitBandwidth;
    double upperLimitBandwidth;

    QLabel *sampleRangeLabel;
    QLabel *bandwidth1RangeLabel;
    QLabel *bandwidth2RangeLabel;
};

#endif // IMPEDANCEFREQDIALOG_H
