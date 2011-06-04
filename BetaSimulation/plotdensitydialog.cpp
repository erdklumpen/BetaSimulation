#include "plotdensitydialog.h"
#include "ui_plotdensitydialog.h"

PlotDensityDialog::PlotDensityDialog(QStringList densities, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlotDensityDialog)
{
    ui->setupUi(this);
    for(int i = 0; i < densities.size(); ++i)
    {
        QListWidgetItem* item = new QListWidgetItem(QString("%1-Dichte").arg(densities.at(i)));
        item->setData(Qt::UserRole, densities.at(i));
        ui->listWidget->insertItem(i, item);
    }
}

PlotDensityDialog::~PlotDensityDialog()
{
    delete ui;
}

QString PlotDensityDialog::getSelected()
{
    QString key = ui->listWidget->currentItem()->data(Qt::UserRole).toString();
    return key;
}

void PlotDensityDialog::changeEvent(QEvent *e)
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
