#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <vector>
#include "globals.h"

class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread(std::vector<int> *);

protected:
    virtual void run();

private:
    bool isOk(int row, int col);
    void dfs(int row);

    std::vector<int> *columns;

signals:
    void sigUpdateView();
};

#endif // MYTHREAD_H
