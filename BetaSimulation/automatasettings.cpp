#include "automatasettings.h"
#include "ui_automatasettings.h"

AutomataSettings::AutomataSettings(QWidget *parent, double alpha, double beta, int steps, int xLength, int yLength) :
    QDialog(parent),
    ui(new Ui::AutomataSettings)
{
    ui->setupUi(this);

    ui->alpha->setValue(alpha);
    ui->beta->setValue(beta);

    ui->steps->setValue(steps);

    ui->xLength->setValue(xLength);
    ui->yLength->setValue(yLength);
}

AutomataSettings::~AutomataSettings()
{
    delete ui;
}

void AutomataSettings::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

double AutomataSettings::alpha()
{
    return ui->alpha->value();
}

double AutomataSettings::beta()
{
    return ui->beta->value();
}

int AutomataSettings::steps()
{
    return ui->steps->value();
}

int AutomataSettings::xLength()
{
    return ui->xLength->value();
}

int AutomataSettings::yLength()
{
    return ui->yLength->value();
}
