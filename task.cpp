//По окончании построения новый график задается только через кнопку Stop


#include "task.h"
#include "ui_task.h"
#include <QDebug>
#include <QPainter>
#include <QLabel>
#include <QPainterPath>

task::task(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::task), X(10), Y(10), save(nullptr), typeOfFunction(0), firstParameter(0), secondParameter(0), thirdParameter(0)
    , x_0(0), x_n(0), step(0), counter(0), maxY(0), minY(0)
{
    ui->setupUi(this);
    QStringList listFunction;
    listFunction << "" << "f(x) = A * (x * x) + B * x + C"
                 << "f(x) = A * sin(x) + B * cos( C * x )"
                 << "f(x) = A*lg( B*x )"
                 << "f(x) = A / ( sin(x*x) * B )";


    ui->listFunction->addItems(listFunction);
    paint = new QTimer(this);

}

task::~task()
{

    delete ui;
}

void task::on_listFunction_activated(int index)
{
    createTableWidget(index);
    typeOfFunction = index;
}

void task::createTableWidget(int index)
{
    //Параметры А и В
    ui->addParameter->setColumnCount(2);
    ui->addParameter->setRowCount(1);

    QTableWidgetItem* itemA = new QTableWidgetItem;
    itemA->setText("A");
    ui->addParameter->setHorizontalHeaderItem(0, itemA);


    QTableWidgetItem* itemB = new QTableWidgetItem;
    itemB->setText("B");
    ui->addParameter->setHorizontalHeaderItem(1, itemB);

    //Параметр С
    if(index <= 2)
    {

        ui->addParameter->setColumnCount(ui->addParameter->columnCount() + 1);
        QTableWidgetItem* itemC = new QTableWidgetItem;
        itemC->setText("C");
        itemC->setTextAlignment(Qt::AlignCenter);
        ui->addParameter->setHorizontalHeaderItem(2, itemC);
        ui->addParameter->setColumnWidth(0, 80);
        ui->addParameter->setColumnWidth(1, 80);
        ui->addParameter->setColumnWidth(2, 80);

    }
    else
    {
        ui->addParameter->setColumnWidth(0, 120);
        ui->addParameter->setColumnWidth(1, 120);
    }
}

void task::getParameters(bool typeOfFunction)
{
    QString str;
    firstParameter = 0;
    secondParameter = 0;
    thirdParameter = 0;
    if(typeOfFunction)
    {
        str = ui->addParameter->item(0,2)->text();
        thirdParameter = str.toDouble();
    }
    str = ui->addParameter->item(0,1)->text();
    secondParameter = str.toDouble();
    str = ui->addParameter->item(0,0)->text();
    firstParameter = str.toDouble();


}

void task::callCalculation()
{
   switch (typeOfFunction) {
            case 1:
            {
                 maxY = calculation(ParabolicFunction, firstParameter, secondParameter, thirdParameter, Y, X);
                 break;
            }
            case 2:
            {

                maxY = calculation(PereodicFunction, firstParameter, secondParameter, thirdParameter, Y, X);
                break;
            }
            case 3:
            {
                if(x_0 <= 0)
                {
                    QMessageBox::information(0, "Предупреждение", "Функция не определена в отрицательных точках!\n Перезадайте интервал");
                    ui->start->clear();
                    ui->stop->clear();
                    break;
                }
                else
                    maxY = calculation(LogarithmicFunction, firstParameter, secondParameter, Y, X);
                break;
            }

            case 4:
            {
                if(X.contains(0))
                {
                    QMessageBox::information(0, "Предупреждение", "Функция не определена в точке 0!\n Перезадайте интервал");
                    ui->start->clear();
                    ui->stop->clear();
                    break;
                }
                else
                    maxY = calculation(InversePeriodicFunction, firstParameter, secondParameter, Y, X);
                break;
            }
}

}

void task::fullX()
{
    X[0] = x_0;
    for(int i = 1; i < X.size(); ++i)
        X[i] = X[i - 1] + step;
}

void task::clear()
{

    typeOfFunction = 0;
    firstParameter = 0;
    secondParameter = 0;
    thirdParameter = 0;
    x_0 = 0;
    x_n = 0;
    step = 0;

    maxY = 0;
    minY = 0;
}

void task::clearWidget()
{
    ui->graph->clearPlottables();
    ui->graph->replot();
    ui->start->clear();
    ui->stop->clear();
    ui->step->clear();
    ui->addParameter->clearContents();
}

void task::enabledFalse()
{
    ui->listFunction->setEnabled(false);
    ui->addParameter->setEnabled(false);
    ui->start->setEnabled(false);
    ui->stop->setEnabled(false);
    ui->step->setEnabled(false);
}

