#ifndef SAVEDATA_H
#define SAVEDATA_H

#include <QDialog>

namespace Ui {
class saveData;
}

class saveData : public QDialog
{
    Q_OBJECT

public:
    explicit saveData(QWidget *parent = nullptr);
    ~saveData();
    void write(int counter, const QVector<double>& x, const QVector<double>& y);
    void addData(int counter, const QVector<double>& x, const QVector<double>& y);
    void clear();

private:
    Ui::saveData *ui;
    int counter;
};

#endif // SAVEDATA_H
