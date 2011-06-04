#ifndef ABSTRACTCA_H
#define ABSTRACTCA_H

#include "abstractstate.h"
#include "cahistory.h"

#include <boost/random.hpp>
#include <ctime>

#include <QVector>
#include <QPoint>

typedef boost::mt19937 MersenneTwister;
typedef boost::uniform_real<> Distribution;
typedef boost::variate_generator<MersenneTwister&, boost::uniform_real<> > Generator;

class AbstractCA
{
public:
    AbstractCA(float alpha, float beta);

    virtual void run(int steps) =0;

    virtual void initCA() =0;
    void initAlpha(float probability) {m_alpha = probability;}
    void initBeta(float probability) {m_beta = probability;}

    float alpha() {return m_alpha;}
    float beta() {return m_beta;}
    float randomNumber() {return (*m_gen)();}

    int dimensions() {return m_dimensions;}

    CAHistory* history() {return m_history;}
    void initHistory() {m_history = new CAHistory();}

    virtual float activity() =0;
    virtual float density(int x) =0;

protected:
    virtual QVector<int> neighbourhood(QPoint i) =0;
    virtual QVector<int> eigenNeighbourhood(QPoint i) =0;
    virtual int rule(QVector<int> neighbours, QPoint self) =0;
    virtual void update(QPoint i, int newState) =0;

    void setDimensions(int dimensions) {m_dimensions =dimensions;}
    CAHistory *m_history;

private:
    int m_dimensions;
    float m_alpha;
    float m_beta;
    MersenneTwister m_rng;
    Distribution m_dist;
    Generator* m_gen;
};

#endif // ABSTRACTCA_H
