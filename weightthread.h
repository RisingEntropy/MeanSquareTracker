#ifndef WEIGHTTHREAD_H
#define WEIGHTTHREAD_H


#include <QObject>
#include <QThread>
#include <QRect>
#include <QPixmap>
class WeightThread : public QThread {
    Q_OBJECT
private:
    QStringList files;
    int duration;
    QRect rect;
public:
    WeightThread(QStringList files,QRect rect,int duration = 180);
    void run()override;
signals:
    void sendBox(QRect rect, QPixmap img,int loss);

};


#endif // WEIGHTTHREAD_H
