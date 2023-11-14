
#ifndef STARTUPDIALOG_H
#define STARTUPDIALOG_H

#include <QDialog>

#include "rhxcontroller.h"
#include "rhxglobals.h"

class QComboBox;
class QCheckBox;
class QDialogButtonBox;

class StartupDialog : public QDialog
{
    Q_OBJECT
public:
    explicit StartupDialog(ControllerType controllerType_, AmplifierSampleRate* sampleRate_, StimStepSize* stimStepSize_,
                           bool* rememberSettings_, bool askToRememberSettings, bool testMode, QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent *) override;

public slots:
    void accept() override;

private:
    ControllerType controllerType;
    AmplifierSampleRate* sampleRate;
    StimStepSize* stimStepSize;
    bool *rememberSettings;

    QComboBox *sampleRateComboBox;
    QComboBox *stimStepComboBox;
    QCheckBox *rememberSettingsCheckBox;
    QDialogButtonBox *buttonBox;
};

#endif // STARTUPDIALOG_H
