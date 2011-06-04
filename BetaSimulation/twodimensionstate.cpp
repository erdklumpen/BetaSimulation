#include "twodimensionstate.h"

TwoDimensionState::TwoDimensionState(int xLength, int yLength)
{
    m_eigenData = new QVector< OneDimensionState* >(yLength);
    m_observedData = new QVector< OneDimensionState* >(yLength);

    for(int i = 0; i < yLength; ++i)
    {
        m_eigenData->replace(i, new OneDimensionState(xLength));
        m_observedData->replace(i, new OneDimensionState(xLength));
    }
}

TwoDimensionState::~TwoDimensionState()
{
    delete m_eigenData;
    delete m_observedData;
}

float TwoDimensionState::density(int x)
{
    int sum;

    for(int i = 0; i < xSize(); ++i)
        sum += m_eigenData->at(i)->density(x);

    return ((float)(sum) / ySize());
}

QString TwoDimensionState::toString()
{
    return "";
}

int TwoDimensionState::size()
{
    return ySize() * xSize();
}

int TwoDimensionState::xSize()
{
    return m_eigenData->at(0)->size();
}

int TwoDimensionState::ySize()
{
    return m_eigenData->size();
}

void TwoDimensionState::setAtEigen(int xPos, int yPos, int value)
{
    m_eigenData->at(yPos)->setAtEigen(xPos, value);
}

void TwoDimensionState::setAtObserved(int xPos, int yPos, int value)
{
    m_observedData->at(yPos)->setAtObserved(xPos, value);
}

void TwoDimensionState::setAt(int xPos, int yPos, int value)
{
    setAtEigen(xPos, yPos, value);
    setAtObserved(xPos, yPos, value);
}

int TwoDimensionState::atEigen(int xPos, int yPos)
{
    if(yPos < 0)
        return m_eigenData->at(ySize() - 1)->atEigen(xPos);

    if(yPos >= ySize())
        return m_eigenData->at(0)->atEigen(xPos);

    return m_eigenData->at(yPos)->atEigen(xPos);
}

int TwoDimensionState::atObserved(int xPos, int yPos)
{
    if(yPos < 0)
        return m_observedData->at(ySize() - 1)->atObserved(xPos);

    if(yPos >= ySize())
        return m_observedData->at(0)->atObserved(xPos);

    return m_observedData->at(yPos)->atObserved(xPos);
}
