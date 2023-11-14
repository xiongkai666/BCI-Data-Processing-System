
#ifndef CONTROLPANELAUDIOANALOGTAB_H
#define CONTROLPANELAUDIOANALOGTAB_H

#include <QtWidgets>
#include "controllerinterface.h"
#include "systemstate.h"

class AnalogOutConfigDialog;

class ControlPanelAudioAnalogTab : public QWidget
{
    Q_OBJECT
public:
    explicit ControlPanelAudioAnalogTab(ControllerInterface* controllerInterface_, SystemState* state_, QWidget *parent = nullptr);
    ~ControlPanelAudioAnalogTab();

    void updateFromState();

private slots:
    void changeAudioFilter(int filterIndex) { state->audioFilter->setIndex(filterIndex); }
    void enableAudio(bool enabled);
    void changeVolume(int volume);
    void changeThreshold(int threshold);
    void changeDacGain(int index);
    void changeDacNoiseSuppress(int index);
    void openDacConfigDialog();
    void dac1LockToSelected(bool enable);
    void enableDacHighpassFilter(bool enable);
    void setDacHighpassFilterFrequency();
    void dac1SetChannel();
    void dac2SetChannel();
    void dac1Disable();
    void dac2Disable();

private:
    SystemState* state;
    ControllerInterface* controllerInterface;

    AnalogOutConfigDialog* analogOutConfigDialog;

    QCheckBox *audioEnabledCheckBox;
    QComboBox *audioFilterComboBox;
    QLabel *audioChannelLabel;

    QLabel *audioVolumeLabel;
    QSlider *audioVolumeSlider;
    QLabel *audioVolumeValueLabel;

    QLabel *audioThresholdLabel;
    QSlider *audioThresholdSlider;
    QLabel *audioThresholdValueLabel;

    QSlider *dacGainSlider;
    QSlider *dacNoiseSuppressSlider;

    QLabel *dacGainLabel;
    QLabel *dacNoiseSuppressLabel;
    QCheckBox *dacHighpassFilterCheckBox;
    QCheckBox *dacLockToSelectedCheckBox;
    QLineEdit *dacHighpassFilterLineEdit;

    QLabel *dac1Label;
    QLabel *dac2Label;

    QPushButton *dac1SetButton;
    QPushButton *dac2SetButton;
    QPushButton *dac1DisableButton;
    QPushButton *dac2DisableButton;
    QPushButton *openDacConfigButton;

    int gainIndexOld;
    int noiseSuppressIndexOld;
    bool analogOutHighpassFilterEnabledOld;
    double analogOutHighpassFilterFrequencyOld;

    QString analogOut1ChannelOld;
    QString analogOut2ChannelOld;
    QString analogOut3ChannelOld;
    QString analogOut4ChannelOld;
    QString analogOut5ChannelOld;
    QString analogOut6ChannelOld;
    QString analogOut7ChannelOld;
    QString analogOut8ChannelOld;
    QString analogRefChannelOld;

    int analogOut1ThresholdOld;
    int analogOut2ThresholdOld;
    int analogOut3ThresholdOld;
    int analogOut4ThresholdOld;
    int analogOut5ThresholdOld;
    int analogOut6ThresholdOld;
    int analogOut7ThresholdOld;
    int analogOut8ThresholdOld;

    bool analogOut1ThresholdEnabledOld;
    bool analogOut2ThresholdEnabledOld;
    bool analogOut3ThresholdEnabledOld;
    bool analogOut4ThresholdEnabledOld;
    bool analogOut5ThresholdEnabledOld;
    bool analogOut6ThresholdEnabledOld;
    bool analogOut7ThresholdEnabledOld;
    bool analogOut8ThresholdEnabledOld;

    void setAllThresholdEnabledValues();
};

#endif // CONTROLPANELAUDIOANALOGTAB_H
