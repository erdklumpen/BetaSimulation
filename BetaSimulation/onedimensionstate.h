#ifndef ONEDIMENSIONSTATE_H
#define ONEDIMENSIONSTATE_H

#include "abstractstate.h"
#include <QBitArray>
#include <QPair>

class OneDimensionState : public AbstractState
{
public:
    OneDimensionState(int size);

    void setOneEigen(int i);
    void setZeroEigen(int i);

    bool atEigen(int i);

    void setOneObserved(int i);
    void setZeroObserved(int i);

    bool atObserved(int i);

    QPair<bool, bool> at(int i);

    void setOne(int i);
    void setZero(int i);

    int size() {return m_eigenData->size();}

    QString toString();
    int density();

private:
    QBitArray* m_eigenData;
    QBitArray* m_observedData;
};

#endif // ONEDIMENSIONSTATE_H
