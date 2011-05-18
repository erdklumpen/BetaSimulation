#include "ecasettings.h"
#include "ui_ecasettings.h"

ECASettings::ECASettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ECASettings)
{
    ui->setupUi(this);
}

ECASettings::~ECASettings()
{
    delete ui;
}

void ECASettings::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

QVector<int> ECASettings::settings()
{
    QVector<int> settingsVec;

    settingsVec << ui->number->value() << ui->length->value() << ui->steps->value();

    return settingsVec;
}
