
#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include <vector>
#include <QtWidgets>
#include "systemstate.h"

using namespace std;

class MultiWaveformPlot;

struct ScrollBarState
{
    int range;                // Scroll bar operates from 0 to this value.
    vector<int> topPosition;  // Current position of scroll bar on each page; always between 0 and (range - pageSize)
    int pageSize;             // Size of one page.  Must be <= range.  Sets scroll bar size.  Increment of movement for page up/down.
    int stepSize;             // Increment of movement from up/down button or cursor up/down
    double zoomFactor;        // Number from 1.0 to ZoomLimit used to expand display
};

class ScrollBar
{
public:
    ScrollBar(QRect position, int numPages, MultiWaveformPlot* parent_);

    void resize(QRect position);

    int getTopPosition() const;
    inline int getStepSize() const { return scrollState.stepSize; }
    inline double getZoomFactor() const { return scrollState.zoomFactor; }

    ScrollBarState getState() const;
    void restoreState(const ScrollBarState& savedState);
    QString getStateString() const { return scrollBarStateToString(getState()); }
    void restoreStateFromString(const QString& stateString) { restoreState(scrollBarStateFromString(stateString)); }
    void adjustToNewNumberOfPages(int numPages);

    void setRange(int range_);
    void setPageSize(int pageSize_);
    inline void setStepSize(int stepSize_) { scrollState.stepSize = stepSize_; }
    inline void zoomIn() { scrollState.zoomFactor = qMin(scrollState.zoomFactor * ZoomStepMultiple, ZoomLimit); }
    inline void zoomOut() { scrollState.zoomFactor = qMax(scrollState.zoomFactor / ZoomStepMultiple, 1.0); }

    void scroll(int delta);

    // Handle mouse and keypress events, and return true if display needs to be updated.
    bool handleMousePress(QPoint position);
    bool handleMouseRelease();
    bool handleMouseMove(QPoint position);
    bool handleWheelEvent(int delta, bool shiftHeld, bool controlHeld);
    bool handleKeyPressEvent(int key);

    const QColor scrollBarColor = Qt::gray;
    const QColor scrollBarActiveColor = Qt::white;

    void draw(QPainter &painter);

private:
    MultiWaveformPlot* parent;

    QImage upArrow;
    QImage upArrowActive;
    QImage downArrow;
    QImage downArrowActive;

    // Long-term state
    ScrollBarState scrollState;

    // Short-term state
    bool upButtonActive;
    bool downButtonActive;
    bool barActive;
    int barGrabPoint;
    int barGrabPosition;

    // Clickable regions
    QRect scrollFrame;
    QRect scrollBar;
    QRect upButton;
    QRect downButton;
    QRect scrollBarBounds;

    const double ZoomLimit = 50.0;
    const double ZoomStepMultiple = 1.5;

    void setTopPosition(int topPosition_, int page);
    static QString scrollBarStateToString(const ScrollBarState& state);
    static ScrollBarState scrollBarStateFromString(const QString& stateString);
};

#endif // SCROLLBAR_H
