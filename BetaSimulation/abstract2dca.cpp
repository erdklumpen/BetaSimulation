#include "abstract2dca.h"

Abstract2DCA::Abstract2DCA(float alpha, float beta, int xLength, int yLength) : AbstractCA(alpha, beta)
{
    m_state = new TwoDimensionState(xLength, yLength);
    setDimensions(2);

    initCA();
}

void Abstract2DCA::initCA()
{
    for(int i = 0; i < m_state->ySize(); ++i)
    {
        for(int j = 0; j < m_state->xSize(); ++j)
        {
            double number = randomNumber();

            if(number > 0.5)
                m_state->setAt(j, i, 1);
            else
                m_state->setAt(j, i, 0);
        }
    }
}

void Abstract2DCA::run(int steps)
{
    if(m_history->getActivity().empty())
    {
        m_history->appendDensity("1", density(1));
        m_history->appendActivity(activity());
    }

    for(int i = 0; i < steps; ++i)
    {
        m_workState = new TwoDimensionState(m_state->xSize(), m_state->ySize());

        for(int j = 0; j < m_state->ySize(); ++j)
        {
            for(int k = 0; k < m_state->xSize(); ++k)
            {
                QVector<int> neighbours = neighbourhood(QPoint(k, j));
                int newState = rule(neighbours, QPoint(k, j));

                //qDebug() << neighbours << " " << newState;

                update(QPoint(k, j), newState);
            }
        }

        delete m_state;
        m_state = m_workState;

//        qDebug() << density(1);
        m_history->appendDensity("1", density(1));
        m_history->appendActivity(activity());
    }
}

float Abstract2DCA::activity()
{
    float instable = 0;

    for(int i = 0; i < m_state->ySize(); ++i)
    {
        for(int j = 0; j < m_state->xSize(); ++j)
        {
            QVector<int> neighbourhood = eigenNeighbourhood(QPoint(j, i));
            int newState = rule(neighbourhood, QPoint(j, i));

            if(newState != m_state->atEigen(j, i))
                instable++;
        }
    }

    instable /= m_state->size();

    return instable;
}

void Abstract2DCA::update(QPoint i, int newState)
{
    double randAlpha = randomNumber();

    if(randAlpha <= alpha())
    {
        setAt(i, newState);
    }
    else
    {
        setAt(i, m_state->atEigen(i.x(), i.y()));
    }
}

void Abstract2DCA::setAt(QPoint i, int newState)
{
    double randBeta = randomNumber();

    m_workState->setAtEigen(i.x(), i.y(), newState);

    if(randBeta <= beta())
    {
        m_workState->setAtObserved(i.x(), i.y(), newState);
    }
    else
    {
        m_workState->setAtObserved(i.x(), i.y(), m_state->atObserved(i.x(), i.y()));
    }
}
