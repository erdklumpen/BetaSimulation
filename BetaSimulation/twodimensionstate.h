#ifndef TWODIMENSIONSTATE_H
#define TWODIMENSIONSTATE_H

#include <QString>
#include <QVector>

#include "onedimensionstate.h"
#include "abstractstate.h"

class TwoDimensionState : public AbstractState
{
public:
    TwoDimensionState(int xLength, int yLength);
    ~TwoDimensionState();

    float density(int x);
    QString toString();

    int size();
    int xSize();
    int ySize();

    void setAtEigen(int xPos, int yPos, int value);
    void setAtObserved(int xPos, int yPos, int value);
    void setAt(int xPost, int yPos, int value);

    int atEigen(int xPos, int yPos);
    int atObserved(int xPos, int yPos);

private:
    QVector< OneDimensionState* >* m_eigenData;
    QVector< OneDimensionState* >* m_observedData;
};

#endif // TWODIMENSIONSTATE_H
