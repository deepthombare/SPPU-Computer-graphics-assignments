#include "koch_curve.h"
#include "ui_koch_curve.h"
#include <QMessageBox>
#include <QMouseEvent>
#include <QColorDialog>
#include <math.h>
#include <iostream>
using namespace std;

Koch_Curve::Koch_Curve(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Koch_Curve)
{
    ui->setupUi(this);
    start = false;
    ver = 0;

    connect( ui -> Draw, SIGNAL ( clicked() ), this, SLOT ( mousePressEvent (QMouseEvent *ev) ) );
}


QImage image ( 900, 900, QImage :: Format_RGB888 );
QColor c;


void Koch_Curve :: dda_line ( float x1, float y1, float x2, float y2 )
{
                                                // Draws line from (x1, y1) to (x2, y2)

    float dx, dy, length, x, y;
    dx = x2 - x1;
    dy = y2 - y1;
                                // greater between dx and dy will be assigned to length
    if ( abs(dx) > abs(dy) )
    {
        length = abs(dx);
    }

    else
    {
        length = abs(dy);
    }

    dx = dx / length;   // Increment in x co-ordinate
    dy = dy / length;   // Increment in y co-ordinate
    x = x1;
    y = y1;

    int i=0;
    image.setPixel ( x, y, c.rgb() );   // plotting first point

    while (i < length)
    {
        x = x + dx;
        y = y + dy;
        image.setPixel ( x, y, c.rgb() );   // plotting other points
        i++;
    }

    ui -> Image -> setPixmap ( QPixmap :: fromImage ( image ) );
}


void Koch_Curve :: koch_curve ( float x1, float y1, float x2, float y2, int it )
{
                        // Draws Koch curve from (x1, y1) to (x2, y2) with it iterations


    float angle = ( 60 * M_PI ) / 180;      // Conversion from degree to radian

    float x3 = ( ( 2 * x1 ) + x2 ) / 3;// (x3, y3) will be at distance of 1/3 length of line from (x1, y1)
    float y3 = ( ( 2 * y1 ) + y2 ) / 3;

    float x4 = ( x1 + ( 2 * x2 ) ) / 3;// (x4, y4) will be at distance of 1/3 length of line from (x2, y2)
    float y4 = ( y1 + ( 2 * y2 ) ) / 3;

    float x = x3 + ( ( x4 - x3 ) * cos(angle) ) + ( ( y4 - y3 ) * sin(angle) );
    float y = y3 - ( ( x4 - x3 ) * sin(angle) ) + ( ( y4 - y3 ) * cos(angle) );

    if (it > 0)
    {                                           // Recursive Calls for each segement
        koch_curve ( x1, y1, x3, y3, it-1 );

        koch_curve ( x3, y3, x, y, it-1 );

        koch_curve ( x, y, x4, y4, it-1 );

        koch_curve ( x4, y4, x2, y2, it-1 );
    }

    else
    {                                       // call to dda_line to join points
        dda_line ( x1, y1, x3, y3 );

        dda_line ( x3, y3, x, y );

        dda_line ( x, y, x4, y4 );

        dda_line ( x4, y4, x2, y2 );
    }
}


void Koch_Curve :: mousePressEvent ( QMouseEvent *ev )
{
    start = true;
        if ( start )
        {
            if ( ev->pos().x()<900 && ev->pos().x()>0 && ev->pos().y()<900 && ev->pos().y()>0 )
            {
                 int p = ev -> pos().x();           // Exception handling for 900 * 900 size
                 int q = ev -> pos().y();
                 a[ver] = p;
                 b[ver] = q;

                 if ( ev -> button() == Qt :: RightButton ) // Right click
                 {               
                      start = false;
                 }

               ver++;   // increment in number of vertices
           }

            else    // If we click out of image label
            {
                 QMessageBox :: critical ( this, " ERROR ", " Invalid Pixel Position...!!!" );
            }

        a[ver] = a[0];
        b[ver] = b[0];
    }
}


void Koch_Curve :: on_show_clicked()     // to show label
{
    start = false;
    ver = 0;

    ui -> Image -> setPixmap ( QPixmap :: fromImage ( image ) );
}


void Koch_Curve :: on_GetColour_clicked()    // to choose colour
{
    c = QColorDialog :: getColor();
}


void Koch_Curve :: on_Clear_clicked()    // clears label
{
    image.fill(0);

    start = false;
    ver = 0;

    ui -> Image -> setPixmap ( QPixmap :: fromImage ( image ) );
}


Koch_Curve::~Koch_Curve()
{
    delete ui;
}



void Koch_Curve::on_Draw_clicked()
{
    int it = ui -> iterations -> toPlainText().toInt();

     if (ui -> iterations -> toPlainText().isEmpty() || it < 0 || it > 6)
     {
                                                            // Iterating Factor range 0-6

         QMessageBox :: critical ( this, " ERROR ", "  Invalid Iterations...!!! " );
     }
    int i = ver;
    while(i>0)
    {
        koch_curve ( a[ver], b[ver], a[ver-1], b[ver-1], it );
        i--;
    }
    koch_curve ( a[0], b[0], a[ver-1], b[ver-1], it );

}
