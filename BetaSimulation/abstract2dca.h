#ifndef ABSTRACT2DCA_H
#define ABSTRACT2DCA_H

#include "abstractca.h"
#include "twodimensionstate.h"

class Abstract2DCA : public AbstractCA
{
public:
    Abstract2DCA(float alpha, float beta, int xLength, int yLength);

    void run(int steps);

    void initCA();

    void setState(TwoDimensionState *state) {m_state  = state;}
    TwoDimensionState* state() {return m_state;}

    float activity();
    float density(int x) {return m_state->density(x);}

protected:
    TwoDimensionState* m_state;
    TwoDimensionState* m_workState;

private:
    void update(QPoint i, int newState);
    void setAt(QPoint i, int newState);
};

#endif // ABSTRACT2DCA_H
