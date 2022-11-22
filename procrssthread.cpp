#include "procrssthread.h"
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <math.h>
ProcrssThread::ProcrssThread(QStringList files, QRect rect, int duration) {
    this->files = files;
    this->duration = duration;
    this->rect = rect;
}

void ProcrssThread::run() {
    QImage last,ori;
    QRect ori_rec;
    bool hasFirst = false;;
    for(QString file:this->files) {
        QImage img ;
        if(!img.load(file))return;
        if(!hasFirst) {
            hasFirst = true;
            last = img;
            ori = img;
            ori_rec = this->rect;
        }
        int h = img.height(),w = img.width();
        int mw = this->rect.width();
        int mh = this->rect.height();

        int Monte = qMax(mw,mh)*2;
        int tx,ty;
        long long mn = 0x7ffffff;
        int mx = this->rect.x();
        int my = this->rect.y();
        int ox = ori_rec.x();
        int oy = ori_rec.y();
        for(int x = qMax(0,this->rect.x()-2*this->rect.width()); x<qMin(w-mw,this->rect.x()+2*this->rect.width()); x+=2) {
            if(x>=w-mw)continue;
            for(int y = qMax(0,this->rect.y()-2*this->rect.height()); y<qMin(h-mh,this->rect.y()+2*this->rect.height()); y++) {
                long long sum = 0;
                for(int i = 0; i<Monte; i++) {
                    int wx = rand()%rect.width();
                    int wy = rand()%rect.height();

                    sum+=(img.pixelColor(x+wx,y+wy).red()-last.pixelColor(mx+wx,my+wy).red())*(img.pixelColor(x+wx,y+wy).red()-last.pixelColor(mx+wx,my+wy).red());
                    if(!img.isGrayscale()) {
                        sum+=(img.pixelColor(x+wx,y+wy).blue()-last.pixelColor(mx+wx,my+wy).blue())*(img.pixelColor(x+wx,y+wy).blue()-last.pixelColor(mx+wx,my+wy).blue());

                        sum+=(img.pixelColor(x+wx,y+wy).green()-last.pixelColor(mx+wx,my+wy).green())*(img.pixelColor(x+wx,y+wy).green()-last.pixelColor(mx+wx,my+wy).green());

                    }
                    if(sum>=mn)break;
                }
                if(sum<mn) {
                    mn = sum;
                    tx = x,ty = y;
                }
            }
        }
        this->rect = QRect(tx,ty,mw,mh);
        last = img;
        emit sendBox(this->rect,QPixmap::fromImage(img),sqrt(mn));
        QThread::msleep(duration);
    }
}
