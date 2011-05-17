#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "eca.h"
#include "onedimensionstate.h"
#include "automatasettings.h"
#include <QDebug>

#include <QGraphicsGridLayout>
#include <QGraphicsWidget>
#include <QGraphicsScene>
#include <QPen>
#include <QBrush>
#include <QInputDialog>
#include <QDockWidget>

#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>
#include <qwt/qwt_data.h>
#include <qwt/qwt_array.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    double m_alpha;
    double m_beta;

    QVector<int> *m_densityData;
    QVector<int> *m_activityData;

    void saveDensity(int density) {m_densityData->append(density);}
    void saveActivity(int activity) {m_activityData->append(activity);}

    void plotDensity();
    void plotActivity();

    QwtPlot* newPlot();

    void drawOneDimensionState(OneDimensionState *state, int line, QGraphicsScene *scene);

private slots:
    void on_actionECA_triggered();
    void on_actionEinstellungen_triggered();
    void on_actionECA50_triggered();
    void on_action1_Dichte_triggered();
};

#endif // MAINWINDOW_H
