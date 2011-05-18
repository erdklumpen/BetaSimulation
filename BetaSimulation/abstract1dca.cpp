#include "abstract1dca.h"

Abstract1DCA::Abstract1DCA(float alpha, float beta, int length) : AbstractCA(alpha, beta)
{
    m_state = new OneDimensionState(length);

    for(int i = 0; i < length; ++i)
    {
        double number = randomNumber();

        if(number > 0.5)
            m_state->setOne(i);
    }
}

void Abstract1DCA::run(int steps)
{
    for(int i = 0; i < steps; ++i)
    {
        m_workState = new OneDimensionState(m_state->size());

        for(int i = 0; i < m_state->size(); ++i)
        {
            QVector<bool> neighbours = neighbourhood(i);
//            qDebug() << neighbours;
            bool newState = rule(neighbours, i);
//            qDebug() << newState;
            update(i, newState);
        }

        OneDimensionState *k = m_workState;
        m_workState = m_state;
        m_state = k;
    }
}

float Abstract1DCA::activity()
{
    float instable = 0;

    for(int i = 0; i < m_state->size(); ++i)
    {
        QVector<bool> neighbourhood = eigenNeighbourhood(i);
        bool newState = rule(neighbourhood, i);

        if(newState != m_state->atEigen(i))
            instable++;
    }

    return instable;
}
