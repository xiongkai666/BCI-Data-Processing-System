
#include "stimparametersclipboard.h"

StimParametersClipboard::StimParametersClipboard(SystemState* state_, ControllerInterface* controllerInterface_) :
    state(state_),
    controllerInterface(controllerInterface_),
    full(false),
    stimParameters(nullptr)
{

}

void StimParametersClipboard::copy(Channel* selectedChannel)
{
    stimParameters = selectedChannel->stimParameters;

    signalType = selectedChannel->getSignalType();
    full = true;
}

void StimParametersClipboard::paste(QList<Channel*> selectedChannels) const
{
    if (state->running) {
        qDebug() << "Error: pasting shouldn't be possible while board is running. Aborting paste";
        return;
    }

    for (QList<Channel*>::const_iterator i = selectedChannels.begin(); i != selectedChannels.end(); ++i) {
        (*i)->stimParameters->populateParametersFrom(stimParameters);
        controllerInterface->uploadStimParameters(*i);
    }

    state->forceUpdate();
}

bool StimParametersClipboard::isFull() const
{
    return full;
}

SignalType StimParametersClipboard::getSignalType() const
{
    return signalType;
}
