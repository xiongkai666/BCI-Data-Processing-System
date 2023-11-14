
#include <iostream>
#include "signalsources.h"
#include "displayundomanager.h"

DisplayUndoManager::DisplayUndoManager(SignalSources* signalSources_) :
    signalSources(signalSources_),
    undoIndex(0)
{
}

void DisplayUndoManager::pushStateToUndoStack()
{
    if (canRedo()) {
        while (canRedo()) {  // If we are in the middle of the undo stack, clear all potential redos before pushing.
            undoStack.removeLast();
        }
        undoStack.removeLast();  // Also remove saved "pre-undo" state (see undo() below).
    }
    undoStack.append(signalSources->saveState());
    undoIndex = undoStack.size();

    while (undoStack.size() > MaxSizeUndoStack) {
        undoStack.removeFirst();
        undoIndex--;
    }
}

void DisplayUndoManager::retractLastPush()
{
    undoStack.removeLast();
    undoIndex = undoStack.size();
}

void DisplayUndoManager::clearUndoStack()
{
    undoStack.clear();
    undoIndex = 0;
}

void DisplayUndoManager::undo()
{
    if (!canUndo()) return;
    if (undoIndex == undoStack.size()) {
        undoStack.append(signalSources->saveState());   // Add "pre-undo" state, so we can optionally redo back to this.
    }
    DisplayState undoState = undoStack.at(undoIndex - 1);
    signalSources->restoreState(undoState);
    undoIndex--;
}

void DisplayUndoManager::redo()
{
    if (!canRedo()) return;
    DisplayState undoState = undoStack.at(undoIndex + 1);
    signalSources->restoreState(undoState);
    undoIndex++;
    if (undoIndex == undoStack.size() - 1) {  // If we redo back to the top of the stack, remove saved "pre-undo" state.
        undoStack.removeLast();
    }
}

