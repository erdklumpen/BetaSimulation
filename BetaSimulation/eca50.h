#ifndef ECA50_H
#define ECA50_H

#include "abstract1dca.h"
#include "onedimensionstate.h"

#include <QDebug>

class ECA50 : public Abstract1DCA
{
public:
    ECA50(float alpha, float beta, int length);
    void rule();
    QVector<bool> neighbourhood(int i);
};

#endif // ECA50_H
