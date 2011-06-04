#ifndef ECA_H
#define ECA_H

#include "abstract1dca.h"
#include <QList>

#include <QDebug>

class ECA;

typedef int (ECA::*Clause)(QVector<int> neighbours, int self);

class ECA : public Abstract1DCA
{
public:
    ECA(float alpha, float beta, int length, int ecaNumber);

private:
    QVector<int> neighbourhood(QPoint i);
    QVector<int> eigenNeighbourhood(QPoint i);
    int rule(QVector<int> neighbours, QPoint self);

    int m_ecaNumber;

    QList<Clause>* m_usedClauses;
    Clause m_clauseArray[8];

    int clause000(QVector<int> neighbours, int self);
    int clause001(QVector<int> neighbours, int self);
    int clause010(QVector<int> neighbours, int self);
    int clause011(QVector<int> neighbours, int self);

    int clause100(QVector<int> neighbours, int self);
    int clause101(QVector<int> neighbours, int self);
    int clause110(QVector<int> neighbours, int self);
    int clause111(QVector<int> neighbours, int self);
};

#endif // ECA_H
