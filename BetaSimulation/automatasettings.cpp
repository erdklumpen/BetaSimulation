#include "automatasettings.h"
#include "ui_automatasettings.h"

AutomataSettings::AutomataSettings(QWidget *parent, double alpha, double beta) :
    QDialog(parent),
    ui(new Ui::AutomataSettings)
{
    ui->setupUi(this);

    ui->alpha->setValue(alpha);
    ui->beta->setValue(beta);
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
