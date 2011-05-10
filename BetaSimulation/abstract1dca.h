#ifndef ABSTRACT1DCA_H
#define ABSTRACT1DCA_H

#include "onedimensionstate.h"
#include "abstractca.h"

#include <ctime>

class Abstract1DCA : public AbstractCA
{
public:
    Abstract1DCA(float alpha, float beta, int length);

    void setState(OneDimensionState *state) {m_state  = state;}
    OneDimensionState* state() {return m_state;}

protected:
    OneDimensionState* m_state;
    OneDimensionState* m_workState;
};

#endif // ABSTRACT1DCA_H
