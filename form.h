#ifndef FORM_H
#define FORM_H

#include <QWidget>
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

private:
    Ui::Form *ui;
    MyThread *thread;

    void setTable(int size);
    void updateView();
};
#endif // FORM_H
