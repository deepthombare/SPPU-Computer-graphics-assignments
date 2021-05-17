#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *ev);
    void BresenhemLine(float x1, float y1, float x2, float y2);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
private slots:
private:
    Ui::MainWindow *ui;
    int ver,a[20],b[20],i,xi[20],j,k;

    bool start;

};
#endif // MAINWINDOW_H
