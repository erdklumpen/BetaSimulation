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
    explicit AutomataSettings(QWidget *parent = 0, double alpha = 1.0, double beta = 1.0,
                              int steps = 1, int xLength = 1, int yLength = 1);
    ~AutomataSettings();

    double alpha();
    double beta();

    int steps();

    int xLength();
    int yLength();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::AutomataSettings *ui;
};

#endif // AUTOMATASETTINGS_H
