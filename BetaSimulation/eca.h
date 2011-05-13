#ifndef ECA_H
#define ECA_H

#include "abstract1dca.h"
#include <QList>

#include <QDebug>

class ECA;

typedef bool (ECA::*Clause)(QVector<bool> neighbours, int self);

class ECA : public Abstract1DCA
{
public:
    ECA(float alpha, float beta, int length, int ecaNumber);

private:
    QVector<bool> neighbourhood(int i);
    bool rule(QVector<bool> neighbours, int self);
    void update(int i, bool newState);

    int m_ecaNumber;

    QList<Clause>* m_usedClauses;
    Clause m_clauseArray[8];

    bool clause000(QVector<bool> neighbours, int self);
    bool clause001(QVector<bool> neighbours, int self);
    bool clause010(QVector<bool> neighbours, int self);
    bool clause011(QVector<bool> neighbours, int self);

    bool clause100(QVector<bool> neighbours, int self);
    bool clause101(QVector<bool> neighbours, int self);
    bool clause110(QVector<bool> neighbours, int self);
    bool clause111(QVector<bool> neighbours, int self);
};

#endif // ECA_H
