
#ifndef STIMFIGURE_H
#define STIMFIGURE_H

#include <QWidget>
#include "abstractfigure.h"

class StimFigure : public AbstractFigure
{
    Q_OBJECT
public:
    explicit StimFigure(StimParameters* stimParameters, QWidget *parent = 0);

    void uniqueRedraw(QPainter &painter) override;

public slots:
    void updateEnableAmpSettle(bool enabled);
    void updateMaintainAmpSettle(bool maintain);
    void updateEnableChargeRecovery(bool enabled);
    void highlightSecondPhaseDuration(bool highlight);
    void highlightInterphaseDelay(bool highlight);
    void highlightFirstPhaseAmplitude(bool highlight);
    void highlightSecondPhaseAmplitude(bool highlight);
    void highlightPreStimAmpSettle(bool highlight);
    void highlightPostStimAmpSettle(bool highlight);
    void highlightPostStimChargeRecovOn(bool highlight);
    void highlightPostStimChargeRecovOff(bool highlight);

private:
    bool localEnableAmpSettle;
    bool localMaintainAmpSettle;
    bool localEnableChargeRecovery;

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
};

#endif // STIMFIGURE_H
