
#ifndef TCPDISPLAY_H
#define TCPDISPLAY_H

#include <QtWidgets>
#include <QtNetwork>

#include "tcpcommunicator.h"
#include "systemstate.h"
#include "signalsources.h"

class QLineEdit;
class QTextEdit;
class QSpinBox;
class QPushButton;
class QLabel;
class QCheckBox;
class QTableWidget;

class TCPDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit TCPDisplay(SystemState* state_, QWidget *parent = nullptr);
    void updateFromState();

private:
    QLineEdit *waveformOutputHostLineEdit;
    QSpinBox *waveformOutputPortSpinBox;

    QLineEdit *spikeOutputHostLineEdit;
    QSpinBox *spikeOutputPortSpinBox;

    QLineEdit *commandsHostLineEdit;
    QSpinBox *commandsPortSpinBox;
    QPushButton *commandsConnectButton;
    QPushButton *commandsDisconnectButton;
    QLabel *commandsStatus;

    QTextEdit *commandTextEdit;
    QPushButton *clearCommandsButton;

    QTextEdit *errorTextEdit;
    QPushButton *clearErrorsButton;

    QPushButton *waveformOutputConnectButton;
    QPushButton *spikeOutputConnectButton;

    QPushButton *waveformOutputDisconnectButton;
    QPushButton *spikeOutputDisconnectButton;

    QTableWidget *presentChannelsTable;

    QPushButton *addChannelButton;
    QPushButton *removeChannelButton;

    QPushButton *addAllChannelsButton;
    QPushButton *removeAllChannelsButton;

    QLabel *filterSelectLabel;
    QComboBox *filterSelectComboBox;

    QTableWidget *channelsToStreamTable;

    QLabel *dataOutputStatus;

    QLabel *dataRateStatus;

    SystemState *state;
    SignalSources *signalSources;

    void parseCommands(const QString& commands);
    void addChannel(const QString& channelName);
    void removeChannel(const QString& channelName);
    void updateTables();
    void updatePresentChannelsTable();
    void updateChannelsToStreamTable();

private slots:
    void updateCommandWidgets();

    void waveformOutputHostEdited();
    void waveformOutputPortChanged();

    void spikeOutputHostEdited();
    void spikeOutputPortChanged();

    void clearCommands();
    void clearErrors();

    void selectPresentChannels();
    void selectChannelsToStream();
    void addChannels();
    void removeChannels();
    void addAllChannels();
    void removeAllChannels();

    void updateDataOutputWidgets();

signals:
    void sendSetCommand(QString parameter, QString value);
    void sendGetCommand(QString parameter);
    void sendExecuteCommand(QString action);
    void sendExecuteCommandWithParameter(QString action, QString parameter);
    void sendNoteCommand(QString note);
    void establishWaveformConnection();
    void establishSpikeConnection();

public slots:
    void processNewCommandConnection();
    void processNewWaveformOutputConnection();
    void processNewSpikeOutputConnection();
    void commandsConnect();
    void waveformOutputConnect();
    void spikeOutputConnect();
    void commandsDisconnect();
    void waveformOutputDisconnect();
    void spikeOutputDisconnect();
    void readClientCommand();
    void TCPReturn(QString result);
    void TCPError(QString errorString);
    void TCPWarning(QString warningString);
};

#endif // TCPDISPLAY_H
