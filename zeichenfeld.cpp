using namespace std;
#include <QtGui>
#include <QMessageBox>
#include <QKeyEvent>
#include <QLabel>
#include <QTextStream>
#include "zeichenFeld.h"


zeichenFeld::zeichenFeld(QWidget *parent): QWidget(parent)
{

    /*hier wird das Design des Spielfeldes festgelegt*/
    setPalette(QPalette(QColor(46, 139, 87)));
    setAutoFillBackground(true);
    setMouseTracking(false);

    /*hier wird die Start-Position des Avatar festgelegt*/

    x=225, y=450;

    /*hier wird der Timer für die "Gegner-Objekte" generiert*/

    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    /*hier wird die y-Start-Position der "Gegner-Objeket" festgelegt*/

    lastU=-1000;
    lastV=-50;
    lastW=-100;

     /*hier wird die x-Start-Position der "Gegner-Objekte" festgelegt*/

    lastA=25;
    lastB=125;
    lastC=346;

    increment=0;
    zaehler=0;

    /*hier wird der Punktestand eingeblendet*/

    label = new QLabel(this);
    label->setNum(zaehler);
    label->setFont(QFont("Times", 18, QFont::Bold));
    label->setGeometry(0,0,100,30);                          /*ist notwendig, damit auch mehrstellige Zahlen gezeigt werden*/



}


void zeichenFeld::paintEvent(QPaintEvent * )
{
   QPainter painter;

   int a,b,c,u,v,w;
   a=lastA;b=lastB;c=lastC;
   u=lastU;v=lastV;w=lastW;


    painter.begin(this);

    /*hier wird der Avatar generiert*/

    painter.setBrush(QBrush(Qt::Dense2Pattern));
    painter.drawRect(x,y,50,50);


    /*hier werden die Objekete generiert*/

    painter.setBrush(QBrush(Qt::red));
    painter.drawEllipse(a,u,70,70);
    if (increment)
     {

        if (lastU<500)lastU++;

        else
        {
            zaehler=zaehler+50;  //Punkte Anzahl wird erhöht, je nach Größe der Objekte gibt es unterschiedliche Punkte
            label->setNum(zaehler);
            lastU=(rand() % 1)-700; // mit Hilfe von rand() gelingt es, dass die Objekte immer von unterschiedlichen Startpositionen aus starten
            lastA=rand()%450;
        }
    }

    painter.setBrush(QBrush(Qt::green));
    painter.drawRect(b,v,30, 30);
    if (increment)
    {
        if (lastV<500)lastV++;

        else
        {
            zaehler=zaehler+10;
            label->setNum(zaehler);
            lastV=(rand() % 1)-10;
            lastB=rand()%450;

        }
    }
    painter.setBrush(QBrush(Qt::blue));
    painter.drawRect(c,w,90, 50);
    if (increment)
    {
        if (lastW<500)lastW++;
        else
        {
            zaehler=zaehler+100;
            label->setNum(zaehler);
            lastW=(rand() % 1)-200;
            lastC=rand()%450;
        }
    }

    /*hier werden die Lebenszeichen generiert*/

    painter.setBrush(QBrush(Qt::darkRed));
    painter.drawEllipse(450,10,10,10);
    painter.drawEllipse(465,10,10,10);
    painter.drawEllipse(480,10,10,10);

    painter.end();



}

void zeichenFeld::keyPressEvent(QKeyEvent *event)
{
    /* hier wird die Beweglichkeit des Avatars it Hilfe der Pfeiltasten gereglet*/

    if (event->key()==Qt::Key_Left)
    {
        if(x>=25)
          x = x - 25;
        update();
    }

    if (event->key() == Qt::Key_Right)
    {
        if(x<450)
          x = x + 25;
        update();
    }

}



void zeichenFeld::serialize(QFile &file)
{

    QTextStream out(&file);
    /*hier werden die Integers gespeichert*/

    out << "p " << x << "p " <<zaehler << "p " <<lastA << "p " <<lastB << "p " <<lastC << "p " <<lastU << "p " <<lastV << "p " <<lastW;

}

void zeichenFeld::deserialize(QFile &file)
{

    char c;

    QTextStream in(&file);

    while (in.status() == QTextStream::Ok)
    {
        in >> c;
        if (in.status() == QTextStream::ReadPastEnd) break;

        if (c!='p')
        {
            QMessageBox::warning(this, tr("Objektfehler"),
                                 tr("Folgender Objekttyp ist unbekannt: ") + c,QMessageBox::Ok);
            return;
        }
        /*hier werden die integers mit den gespeicherten Zahlen befüllt*/
        in >>x >> c >> zaehler >> c >> lastA >> c >> lastB >> c >> lastC >>c >> lastU >>c >> lastV >>c >> lastW;

        label->setNum(zaehler);     //ist notwendig, damit die gespeicherte und geladene zahl auch angezeigt wird.
    }

    update();
}




