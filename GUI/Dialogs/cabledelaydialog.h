
#ifndef CABLEDELAYDIALOG_H
#define CABLEDELAYDIALOG_H

#include <QDialog>

using namespace std;

class QCheckBox;
class QSpinBox;
class QDialogButtonBox;

class CableDelayDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CableDelayDialog(vector<bool> &manualDelayEnabled, vector<int> &currentDelay, int numPorts,
                              QWidget *parent = nullptr);

    QCheckBox *manualPortACheckBox;
    QCheckBox *manualPortBCheckBox;
    QCheckBox *manualPortCCheckBox;
    QCheckBox *manualPortDCheckBox;
    QCheckBox *manualPortECheckBox;
    QCheckBox *manualPortFCheckBox;
    QCheckBox *manualPortGCheckBox;
    QCheckBox *manualPortHCheckBox;

    QSpinBox *delayPortASpinBox;
    QSpinBox *delayPortBSpinBox;
    QSpinBox *delayPortCSpinBox;
    QSpinBox *delayPortDSpinBox;
    QSpinBox *delayPortESpinBox;
    QSpinBox *delayPortFSpinBox;
    QSpinBox *delayPortGSpinBox;
    QSpinBox *delayPortHSpinBox;

    QDialogButtonBox *buttonBox;
};

#endif // CABLEDELAYDIALOG_H
