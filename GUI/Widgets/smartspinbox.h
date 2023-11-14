
#ifndef SMARTSPINBOX_H
#define SMARTSPINBOX_H

#include <QWidget>
#include <QDoubleSpinBox>
#include "rhxglobals.h"

class SmartSpinBox : public QWidget
{
    Q_OBJECT
public:
    explicit SmartSpinBox(double step_, QWidget *parent = nullptr);
    void setRange(double minimum, double maximum) { doubleSpinBox->setRange(minimum, maximum); }
    double getTrueValue() { return value; }
    virtual void setTrueMinimum(double min) = 0;
    QWidget* pointer() { return doubleSpinBox; }

public slots:
    void setValue(double val) { doubleSpinBox->setValue(val); }
    virtual void loadValue(double val) = 0;
    virtual void roundValue() = 0;

protected slots:
    virtual void scaleUnits(double val) = 0;
    virtual void sendSignalValueMicro(double val) = 0;

protected:
    QDoubleSpinBox *doubleSpinBox;
    double value;
    double step;

signals:
    void editingFinished();
    void valueChanged(double);
    void trueValueChanged(double);
};


class CurrentSpinBox : public SmartSpinBox
{
    Q_OBJECT
public:
    explicit CurrentSpinBox(double step_, QWidget *parent = nullptr);
    void setTrueMinimum(double min);

public slots:
    void loadValue(double val);
    void roundValue();

private slots:
    void scaleUnits(double val);
    void sendSignalValueMicro(double val);
};


class TimeSpinBox : public SmartSpinBox
{
    Q_OBJECT
public:
    explicit TimeSpinBox(double step_, QWidget *parent = nullptr);
    void setTrueMinimum(double min);

public slots:
    void loadValue(double val);
    void roundValue();

private slots:
    void scaleUnits(double val);
    void sendSignalValueMicro(double val);
};

#endif // SMARTSPINBOX_H
