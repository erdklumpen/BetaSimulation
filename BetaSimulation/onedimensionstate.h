#ifndef ONEDIMENSIONSTATE_H
#define ONEDIMENSIONSTATE_H

#include "abstractstate.h"
#include <QVector>
#include <QPair>

#include <QDebug>

class OneDimensionState : public AbstractState
{
public:
    OneDimensionState(int size);
    ~OneDimensionState();

    void setAtEigen(int index, int value);
    void setAtObserved(int index, int value);
    void setAt(int index, int value);

    int atEigen(int index);
    int atObserved(int index);

    int size() {return m_eigenData->size();}

    QString toString();
    float density(int x);

private:
    QVector<int>* m_eigenData;
    QVector<int>* m_observedData;
};

#endif // ONEDIMENSIONSTATE_H
