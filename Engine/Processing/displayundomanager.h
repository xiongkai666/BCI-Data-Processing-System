
#ifndef DISPLAYUNDOMANAGER_H
#define DISPLAYUNDOMANAGER_H

#include <vector>
#include <QString>
#include <QColor>
#include "scrollbar.h"

using namespace std;

class SignalSources;

// ChannelState, SignalGroupState, and SignalSourcesState are used to save and restore user-configurable aspects of
// SignalSources, e.g. for saving/loading settings files, or undo/redo operations.
struct ChannelState
{
    QString nativeChannelName;
    QString customChannelName;
    QColor color;
    int userOrder;
    int groupID;
    bool enabled;
    bool selected;
    bool outputToTcp;
    QString reference;
};

struct SignalGroupState
{
    QString name;
    vector<ChannelState> signalChannels;
};

struct DisplayColumnState
{
    QStringList pinnedWaveNames;
    bool showPinned;
    bool columnVisible;
    QString visiblePortName;
    ScrollBarState scrollBarState;
};

struct DisplayState
{
    vector<DisplayColumnState> columns;
    vector<SignalGroupState> groups;
};


class DisplayUndoManager
{
public:
    DisplayUndoManager(SignalSources* signalSources_);
    void pushStateToUndoStack();
    void retractLastPush();
    void clearUndoStack();
    void undo();
    void redo();
    inline bool canUndo() const { return undoIndex > 0; }
    inline bool canRedo() const { return undoIndex < undoStack.size() - 1; }

private:
    SignalSources* signalSources;

    QList<DisplayState> undoStack;
    int undoIndex;
    const int MaxSizeUndoStack = 200;
};

#endif // DISPLAYUNDOMANAGER_H
