#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
using namespace  std;
#include<QColorDialog>
QColor C;
static QImage img(500,500,QImage::Format_RGB888);
static QImage img2(500,500,QImage::Format_RGB888);

const int L = 1;        // 0001
const int R = 2;        // 0010
const int B = 4;        // 0100
const int T = 8;        // 1000
const int INSIDE = 0;   // 0000

const int xmax = 450;
const int ymax = 350;
const int xmin = 50;
const int ymin = 150;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    start = true;
    accept = false;
    ver = 0;
    cnt = 0;

}

MainWindow::~MainWindow()
{
    delete ui;
}
int computeCode(double x, double y)
{
    int code = INSIDE;

    if (x < xmin)
        code |= L;
    else if (x > xmax)
        code |= R;
    if (y < ymin)
        code |= B;
    else if (y > ymax)
        code |= T;

    return code;
}
void MainWindow::DDA(int x1, int y1, int x2, int y2,QImage &img)
{
    float dx, dy, step;
    dx = x2 - x1;
    dy = y2 - y1;
    if(abs(dx) > abs(dy))
        step = abs(dx);
    else
        step = abs(dy);

    float x =x1,y = y1;

    float xincr = dx / step, yincr = dy / step;

    for(int i = 0;i<step;++i)
    {
        img.setPixel(x,y, C.rgb());
        x += xincr;
        y += yincr;

    }
     ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::mousePressEvent(QMouseEvent *ev)
{

    if(start)
    {
        cnt++;
        int p = ev->pos().x();
        int q = ev->pos().y();
        a[ver] = p;
        b[ver] = q;

        if(ev->button() == Qt::RightButton)
        {
            start = false;
        }

        if(cnt == 2)
       {
            if(ver > 0)
        {
            DDA(a[ver],b[ver],a[ver-1],b[ver-1],img);
        }
        cnt = 0;
        }

        ver++;

      }


}


void MainWindow::cohenSutherlandClip(double x1, double y1,double x2, double y2)
{    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    bool accept = false;

    while (true)
    {
            if ((code1 == 0) && (code2 == 0))
            {
                accept = true;
                break;
            }
            else if (code1 & code2)
            {
                break;
            }
            else
            {
                    int code_out;
                    double x, y;

                    if (code1 != 0)
                        code_out = code1;
                    else
                        code_out = code2;

                    if (code_out & T) {
                        x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                        y = ymax;
                    }
                    else if (code_out & B) {
                        x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                        y = ymin;
                    }
                    else if (code_out & R) {
                        y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                        x = xmax;
                    }
                    else if (code_out & L) {
                        y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                        x = xmin;
                    }
                    if (code_out == code1) {
                        x1 = x;
                        y1 = y;
                        code1 = computeCode(x1, y1);
                    }
                    else
                    {
                        x2 = x;
                        y2 = y;
                        code2 = computeCode(x2, y2);
                    }
            }
    }
    if (accept) { DDA(x1,y1,x2,y2,img2);}
}

void MainWindow::on_pushButton_clicked()
{
    DDA(50,150,450,150,img);
    DDA(50,150,50,350,img);
    DDA(50,350,450,350,img);
    DDA(450,150,450,350,img);

    DDA(50,150,450,150,img2);
    DDA(50,150,50,350,img2);
    DDA(50,350,450,350,img2);
    DDA(450,150,450,350,img2);
}

void MainWindow::on_pushButton_2_clicked()
{
       for(i = 0;i < ver;i+=2)
       {
           cohenSutherlandClip(a[i],b[i],a[i+1],b[i+1]);
       }
}


void MainWindow::on_pushButton_3_clicked()
{
    C=QColorDialog::getColor();
}
