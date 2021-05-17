#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"qmath.h"
#include<QColorDialog>
static QImage img(500,500,QImage::Format_RGB888);
QColor C;
#define SIN(x) sin(x * 3.141592653589/180)
#define COS(x) cos(x * 3.141592653589/180)
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
class Matrix
{
public: int mat[1][2] = {{0}}, trans[2][2];
        Matrix operator * (Matrix &b)
        {   Matrix out;
                int k;
                for(int j = 0;j<=1;j++)
                {   int sum = 0;
                    for (k = 0; k < 2; k++)
                    {
                        sum +=  this->mat[0][k]*b.trans[k][j];
                    }
                    out.mat[0][j] = sum ;
                }
            return out;
        }

};

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
        img.setPixel(x, y, C.rgb());
        x += xincr;
        y += yincr;

    }
     ui->label->setPixmap(QPixmap::fromImage(img));
}


void MainWindow::on_pushButton_4_clicked()
{
    base = ui->textEdit_7->toPlainText().toInt();
    float h = base*sqrt(3)/2;

    DDA(25,75,25+base,75,img);
    DDA(25,75,25+base/2,h,img);
    DDA(25+base,75,25+base/2,h,img);
    c[0][0] = 25;
    c[0][1] = 75;
    c[1][0] = 25+base;
    c[1][1] = 75;
    c[2][0] = 25+base/2;
    c[2][1] = h;
    c[3][0] = 25;
    c[3][1] = 75;
}

void MainWindow::on_pushButton_5_clicked()
{
     ld = ui->textEdit_8->toPlainText().toInt();
     sd = ui->textEdit_6->toPlainText().toInt();
     c[0][0] = 25;
     c[0][1] = 150;
     c[1][0] = 25+ld/2;
     c[1][1] = 150+sd/2;
     c[2][0] = 25+ld;
     c[2][1] = 150;
     c[3][0] = 25+ld/2;
     c[3][1] = 150 - sd/2;
    DDA(c[0][0],c[0][1],c[1][0],c[1][1],img);
    DDA(c[1][0],c[1][1],c[2][0],c[2][1],img);
    DDA(c[2][0],c[2][1],c[3][0],c[3][1],img);
    DDA(c[0][0],c[0][1],c[3][0],c[3][1],img);

}

void MainWindow::on_pushButton_2_clicked()      //Scaling
{
    sx = ui->textEdit_3->toPlainText().toInt();
    sy = ui->textEdit_4->toPlainText().toInt();
    Matrix res;
    Matrix scale;
    scale.trans[0][0] = sx;
    scale.trans[0][1] = 0;
    scale.trans[1][0] = 0;
    scale.trans[1][1] = sx;

    for (int r = 0; r < 4; r++)
    {   Matrix out;
        res.mat[0][0] =c[r][0];
        res.mat[0][1] =c[r][1];
        out = res * scale;
        c[r][0] = out.mat[0][0];
        c[r][1] = out.mat[0][1];
        //c[r][0] = c[r][0] * sx;
        //c[r][1] = c[r][1] * sy;
    }

    DDA(c[0][0],c[0][1],c[1][0],c[1][1],img);
    DDA(c[1][0],c[1][1],c[2][0],c[2][1],img);
    DDA(c[2][0],c[2][1],c[3][0],c[3][1],img);
    DDA(c[0][0],c[0][1],c[3][0],c[3][1],img);

}

void MainWindow::on_pushButton_3_clicked()         //Rotation
{   int angle = ui->textEdit_5->toPlainText().toInt();
    int x_pivot = 0,y_pivot = 0;
    int i = 0;
    while (i < 4)
    {
        int x_shifted = c[i][0] - x_pivot;
        int y_shifted = c[i][1] - y_pivot;
        c[i][0] = x_pivot + (x_shifted*COS(angle)
                          - y_shifted*SIN(angle));
        c[i][1] = y_pivot + (x_shifted*SIN(angle)
                          + y_shifted*COS(angle));
        i++;
    }
    DDA(c[0][0],c[0][1],c[1][0],c[1][1],img);
    DDA(c[1][0],c[1][1],c[2][0],c[2][1],img);
    DDA(c[2][0],c[2][1],c[3][0],c[3][1],img);
    DDA(c[0][0],c[0][1],c[3][0],c[3][1],img);
}

void MainWindow::on_pushButton_clicked()  //Translation
{
    int tx = ui->textEdit->toPlainText().toInt();
    int ty = ui->textEdit_2->toPlainText().toInt();
    int T[] = {tx, ty};
    for (int i = 0;i<4;i++)
    {
        c[i][0] = c[i][0] + T[0];
        c[i][1] = c[i][1] + T[1];
    }

    DDA(c[0][0],c[0][1],c[1][0],c[1][1],img);
    DDA(c[1][0],c[1][1],c[2][0],c[2][1],img);
    DDA(c[2][0],c[2][1],c[3][0],c[3][1],img);
    DDA(c[0][0],c[0][1],c[3][0],c[3][1],img);
}

void MainWindow::on_pushButton_6_clicked()
{
    C=QColorDialog::getColor();
}
