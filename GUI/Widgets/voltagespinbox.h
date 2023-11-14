
#ifndef VOLTAGESPINBOX_H
#define VOLTAGESPINBOX_H

#include <QWidget>
#include <QDoubleSpinBox>

class QDoubleSpinBox;

class VoltageSpinBox : public QWidget
{
    Q_OBJECT
public:
    explicit VoltageSpinBox(QWidget *parent = nullptr);
    void setRange(double minimum, double maximum) { doubleSpinBox->setRange(minimum, maximum); }
    double getValue() { return doubleSpinBox->value(); }
    QWidget* pointer() {  return (QWidget*) doubleSpinBox; }

public slots:
    void setValue(double val) { doubleSpinBox->setValue(val); }
    void roundValue();

private:
    QDoubleSpinBox *doubleSpinBox;
    double voltagestep;

signals:
    void editingFinished();
    void valueChanged(double);
    void trueValueChanged(double);
};

#endif // VOLTAGESPINBOX_H
