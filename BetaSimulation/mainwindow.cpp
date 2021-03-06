#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_alpha = 1;
    m_beta = 1;

    m_steps = 10;

    m_xLength = 10;
    m_yLength = 10;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionEinstellungen_triggered()
{
    AutomataSettings* settings = new AutomataSettings(this, m_alpha, m_beta, m_steps, m_xLength, m_yLength);
    settings->exec();

    m_alpha = settings->alpha();
    m_beta = settings->beta();

    m_steps = settings->steps();

    m_xLength = settings->xLength();
    m_yLength = settings->yLength();
}

void MainWindow::drawOneDimensionState(OneDimensionState *state, int line, QGraphicsScene *scene)
{
    for(int i = 0; i < state->size(); ++i)
    {
        QPen pen(Qt::black);
        QBrush brush;

//        qDebug() << state->atEigen(i);
        if(state->atEigen(i))
            brush = QBrush(Qt::black);
        else
            brush = QBrush(Qt::white);

        scene->addRect(0 + 10*i, 10 + line*10, 10, 10, pen, brush);
    }
}

void MainWindow::drawTwoDimensionState(TwoDimensionState *state, int column, QGraphicsScene *scene)
{
    int xOffset = column * state->xSize() * 10;

    for(int i = 0; i < state->ySize(); ++i)
    {
        for(int j = 0; j < state->xSize(); ++j)
        {
            QPen pen(Qt::black);
            QBrush brush;

            if(state->atEigen(j, i))
                brush = QBrush(Qt::black);
            else
                brush = QBrush(Qt::white);

            scene->addRect(0 + 10*j + xOffset, 0 + i*10, 10, 10, pen, brush);
        }

        scene->addRect(0 + xOffset, 0, state->xSize() * 10, state->ySize() * 10, QPen(Qt::red));
    }
}

CAHistory* MainWindow::runCA(AbstractCA &ca, int steps, bool draw)
{
    if(ui->graphicsView->scene() != 0)
    {
        ui->graphicsView->scene()->clear();
    }

    if(ca.dimensions() == 1)
    {
        Abstract1DCA& oneDCA = dynamic_cast<Abstract1DCA&>(ca);
        runOneDimensionalCA(oneDCA, steps, draw);
    }

    else if(ca.dimensions() == 2)
    {
        Abstract2DCA& twoDCA = dynamic_cast<Abstract2DCA&>(ca);
        runTwoDimensionalCA(twoDCA, steps, draw);
    }

    caData = ca.history();
    return ca.history();
}

CAHistory* MainWindow::runOneDimensionalCA(Abstract1DCA &ca, int steps, bool draw)
{
    QGraphicsScene *scene;

    if(ui->graphicsView->scene() == 0 && draw)
    {
        scene = new QGraphicsScene;
        ui->graphicsView->setScene(scene);
    }
    else if(draw)
        scene = ui->graphicsView->scene();

    OneDimensionState *state = ca.state();

    if(draw)
        drawOneDimensionState(state, 0, scene);

    for(int j = 0; j < steps; ++j)
    {
//        qDebug() << "Step: " << j;
        ca.run(1);
        state = ca.state();

        if(draw)
            drawOneDimensionState(state, j + 1 , scene);
    }

    return ca.history();
}

CAHistory* MainWindow::runTwoDimensionalCA(Abstract2DCA &ca, int steps, bool draw)
{
    QGraphicsScene *scene;

    if(ui->graphicsView->scene() == 0 && draw)
    {
        scene = new QGraphicsScene;
        ui->graphicsView->setScene(scene);
    }
    else if(draw)
        scene = ui->graphicsView->scene();

    TwoDimensionState *state = ca.state();

    if(draw)
        drawTwoDimensionState(state, 0, scene);

    for(int j = 0; j < steps; ++j)
    {
//        qDebug() << "Step: " << j;
        ca.run(1);
        state = ca.state();

        if(draw)
            drawTwoDimensionState(state, j + 1, scene);
    }

    return ca.history();
}

void MainWindow::plotDensity(QVector<QPointF> density)
{
//    qDebug() << density;

    QwtPlotCurve *curve = new QwtPlotCurve();
    curve->setSamples(density);

    QwtPlot *plot = newPlot();
    curve->attach(plot);
}

void MainWindow::plotActivity(QVector<QPointF> activity)
{
    QwtPlotCurve *curve = new QwtPlotCurve();
    curve->setSamples(activity);

    QwtPlot *plot = newPlot();
    curve->attach(plot);
}

QwtPlot* MainWindow::newPlot()
{
    QwtPlot *plot = new QwtPlot();

    QDockWidget *dock =  new QDockWidget();
    dock->setWidget(plot);
    this->addDockWidget(Qt::RightDockWidgetArea, dock);

    return plot;
}

void MainWindow::on_action1_Dichte_triggered()
{
    QStringList densities = caData->getDensities();

    PlotDensityDialog *plotDensityDialog = new PlotDensityDialog(densities, this);
    plotDensityDialog->exec();

    QString key = plotDensityDialog->getSelected();

    plotDensity(caData->getDensity(key));
}

