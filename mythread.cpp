#include "mythread.h"

MyThread::MyThread()
{
}

void MyThread::run()
{
}

void MyThread::dfs(int row)
{
    /* try all columns in current row */
    for (int c = 0; c < QUEEN_NUM; c++) {
        if (isOk(row, c)) {
            columns[row] = c;
            if (row == QUEEN_NUM - 1)
                emit sigUpdateView();
            else
                dfs(row + 1);
        }
    }
    columns[row] = -1;
}

bool MyThread::isOk(int row, int col)
{
    /* for all previous rows */
    for (int r = 0; r < row; r++) {
        /* column collision */
        if (columns[r] == col)
            return false;
        /* diagonal collision */
        if ((r + columns[r] == row + col) || (r - columns[r] == row - col))
            return false;
    }
    return true;
}
