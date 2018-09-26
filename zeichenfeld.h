using namespace std;
#include <QWidget>
#include <QFile>
#include <QKeyEvent>
#include <QTimer>
#include <QLabel>


class zeichenFeld : public QWidget
{

    //Q_OBJECT

public:

    zeichenFeld(QWidget *parent = 0);

    void serialize(QFile &file);
    void deserialize(QFile &file);

    enum drawType { square, circle };
    void start(void){ timer->start(10); increment=1;}
    void stop (void){timer->stop();increment=0;}
    int zaehler;
    QLabel *label;

private:
    int x,y;
    QTimer *timer;
    int lastU;
    int lastV;
    int lastW;
    int lastA;
    int lastB;
    int lastC;
    int increment;
    int phase;


protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent* event);


};


