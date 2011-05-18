#ifndef ABSTRACTSTATE_H
#define ABSTRACTSTATE_H

#include <QMap>
#include <QString>

class AbstractState
{
public:
    AbstractState();
    virtual QString toString() =0;
    virtual float density() =0;
};

#endif // ABSTRACTSTATE_H
