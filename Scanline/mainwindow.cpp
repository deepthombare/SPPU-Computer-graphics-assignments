#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"iostream"
#include"QMouseEvent"
#include<QTimer>
#include<QColorDialog>
using namespace std;
QColor C;
static QImage img(500,500,QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ver=0;
    start=true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *ev)
{
  if(start)
  {
      int p=ev->pos().x();
      int q=ev->pos().y();
      a[ver]=p;
      b[ver]=q;
      if(ev->button()==Qt::RightButton)
      {
          BresenhemLine(a[0],b[0],a[ver-1],b[ver-1]);
          a[ver] = a[0];
          b[ver] = b[0];
          start=false;
      }
      else
      {
          if(ver>0)
          {
              BresenhemLine(a[ver],b[ver],a[ver-1],b[ver-1]);
          }
      }
      ver++;


  }
}

void MainWindow::BresenhemLine(float x1, float y1, float x2, float y2)
{
    float x=x1, y=y1;
    float dx=abs(x2-x1);
    float dy=abs(y2-y1);
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
        img.setPixel(x, y, C.Rgb);
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
    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_pushButton_clicked()
{
    float xmin,ymin,xmax,ymax,inter[20];
    xmin=xmax=a[0];
    ymin=ymax=b[0];
    for(int i=1;i<ver;i++)
    {
        if(xmin>a[i])
        xmin=a[i];
        if(xmax<a[i])
        xmax=a[i];
        if(ymin>b[i])
        ymin=b[i];
        if(ymax<b[i])
        ymax=b[i];
    }
    float z,x;
    int c = 0;
    for (z = ymin+0.01; z<=ymax;z++)
    {   int x1,x2,y1,y2,temp;
        c=0;
        for(int i=0;i<ver;i++)
        {
            x1=a[i];
            y1=b[i];
            x2=a[i+1];
            y2=b[i+1];
            if(y2<y1)
            {
                temp=x1;
                x1=x2;
                x2=temp;
                temp=y1;
                y1=y2;
                y2=temp;
            }
            if(z<=y2&&z>=y1)
            {
                if((y1-y2)==0)
                    x=x1;
                else // used to make changes in x. so that we can fill our polygon after cerain distance
                {
                    x=((x2-x1)*(z-y1))/(y2-y1);
                    x=x+x1;
                }
                if(x<=xmax && x>=xmin)
                    inter[c++]=x;
            }
        }
        for(int i=0; i<c;i+=2)
        {
             BresenhemLine(inter[i],z,inter[i+1],z);  // Used to fill the polygon ....
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    C=QColorDialog::getColor();
}
