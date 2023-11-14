
#ifndef ISIDIALOG_H
#define ISIDIALOG_H

#include <QDialog>
#include "systemstate.h"
#include "isiplot.h"

class QLabel;
class QComboBox;
class QPushButton;
class QCheckBox;
class WaveformFifo;

class ISIDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ISIDialog(SystemState* state_, QWidget *parent = nullptr);
    ~ISIDialog();

    void updateForRun();
    void updateForLoad();
    void updateForStop();
    void updateForChangeHeadstages();

    void updateISI(WaveformFifo *waveformFifo, int numSamples);
    void activate();

private slots:
    void updateFromState();
    void changeCurrentChannel(const QString& nativeChannelName)
        { state->isiChannel->setValue(nativeChannelName); }
    void toggleLock() { updateFromState(); }
    void setToSelected();
    void setTimeSpan(int index)
        { state->tSpanISI->setIndex(index); }
    void setBinSize(int index)
        { state->binSizeISI->setIndex(index); }
    void changeYAxisMode(int index)
        { state->yAxisLogISI->setValue((bool) index); }
    void clearISI() { isiPlot->resetISI(); isiPlot->setFocus(); }
    void configSave();
    void saveData();

private:
    SystemState* state;

    QLabel *channelName;

    QCheckBox *lockScopeCheckbox;
    QPushButton *setToSelectedButton;

    QComboBox *timeSpanComboBox;
    QComboBox *binSizeComboBox;

    QButtonGroup *yAxisButtonGroup;
    QRadioButton *yAxisLinearRadioButton;
    QRadioButton *yAxisLogRadioButton;

    QPushButton *clearISIPushButton;

    QPushButton *configSaveButton;
    QPushButton *saveButton;

    ISIPlot* isiPlot;

    void updateTitle();
};


class ISISaveConfigDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ISISaveConfigDialog(SystemState* state_, QWidget *parent = nullptr);

    QCheckBox *csvFileCheckBox;
    QCheckBox *matFileCheckBox;
    QCheckBox *pngFileCheckBox;

private:
    SystemState* state;
    QDialogButtonBox* buttonBox;
};

#endif // ISIDIALOG_H
