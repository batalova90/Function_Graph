#ifndef TASK_H
#define TASK_H

#include <QMainWindow>
//#include <QWidget>
QT_BEGIN_NAMESPACE
namespace Ui { class task; }
QT_END_NAMESPACE
#include "function.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <functional>

#include <QTimer>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include "savedata.h"

class task : public QMainWindow
{
    Q_OBJECT

public:
    task(QWidget *parent = nullptr);
    ~task();
    friend void calculation(double (*foo)(double first, double second, double third, double x),
                            QVector<double>& y, QVector<double>& x);

    friend void calculation(double (*foo)(double first, double second, double x),
                                 QVector<double>& y, QVector<double>& x);
private slots:
    void on_listFunction_activated(int index);

    void on_startButton_clicked();

    void incrementCounter();

    void on_stopButton_clicked();

    void on_pauseButton_clicked();

    void on_actionSave_triggered();


    
public slots:
     void paintEvent(QPaintEvent *event);

     void clickedGraph(QMouseEvent* event);

private:
    Ui::task *ui;

    QVector<double> X;
    QVector<double> Y;
    QTimer* paint;
    saveData* save;
    int typeOfFunction;

    double firstParameter;
    double secondParameter;
    double thirdParameter;
    //Параметры, задающие интервал
    double x_0;
    double x_n;
    double step;
    //Переменная-счетчик таймера
    int counter;
    //Для задания длины осей
    double maxY;
    double minY;

    void getParameters(bool typeOfFunction);
    void createTableWidget(int index); //добавить название
    bool check();
    void callCalculation();
    void fullX();
    void clear();
    void clearWidget();
    void openFile();
    void enabledFalse();
    void enabledTrue();
    void updateButton();


};
#endif // TASK_H
