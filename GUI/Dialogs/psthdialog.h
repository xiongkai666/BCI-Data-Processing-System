
#ifndef PSTHDIALOG_H
#define PSTHDIALOG_H

#include <QDialog>
#include "systemstate.h"
#include "psthplot.h"

class QLabel;
class QComboBox;
class QPushButton;
class QCheckBox;
class WaveformFifo;

class PSTHDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PSTHDialog(SystemState* state_, QWidget *parent = nullptr);
    ~PSTHDialog();

    void updateForRun();
    void updateForLoad();
    void updateForStop();
    void updateForChangeHeadstages();
    void updatePSTH(WaveformFifo *waveformFifo, int numSamples);
    void activate();

private slots:
    void updateFromState();
    void changeCurrentChannel(const QString& nativeChannelName)
        { state->psthChannel->setValue(nativeChannelName); }
    void toggleLock() { updateFromState(); }
    void setToSelected();
    void setPreTriggerSpan(int index)
        { state->tSpanPreTriggerPSTH->setIndex(index); }
    void setPostTriggerSpan(int index)
        { state->tSpanPostTriggerPSTH->setIndex(index); }
    void setBinSize(int index)
        { state->binSizePSTH->setIndex(index); }
    void setMaxNumTrials(int index)
        { state->maxNumTrialsPSTH->setIndex(index); }
    void clearLastTrial() { psthPlot->deleteLastRaster(); psthPlot->setFocus(); }
    void clearAllTrials() { psthPlot->resetPSTH(); psthPlot->setFocus(); }
    void setDigitalTrigger(int index)
        { state->digitalTriggerPSTH->setIndex(index); }
    void setTriggerPolarity(int index)
        { state->triggerPolarityPSTH->setIndex(index); }
    void configSave();
    void saveData();

private:
    SystemState* state;

    QLabel *channelName;

    QCheckBox *lockScopeCheckbox;
    QPushButton *setToSelectedButton;

    QComboBox *preTriggerSpanComboBox;
    QComboBox *postTriggerSpanComboBox;
    QComboBox *binSizeComboBox;

    QComboBox *maxNumTrialsComboBox;
    QPushButton *clearAllTrialsPushButton;
    QPushButton *clearLastTrialPushButton;

    QComboBox *digitalTriggerComboBox;
    QComboBox *triggerPolarityComboBox;

    QPushButton *configSaveButton;
    QPushButton *saveButton;

    PSTHPlot* psthPlot;

    void updateTitle();
};


class PSTHSaveConfigDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PSTHSaveConfigDialog(SystemState* state_, QWidget *parent = nullptr);

    QCheckBox *csvFileCheckBox;
    QCheckBox *matFileCheckBox;
    QCheckBox *pngFileCheckBox;

private:
    SystemState* state;
    QDialogButtonBox* buttonBox;
};

#endif // PSTHDIALOG_H
