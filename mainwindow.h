using namespace std;
#include <QWidget>
#include <QFileDialog>
#include "zeichenfeld.h"

class meinWidget : public QWidget
{

Q_OBJECT

public:
    meinWidget(QWidget *parent = 0);
    QPushButton *button;

private:
    zeichenFeld *meinZeichenFeld ;
private slots:
      void saveFile(void);
      void loadFile(void);
      void start(void);
      void stop (void);
};
