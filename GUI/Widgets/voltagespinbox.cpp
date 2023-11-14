
#include <QtWidgets>
#include "voltagespinbox.h"

VoltageSpinBox::VoltageSpinBox(QWidget *parent) :
    QWidget(parent)
{
    voltagestep = 0.01;

    doubleSpinBox = new QDoubleSpinBox();
    doubleSpinBox->setSingleStep(voltagestep);
    doubleSpinBox->setDecimals(2);
    doubleSpinBox->setSuffix(" V");

    connect(doubleSpinBox, SIGNAL(editingFinished()), this, SIGNAL(editingFinished()));

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(doubleSpinBox);
    setLayout(mainLayout);
}

void VoltageSpinBox::roundValue()
{
    int sign = (getValue() >= 0 ? 1 : -1);
    // Use modulo to find the difference between the current value and the closest multiple of voltage step
    // due to errors in floating point modulo, conduct modulo in the integer domain, and then bring back to double.
    long valueInt = (long) ((this->getValue() * 1000.0) + sign * 0.5);
    long voltagestepInt = (long) (voltagestep * 1000.0);
    int modint = (sign * valueInt) % voltagestepInt;
    double mod = modint / 1000.0;

    // If the modulo is not zero, the current value is not a multiple of voltage step.
    if (mod != 0) {
        // If the modulo is less than half of the voltage step, the value should round down.
        if (mod < voltagestep / 2.0) {
            doubleSpinBox->setValue(doubleSpinBox->value() - sign * mod);
        } else {
            doubleSpinBox->setValue(doubleSpinBox->value() + sign * (voltagestep - mod));
        }
    }
}
