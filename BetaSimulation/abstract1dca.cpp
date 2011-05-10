#include "abstract1dca.h"

Abstract1DCA::Abstract1DCA(float alpha, float beta, int length) : AbstractCA(alpha, beta)
{
    m_state = new OneDimensionState(length);

    typedef boost::mt19937 RandomNumberGen;
    RandomNumberGen rng(time(0));
    boost::uniform_real<> zeroToOne(0, 1);
    boost::variate_generator< RandomNumberGen&, boost::uniform_real<> > gen(rng, zeroToOne);

    for(int i = 0; i < length; ++i)
    {
        double number = gen();

        if(number > 0.5)
            m_state->setOne(i);
    }
}
