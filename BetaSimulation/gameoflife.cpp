#include "gameoflife.h"

GameOfLife::GameOfLife(float alpha, float beta, int xSize, int ySize) : Abstract2DCA(alpha, beta, xSize, ySize)
{
}

QVector<int> GameOfLife::neighbourhood(QPoint i)
{
    QVector<int> neighbours(8);

    neighbours[0] = m_state->atObserved(i.x() - 1, i.y() - 1);
    neighbours[1] = m_state->atObserved(i.x(), i.y() - 1);
    neighbours[2] = m_state->atObserved(i.x() + 1, i.y() - 1);

    neighbours[3] = m_state->atObserved(i.x() - 1, i.y());
    neighbours[4] = m_state->atObserved(i.x() + 1, i.y());

    neighbours[5] = m_state->atObserved(i.x() - 1, i.y() + 1);
    neighbours[6] = m_state->atObserved(i.x(), i.y() + 1);
    neighbours[7] = m_state->atObserved(i.x() + 1, i.y() + 1);

    return neighbours;
}

QVector<int> GameOfLife::eigenNeighbourhood(QPoint i)
{
    QVector<int> neighbours(8);

    neighbours[0] = m_state->atEigen(i.x() - 1, i.y() - 1);
    neighbours[1] = m_state->atEigen(i.x(), i.y() - 1);
    neighbours[2] = m_state->atEigen(i.x() + 1, i.y() - 1);

    neighbours[3] = m_state->atEigen(i.x() - 1, i.y());
    neighbours[4] = m_state->atEigen(i.x() + 1, i.y());

    neighbours[5] = m_state->atEigen(i.x() - 1, i.y() + 1);
    neighbours[6] = m_state->atEigen(i.x(), i.y() + 1);
    neighbours[7] = m_state->atEigen(i.x() + 1, i.y() + 1);

    return neighbours;
}

int GameOfLife::rule(QVector<int> neighbours, QPoint self)
{
    int sum = 0;

    int selfState = m_state->atEigen(self.x(), self.y());

    for(int i = 0; i < neighbours.size(); ++i)
    {
        if(neighbours.at(i) == 1)
            sum += 1;
    }

    if(selfState == 0 && sum == 3)
        return 1;

    if(selfState == 1 && (sum == 2 || sum == 3))
        return 1;

    return 0;
}
