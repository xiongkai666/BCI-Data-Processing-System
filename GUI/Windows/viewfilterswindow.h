
#ifndef VIEWFILTERSWINDOW_H
#define VIEWFILTERSWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include "filterplot.h"

class ViewFiltersWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ViewFiltersWindow(SystemState* state_, QWidget *parent = nullptr);
    ~ViewFiltersWindow();

private slots:
    void updateFromState();
    void toggleLogarithmic(bool log);
    void updateStatusBar(double frequency, double wideNormalizedGain, double lowNormalizedGain, double highNormalizedGain);
    void clearStatusBar();

private:
    SystemState* state;

    FilterPlot *filterPlot;

    QRadioButton *logarithmicButton;
    QRadioButton *linearButton;

    QLabel *hardwareLowCutoffLabel;
    QLabel *hardwareHighCutoffLabel;
    QLabel *hardwareDSPLabel;

    QLabel *softwareNotchLabel;
    QLabel *softwareLowPassLabel;
    QLabel *softwareHighPassLabel;

    QLabel *statusBarLabel;

    QDialogButtonBox *buttonBox;

    void updateFilterParameterText();
    QString freqAsString(double frequency, bool hz = true);  // Write given frequency as a string, in S/s, kS/s, Hz, or kHz
    QString ordinalNumberString(int number) const;
};

#endif // VIEWFILTERSWINDOW_H
