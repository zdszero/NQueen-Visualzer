#include "form.h"
#include "ui_form.h"
#include <QDebug>

Form::Form(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Form)
{
    ui->setupUi(this);

    columns.resize(8, -1);
    ui->editNum->setText("8");

    /* default talbe config */
    this->setTable(8);
    ui->table->verticalHeader()->setVisible(false);
    ui->table->horizontalHeader()->setVisible(false);

    /* buttons enable */
    ui->btnStop->setEnabled(false);
    ui->btnStart->setEnabled(false);
    ui->btnReset->setEnabled(false);

    /* signals */
    connect(ui->btnExit, &QPushButton::clicked, this, &QWidget::close);
    connect(ui->slider, &QSlider::valueChanged, this, [this](){
        sleepTime = 2000 - ui->slider->value();
        qDebug() << "slider value changed to " << sleepTime;
    });
    connect(this->thread, &MyThread::sigUpdateView, this, &Form::updateView);
}

Form::~Form()
{
    delete ui;
}

void Form::setTable(int size)
{
    ui->table->setRowCount(size);
    ui->table->setColumnCount(size);
    for (int i = 0; i < size; ++i) {
        ui->table->setRowHeight(i, 450/size);
        ui->table->setColumnWidth(i, 450/size);
    }
}


void Form::on_btnConfirm_clicked()
{
    ui->btnStart->setEnabled(true);
    ui->btnReset->setEnabled(true);
    QUEEN_NUM = ui->editNum->text().toInt();
    columns.resize(QUEEN_NUM, -1);
}


void Form::updateView()
{

}
