#include "profiler.h"
#include "UTProfiler.h"
#include <QApplication>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QInputDialog>
#include <QLineEdit>
#include "uvediteur.h"

void Profiler::chargeUVs()
{
   try
    {
        UVManager& m=UVManager::getInstance();
        QString fileName = QFileDialog::getOpenFileName(this,tr("Open file"), "", tr("XML Files (*.xml)"));
        if(fileName != NULL)
        {
            m.load(fileName);

            QMessageBox message;
            message.setText("Le fichier a correctement été ouvert");
            message.exec();
            path=fileName;
            emit UvsChargee(true);
        }
    }
    catch(UTProfilerException& e)
    {
        QMessageBox message;
        message.setText(e.getInfo());
        message.exec();
    }
}
void Profiler::editUV()
{
    try
    {
        bool ok;
        UVManager& m=UVManager::getInstance();
        QString text = QInputDialog::getText(this, tr("Entrez le code de l'UV"),tr("UV"), QLineEdit::Normal,QDir::home().dirName(), &ok);
        if (ok && !text.isEmpty())
        {
            UVManager& m=UVManager::getInstance();
            UV& mUv= m.getUV(text);
            UVEditeur* fenetre=new UVEditeur(mUv,path);
            fenetre->show();
        }
    }
    catch(UTProfilerException& e)
    {
        QMessageBox message;
        message.setText(e.getInfo());
        message.exec();
    }
}

Profiler::Profiler(QWidget *parent) :  QMainWindow(parent)
{
    UVManager& m=UVManager::getInstance();

    QMenu *menuFichier = menuBar()->addMenu("&Fichier");
    QMenu *menuEdition = menuBar()->addMenu("&Edition");
    QMenu *charger = menuFichier->addMenu("&Charger");

    QAction *actionQuitter = new QAction("&Quitter", this);
    menuFichier->addAction(actionQuitter);

    QAction *actionUV = new QAction("&UV", this);
    actionUV->setEnabled(false);
    menuEdition->addAction(actionUV);

    QAction *actionChargerUV = new QAction("&Catalogue UVs", this);
    charger->addAction(actionChargerUV);

    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(actionChargerUV, SIGNAL(triggered()), this, SLOT(chargeUVs()));
    connect(actionUV, SIGNAL(triggered()), this, SLOT(editUV()));
    connect(this,SIGNAL(UvsChargee(bool)),actionUV,SLOT(setEnabled(bool)));
}
