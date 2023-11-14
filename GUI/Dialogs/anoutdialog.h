
#ifndef ANOUTDIALOG_H
#define ANOUTDIALOG_H

#include <QDialog>
#include "systemstate.h"
#include "stimparameters.h"

class QDialogButtonBox;
class QWidget;
class QComboBox;
class QDoubleSpinBox;
class QSpinBox;
class QLabel;
class QCheckBox;
class StimParameters;
class TimeSpinBox;
class VoltageSpinBox;
class AnOutFigure;

class AnOutDialog : public QDialog
{
    Q_OBJECT
public:
    AnOutDialog(SystemState* state_, Channel* channel_, QWidget *parent = nullptr);
    void loadParameters(StimParameters* parameters);

public slots:
    void accept();
    void notifyFocusChanged(QWidget *lostFocus, QWidget *gainedFocus);

private:
    SystemState* state;
    Channel* channel;

    QDialogButtonBox *buttonBox;

    AnOutFigure *anOutFigure;

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
    VoltageSpinBox *firstPhaseAmplitudeSpinBox;
    QLabel *firstPhaseAmplitudeLabel;
    VoltageSpinBox *secondPhaseAmplitudeSpinBox;
    QLabel *secondPhaseAmplitudeLabel;
    VoltageSpinBox *baselineVoltageSpinBox;
    QLabel *baselineVoltageLabel;

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

    double timestep, currentstep;

private slots:
    void enableWidgets();
    void calculatePulseTrainFrequency();
    void constrainPulseTrainPeriod();
    void roundTimeInputs();
    void roundVoltageInputs();
    void updateMonophasicAndPositive();

signals:
    // Signal that is emitted when the DoubleSpinBoxes or ComboBox that control the minimum pulse train period have been changed
    void minimumPeriodChanged();

    // Signals that are emitted when various widgets that control the Stimulation Parameters are selected
    void monophasicAndPositiveSignalChanged(bool logicValue);
    void highlightBaselineVoltage(bool highlight);
    void highlightFirstPhaseDuration(bool highlight);
    void highlightSecondPhaseDuration(bool highlight);
    void highlightInterphaseDelay(bool highlight);
    void highlightFirstPhaseAmplitude(bool highlight);
    void highlightSecondPhaseAmplitude(bool highlight);
    void highlightPostTriggerDelay(bool highlight);
    void highlightPulseTrainPeriod(bool highlight);
    void highlightRefractoryPeriod(bool highlight);
};

#endif // ANOUTDIALOG_H
