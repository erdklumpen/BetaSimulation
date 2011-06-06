#include "Majority.h"

Majority::Majority(float alpha, float  beta, int xLength, int yLength) : Abstract2DCA(alpha, beta, xLength, yLength)
{
}

QVector<int> Majority::neighbourhood(QPoint i)
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

QVector<int> Majority::eigenNeighbourhood(QPoint i)
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

int Majority::rule(QVector<int> neighbours, QPoint self)
{
    int sum = 0;

    for(int i = 0; i < neighbours.size(); ++i)
    {
        if(neighbours.at(i) == 1)
            ++sum;
    }

    if(m_state->atEigen(self.x(), self.y()) == 1)
        ++sum;

    if(sum > 4)
        return 1;

    return 0;
}
