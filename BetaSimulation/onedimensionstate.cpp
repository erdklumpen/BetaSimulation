#include "onedimensionstate.h"

OneDimensionState::OneDimensionState(int size)
{
    m_eigenData = new QBitArray(size);
    m_observedData = new QBitArray(size);
}

void OneDimensionState::setOneEigen(int i)
{
    m_eigenData->setBit(i);
}

void OneDimensionState::setZeroEigen(int i)
{
    m_eigenData->clearBit(i);
}

bool OneDimensionState::atEigen(int i)
{
    if(i < 0)
        return m_eigenData->testBit(size() - 1);

    if(i >= size())
        return m_eigenData->testBit(0);

    return m_eigenData->testBit(i);
}


void OneDimensionState::setOneObserved(int i)
{
    m_observedData->setBit(i);
}

void OneDimensionState::setZeroObserved(int i)
{
    m_observedData->clearBit(i);
}

bool OneDimensionState::atObserved(int i)
{
    if(i < 0)
        return m_observedData->testBit(size() - 1);

    if(i >= size())
        return m_observedData->testBit(0);

    return m_observedData->testBit(i);
}

QPair<bool, bool> OneDimensionState::at(int i)
{
    return QPair<bool, bool>(m_eigenData->testBit(i), m_observedData->testBit(i));
}

void OneDimensionState::setOne(int i)
{
    setOneEigen(i);
    setOneObserved(i);
}

void OneDimensionState::setZero(int i)
{
    setZeroEigen(i);
    setZeroObserved(i);
}

QString OneDimensionState::toString()
{
    QString out;

    for(int i = 0; i < m_eigenData->size(); ++i)
    {
        if(atEigen(i))
            out += "true ";
        else
            out += "false ";
    }


    return out;
}
