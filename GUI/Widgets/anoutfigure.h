
#ifndef ANOUTFIGURE_H
#define ANOUTFIGURE_H

#include <QWidget>
#include "stimparameters.h"
#include "abstractfigure.h"

class AnOutFigure : public AbstractFigure
{
    Q_OBJECT
public:
    explicit AnOutFigure(StimParameters* stimParameters, QWidget *parent = nullptr);
    void uniqueRedraw(QPainter &painter);

public slots:
    void updateMonophasicAndPositive(bool logicValue);
    void highlightSecondPhaseDuration(bool highlight);
    void highlightInterphaseDelay(bool highlight);
    void highlightFirstPhaseAmplitude(bool highlight);
    void highlightSecondPhaseAmplitude(bool highlight);
    void highlightBaselineVoltage(bool highlight);

private:
    QSize sizeHint() const;
    QSize minimumSizeHint() const;
    bool localMonophasicAndPositive;
    QColor oldColor;
};

#endif // ANOUTFIGURE_H
