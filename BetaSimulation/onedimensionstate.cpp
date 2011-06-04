#include "onedimensionstate.h"

OneDimensionState::OneDimensionState(int size)
{
    m_eigenData = new QVector<int>(size);
    m_observedData = new QVector<int>(size);
}

OneDimensionState::~OneDimensionState()
{
    delete m_eigenData;
    delete m_observedData;
}

void OneDimensionState::setAtEigen(int index, int value)
{
    m_eigenData->replace(index, value);
}

void OneDimensionState::setAtObserved(int index, int value)
{
    m_observedData->replace(index, value);
}

void OneDimensionState::setAt(int index, int value)
{
    setAtEigen(index, value);
    setAtObserved(index, value);
}

int OneDimensionState::atEigen(int index)
{
    if(index < 0)
        return m_eigenData->at(size() - 1);

    if(index >= size())
        return m_eigenData->at(0);

    return m_eigenData->at(index);
}

int OneDimensionState::atObserved(int index)
{
    if(index < 0)
        return m_observedData->at(size() - 1);

    if(index >= size())
        return m_observedData->at(0);

    return m_observedData->at(index);
}

QString OneDimensionState::toString()
{
    QString out;

    for(int i = 0; i < m_eigenData->size(); ++i)
    {
        out += QString("%1").arg(m_eigenData->at(i));
    }


    return out;
}

float OneDimensionState::density(int x)
{
    return ((float)(m_eigenData->count(x)) / size());
}
