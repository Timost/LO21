#include "mainfenetre.h"
#include "ui_mainfenetre.h"
#include <QtGui>
#include <QDebug>
MainFenetre::MainFenetre(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainFenetre)
{
    ui->setupUi(this);
    //Affichage UV
    TemplateManager<UV>& tUV=TemplateManager<UV>::getInstance();
    ui->UVTable->setRowCount(tUV.size());
    for(unsigned int i=0; i<tUV.size(); i++)
    {
        QTableWidgetItem* code=new QTableWidgetItem(QString(tUV.getIterator()[i].getCode().c_str()));
        QTableWidgetItem* titre=new QTableWidgetItem(QString(tUV.getIterator()[i].getTitre().c_str()));
        ui->UVTable->setItem(i, 0, code);
        ui->UVTable->setItem(i, 1, titre);
    }

    //Affichage Etudiant
    TemplateManager<Etudiant>& tEtu=TemplateManager<Etudiant>::getInstance();
    ui->EtudiantTable->setRowCount(tEtu.size());
    for(unsigned int i=0; i<tEtu.size(); i++)
    {
        QTableWidgetItem* login=new QTableWidgetItem(tEtu.getIterator()[i].getLogin());
        QTableWidgetItem* prenom=new QTableWidgetItem(tEtu.getIterator()[i].getPrenom());
        QTableWidgetItem* nom=new QTableWidgetItem(tEtu.getIterator()[i].getNom());
        ui->EtudiantTable->setItem(i, 0, login);
        ui->EtudiantTable->setItem(i, 1, nom);
        ui->EtudiantTable->setItem(i, 2, prenom);
    }

    //Affichage Formation
    //Affichage UV
    TemplateManager<Formation>& tForm=TemplateManager<Formation>::getInstance();
    ui->FormationTable->setRowCount(tForm.size());
    for(unsigned int i=0; i<tForm.size(); i++)
    {
        QTableWidgetItem* nom=new QTableWidgetItem(tForm.getIterator()[i].getNom());
        QTableWidgetItem* description=new QTableWidgetItem(tForm.getIterator()[i].getDescription());
        ui->FormationTable->setItem(i, 0, nom);
        ui->FormationTable->setItem(i, 1, description);
    }

}

MainFenetre::~MainFenetre()
{
    delete ui;
}
