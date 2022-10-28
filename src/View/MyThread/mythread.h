#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <unistd.h>

#include <QThread>
#include <QTimer>

class MyThread : public QThread {
    Q_OBJECT
public:
    ~MyThread();
    void run();
    static MyThread* GetInstance();
    void ChangeFps(int fps);
    void Stop();

private:
    static MyThread* instance_;
    int fps_;
    bool stop_ = false;
signals:
    void Update();
};

#endif  // MYTHREAD_H
