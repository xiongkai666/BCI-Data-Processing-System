
#ifndef STIMPARAMDIALOG_H
#define STIMPARAMDIALOG_H

#include <QDialog>
#include "signalsources.h"
#include "systemstate.h"
#include "stimfigure.h"
#include "smartspinbox.h"

class QDialogButtonBox;
class QWidget;
class QComboBox;
class QDoubleSpinBox;
class QSpinBox;
class QLabel;
class QCheckBox;
class CurrentSpinBox;
class StimFigure;

class StimParamDialog : public QDialog
{
    Q_OBJECT
public:
    StimParamDialog(SystemState* state_, Channel* channel_, QWidget *parent = nullptr);

    void updateParametersFromState(StimParameters* parameters);
    void activate();

public slots:
    void accept();

private slots:
    void notifyFocusChanged(QWidget* lostFocus, QWidget* gainedFocus);
    void updateFromState();

private:
    SystemState* state;
    Channel* channel;

    QDialogButtonBox *buttonBox;
    StimFigure *stimFigure;

    StimParameters *parameters;

    QComboBox *stimShapeComboBox;
    QLabel *stimShapeLabel;
    QComboBox *stimPolarityComboBox;
    QLabel *stimPolarityLabel;
    TimeSpinBox *firstPhaseDurationSpinBox;
    QLabel *firstPhaseDurationLabel;
    TimeSpinBox *secondPhaseDurationSpinBox;
    QLabel *secondPhaseDurationLabel;
    TimeSpinBox *interphaseDelaySpinBox;
    QLabel *interphaseDelayLabel;
    CurrentSpinBox *firstPhaseAmplitudeSpinBox;
    QLabel *firstPhaseAmplitudeLabel;
    CurrentSpinBox *secondPhaseAmplitudeSpinBox;
    QLabel *secondPhaseAmplitudeLabel;
    QLabel *totalPosChargeLabel;
    QLabel *totalNegChargeLabel;
    QLabel *chargeBalanceLabel;

    QCheckBox *enableStimCheckBox;
    QComboBox *triggerSourceComboBox;
    QLabel *triggerSourceLabel;
    QComboBox *triggerEdgeOrLevelComboBox;
    QLabel *triggerEdgeOrLevelLabel;
    QComboBox *triggerHighOrLowComboBox;
    QLabel *triggerHighOrLowLabel;
    TimeSpinBox *postTriggerDelaySpinBox;
    QLabel *postTriggerDelayLabel;

    QComboBox *pulseOrTrainComboBox;
    QLabel *pulseOrTrainLabel;
    QSpinBox *numberOfStimPulsesSpinBox;
    QLabel *numberOfStimPulsesLabel;
    TimeSpinBox *pulseTrainPeriodSpinBox;
    QLabel *pulseTrainPeriodLabel;
    QLabel *pulseTrainFrequencyLabel;
    TimeSpinBox *refractoryPeriodSpinBox;
    QLabel *refractoryPeriodLabel;

    TimeSpinBox *preStimAmpSettleSpinBox;
    QLabel *preStimAmpSettleLabel;
    TimeSpinBox *postStimAmpSettleSpinBox;
    QLabel *postStimAmpSettleLabel;
    QCheckBox *maintainAmpSettleCheckBox;
    QCheckBox *enableAmpSettleCheckBox;

    TimeSpinBox *postStimChargeRecovOnSpinBox;
    QLabel *postStimChargeRecovOnLabel;
    TimeSpinBox *postStimChargeRecovOffSpinBox;
    QLabel *postStimChargeRecovOffLabel;
    QCheckBox *enableChargeRecoveryCheckBox;

    double timestep;
    double currentstep;

private slots:
    void enableWidgets();
    void calculateCharge();
    void calculatePulseTrainFrequency();
    void constrainPostTriggerDelay();
    void constrainPostStimChargeRecovery();
    void constrainRefractoryPeriod();
    void constrainPulseTrainPeriod();
    void roundTimeInputs();
    void roundCurrentInputs();

signals:
    // Signal that is emitted when the DoubleSpinBoxes that control charge have been changed
    void chargeChanged();

    // Signal that is emitted when the DoubleSpinBoxes or ComboBox that control the minimum pulse train period have been changed
    void minimumPeriodChanged();

    // Signals that are emitted when various widgets that control the Stimulation Parameters are selected
    void highlightFirstPhaseDuration(bool highlight);
    void highlightSecondPhaseDuration(bool highlight);
    void highlightInterphaseDelay(bool highlight);
    void highlightFirstPhaseAmplitude(bool highlight);
    void highlightSecondPhaseAmplitude(bool highlight);
    void highlightPostTriggerDelay(bool highlight);
    void highlightPulseTrainPeriod(bool highlight);
    void highlightRefractoryPeriod(bool highlight);
    void highlightPreStimAmpSettle(bool highlight);
    void highlightPostStimAmpSettle(bool highlight);
    void highlightPostStimChargeRecovOn(bool highlight);
    void highlightPostStimChargeRecovOff(bool highlight);
};

#endif // STIMPARAMDIALOG_H
