#ifndef KOCH_CURVE_H
#define KOCH_CURVE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Koch_Curve; }
QT_END_NAMESPACE

class Koch_Curve : public QMainWindow
{
    Q_OBJECT

public:

    Koch_Curve(QWidget *parent = nullptr);

    ~Koch_Curve();

private slots:

    void on_show_clicked();

    void on_GetColour_clicked();

    void on_Clear_clicked();

    void on_Draw_clicked();

private:

    Ui::Koch_Curve *ui;

    float a[20], b[20];
    int ver = 0;
    bool start = false;

    void dda_line ( float, float, float, float );

    void mousePressEvent ( QMouseEvent * );

    void koch_curve ( float, float, float, float, int);

};
#endif // KOCH_CURVE_H
