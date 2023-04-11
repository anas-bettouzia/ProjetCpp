#include "statistiques.h"
#include "ui_statistiques.h"
#include <QPainter>
statistiques::statistiques(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistiques)
{
    ui->setupUi(this);
}
void statistiques::paintEvent(QPaintEvent *)
{

     int A=V.statistique1();
     int B=V.statistique2();
     float s1= A*100 ;
            float s2=B*100;
            float nb = A+B;
            float q2 ;
            q2 = s1/nb ;
            float q3;
            q3=s2/nb;
            float y  ;
            y = (q2*360)/100 ;
            float m;
            m= (q3*360)/100;

           QPainter painter(this);
           QRectF size=QRectF(10,10,this->width()-100,this->width()-100);
           painter.setBrush(Qt::blue);

           painter.drawPie(size,0,16*y);
           painter.setBrush(Qt::green);
           painter.drawPie(size,16*y,16*m);


        update();
   }
statistiques::~statistiques()
{
    delete ui;
}

void statistiques::on_pushButton_11_clicked()
{
    close();
}
