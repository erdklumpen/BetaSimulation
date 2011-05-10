#include "abstractca.h"

AbstractCA::AbstractCA(float alpha, float beta)
{
    initAlpha(alpha);
    initBeta(beta);
}

void AbstractCA::run(int steps)
{
    for(int i = 0; i < steps; ++i)
    {
        rule();
    }
}
