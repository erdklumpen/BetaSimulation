#include "abstractca.h"

AbstractCA::AbstractCA(float alpha, float beta)
{
    initAlpha(alpha);
    initBeta(beta);

    m_rng();
    m_rng.seed(time(0));
    m_gen = new Generator(m_rng, m_dist);

    m_history = new CAHistory();
}
