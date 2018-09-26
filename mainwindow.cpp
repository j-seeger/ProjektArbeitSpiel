using namespace std;
#include <QtGui>
#include <QPushButton>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>
#include "mainwindow.h"


meinWidget::meinWidget(QWidget *parent)
    : QWidget(parent)
{



/*hier werden die buttons generiert*/



    button = new QPushButton(tr("Starten"));
    button->setFont(QFont("Times", 18, QFont::Bold));
    button->setDefault(button);
    connect(button, SIGNAL(clicked()), this , SLOT(start()));


    QPushButton *quit = new QPushButton(tr("Beenden"));
    quit->setFont(QFont("Times", 18, QFont::Bold));
    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    QPushButton*saver = new QPushButton(tr("Speichern"));
    saver->setFont(QFont("Times", 18, QFont::Bold));
    connect(saver, SIGNAL(clicked()), this, SLOT(saveFile()));

    QPushButton *loader = new QPushButton(tr("Laden"));
    loader->setFont(QFont("Times", 18, QFont::Bold));
    connect(loader, SIGNAL(clicked()), this, SLOT(loadFile()));

    meinZeichenFeld = new zeichenFeld;
    meinZeichenFeld->setFocusPolicy(Qt::StrongFocus); // ist nowtendig damit sich der Avatar bewegt, gibt an dass der Avatar sich sowohl beim "klicken" als auch "tappen" der Pfeiltasten bewegt
    meinZeichenFeld->setFixedSize(500,500); //regelt die Größe des Spielfeldes

    /*hier wird nun das design des ganzen fensters festgelegt*/

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(button, 0, 0);
    gridLayout->addWidget(saver, 0, 3);
    gridLayout->addWidget(loader, 0,4);
    gridLayout->addWidget(quit, 2,4);
    gridLayout->addWidget(meinZeichenFeld, 1,1,1,1);
    gridLayout->setColumnStretch(1, 10);
    setLayout(gridLayout);


}

void meinWidget::start(void)
{
    button->setText(tr("Pause")); //macht aus Start-Pause
    button->setFont(QFont("Times", 18, QFont::Bold));
    connect(button, SIGNAL(clicked()), this , SLOT(stop()));
    meinZeichenFeld->start();

}

void meinWidget::stop(void)
{
    button->setText(tr("Starten")); //macht aus Pause -Start
    button->setFont(QFont("Times", 18, QFont::Bold));
    button->setDefault(button);
    connect(button, SIGNAL(clicked()), this , SLOT(start()));
    meinZeichenFeld->stop();

}





void meinWidget::saveFile(void)
{
    QFileDialog dialog(this);
    QString fileName;
    QFile file;

    dialog.setFileMode(QFileDialog::AnyFile);
    fileName = dialog.getSaveFileName(this,
                                      tr("Speichern als"), ".", tr("Zeichnungen (*.myz)"));

    if (fileName.isNull()==false)
    {
        file.setFileName(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Dateifehler"),
                                 tr("Folgende Datei kann nicht verwendet werden: ") + fileName,QMessageBox::Ok);
        }
        meinZeichenFeld->serialize(file);
        file.close();
        return;
    }
}

void meinWidget::loadFile(void)
{
    QFileDialog dialog(this);
    QString fileName;
    QFile file;

    dialog.setFileMode(QFileDialog::AnyFile);
    fileName = dialog.getOpenFileName(this,
                                      tr("Speichern als"), ".", tr("Zeichnungen (*.myz)"));

    if (fileName.isNull()==false)
    {
        file.setFileName(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Dateifehler"),
                                 tr("Folgende Datei kann nicht geÃ¶ffnet werden: ") + fileName,QMessageBox::Ok);
        }

        meinZeichenFeld->deserialize(file);
        file.close();
        return;
    }
}
