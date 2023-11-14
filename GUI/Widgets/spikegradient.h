
#ifndef SPIKEGRADIENT_H
#define SPIKEGRADIENT_H

#include <QtWidgets>

#include "systemstate.h"
#include "rhxglobals.h"

class SpikeGradient : public QWidget
{
    Q_OBJECT
public:
    explicit SpikeGradient(SystemState* state_, QWidget *parent = nullptr);

    // Set up a QLinearGradient representing the portion of the black-white gradient that we want to represent time since last spike
    static QLinearGradient setupGradient();

    // Take a number of seconds and returns the corresponding color
    static QColor getColor(float seconds, float decayTime);

protected:
    void paintEvent(QPaintEvent *) override; // Initialize display for every paint event.
    void closeEvent(QCloseEvent *event) override; // Perform any clean-up here before application closes.

private:
    QSize minimumSizeHint() const override; // Minimum size of the gradient widget
    QSize sizeHint() const override; // Default suggested size of the page

    SystemState* state;
    QPixmap pixmap;
};

#endif // SPIKEGRADIENT_H
