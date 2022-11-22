#include "imglabel.h"
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
ImgLabel::ImgLabel(bool *mode,QWidget *parent):QLabel(parent) {
    this->selectMode = mode;
}

void ImgLabel::setMode(bool *mode) {
    this->selectMode = mode;
}

QRect ImgLabel::getRect() {
    qDebug()<<"w:"<<endX-startX<<"Y:"<<endY-startY;
    return QRect(startX,startY,endX-startX,endY-startY);
}

bool ImgLabel::hasSelected() {
    return this->selected;
}

void ImgLabel::onBoxing(QRect rect, QPixmap img,int loss) {
    QPainter painter(&img);
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawRect(rect);
    painter.drawText(QPointF(0,10),QString("mse_loss:%1").arg(loss));
    this->setPixmap(img);
}

void ImgLabel::enterEvent(QEvent *event) {

    qDebug()<<"mouse enter";
    if(*this->selectMode) {
        setCursor(Qt::CrossCursor);
    } else {
        setCursor(Qt::ArrowCursor);
    }
}

void ImgLabel::mousePressEvent(QMouseEvent *event) {
    if(*this->selectMode) {
        if(event->button()==Qt::LeftButton) {
            this->mousePressed = true;
            this->startX = event->x();
            this->startY = event->y();
            this->currX = event->x();
            this->currY = event->y();
        }
    }
}

void ImgLabel::mouseReleaseEvent(QMouseEvent *event) {
    if(*this->selectMode) {
        if(event->button()==Qt::LeftButton) {
            this->mousePressed = false;
            this->endX = event->x();
            this->endY = event->y();
            this->selected = true;
            *this->selectMode = false;
            setCursor(Qt::ArrowCursor);
            update();
        }
    }
}

void ImgLabel::mouseMoveEvent(QMouseEvent *event) {
    if(this->mousePressed) {
        this->currX = event->x();
        this->currY = event->y();
        update();
    }
}

void ImgLabel::paintEvent(QPaintEvent *event) {
    QLabel::paintEvent(event);
    if(*this->selectMode) {
        QPainter painter(this);
        QPen pen;
        pen.setColor(Qt::red);
        pen.setWidth(3);
        painter.setPen(pen);
        painter.drawRect(startX,startY,currX-startX+1,currY-startY+1);
    }
}

ImgLabel::ImgLabel(QWidget *parent):QLabel(parent) {

}
