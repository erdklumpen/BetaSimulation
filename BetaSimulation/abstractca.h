#ifndef ABSTRACTCA_H
#define ABSTRACTCA_H

#include "abstractstate.h"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/uniform_real.hpp>
#include <QVector>

class AbstractCA
{
public:
    AbstractCA(float alpha, float beta);

    void run(int steps);
    virtual void rule() =0;
    virtual QVector<bool> neighbourhood(int i) =0;

    void initAlpha(float probability) {m_alpha = probability;}
    void initBeta(float probability) {m_beta = probability;}

    float alpha() {return m_alpha;}
    float beta() {return m_beta;}

private:
    float m_alpha;
    float m_beta;
};

#endif // ABSTRACTCA_H
