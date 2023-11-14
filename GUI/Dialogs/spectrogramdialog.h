
#ifndef SPECTROGRAMDIALOG_H
#define SPECTROGRAMDIALOG_H

#include <QDialog>
#include "systemstate.h"
#include "spectrogramplot.h"

class QLabel;
class QComboBox;
class QSlider;
class QSpinBox;
class QPushButton;
class QRadioButton;
class QButtonGroup;
class QCheckBox;
class WaveformFifo;


class SpectrogramDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SpectrogramDialog(SystemState* state_, QWidget *parent = nullptr);
    ~SpectrogramDialog();

    void updateForRun();
    void updateForLoad();
    void updateForStop();
    void updateForChangeHeadstages();
    void updateSpectrogram(WaveformFifo *waveformFifo, int numSamples);
    void activate();

private slots:
    void updateFromState();
    void changeCurrentChannel(const QString& nativeChannelName)
        { state->spectrogramChannel->setValue(nativeChannelName); }
    void toggleLock() { updateFromState(); }
    void setToSelected();
    void changeDisplayMode(int index);
    void setNumFftPoints(int index)
        { state->fftSizeSpectrogram->setIndex(index); }
    void setFMin(int fMin);
    void setFMax(int fMax);
    void setFMarker(int fMarker)
        { state->fMarkerSpectrogram->setValue(fMarker); }
    void toggleShowFMarker(bool enabled);
    void setNumHarmonics(int num)
        { state->numHarmonicsSpectrogram->setValue(num); }
    void setTimeScale(int index)
        { state->tScaleSpectrogram->setIndex(index); }
    void setDigitalDisplay(int index)
        { state->digitalDisplaySpectrogram->setIndex(index); }
    void configSave();
    void saveData();

private:
    SystemState* state;

    QLabel *channelName;

    QCheckBox *lockScopeCheckbox;
    QPushButton *setToSelectedButton;

    QButtonGroup *displayModeButtonGroup;
    QRadioButton *spectrogramRadioButton;
    QRadioButton *spectrumRadioButton;

    QSpinBox *fMinSpinBox;
    QSpinBox *fMaxSpinBox;
    QSpinBox *fMarkerSpinBox;
    QLabel *fMarkerLabel;
    QCheckBox *fMarkerShowCheckBox;
    QSpinBox *fMarkerHarmonicsSpinBox;
    QLabel *fMarkerHarmonicsLabel1;
    QLabel *fMarkerHarmonicsLabel2;

    QLabel *deltaTimeLabel;
    QLabel *deltaFreqLabel;

    QSlider *nFftSlider;

    QLabel *timeScaleLabel;
    QComboBox *timeScaleComboBox;

    QComboBox *digitalDisplayComboBox;

    QPushButton *configSaveButton;
    QPushButton *saveButton;

    static const int FSpanMin = 10;

    SpectrogramPlot* specPlot;

    void updateDeltaTimeFreqLabels();
    void updateTitle();
};


class SpectrogramSaveConfigDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SpectrogramSaveConfigDialog(SystemState* state_, QWidget *parent = nullptr);

    QCheckBox *csvFileCheckBox;
    QCheckBox *matFileCheckBox;
    QCheckBox *pngFileCheckBox;

private:
    SystemState* state;
    QDialogButtonBox* buttonBox;
};

#endif // SPECTROGRAMDIALOG_H
