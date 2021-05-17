#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtWidgets"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{   int x1,x2,y1,y2,length,dx,dy,x,y,i;
    x1 = ui->textEdit->toPlainText().toInt();
    y1 = ui->textEdit_2->toPlainText().toInt();
    x2 = ui->textEdit_3->toPlainText().toInt();
    y2 = ui->textEdit_4->toPlainText().toInt();
    QImage img(300,300,QImage::Format_RGB888);

    if (abs(x2-x1)>abs(y2-y1))
    {
        length = abs(x2-x1);
        dx = (x2-x1)/length;
        dy = (y2-y1)/length;
    }
    else
    {
        length = abs(y2-y1);
        dx = (x2-x1)/length;
        dy = (y2-y1)/length;
    }
    x = x1 + 0.5 ;
    y= y1 + 0.5;

   i = 1;
   while(i<=length)
   {
       img.setPixel(int(x),int(y),qRgb(0,255,0));
       x = x + dx;
       y = y + dy;
       i++;
   }
   ui->label->setPixmap(QPixmap::fromImage(img));
}
