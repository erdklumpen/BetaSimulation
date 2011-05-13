#ifndef AUTOMATASETTINGS_H
#define AUTOMATASETTINGS_H

#include <QDialog>

namespace Ui {
    class AutomataSettings;
}

class AutomataSettings : public QDialog
{
    Q_OBJECT

public:
    explicit AutomataSettings(QWidget *parent = 0, double alpha = 1.0, double beta = 1.0);
    ~AutomataSettings();

    double alpha();
    double beta();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::AutomataSettings *ui;
};

#endif // AUTOMATASETTINGS_H
