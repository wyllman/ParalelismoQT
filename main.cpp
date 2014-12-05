#include <QApplication>
#include "mainwindow.h"

#include <QtGui>
#include <QDateTime>

#include <iostream>

using namespace std;
//#include <QtCore>

class Thread : public QThread {
    Q_OBJECT

public:
      Thread():m_stop(false), _contador(0) {}
      int _contador;
      QTime _time;

public slots:
    void stop() {
        qDebug()<<"Thread::stop called from main thread: "<<currentThreadId();
        QMutexLocker locker(&m_mutex);
        m_stop=true;
    }

private:
    QMutex m_mutex;
    bool m_stop;
    //QDate _date; // = QDate::currentDate();
     // = QTime::currentTime();


    void run() {
        /*qDebug()<<"From worker thread: "<<currentThreadId();
        while (1) {
            {
            QMutexLocker locker(&m_mutex);
            if (m_stop) {
               _time = QTime::currentTime();
               //_date = QDate::currentDate();
               qDebug() << "Hora: " << _time.toString("hh:mm:ss.zzz");
               qDebug() << "hola desde:" << currentThreadId() << endl;
               ++_contador;
               if (_contador >= 5) break;
               //_date = QDate::currentDate();
               m_stop = false;
            }
            }
            //msleep(10);
        }*/
        _time = QTime::currentTime();
        qDebug() << "Hora: " << _time.toString("hh:mm:ss.zzz");
    }
};

class MainThread: public QObject {
   Q_OBJECT
   public:
         MainThread() {}
         QTime _time;

   public slots:
       void mainRun() {
           _time = QTime::currentTime();
           qDebug() << "Hora(m): " << _time.toString("hh:mm:ss.zzz");
           //qDebug() << "MainThread::mainRun() called from main thread: " << QThread::currentThreadId();
           //QMutexLocker locker(&m_mutex);
           //m_stop=true;
       }
};

#include "main.moc"
int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    qDebug() << "Numero de cores: " << QThread::idealThreadCount();
    qDebug() << "From main thread: " << QThread::currentThreadId();
    QPushButton btn("Stop Thread");
    Thread* t = new Thread ();
    //Thread* t2 = new Thread ();
    MainThread* mT = new MainThread ();

    //QObject::connect(&btn, SIGNAL(clicked()), t, SLOT(stop()));
    QObject::connect(&btn, SIGNAL(clicked()), t, SLOT(start()));
    //QObject::connect(&btn, SIGNAL(clicked()), t2, SLOT(stop()));

    QObject::connect(&btn, SIGNAL(clicked()), mT, SLOT(mainRun()));
    //QObject::connect(t, SIGNAL(finished()), &a, SLOT(quit()));

    //t->start();
    //t2->start();
    btn.show();

    int reNum = a.exec();
    //t->wait();
    //t2->wait();
    qDebug() << "Ultimas horas registradas.";
    qDebug() << t->_time.toString("hh:mm:ss.zzz");
    qDebug() << mT->_time.toString("hh:mm:ss.zzz");
    //qDebug() << t2->_contador;

    return reNum;
}


/*
int main(int argc, char *argv[]) {
   QApplication a(argc, argv);
   MainWindow w;
   w.show();
   
   return a.exec();
}*/
