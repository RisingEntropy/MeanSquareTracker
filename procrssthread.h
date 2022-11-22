#ifndef PROCRSSTHREAD_H
#define PROCRSSTHREAD_H

#include <QObject>
#include <QThread>
#include <QRect>
#include <QPixmap>
class ProcrssThread : public QThread {
    Q_OBJECT
private:
    QStringList files;
    int duration;
    QRect rect;
public:
    ProcrssThread(QStringList files,QRect rect,int duration = 180);
    void run()override;
signals:
    void sendBox(QRect rect, QPixmap img,int loss);

};

#endif // PROCRSSTHREAD_H
