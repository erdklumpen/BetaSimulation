#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_densityData = new QVector<QPointF>();
    m_activityData = new QVector<QPointF>();

    m_alpha = 1;
    m_beta = 1;

    m_automats << QPair<QString, QWidget*>("ECA", new ECASettings());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionECA50_triggered()
{
    ECA eca(m_alpha, m_beta, 50, 50);
    QGraphicsScene *scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);

    OneDimensionState *state = eca.state();

    for(int i = 0; i < state->size(); ++i)
    {
        QPen pen(Qt::black);
        QBrush brush;

        if(state->atEigen(i))
            brush = QBrush(Qt::black);
        else
            brush = QBrush(Qt::white);

        scene->addRect(0 + 10*i, 0, 10, 10, pen, brush);
    }

    for(int j = 0; j < 50; ++j)
    {
        eca.run(1);
        state = eca.state();

        for(int i = 0; i < state->size(); ++i)
        {
            QPen pen(Qt::black);
            QBrush brush;

            if(state->atEigen(i))
                brush = QBrush(Qt::black);
            else
                brush = QBrush(Qt::white);

            scene->addRect(0 + 10*i, 10 + j*10, 10, 10, pen, brush);
        }
    }
}

void MainWindow::on_actionEinstellungen_triggered()
{
    AutomataSettings* settings = new AutomataSettings(this, m_alpha, m_beta);
    settings->exec();
    m_alpha = settings->alpha();
    m_beta = settings->beta();
}

void MainWindow::on_actionECA_triggered()
{
    int ecaNumber = QInputDialog::getInt(this, "ECA Nummer", "Bitte Nummer des ECA eingeben", 0, 0, 255);
    int size = QInputDialog::getInt(this, "Automatengröße", "Bitte gewünschte Größe des Automaten eingeben", 1, 1, 1000000);
    int steps = QInputDialog::getInt(this, "Schritte", "Bitte Anzahl der Schritte eingeben", 1, 1, 100000);

    m_activityData->clear();
    m_densityData->clear();

    ECA eca(m_alpha, m_beta, size, ecaNumber);
    QGraphicsScene *scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);

    OneDimensionState *state = eca.state();

    if(size < 500)
        drawOneDimensionState(state, 0, scene);

    for(int j = 0; j < steps; ++j)
    {
        qDebug() << "Step: " << j;
        eca.run(1);
        state = eca.state();

        if(size < 500)
            drawOneDimensionState(state, j + 1 , scene);

        saveDensity(eca.density());
        saveActivity(eca.activity());
    }
}

void MainWindow::drawOneDimensionState(OneDimensionState *state, int line, QGraphicsScene *scene)
{
    for(int i = 0; i < state->size(); ++i)
    {
        QPen pen(Qt::black);
        QBrush brush;

        if(state->atEigen(i))
            brush = QBrush(Qt::black);
        else
            brush = QBrush(Qt::white);

        scene->addRect(0 + 10*i, 10 + line*10, 10, 10, pen, brush);
    }
}

void MainWindow::plotDensity()
{
//    qDebug() << *m_densityData;

    QwtPlotCurve *curve = new QwtPlotCurve();
    curve->setSamples(*m_densityData);

    QwtPlot *plot = newPlot();
    curve->attach(plot);
}

void MainWindow::plotActivity()
{

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
    plotDensity();
}

void MainWindow::on_actionExperiment_triggered()
{
    ExperimentWizard *wizard = new ExperimentWizard(m_automats, this);
    wizard->exec();
}

void MainWindow::on_actionECA1000_triggered()
{
    int ecaNumber = QInputDialog::getInt(this, "ECA Nummer", "Bitte Nummer des ECA eingeben", 0, 0, 255);
    int size = QInputDialog::getInt(this, "Automatengröße", "Bitte gewünschte Größe des Automaten eingeben", 1, 1, 1000000);
    int steps = QInputDialog::getInt(this, "Schritte", "Bitte Anzahl der Schritte eingeben", 1, 1, 100000);

    m_densityAlphaData = new QVector<QPointF>;
    m_densityBetaData = new QVector<QPointF>;

    float alpha = 0.0;
    float beta = 0.0;

    while(alpha < 1.1)
    {
        QVector<float> density;

        for(int i = 0; i < 100; ++i)
        {
            ECA eca(alpha, 1.0, size, ecaNumber);

            OneDimensionState *state = eca.state();

            for(int j = 0; j < steps; ++j)
            {
                density << state->density();
                state = eca.state();
//                qDebug() << "Step: " << j;
                eca.run(1);
            }

            delete state;
        }

//        qDebug() << density;

        float densityAverage = 0.0;
        for(int j = 0; j < density.size(); ++j)
        {
            densityAverage += density[j];
        }

        densityAverage /= density.size();

        m_densityAlphaData->append(QPointF(alpha, densityAverage));

        alpha += 0.1;
    }

    while(beta < 1.1)
    {
        QVector<float> density;

        for(int i = 0; i < 100; ++i)
        {
            ECA eca(1.0, beta, size, ecaNumber);

            OneDimensionState *state = eca.state();

            for(int j = 0; j < steps; ++j)
            {
                density << state->density();
                state = eca.state();
//                qDebug() << "Step: " << j;
                eca.run(1);
            }

            delete state;
        }

//        qDebug() << density;

        float densityAverage = 0.0;
        for(int j = 0; j < density.size(); ++j)
        {
            densityAverage += density[j];
        }

        densityAverage /= density.size();

        m_densityBetaData->append(QPointF(beta, densityAverage));

        beta += 0.1;
    }

    qDebug() << (*m_densityAlphaData);
    qDebug() << (*m_densityBetaData);

    QwtPlotCurve *curveAlpha = new QwtPlotCurve();
    curveAlpha->setSamples(*m_densityAlphaData);
    curveAlpha->setPen(QPen(Qt::red));

    QwtPlotCurve *curveBeta = new QwtPlotCurve();
    curveBeta->setSamples(*m_densityBetaData);
    curveBeta->setPen(QPen(Qt::green));

    QwtPlot *plot = newPlot();
    curveAlpha->attach(plot);
    curveBeta->attach(plot);
}
