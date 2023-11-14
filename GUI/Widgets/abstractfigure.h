
#ifndef ABSTRACTFIGURE_H
#define ABSTRACTFIGURE_H

#include <QWidget>
#include "systemstate.h"

// Abstract Figure is a superclass that DigFigure, StimFigure, and AnOutFigure inherit from.
// Contains general functions that are inherited, and virtual functions that are reimplemented uniquely for each class.

class AbstractFigure : public QWidget
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent* event) override;

    void generalSetup(StimParameters *stimParameters, QWidget*);
    void generalRedraw();
    void drawDashedHorizontalLine(QPainter &painter, int xLeft, int xRight, int y, QColor color, int dashSize = 4);
    QRect drawHorizontalArrow(QPainter &painter, int xLeft, int xRight, int y, QColor color, QString label = "", bool labelTop = true);
    void drawStimPulse(QPainter &painter, int xLeft, int xRight, int y, int yMaxAmplitude);
    QRect drawVerticalArrow(QPainter &painter, int x, int yTop, int yBottom, QColor color, QString label, bool labelLeft);

    // Colors used to draw the figure
    const QColor backgroundColor = Qt::white;
    const QColor frameColor = Qt::darkGray;
    const QColor currentColor = Qt::darkGray;
    const QColor currentColorHL = Qt::darkRed;
    const QColor durationLabelColor = Qt::darkGray;
    const QColor durationLabelColorHL = Qt::red;
    const QColor amplitudeLabelColor = Qt::darkGray;
    const QColor amplitudeLabelColorHL = Qt::red;
    const QColor ampSettleColor = Qt::darkGray;
    const QColor ampSettleColorHL = Qt::darkYellow;
    const QColor chargeRecovColor = Qt::darkGray;
    const QColor chargeRecovColorHL = Qt::darkGreen;

    // Sizes used to draw the figure
    const int figureXSize = 320;
    const int figureYSize = 250; 
    const int ArrowSize = 4;

    // Variables used to draw the figure
    QPixmap pixmap;
    QRect frame;

    // Access to the StimParameters object from any function in this class or any inherited class
    StimParameters* parameters;

    // Boolean variables used to store the state of the figure and draw it
    bool highlitFirstPhaseDuration;
    bool highlitPostTriggerDelay;
    bool highlitPulseTrainPeriod;
    bool highlitRefractoryPeriod;
    bool highlitStimTrace;
    bool highlitSecondPhaseDuration;
    bool highlitInterphaseDelay;
    bool highlitFirstPhaseAmplitude;
    bool highlitSecondPhaseAmplitude;
    bool highlitPreStimAmpSettle;
    bool highlitPostStimAmpSettle;
    bool highlitPostStimChargeRecovOn;
    bool highlitPostStimChargeRecovOff;
    bool highlitBaselineVoltage;
    bool noAmplitude;

    // Local variables used to store the state of the figure and draw it
    StimShape localStimShape;
    StimPolarity localStimPolarity;
    PulseOrTrain localPulseOrTrain;

    // Variables accessible to this class and any inherited classes, used to draw the figure
    int triggerLabelWidth;
    int EndOfLineabelWidth;
    int x0;
    int xEnd;
    int xLength;
    QRect stimFrame;
    int xStimBegin;
    int y0;
    QString triggerLabel;
    QString EndOfLineabel;

private:
    virtual void uniqueRedraw(QPainter& painter) = 0;

public slots:
    void updateStimShape(int stimShape);
    void updateStimPolarity(int stimPolarity);
    void updatePulseOrTrain(int pulseOrTrain);
    void highlightPostTriggerDelay(bool highlight);
    void highlightPulseTrainPeriod(bool highlight);
    void highlightRefractoryPeriod(bool highlight);
    void highlightStimTrace(bool highlight);
    void highlightFirstPhaseDuration(bool highlight);
};

#endif // ABSTRACTFIGURE_H