void task::enabledTrue()
{
    ui->listFunction->setEnabled(true);
    ui->addParameter->setEnabled(true);
    ui->start->setEnabled(true);
    ui->stop->setEnabled(true);
    ui->step->setEnabled(true);

}

void task::updateButton()
{
    ui->startButton->setText("Start");
    ui->stopButton->setText("Stop");
    ui->pauseButton->setText("Pause");

}

void task::on_startButton_clicked()
{
    if(ui->startButton->text() == "New")
    {
        if(!X.isEmpty() )
             X.clear();
        if(!Y.isEmpty() )
            Y.clear();
        counter = 0;
        if( save != nullptr)
            save->clear();

        clear();
        clearWidget();

        enabledTrue();
        updateButton();
        //qDebug() << ui->startButton->text();

    }
    else if(ui->startButton->text() == "Start")
        {

            if(typeOfFunction == 0)
               {
                  QMessageBox::information(0, "Предупреждение", "Выберите тип функции!");
                  return;
               }

            if(typeOfFunction <= 2)
                getParameters(true);
            else
                getParameters(false);
            ui->pauseButton->setText("Pause");
            ui->startButton->setText("Progress");
            x_0 = ui->start->text().toDouble();
            x_n = ui->stop->text().toDouble();
            step = ui->step->text().toDouble();
            int interval = std::abs(x_0 - x_n) / step;

            if(interval == 0 || step ==0 )
            {
                QMessageBox::information(0, "Предупреждение", "Введите данные для построения функции");
                ui->startButton->setText("Start");
                return;
            }

            X.resize(interval);
            Y.resize(interval);
            enabledFalse();
            fullX();
            callCalculation();
            minY = *std::min_element(Y.begin(), Y.end());
            connect(paint, SIGNAL(timeout()), SLOT(incrementCounter()));
            paint->start(100);

        }




}


void task::incrementCounter()
{
    counter++;
    update();
}


void task::paintEvent(QPaintEvent *event)
{
    if(counter < X.size())
    {
        ui->graph->clearGraphs();
        //Добавляем один график в widget
        ui->graph->addGraph();
        ui->graph->graph(0)->setData(X, Y);
        ui->graph->graph(0)->setPen(QColor(Qt::darkRed));//задаем цвет точки

        //Подписываем оси Ox и Oy
        ui->graph->xAxis->setLabel("X");
        ui->graph->yAxis->setLabel("Y");

        //Установим область, которая будет показываться на графике
        ui->graph->xAxis->setRange(X[0], X[counter]);//Для оси Ox
        ui->graph->yAxis->setRange(minY-1, maxY + 1);//Для оси Oy
        ui->graph->replot();
    }
    else
    {

        paint->stop();
        ui->statusbar->showMessage("Построение графика завершено");

    }

}

void task::clickedGraph(QMouseEvent *event)
{
    if(ui->startButton->text() == "New" || ui->pauseButton->text() == "Continue")
    {
        ui->graph->mousePress(event);
        if(save == nullptr)
        {
          save = new saveData(this);
          save->write(counter, X, Y);
          save->show();
        }
        else
        {
            save->addData(counter, X, Y);
            save->show();
        }

    }
}

void task::on_stopButton_clicked()
{

        paint->stop();

        ui->startButton->setText("New");
        ui->pauseButton->setText("Pause");

        connect(ui->graph, SIGNAL(mouseDoubleClick(QMouseEvent*)), SLOT(clickedGraph(QMouseEvent*)));

}

void task::on_pauseButton_clicked()
{

    if(paint->isActive())
    {
        paint->stop();
        ui->pauseButton->setText("Continue");
        connect(ui->graph, SIGNAL(mouseDoubleClick(QMouseEvent*)), SLOT(clickedGraph(QMouseEvent*)));
    }
    else if(ui->pauseButton->text() == "Continue")
    {
        ui->pauseButton->setText("Pause");
        paint->start();
    }

}

void task::on_actionSave_triggered()
{
    if( X.empty() && Y.empty())
        return;
    else
    {
        QString path = QFileDialog::getOpenFileName(this, "Open File");
        if(path.isEmpty())
              return;
        QFile file(path);
        if(!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::critical(this, "Ошибка", file.errorString());
            ui->statusbar->showMessage("Невозможно сохранить файл");
            return;
        }
        QTextStream stream(&file);
        stream << typeOfFunction << " " << firstParameter << " "
               << secondParameter << " " << thirdParameter << " " <<
               x_0 << " " << x_n << " " << step << " " << counter
               << " " << maxY << " " << minY << "\n" ;
        for(int i = 0; i < X.size(); ++i)
        {
            stream << X[i] << "\t" << Y[i] << "\n";
        }
        file.close();

    }
}

