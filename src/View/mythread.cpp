#include "mythread.h"

MyThread* MyThread::instance_ = nullptr;

MyThread::~MyThread() { delete GetInstance(); }

void MyThread::run() {
    stop_ = false;
    while (true) {
        emit Update();
        QThread::msleep(fps_);
        if (stop_) break;
    }
}

MyThread* MyThread::GetInstance() {
    if (!instance_) instance_ = new MyThread();
    return instance_;
}

void MyThread::ChangeFps(int fps) { GetInstance()->fps_ = fps; }

void MyThread::Stop() { stop_ = true; }
