#ifndef MINORITY_H
#define MINORITY_H

#include "abstract2dca.h"

class Minority : public Abstract2DCA
{
public:
    Minority(float alpha, float  beta, int xLength, int yLength);

    QVector<int> neighbourhood(QPoint i);
    QVector<int> eigenNeighbourhood(QPoint i);
    int rule(QVector<int> neighbours, QPoint self);
};

#endif // MINORITY_H
