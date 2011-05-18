#include "experimentwizard.h"
#include "ui_experimentwizard.h"

ExperimentWizard::ExperimentWizard(QList< QPair<QString, QWidget*> > automatsList, QWidget *parent) :
    QWizard(parent),
    ui(new Ui::ExperimentWizard)
{
    m_automats = automatsList;

    ui->setupUi(this);
    ui->automats->addItem("");
    for(int i = 0; i < m_automats.size(); ++i)
        ui->automats->addItem(m_automats[i].first);
}

ExperimentWizard::~ExperimentWizard()
{
    delete ui;
}

void ExperimentWizard::changeEvent(QEvent *e)
{
    QWizard::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ExperimentWizard::on_automats_currentIndexChanged(int index)
{
    for(int i = 0; i < m_automats.size(); ++i)
    {
        if(ui->automats->currentText() == m_automats[i].first)
        {
            QHBoxLayout *layout = new QHBoxLayout();
            layout->addWidget(m_automats[i].second);
            ui->settings->setLayout(layout);
        }
    }
}

AbstractCA* getCA()
{

}
