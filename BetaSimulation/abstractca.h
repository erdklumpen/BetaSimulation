#ifndef ABSTRACTCA_H
#define ABSTRACTCA_H

#include "abstractstate.h"

class AbstractCA
{
public:
    AbstractCA();

private:
    AbstractState *state;
};

#endif // ABSTRACTCA_H
