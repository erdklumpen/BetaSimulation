#ifndef PLOTDENSITYDIALOG_H
#define PLOTDENSITYDIALOG_H

#include <QDialog>
#include <QString>
#include <QStringList>

namespace Ui {
    class PlotDensityDialog;
}

class PlotDensityDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlotDensityDialog(QStringList densities, QWidget *parent = 0);
    ~PlotDensityDialog();

    QString getSelected();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::PlotDensityDialog *ui;
};

#endif // PLOTDENSITYDIALOG_H
