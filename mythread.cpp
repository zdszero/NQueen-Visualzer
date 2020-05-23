#include "mythread.h"
#include <QDebug>

MyThread::MyThread(std::vector<int> *columns)
{
    this->columns = columns;
}

void MyThread::run()
{
    qDebug() << "thread started to run";
    dfs(0);
    qDebug() << "thread finished running";
}

void MyThread::dfs(int row)
{
    // finish dfs function if retFlag is true
    if (retFlag == true)
        return;
    /* try all columns in current row */
    for (int c = 0; c < QUEEN_NUM; c++) {
        if (isOk(row, c)) {
            (*this->columns)[row] = c;
            if (row == QUEEN_NUM - 1) {
                emit sigUpdateView();
                // sleep after get each solution
                QThread::msleep(sleepTime);
                // spinning if startFlag is false
                while (startFlag != true);
            }
            else {
                if (retFlag == true)
                    return;
                dfs(row + 1);
            }
        }
    }
    (*this->columns)[row] = -1;
}

bool MyThread::isOk(int row, int col)
{
    /* for all previous rows */
    for (int r = 0; r < row; r++) {
        /* column collision */
        if ((*this->columns)[r] == col)
            return false;
        /* diagonal collision */
        if ((r + (*this->columns)[r] == row + col) || (r - (*this->columns)[r] == row - col))
            return false;
    }
    return true;
}
