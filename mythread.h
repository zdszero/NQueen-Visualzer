#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "globals.h"

class MyThread : public QThread
{
public:
    MyThread();

protected:
    virtual void run();

private:
    bool isOk(int row, int col);
    void dfs(int row);

signals:
    void sigUpdateView();
};

#endif // MYTHREAD_H
