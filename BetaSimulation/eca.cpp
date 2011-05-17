#include "eca.h"

ECA::ECA(float alpha, float beta, int length, int ecaNumber) : Abstract1DCA(alpha, beta, length)
{
    m_ecaNumber = ecaNumber;
    m_usedClauses = new QList<Clause>();

    m_clauseArray[0] = &ECA::clause000;
    m_clauseArray[1] = &ECA::clause001;
    m_clauseArray[2] = &ECA::clause010;
    m_clauseArray[3] = &ECA::clause011;

    m_clauseArray[4] = &ECA::clause100;
    m_clauseArray[5] = &ECA::clause101;
    m_clauseArray[6] = &ECA::clause110;
    m_clauseArray[7] = &ECA::clause111;

    for(int i = 0; ecaNumber > 0; ++i)
    {
        int bit = ecaNumber % 2;
        ecaNumber = ecaNumber >> 1;

        qDebug() << bit;

        if(bit == 1)
            m_usedClauses->append(m_clauseArray[i]);
    }
}

QVector<bool> ECA::neighbourhood(int i)
{
    QVector<bool> neighbours(2);

    neighbours[0] = m_state->atObserved(i-1);
    neighbours[1] = m_state->atObserved(i+1);
    return neighbours;
}

QVector<bool> ECA::eigenNeighbourhood(int i)
{
    QVector<bool> neighbours(2);

    neighbours[0] = m_state->atEigen(i-1);
    neighbours[1] = m_state->atEigen(i+1);
    return neighbours;
}

bool ECA::rule(QVector<bool> neighbours, int self)
{
    for(int i = 0; i < m_usedClauses->length(); ++i)
    {
        Clause clause = m_usedClauses->at(i);
        bool result = (this->*clause)(neighbours, self);

        if(result == 1)
            return true;
    }

    return false;
}

void ECA::update(int i, bool newState)
{
    double randAlpha = randomNumber();
    double randBeta = randomNumber();

    if(randAlpha <= alpha())
    {
        if(newState)
        {
            m_workState->setOneEigen(i);

            if(randBeta <= beta())
                m_workState->setOneObserved(i);
        }
        else
        {
            m_workState->setZeroEigen(i);

            if(randBeta <= beta())
                m_workState->setZeroObserved(i);
        }
    }
}

// 000
bool ECA::clause000(QVector<bool> neighbours, int self)
{
    if(!neighbours[0] && !m_state->atEigen(self) && !neighbours[1])
        return true;

    else
        return false;
}

// 001
bool ECA::clause001(QVector<bool> neighbours, int self)
{
    if(!neighbours[0] && !m_state->atEigen(self) && neighbours[1])
        return true;

    else
        return false;

}

// 010
bool ECA::clause010(QVector<bool> neighbours, int self)
{
    if(!neighbours[0] && m_state->atEigen(self) && !neighbours[1])
        return true;

    else
        return false;

}

// 011
bool ECA::clause011(QVector<bool> neighbours, int self)
{
    if(!neighbours[0] && m_state->atEigen(self) && neighbours[1])
        return true;

    else
        return false;

}

//100
bool ECA::clause100(QVector<bool> neighbours, int self)
{
    if(neighbours[0] && !m_state->atEigen(self) && !neighbours[1])
        return true;

    else
        return false;

}

// 101
bool ECA::clause101(QVector<bool> neighbours, int self)
{
    if(neighbours[0] && !m_state->atEigen(self) && neighbours[1])
        return true;

    else
        return false;

}
// 110
bool ECA::clause110(QVector<bool> neighbours, int self)
{
    if(neighbours[0] && m_state->atEigen(self) && !neighbours[1])
        return true;

    else
        return false;

}

// 111
bool ECA::clause111(QVector<bool> neighbours, int self)
{
    if(neighbours[0] && m_state->atEigen(self) && neighbours[1])
        return true;

    else
        return false;

}
