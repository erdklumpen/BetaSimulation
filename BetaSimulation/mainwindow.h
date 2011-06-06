#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "eca.h"
#include "gameoflife.h"
#include "onedimensionstate.h"
#include "automatasettings.h"
#include "ecasettings.h"
#include "plotdensitydialog.h"

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
#include <QPoint>
#include <QList>
#include <QString>
#include <QStringList>
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

    int m_steps;

    int m_xLength;
    int m_yLength;

    CAHistory *caData;

    void plotDensity(QVector<QPointF> density);
    void plotActivity(QVector<QPointF> activity);

    QwtPlot* newPlot();

    void drawOneDimensionState(OneDimensionState *state, int line, QGraphicsScene *scene);
    void drawTwoDimensionState(TwoDimensionState *state, int column, QGraphicsScene *scene);

    CAHistory* runCA(AbstractCA &ca, int steps, bool draw = false);
    CAHistory* runOneDimensionalCA(Abstract1DCA &ca, int steps, bool draw);
    CAHistory* runTwoDimensionalCA(Abstract2DCA &ca, int steps, bool draw);

    CAHistory* averageHistory(QVector<CAHistory*> historyVector);
    QVector<QPointF> averageAverageHistory(QVector<CAHistory*> historyVector, QString key);

    void plotAlphaBeta(QVector<QPointF> alpha, QVector<QPointF> beta, QString title);

    void testAutomata(AbstractCA &ca, int steps, int samples);

private slots:
    void on_actionSpiel_des_Lebens_2_triggered();
    void on_actionAktivit_t_triggered();
    void on_actionSpiel_des_Lebens_triggered();
    void on_actionECA1000_triggered();
    void on_actionECA_triggered();
    void on_actionEinstellungen_triggered();
    void on_action1_Dichte_triggered();
};

#endif // MAINWINDOW_H
