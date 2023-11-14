
#ifndef DIGOUTDIALOG_H
#define DIGOUTDIALOG_H

#include <QDialog>
#include "systemstate.h"
#include "stimparameters.h"
#include "rhxglobals.h"

class QDialogButtonBox;
class QWidget;
class QComboBox;
class QSpinBox;
class QLabel;
class QCheckBox;
class StimParameters;
class TimeSpinBox;
class DigFigure;

class DigOutDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DigOutDialog(SystemState* state_, Channel* channel_, QWidget *parent = nullptr);
    void loadParameters(StimParameters* parameters);

public slots:
    void accept();
    void notifyFocusChanged(QWidget *lostFocus, QWidget *gainedFocus);

private:
    SystemState* state;
    Channel* channel;

    QDialogButtonBox *buttonBox;

    DigFigure *digFigure;

    StimParameters *parameters;

    QCheckBox *enablePulseCheckBox;
    QComboBox *triggerSourceComboBox;
    QLabel *triggerSourceLabel;
    QComboBox *triggerEdgeOrLevelComboBox;
    QLabel *triggerEdgeOrLevelLabel;
    QComboBox *triggerHighOrLowComboBox;
    QLabel *triggerHighOrLowLabel;
    TimeSpinBox *postTriggerDelaySpinBox;
    QLabel *postTriggerDelayLabel;

    TimeSpinBox *pulseDurationSpinBox;
    QLabel *pulseDurationLabel;
    QComboBox *pulseRepetitionComboBox;
    QLabel *pulseRepetitionLabel;
    QSpinBox *numPulsesSpinBox;
    QLabel *numPulsesLabel;
    TimeSpinBox *pulseTrainPeriodSpinBox;
    QLabel *pulseTrainPeriodLabel;
    QLabel *pulseTrainFrequencyLabel;
    TimeSpinBox *refractoryPeriodSpinBox;
    QLabel *refractoryPeriodLabel;

    double timestep;

private slots:
    void enableWidgets();
    void roundTimeInputs();
    void calculatePulseTrainFrequency();
    void constrainPulseTrainPeriod();

signals:
    void highlightFirstPhaseDuration(bool highlight);
    void highlightPostTriggerDelay(bool highlight);
    void highlightPulseTrainPeriod(bool highlight);
    void highlightRefractoryPeriod(bool highlight);

};

#endif // DIGOUTDIALOG_H
