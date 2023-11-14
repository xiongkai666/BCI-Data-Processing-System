
#ifndef IMPEDANCEGRADIENT_H
#define IMPEDANCEGRADIENT_H

#include <QtWidgets>

#include "rhxglobals.h"

class ImpedanceGradient : public QWidget
{
    Q_OBJECT
public:
    explicit ImpedanceGradient(QWidget *parent = nullptr);

    // Set up a QLinearGradient representing the portion of the rainbow from purple to red that we want to represent impedances from 10K to 10M
    static QLinearGradient setupGradient();

    // Take a scaled magnitude number (from 0 to 1, 0 representing 10K and 1 representing 10M) and returns the corresponding color according to our rainbow
    static QColor getColor(float magnitudeScaled);

protected:
    void paintEvent(QPaintEvent *) override; // Initialize display for every paint event.
    void closeEvent(QCloseEvent *event) override; // Perform any clean-up here before application closes.

private:
    QSize minimumSizeHint() const override; // Minimum size of the gradient widget
    QSize sizeHint() const override; // Default suggested size of the page

    QPixmap pixmap;
};

#endif // IMPEDANCEGRADIENT_H
