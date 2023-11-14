
#ifndef DIGFIGURE_H
#define DIGFIGURE_H

#include <QWidget>
#include "stimparameters.h"
#include "abstractfigure.h"

class DigFigure : public AbstractFigure
{
    Q_OBJECT
public:
    explicit DigFigure(StimParameters* stimParameters, QWidget* parent = nullptr);
    void uniqueRedraw(QPainter &painter);

private:
    QSize sizeHint() const;
    QSize minimumSizeHint() const;
};


#endif // DIGFIGURE_H
