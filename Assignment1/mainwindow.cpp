#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QtWidgets>
#include <QtMath>

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

void dda(float x1,float y1,float x2,float y2,QImage &img)
{
        int length,dx,dy,x,y,i;
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
}
void circle(float p,float q,float r,QImage &img)
{
    int x,y,d;
    d = 3 - (2*r);
    x=0;
    y=r;
    while(x<=y)
    {         img.setPixel(x+p,y+q,qRgb(0,255,0));
              img.setPixel(-x+p, y+q,qRgb(0,255,0));
              img.setPixel(x+p, -y+q,qRgb(0,255,0));
              img.setPixel(-x+p, -y+q,qRgb(0,255,0));
              img.setPixel(y+p, x+q,qRgb(0,255,0));
              img.setPixel(y+p, -x+q,qRgb(0,255,0));
              img.setPixel(-y+p, x+q,qRgb(0,255,0));
              img.setPixel(-y+p, -x+q,qRgb(0,255,0));

              if(d<=0)
              {
                 d=d+4*(x)+6;
              }
              else
              {
                 d=d+4*(x-y)+10;
                 y=y-1;
              }
              x = x+1;
    }
}
void BresenhemLine(double x1, double y1, double x2, double y2,QImage &img)
{
    double x=x1, y=y1;
    double dx=abs(x2-x1);
    double dy=abs(y2-y1);
    int s1,s2;
    if((x2-x1)<0)
    {
        s1 = -1;
    }
    else if ((x2-x1) == 0)
    {
        s1 = 0;
    }
    else {
        s1 = 1;
    }
    if((y2-y1)<0)
    {
        s2 = -1;
    }
    else if((x2-x1)==0)
    {
        s2 = 0;
    }
    else {
        s2 = 1;
    }
    double interchange;
    if(dy>dx){
        double temp=dx;
        dx=dy;
        dy=temp;
        interchange=1;
    }
    else{
        interchange=0;
    }

    double e=2*dy-dx;

    for(int i=0; i<=dx; i++){
        img.setPixel(x, y, qRgb(255,255,255));
        while(e>0){
            if(interchange==1){
                x=x+s1;
            }
            else{
                y=y+s2;
            }
            e=e-(2*dx);
        }
        if(interchange==1){
            y=y+s2;
        }
        else{
            x=x+s1;
        }
        e=e+(2*dy);
    }
}

void MainWindow::on_pushButton_clicked()
{
    int l,b,x,y;
    l = ui->textEdit->toPlainText().toInt();
    b = ui->textEdit_2->toPlainText().toInt();
    x = ui->textEdit_3->toPlainText().toInt();
    y = ui->textEdit_4->toPlainText().toInt();

    QImage img(400,400,QImage::Format_RGB888);
    //Rectangle
    dda(x,y,x+l,y,img);
    dda(x,y,x,y+b,img);
    dda(x+l,y,x+l,y+b,img);
    dda(x,y+b,x+l,y+b,img);
    //Rhombus
    float xm = l/2,ym = b/2;
    BresenhemLine(x+xm,y,x+l,y+ym,img);
    BresenhemLine(x+l,y+ym,x+xm,y+b,img);
    BresenhemLine(x+xm,y+b,y,y+ym,img);
    BresenhemLine(x,y+ym,x+xm,y,img);
    //Circle
    float r;
    r = (l * b)/(2 * sqrt ( l*l + b*b ));
    circle(x+l/2,y+b/2,r,img);

    ui->label_4->setPixmap(QPixmap::fromImage(img));
}
