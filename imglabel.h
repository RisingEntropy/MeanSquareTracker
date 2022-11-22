#ifndef IMGLABEL_H
#define IMGLABEL_H

#include <QObject>
#include <QLabel>
#include <QEvent>
class ImgLabel : public QLabel {
private:
    bool *selectMode;

    int startX,startY,endX,endY;
    int currX,currY;
    bool selected = false;
    bool mousePressed = false;
    void enterEvent(QEvent *event)override;
    void mousePressEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent *event)override;
    void mouseMoveEvent(QMouseEvent*event)override;
    void paintEvent(QPaintEvent*event)override;
public:
    ImgLabel(QWidget*parent = nullptr);
    explicit ImgLabel(bool *mode,QWidget *parent = nullptr);
    void setMode(bool *mode);
    QRect getRect();
    bool hasSelected();
public slots:
    void onBoxing(QRect rect,QPixmap img,int loss);
};

#endif // IMGLABEL_H
