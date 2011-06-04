#include "abstract1dca.h"

Abstract1DCA::Abstract1DCA(float alpha, float beta, int length) : AbstractCA(alpha, beta)
{
    m_state = new OneDimensionState(length);
    setDimensions(1);

    initCA();
}

void Abstract1DCA::run(int steps)
{
    for(int i = 0; i < steps; ++i)
    {
        m_workState = new OneDimensionState(m_state->size());

        for(int j = 0; j < m_state->size(); ++j)
        {
            QVector<int> neighbours = neighbourhood(QPoint(j, 0));
//            qDebug() << neighbours;
            int newState = rule(neighbours, QPoint(j, 0));
//            qDebug() << newState;
            update(QPoint(j, 0) , newState);
        }

        delete m_state;
        m_state = m_workState;

        m_history->appendDensity("1", density(1));
        m_history->appendActivity(activity());
    }
}

void Abstract1DCA::initCA()
{
    for(int i = 0; i < m_state->size(); ++i)
    {
        double number = randomNumber();

        if(number > 0.5)
            m_state->setAt(i, 1);
        else
            m_state->setAt(i, 0);
    }
}

float Abstract1DCA::activity()
{
    float instable = 0;

    for(int i = 0; i < m_state->size(); ++i)
    {
        QVector<int> neighbourhood = eigenNeighbourhood(QPoint(i, 0));
        int newState = rule(neighbourhood, QPoint(i,0));

        if(newState != m_state->atEigen(i))
            instable++;
    }

    return instable;
}

void Abstract1DCA::update(QPoint i, int newState)
{
    double randAlpha = randomNumber();

    if(randAlpha <= alpha())
    {
        setAt(i.x(), newState);
    }
    else
    {
        setAt(i.x(), m_state->atEigen(i.x()));
    }
}

void Abstract1DCA::setAt(int i, int newState)
{
    double randBeta = randomNumber();

    m_workState->setAtEigen(i, newState);

    if(randBeta <= beta())
    {
        m_workState->setAtObserved(i, newState);
    }
    else
    {
        m_workState->setAtObserved(i, m_state->atObserved(i));
    }
}
