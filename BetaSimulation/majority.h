#ifndef MAJORITY_H
#define MAJORITY_H

#include "abstract2dca.h"

class Majority : public Abstract2DCA
{
public:
    Majority(float alpha, float  beta, int xLength, int yLength);

    QVector<int> neighbourhood(QPoint i);
    QVector<int> eigenNeighbourhood(QPoint i);
    int rule(QVector<int> neighbours, QPoint self);
};

#endif // MAJORITY_H