void MainWindow::testAutomata(AbstractCA &ca, int steps, int samples)
{
    CAHistory alphaHistory;
    CAHistory betaHistory;

    float border = 1.01;
    float start = 0.0;
    float step = 0.1;

    float alpha = start;
    while(alpha < border)
    {
        qDebug() << "alpha: " << alpha;
        ca.initAlpha(alpha);

        QMap<QString, float> sampleSum;
        float activitySum = 0.0;

        for(int i = 0; i < samples; ++i)
        {
            qDebug() << "sample: " << i;
            CAHistory* lastRun = runCA(ca, steps);

            activitySum += lastRun->getActivity().last().y();

            QStringList keys = lastRun->getDensities();
            for(int j = 0; j < keys.size(); ++j)
            {
                QString key = keys.at(j);

                if(!sampleSum.contains(key))
                    sampleSum.insert(key, lastRun->getDensity(key).last().y());
                else
                    sampleSum.insert(key,lastRun->getDensity(key).last().y() + sampleSum.value(key));
            }

            ca.initHistory();
            ca.initCA();

            delete lastRun;
        }

        float averageActivity = activitySum / samples;
        alphaHistory.appendActivity(averageActivity, alpha);

        QStringList keys = sampleSum.keys();
        for(int i = 0; i < keys.size(); ++i)
        {
            QString key = keys.at(i);

            float average = sampleSum.value(key) / samples;
            alphaHistory.appendDensity(key, average, alpha);
        }

        alpha += step;
    }

    float beta = start;
    while(beta < border)
    {
        qDebug() << "beta: " << beta;
        ca.initBeta(beta);

        QMap<QString, float> sampleSum;
        float activitySum = 0.0;

        for(int i = 0; i < samples; ++i)
        {
            qDebug() << "sample: " << i;
            CAHistory* lastRun = runCA(ca, steps);

            activitySum += lastRun->getActivity().last().y();

            QStringList keys = lastRun->getDensities();
            for(int j = 0; j < keys.size(); ++j)
            {
                QString key = keys.at(j);

                if(!sampleSum.contains(key))
                    sampleSum.insert(key, lastRun->getDensity(key).last().y());
                else
                    sampleSum.insert(key,lastRun->getDensity(key).last().y() + sampleSum.value(key));
            }

            ca.initHistory();
            ca.initCA();

            delete lastRun;
        }

        float averageActivity = activitySum / samples;
        betaHistory.appendActivity(averageActivity, beta);

        QStringList keys = sampleSum.keys();
        for(int i = 0; i < keys.size(); ++i)
        {
            QString key = keys.at(i);

            float average = sampleSum.value(key) / samples;
            betaHistory.appendDensity(key, average, beta);
        }

        beta += step;
    }

    plotAlphaBeta(alphaHistory.getDensity("1"), betaHistory.getDensity("1"), "1-Dichte");
    plotAlphaBeta(alphaHistory.getActivity(), betaHistory.getActivity(), "Aktivitaet");
}

void MainWindow::plotAlphaBeta(QVector<QPointF> alpha, QVector<QPointF> beta, QString title)
{
    QwtPlotCurve *curveAlpha = new QwtPlotCurve();
    curveAlpha->setSamples(alpha);
    curveAlpha->setPen(QPen(Qt::blue));

    QwtPlotCurve *curveBeta = new QwtPlotCurve();
    curveBeta->setSamples(beta);
    curveBeta->setPen(QPen(Qt::red));

    QwtPlot *plot = newPlot();
    plot->setTitle(title);
    curveAlpha->attach(plot);
    curveBeta->attach(plot);
}

void MainWindow::on_actionECA_triggered()
{
    int ecaNumber = QInputDialog::getInt(this, "ECA Nummer", "Bitte Nummer des ECA eingeben", 0, 0, 255);
    int size = m_xLength;
    int steps = m_steps;

    ECA eca = ECA(m_alpha, m_beta, size, ecaNumber);
    runCA(eca, steps, true);
}

void MainWindow::on_actionECA1000_triggered()
{
    int ecaNumber = QInputDialog::getInt(this, "ECA Nummer", "Bitte Nummer des ECA eingeben", 0, 0, 255);
    int size = m_xLength;
    int steps = m_steps;
    int samples = 100;

    ECA eca = ECA(m_alpha, m_beta, size, ecaNumber);
    testAutomata(eca, steps, samples);
}

void MainWindow::on_actionSpiel_des_Lebens_triggered()
{
    GameOfLife gol = GameOfLife(m_alpha, m_beta, m_xLength, m_yLength);
    runCA(gol, m_steps, true);
}

void MainWindow::on_actionAktivit_t_triggered()
{
    QVector<QPointF> activity = caData->getActivity();
    plotActivity(activity);
}

void MainWindow::on_actionSpiel_des_Lebens_2_triggered()
{
    int samples = 50;

    GameOfLife gol = GameOfLife(m_alpha, m_beta, m_xLength, m_yLength);
    testAutomata(gol, m_steps, samples);
}

void MainWindow::on_actionMajority_triggered()
{
    Majority majority = Majority(m_alpha, m_beta, m_xLength, m_yLength);
    runCA(majority, m_steps, true);
}

void MainWindow::on_actionMinority_triggered()
{
    Minority Minority = Minority(m_alpha, m_beta, m_xLength, m_yLength);
    runCA(Minority, m_steps, true);
}
