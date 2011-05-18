#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "eca.h"
#include "onedimensionstate.h"
#include "automatasettings.h"
#include "experimentwizard.h"

#include "ecasettings.h"

#include <QDebug>

#include <QMainWindow>
#include <QGraphicsGridLayout>
#include <QGraphicsWidget>
#include <QGraphicsScene>
#include <QPen>
#include <QBrush>
#include <QInputDialog>
#include <QDockWidget>
#include <QPointF>
#include <QList>
#include <QString>
#include <QMap>

#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>
#include <qwt/qwt_series_data.h>

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

    QVector<QPointF> *m_densityData;
    QVector<QPointF> *m_activityData;

    QVector<QPointF> *m_densityAlphaData;
    QVector<QPointF> *m_densityBetaData;

    QList< QPair<QString, QWidget*> > m_automats;

    void saveDensity(float density) {m_densityData->append(QPointF(m_densityData->size(), density));}
    void saveActivity(float activity) {m_activityData->append(QPointF(m_activityData->size(), activity));}

    void plotDensity();
    void plotActivity();

    QwtPlot* newPlot();

    void drawOneDimensionState(OneDimensionState *state, int line, QGraphicsScene *scene);

private slots:
    void on_actionECA1000_triggered();
    void on_actionExperiment_triggered();
    void on_actionECA_triggered();
    void on_actionEinstellungen_triggered();
    void on_actionECA50_triggered();
    void on_action1_Dichte_triggered();
};

#endif // MAINWINDOW_H
