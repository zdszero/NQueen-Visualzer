#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <vector>
#include <QSemaphore>
#include "globals.h"
#include "mythread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Form; }
QT_END_NAMESPACE

class Form : public QWidget
{
    Q_OBJECT

public:
    Form(QWidget *parent = nullptr);
    ~Form();

private slots:
    void on_btnConfirm_clicked();

    void on_btnStart_clicked();

    void on_btnStop_clicked();

    void on_btnReset_clicked();

private:
    Ui::Form *ui;
    MyThread *thread;
    std::vector<int> columns, lastCols;

    void setTable(int size);
    void updateView();
    void changeSleepTime();
};
#endif // FORM_H
