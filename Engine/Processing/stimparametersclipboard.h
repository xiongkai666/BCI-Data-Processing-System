
#ifndef STIMPARAMETERSCLIPBOARD_H
#define STIMPARAMETERSCLIPBOARD_H

#include "channel.h"
#include "controllerinterface.h"


class StimParametersClipboard
{
public:
    StimParametersClipboard(SystemState* state_, ControllerInterface* controllerInterface_);

    void copy(Channel* selectedChannel);
    void paste(QList<Channel*> selectedChannels) const;
    bool isFull() const;
    SignalType getSignalType() const;

private:
    SystemState* state;
    ControllerInterface* controllerInterface;

    bool full;
    SignalType signalType;
    StimParameters *stimParameters;
};

#endif // STIMPARAMETERSCLIPBOARD_H
