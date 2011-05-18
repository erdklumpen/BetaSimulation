#ifndef ECASETTINGS_H
#define ECASETTINGS_H

#include <QWidget>
#include <QVector>

namespace Ui {
    class ECASettings;
}

class ECASettings : public QWidget
{
    Q_OBJECT

public:
    explicit ECASettings(QWidget *parent = 0);
    ~ECASettings();

    QVector<int> settings();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ECASettings *ui;
};

#endif // ECASETTINGS_H
