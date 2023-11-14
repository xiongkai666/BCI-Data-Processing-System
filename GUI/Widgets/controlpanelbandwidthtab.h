
#ifndef CONTROLPANELBANDWIDTHTAB_H
#define CONTROLPANELBANDWIDTHTAB_H

#include <QtWidgets>
#include "controllerinterface.h"
#include "systemstate.h"
#include "viewfilterswindow.h"

class ControlPanelBandwidthTab : public QWidget
{
    Q_OBJECT
public:
    explicit ControlPanelBandwidthTab(ControllerInterface* controllerInterface_, SystemState* state_, QWidget *parent = nullptr);
    ~ControlPanelBandwidthTab();

    void updateFromState();

private slots:
    void simpleBandwidthDialog();
    void advancedBandwidthDialog();
    void viewFiltersSlot();
    void changeNotchFilter(int filterIndex) { state->notchFreq->setIndex(filterIndex); }
    void changeLowType(int lowType) { state->lowType->setIndex(lowType); }
    void changeHighType(int highType) { state->highType->setIndex(highType); }
    void changeLowOrder(int lowOrder) { state->lowOrder->setValueWithLimits(lowOrder); }
    void changeHighOrder(int highOrder) { state->highOrder->setValueWithLimits(highOrder); }
    void changeLowCutoff() { state->lowSWCutoffFreq->setValueWithLimits(lpCutoffLineEdit->text().toDouble()); }
    void changeHighCutoff() { state->highSWCutoffFreq->setValueWithLimits(hpCutoffLineEdit->text().toDouble()); }

private:
    SystemState* state;
    ControllerInterface* controllerInterface;

    ViewFiltersWindow *viewFiltersWindow;

    QLabel *bandwidthLabel;

    QPushButton *changeBandwidthButton;
    QPushButton *advancedBandwidthButton;

    QComboBox *notchFilterComboBox;

    QComboBox *lpTypeComboBox;
    QLabel *lpOrderLabel;
    QSpinBox *lpOrderSpinBox;
    QLineEdit *lpCutoffLineEdit;

    QComboBox *hpTypeComboBox;
    QLabel *hpOrderLabel;
    QSpinBox *hpOrderSpinBox;
    QLineEdit *hpCutoffLineEdit;
    QPushButton *viewFiltersButton;

    static double lower3dBPoint(double hpf1Cutoff, double hpf2Cutoff, bool hpf2Enabled);
    static double secondPoleLocation(double target3dBPoint, double hpf1Cutoff);
};

#endif // CONTROLPANELBANDWIDTHTAB_H
