
#ifndef CONTROLPANELIMPEDANCETAB_H
#define CONTROLPANELIMPEDANCETAB_H

#include <QtWidgets>
#include "controllerinterface.h"
#include "systemstate.h"
#include "commandparser.h"

class ControlPanelImpedanceTab : public QWidget
{
    Q_OBJECT
public:
    explicit ControlPanelImpedanceTab(ControllerInterface* controllerInterface_, SystemState* state_, CommandParser* parser_,
                                      QWidget *parent = nullptr);

    void updateFromState();

signals:
    void sendSetCommand(QString parameter, QString value);
    void sendExecuteCommand(QString action);

private slots:
    void changeImpedanceFrequency();
    void runImpedanceTest();
    void saveImpedance();

private:
    SystemState* state;
    CommandParser* parser;
    ControllerInterface* controllerInterface;

    QPushButton *impedanceFreqSelectButton;
    QPushButton *runImpedanceTestButton;
    QPushButton *saveImpedancesButton;

    QLabel *desiredImpedanceFreqLabel;
    QLabel *actualImpedanceFreqLabel;

    void updateImpedanceFrequency();
};

#endif // CONTROLPANELIMPEDANCETAB_H
