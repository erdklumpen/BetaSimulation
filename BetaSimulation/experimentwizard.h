#ifndef EXPERIMENTWIZARD_H
#define EXPERIMENTWIZARD_H

#include "abstractca.h"

#include <QWizard>
#include <QList>
#include <QWidget>
#include <QString>
#include <QHBoxLayout>

namespace Ui {
    class ExperimentWizard;
}

class ExperimentWizard : public QWizard
{
    Q_OBJECT

public:
    explicit ExperimentWizard(QList< QPair<QString, QWidget*> > automatsList, QWidget *parent = 0);
    ~ExperimentWizard();

    AbstractCA* getCA();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ExperimentWizard *ui;

    QList< QPair<QString, QWidget*> > m_automats;

private slots:
    void on_automats_currentIndexChanged(int index);
};

#endif // EXPERIMENTWIZARD_H
