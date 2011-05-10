#include "eca50.h"

ECA50::ECA50(float alpha, float beta, int length) : Abstract1DCA(alpha, beta, length)
{
}

QVector<bool> ECA50::neighbourhood(int i)
{
    QVector<bool> neighbours(2);

    neighbours[0] = m_state->atObserved(i-1);
    neighbours[1] = m_state->atObserved(i+1);

    return neighbours;
}

void ECA50::rule()
{
    m_workState = new OneDimensionState(m_state->size());

    for(int i = 0; i < m_state->size(); ++i)
    {
        QVector<bool> neighbours = neighbourhood(i);

        if(!m_state->atEigen(i) && (
           (!neighbours[0] && neighbours[1]) ||
           (neighbours[0] && !neighbours[1]) ||
           (neighbours[0] && neighbours[1])
          ))
        {
            m_workState->setOneEigen(i);
            m_workState->setOneObserved(i);
        }

        else
        {
            m_workState->setZeroEigen(i);
            m_workState->setZeroObserved(i);
        }
    }

    OneDimensionState *k = m_workState;
    m_workState = m_state;
    m_state = k;
}
