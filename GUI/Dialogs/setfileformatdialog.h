
#ifndef SETFILEFORMATDIALOG_H
#define SETFILEFORMATDIALOG_H

#include <QDialog>

#include "rhxglobals.h"
#include "systemstate.h"

class QDialogButtonBox;
class QSpinBox;
class QComboBox;
class QCheckBox;
class QRadioButton;
class QButtonGroup;
class QLabel;

class SetFileFormatDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SetFileFormatDialog(SystemState* state_, QWidget *parent);

    void updateFromState();

    bool getCreateNewDirectory() const;
    bool getSaveAuxInWithAmps() const;
    bool getSaveWidebandAmps() const;
    bool getSaveLowpassAmps() const;
    bool getSaveHighpassAmps() const;
    bool getSaveDCAmps() const;
    bool getSaveSpikeData() const;
    bool getSaveSpikeSnapshots() const;
    int getSnapshotPreDetect() const;
    int getSnapshotPostDetect() const;
    int getRecordTime() const;
    int getLowpassDownsampleFactorIndex() const;
    QString getFileFormat() const;

private slots:
    void updateOldFileFormat();
    void updateLowpassSampleRate();
    void updateSaveLowpass();
    void updateSaveSpikes();
    void updateSaveSnapshots();

private:
    SystemState* state;

    QCheckBox *createNewDirectoryCheckBox;
    QCheckBox *saveAuxInWithAmpCheckBox;
    QCheckBox *saveWidebandAmplifierWaveformsCheckBox;
    QCheckBox *saveLowpassAmplifierWaveformsCheckBox;
    QCheckBox *saveHighpassAmplifierWaveformsCheckBox;
    QCheckBox *saveSpikeDataCheckBox;
    QCheckBox *saveSpikeSnapshotsCheckBox;
    QSpinBox *spikeSnapshotPreDetectSpinBox;
    QSpinBox *spikeSnapshotPostDetectSpinBox;
    QCheckBox *saveDCAmplifierWaveformsCheckBox;
    QSpinBox *recordTimeSpinBox;
    QComboBox *lowpassWaveformDownsampleRateComboBox;

    QButtonGroup *buttonGroup;
    QRadioButton *fileFormatIntanButton;
    QRadioButton *fileFormatNeuroScopeButton;
    QRadioButton *fileFormatOpenEphysButton;
    QDialogButtonBox *buttonBox;

    QLabel *downsampleLabel;
    QLabel *lowpassSampleRateLabel;
    QLabel *fromLabel;
    QLabel *toLabel;

    FileFormat fileFormat;
};

#endif // SETFILEFORMATDIALOG_H
