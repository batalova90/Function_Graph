#include "savedata.h"
#include "ui_savedata.h"
#include <QDebug>
#include <QString>
saveData::saveData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::saveData), counter(0)
{
    ui->setupUi(this);
}

saveData::~saveData()
{
    if( ui != nullptr)
        delete ui;
}

void saveData::write(int counter, const QVector<double> &x, const QVector<double> &y)
{

    ui->tableData->setRowCount(x.size());
    ui->tableData->setColumnCount(2);
    QTableWidgetItem* pointer_X = new QTableWidgetItem();
    pointer_X->setText("X");
    ui->tableData->setHorizontalHeaderItem(0, pointer_X);
    QTableWidgetItem* pointer_Y = new QTableWidgetItem();
    pointer_Y->setText("Y");
    ui->tableData->setHorizontalHeaderItem(1, pointer_Y);

        for(int i = 0; i < x.size(); ++i)
        {
            if(this->counter <= counter)
            {

                QTableWidgetItem* X_i = new QTableWidgetItem(QString::number(x[i]));

                ui->tableData->setItem(i,0,X_i);
                QTableWidgetItem* Y_i = new QTableWidgetItem(QString::number(y[i]));
                ui->tableData->setItem(i, 1, Y_i);
                this->counter++;
            }
            else
                return;

        }
}

void saveData::addData(int counter, const QVector<double> &x, const QVector<double> &y)
{
    for(int i = this->counter; i < x.size(); ++i)
    {
        if(this->counter <= counter)
        {

            QTableWidgetItem* X_i = new QTableWidgetItem(QString::number(x[i]));

            ui->tableData->setItem(i,0,X_i);
            QTableWidgetItem* Y_i = new QTableWidgetItem(QString::number(y[i]));
            ui->tableData->setItem(i, 1, Y_i);
            this->counter++;
        }
        else
            return;
    }

}

void saveData::clear()
{
    if(counter != 0)
    {
        ui->tableData->clearContents();
        counter =0;
    }

}
