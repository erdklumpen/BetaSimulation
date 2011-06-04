#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <QVector>

#include "abstract2dca.h"

class GameOfLife : public Abstract2DCA
{
public:
    GameOfLife(float alpha, float beta, int xSize, int ySize);

    QVector<int> neighbourhood(QPoint i);
    QVector<int> eigenNeighbourhood(QPoint i);
    int rule(QVector<int> neighbours, QPoint self);
};

#endif // GAMEOFLIFE_H
