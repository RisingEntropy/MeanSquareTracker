#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <procrssthread.h>
#include "imglabel.h"
#include "weightthread.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->ui->label->setMode(&this->selectMode);
    QMessageBox::information(this,tr("Welcome"),tr("欢迎使用本程序\n"),QMessageBox::Ok);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::processFinish(QPixmap img) {
    ui->label->setPixmap(img);
}


void MainWindow::on_pushButton_file_clicked() {
    QString filter="图片文件(*.jpg *.gif *.png *.bmp)";
    QStringList files = QFileDialog::getOpenFileNames(this,tr("选择文件"),"./",filter);
    files.sort();
    QImage* img = new QImage;
    img->load(files[0]);
//    ui->label->setAlignment(Qt::A)
    ui->label->setPixmap(QPixmap::fromImage(*img));
    this->files = files;
    this->fileChosen = true;

}

void MainWindow::on_pushButton_zone_clicked() {
    this->selectMode = true;

}

void MainWindow::on_pushButton_start_clicked() {
    if(!fileChosen) {
        QMessageBox::warning(this,tr("错误"),tr("未选择文件"));
        return;
    }
    if(!ui->label->hasSelected()) {
        QMessageBox::warning(this,tr("错误"),tr("未选择区域"));
        return;
    }
    ProcrssThread *thread = new ProcrssThread(this->files,ui->label->getRect(),ui->spinBox->value());
    connect(thread,&ProcrssThread::sendBox,ui->label,&ImgLabel::onBoxing);
    thread->start();

}

void MainWindow::on_pushButton_clicked() {
    if(!fileChosen) {
        QMessageBox::warning(this,tr("错误"),tr("未选择文件"));
        return;
    }
    if(!ui->label->hasSelected()) {
        QMessageBox::warning(this,tr("错误"),tr("未选择区域"));
        return;
    }
    WeightThread *thread = new WeightThread(this->files,ui->label->getRect(),ui->spinBox->value());
    connect(thread,&WeightThread::sendBox,ui->label,&ImgLabel::onBoxing);
    thread->start();
}
