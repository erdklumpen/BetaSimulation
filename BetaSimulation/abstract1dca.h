#ifndef ABSTRACT1DCA_H
#define ABSTRACT1DCA_H

#include "onedimensionstate.h"
#include "abstractca.h"

#include <QDebug>

class Abstract1DCA : public AbstractCA
{
public:
    Abstract1DCA(float alpha, float beta, int length);

    void run(int steps);

    void initCA();

    void setState(OneDimensionState *state) {m_state  = state;}
    OneDimensionState* state() {return m_state;}

    float activity();
    float density(int x) {return m_state->density(x);}

protected:
    OneDimensionState* m_state;
    OneDimensionState* m_workState;

private:
    void update(QPoint i, int newState);
    void setAt(int i, int newState);
};

#endif // ABSTRACT1DCA_H
