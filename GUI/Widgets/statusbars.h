
#ifndef STATUSBARS_H
#define STATUSBARS_H

#include <QtWidgets>

class StatusBars : public QWidget
{
    Q_OBJECT
public:
    explicit StatusBars(QWidget *parent = nullptr);

public slots:
    void updateBars(double hwBufferPercent_, double swBufferPercent_, double cpuLoadPercent_);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QImage image;
    QImage background;

    double hwBufferPercent;
    double swBufferPercent;
    double cpuLoadPercent;

    QColor colorFromPercent(double percent) const;
};

#endif // STATUSBARS_H
