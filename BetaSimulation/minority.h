#ifndef MINORITY_H
#define MINORITY_H

#include "abstract2dca.h"

class Minority : public Abstract2DCA
{
public:
    Minority(float alpha, float  beta, int xLength, int yLength);

    QVector<QPointF> neighbourhood(QPoint i);
    QVector<QPointF> eigenNeighbourhood(QPoint i);
    int rule(QVector<QPointF> neighbours, QPoint self);
};

#endif // MINORITY_H
