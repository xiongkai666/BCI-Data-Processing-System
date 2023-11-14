
#ifndef TCPCOMMUNICATOR_H
#define TCPCOMMUNICATOR_H

#include <QObject>
#include <QtNetwork>

class TCPCommunicator : public QObject
{
    Q_OBJECT
public:

    enum ConnectionStatus {
        Disconnected,
        Pending,
        Connected
    };

    explicit TCPCommunicator(QString address_ = "127.0.0.1", int port_ = 5000, QObject *parent = nullptr);
    bool connectionAvailable();
    bool serverListening();
    bool listen(QString host, int port);
    QString read();
    void writeQString(QString message);
    void writeData(char* data, qint64 len);
    qint64 bytesUnwritten();

    bool passwordCleared;
    ConnectionStatus status;
    QString address;
    int port;

signals:
    void newConnection();
    void readyRead();
    void statusChanged();

public slots:
    void attemptNewConnection();
    void returnToDisconnected();
    void establishConnection();
    void TCPDataOutput(QByteArray* array, qint64 len);

private slots:
    void emitNewConnection();
    void emitReadyRead();

private:
    QTcpServer *server;
    QTcpSocket *socket;
    QByteArray cachedCommands;
};

#endif // TCPCOMMUNICATOR_H
