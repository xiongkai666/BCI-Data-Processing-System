
#ifndef CONTROLPANELCONFIGURETAB_H
#define CONTROLPANELCONFIGURETAB_H

#include <QtWidgets>
#include "controllerinterface.h"
#include "systemstate.h"
#include "commandparser.h"

class ControlPanelConfigureTab : public QWidget
{
    Q_OBJECT
public:
    explicit ControlPanelConfigureTab(ControllerInterface* controllerInterface_, SystemState* state_, CommandParser* parser_,
                                      QWidget *parent = nullptr);
    void updateFromState();
    void updateForRun();
    void updateForLoad();
    void updateForStop();

    QCheckBox *fastSettleCheckBox;

signals:
    void sendExecuteCommand(QString);
    void sendNoteCommand(QString);

public slots:
    void rescanPorts();
    void enableFastSettle(bool enable);

private slots:
    void manualCableDelayControl();
    void configDigOutControl();
    void enableExternalFastSettle(bool enable);
    void setExternalFastSettleChannel(int channel);
    void addLiveNote();
    void displayLastLiveNote(QString note) { lastLiveNoteLabel->setText("Last note: " + note); }
    void setNotes();

private:
    void enableNotes(bool enabled);

    SystemState* state;
    CommandParser* parser;
    ControllerInterface* controllerInterface;

    QPushButton *scanButton;
    QPushButton *setCableDelayButton;
    QPushButton *digOutButton;

    QCheckBox *externalFastSettleCheckBox;
    QSpinBox *externalFastSettleSpinBox;

    QLineEdit *note1LineEdit;
    QLineEdit *note2LineEdit;
    QLineEdit *note3LineEdit;

    QLineEdit *liveNotesLineEdit;
    QPushButton *liveNotesButton;
    QLabel *lastLiveNoteLabel;

    vector<SignalGroup*> spiPort;
    vector<bool> manualDelayEnabledOld;
    vector<int> manualDelayOld;
    bool fastSettleEnabledOld;
    bool externalFastSettleEnabledOld;
    int externalFastSettleChannelOld;
};

#endif // CONTROLPANELCONFIGURETAB_H
