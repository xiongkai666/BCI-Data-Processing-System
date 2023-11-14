
#ifndef PERFORMANCEOPTIMIZATIONDIALOG_H
#define PERFORMANCEOPTIMIZATIONDIALOG_H

#include <QDialog>

#include "rhxglobals.h"
#include "systemstate.h"


class QGroupBox;
class QLabel;
class QComboBox;
class QDialogButtonBox;

class PerformanceOptimizationDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PerformanceOptimizationDialog(SystemState* state_, QWidget *parent = nullptr);

    QComboBox *XPUSelectionComboBox;
    QComboBox *writeLatencyComboBox;
    QComboBox *plottingModeComboBox;

signals:
    void usedXPUIndexChanged(int index);

private:
    void initialize();

    SystemState* state;
    QDialogButtonBox *buttonBox;
};

#endif // PERFORMANCEOPTIMIZATIONDIALOG_H
