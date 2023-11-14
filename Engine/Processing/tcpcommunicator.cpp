
#include "tcpcommunicator.h"

TCPCommunicator::TCPCommunicator(QString address_, int port_, QObject *parent) :
    QObject(parent),
    passwordCleared(false),
    status(Disconnected),
    address(address_),
    port(port_),
    server(nullptr),
    socket(nullptr)
{
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(emitNewConnection()));
}

bool TCPCommunicator::connectionAvailable()
{
    return server->hasPendingConnections();
}

void TCPCommunicator::establishConnection()
{
    static bool firstConnection = true;
    if (connectionAvailable()) {
        socket = server->nextPendingConnection();
        if (firstConnection) {
            connect(socket, SIGNAL(readyRead()), this, SLOT(emitReadyRead()));
            connect(socket, SIGNAL(disconnected()), this, SLOT(returnToDisconnected()));
        }
        firstConnection = false;
        server->close();
        status = Connected;
        emit statusChanged();
    }
}

bool TCPCommunicator::serverListening()
{
    return server->isListening();
}

bool TCPCommunicator::listen(QString host, int port)
{
    status = Pending;
    emit statusChanged();
    return server->listen(QHostAddress(host), port);
}

QString TCPCommunicator::read()
{
    // Straight-forward read if status is Connected
    if (status == Connected) {
        return socket->readAll();
    }

    // Read from cached commands if status is not Connected
    else {
        QString cacheString = cachedCommands;
        cachedCommands.clear();
        return cacheString;
    }
}

void TCPCommunicator::writeQString(QString message)
{
    // Only attempt a write if status is Connected
    if (status == Connected) {
        socket->write(message.toLatin1());
        socket->waitForBytesWritten();
    }
}

void TCPCommunicator::writeData(char *data, qint64 len)
{
    // Only attempt a write if status is Connected
    if (status == Connected) {
        socket->write(data, len);
        socket->waitForBytesWritten();
    }
}

void TCPCommunicator::attemptNewConnection()
{
    if (!serverListening()) {
        listen(address, port);
    }
}

void TCPCommunicator::returnToDisconnected()
{
    if (socket) {
        // Before disconnecting, if any data is on the socket, grab it.
        cachedCommands = socket->readAll();
        // Disconnect and destroy socket
        socket->disconnectFromHost();
        disconnect(socket, SIGNAL(readyRead()), this, SLOT(emitReadyRead()));
        disconnect(socket, SIGNAL(disconnected()), this, SLOT(returnToDisconnected()));
        socket = nullptr;
    }
    server->close();
    status = Disconnected;
    emit statusChanged();
}

qint64 TCPCommunicator::bytesUnwritten()
{
    return socket->bytesToWrite();
}

void TCPCommunicator::emitNewConnection()
{
    emit newConnection();
}

void TCPCommunicator::emitReadyRead()
{
    emit readyRead();
}

void TCPCommunicator::TCPDataOutput(QByteArray *array, qint64 len)
{
    socket->write(array->data(), len);
}
