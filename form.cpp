#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Form)
{
    ui->setupUi(this);

    this->setWindowTitle("NQueen Problem Visualizer");
    this->setFixedSize(800, 480);
    ui->editNum->setText("8");

    this->columns.resize(8, -1);
    this->lastCols.resize(8, 0);
    this->thread = new MyThread(&(this->columns));

    /* default table config */
    this->setTable(8);
    ui->table->verticalHeader()->setVisible(false);
    ui->table->horizontalHeader()->setVisible(false);

    /* default buttons config */
    ui->btnStop->setEnabled(false);
    ui->btnStart->setEnabled(false);
    ui->btnReset->setEnabled(false);

    /* signals */
    connect(ui->btnExit, &QPushButton::clicked, this, &QWidget::close);
    connect(ui->slider, &QSlider::valueChanged, this, &Form::changeSleepTime);
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

void Form::changeSleepTime()
{
    sleepTime = 2000 - ui->slider->value();
}


void Form::updateView()
{
    int col;
    for (int i = 0; i < QUEEN_NUM; i++) {
        col = this->lastCols.at(i);
        ui->table->setItem(i, col, NULL);
    }
    for (int i = 0; i < QUEEN_NUM; i++) {
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setBackground(QBrush(Qt::red));
        col = this->columns.at(i);
        ui->table->setItem(i, col, item);
        this->lastCols[i] = this->columns[i];
    }
}

// confirm queen number
void Form::on_btnConfirm_clicked()
{
    ui->btnStart->setEnabled(true);
    ui->btnConfirm->setEnabled(false);

    retFlag = false;
    QUEEN_NUM = ui->editNum->text().toInt();
    this->columns.resize(QUEEN_NUM, -1);
    this->lastCols.resize(QUEEN_NUM, 0);
    setTable(QUEEN_NUM);
}

// start to show solutions
void Form::on_btnStart_clicked()
{
    ui->btnStop->setEnabled(true);
    ui->btnStart->setEnabled(false);
    ui->btnReset->setEnabled(false);
    startFlag = true;
    this->thread->start();
}

// stop showing
void Form::on_btnStop_clicked()
{
    ui->btnStop->setEnabled(false);
    ui->btnStart->setEnabled(true);
    ui->btnReset->setEnabled(true);
    startFlag = false;
}

// reset queen number
void Form::on_btnReset_clicked()
{
    ui->btnStart->setEnabled(false);
    ui->btnConfirm->setEnabled(true);
    startFlag = true;
    retFlag = true;
    for (int i = 0; i < QUEEN_NUM; i++) {
        for (int j = 0; j < QUEEN_NUM; j++) {
            ui->table->setItem(i, j, NULL);
        }
    }
}
