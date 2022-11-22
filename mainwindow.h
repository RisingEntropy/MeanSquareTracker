#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    bool fileChosen = false,selectMode = false;
    QStringList files;
private slots:
    void processFinish(QPixmap img);
    void on_pushButton_file_clicked();
    void on_pushButton_zone_clicked();
    void on_pushButton_start_clicked();
    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
