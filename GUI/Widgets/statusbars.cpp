
#include "statusbars.h"

StatusBars::StatusBars(QWidget *parent) :
    QWidget(parent)
{
    hwBufferPercent = 0.0;
    swBufferPercent = 0.0;
    cpuLoadPercent = 0.0;

    background = QImage(":images/status_header.png");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setMinimumSize(background.size());
    setMaximumSize(background.size());
    image = QImage(background.size(), QImage::Format_ARGB32_Premultiplied);
}

QSize StatusBars::minimumSizeHint() const
{
    return background.size();
}

QSize StatusBars::sizeHint() const
{
    return background.size();
}

void StatusBars::paintEvent(QPaintEvent* /* event */)
{
    QPainter painter(&image);
    painter.drawImage(QPoint(0, 0), background);

    painter.fillRect(QRect(48, 3, round(hwBufferPercent), 5), colorFromPercent(hwBufferPercent));
    painter.fillRect(QRect(48, 11, round(swBufferPercent), 5), colorFromPercent(swBufferPercent));
    painter.fillRect(QRect(48, 19, round(cpuLoadPercent), 5), colorFromPercent(cpuLoadPercent));

    QStylePainter stylePainter(this);
    stylePainter.drawImage(0, 0, image);
}

void StatusBars::updateBars(double hwBufferPercent_, double swBufferPercent_, double cpuLoadPercent_)
{
    hwBufferPercent = hwBufferPercent_;
    swBufferPercent = swBufferPercent_;
    cpuLoadPercent = cpuLoadPercent_;
    update();
}

QColor StatusBars::colorFromPercent(double percent) const
{
    if (percent >= 90.0) return QColor(245, 10, 0);  // red
    else if (percent >= 80.0) return QColor(255, 191, 0);  // amber
    else return QColor(0, 150, 0);  // green
}
