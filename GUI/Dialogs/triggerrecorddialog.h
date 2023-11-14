
#ifndef TRIGGERRECORDDIALOG_H
#define TRIGGERRECORDDIALOG_H

#include <QDialog>
#include "systemstate.h"

class QDialogButtonBox;
class QCheckBox;
class QComboBox;
class QSpinBox;

class TriggerRecordDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TriggerRecordDialog(SystemState* state_, QWidget *parent);

    void updateFromState();

    QString getTriggerSave();
    QString getTriggerInput();
    QString getTriggerPolarity();
    QString getRecordBuffer();
    QString getPostTriggerBufferSeconds();

private:
    SystemState* state;

    QCheckBox *triggerSaveCheckBox;

    QComboBox *digitalInputComboBox;
    QComboBox *triggerPolarityComboBox;
    QSpinBox *recordBufferSpinBox;
    QSpinBox *postTriggerSpinBox;
    QDialogButtonBox *buttonBox;

    int digitalInput;
    int triggerPolarity;

private slots:
    void setDigitalInput(int index);
    void setTriggerPolarity(int index);
};

#endif // TRIGGERRECORDDIALOG_H
