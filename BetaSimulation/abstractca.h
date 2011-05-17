#ifndef ABSTRACTCA_H
#define ABSTRACTCA_H

#include "abstractstate.h"

#include <boost/random.hpp>
#include <ctime>

#include <QVector>

typedef boost::mt19937 MersenneTwister;
typedef boost::uniform_real<> Distribution;
typedef boost::variate_generator<MersenneTwister&, boost::uniform_real<> > Generator;

class AbstractCA
{
public:
    AbstractCA(float alpha, float beta);

    virtual void run(int steps) =0;

    void initAlpha(float probability) {m_alpha = probability;}
    void initBeta(float probability) {m_beta = probability;}

    float alpha() {return m_alpha;}
    float beta() {return m_beta;}
    float randomNumber() {return (*m_gen)();}

    virtual int activity() =0;
    virtual int density() =0;

protected:
    virtual QVector<bool> neighbourhood(int i) =0;
    virtual QVector<bool> eigenNeighbourhood(int i) =0;
    virtual bool rule(QVector<bool> neighbours, int self) =0;
    virtual void update(int i, bool newState) =0;

private:
    float m_alpha;
    float m_beta;
    MersenneTwister m_rng;
    Distribution m_dist;
    Generator* m_gen;

};

#endif // ABSTRACTCA_H
