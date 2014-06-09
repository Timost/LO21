#include "mainfenetre.h"
#include "ui_mainfenetre.h"
#include <QtGui>
#include <QDebug>
MainFenetre::MainFenetre(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainFenetre)
{
    ui->setupUi(this);
    //sauvegarde
    QObject::connect(ui->actionSauvegarder, SIGNAL(triggered()), this, SLOT(save()) );
    //Charger
    QObject::connect(ui->actionCharger, SIGNAL(triggered()), this, SLOT(load()) );
    //ajout
    QObject::connect(ui->actionAjouter_Etudiant, SIGNAL(triggered()), this, SLOT(ajouterEtudiant()) );
    //Rafraichir
    QObject::connect(ui->actionRafraichir, SIGNAL(triggered()), this, SLOT(refresh()) );
    //Affichage UV
    updateUV();
    //Affichage Etudiant
    updateEtudiant();
    //Affichage Formation
    updateFormation();
}

//rafraichit tout
void MainFenetre::refresh()
{
    updateUV();
    updateEtudiant();
    updateFormation();
}

//met à jour le tableau UV
void MainFenetre::updateUV()
{
    TemplateManager<UV>& tUV=TemplateManager<UV>::getInstance();
    ui->UVTable->setRowCount(tUV.size());
    for(unsigned int i=0; i<tUV.size(); i++)
    {
        QTableWidgetItem* code=new QTableWidgetItem(QString(tUV.getIterator()[i].getCode().c_str()));
        QTableWidgetItem* titre=new QTableWidgetItem(QString(tUV.getIterator()[i].getTitre().c_str()));
        QPushButton* modif=new QPushButton("Modifier");
        ui->UVTable->setCellWidget(i, 2, modif);
        QPushButton* suppr=new QPushButton("Supprimer");
        ui->UVTable->setCellWidget(i, 3, suppr);
        code->setFlags(Qt::ItemIsEnabled);
        titre->setFlags(Qt::ItemIsEnabled);
        ui->UVTable->setItem(i, 0, code);
        ui->UVTable->setItem(i, 1, titre);

        //config du suppr
        QSignalMapper* sig = new QSignalMapper(this);
        QObject::connect(suppr, SIGNAL(clicked()), sig, SLOT(map()));
        sig->setMapping(suppr, i);
        QObject::connect(sig, SIGNAL(mapped(int)), this, SLOT(deleteUV(int)));
        //config modif
        QSignalMapper* sig2 = new QSignalMapper(this);
        QObject::connect(modif, SIGNAL(clicked()), sig2, SLOT(map()));
        sig->setMapping(modif, i);
        QObject::connect(sig, SIGNAL(mapped(int)), this, SLOT(modifierUV(int)));
    }
}

//Met à jour le tableau etudiant
void MainFenetre::updateEtudiant()
{
    TemplateManager<Etudiant>& tEtu=TemplateManager<Etudiant>::getInstance();
    ui->EtudiantTable->setRowCount(tEtu.size());
    for(unsigned int i=0; i<tEtu.size(); i++)
    {
        QTableWidgetItem* login=new QTableWidgetItem(tEtu.getIterator()[i].getLogin());
        QTableWidgetItem* prenom=new QTableWidgetItem(tEtu.getIterator()[i].getPrenom());
        QTableWidgetItem* nom=new QTableWidgetItem(tEtu.getIterator()[i].getNom());
        QPushButton* modif=new QPushButton("Modifier");
        ui->EtudiantTable->setCellWidget(i, 3, modif);
        QPushButton* suppr=new QPushButton("Supprimer");
        ui->EtudiantTable->setCellWidget(i, 4, suppr);
        login->setFlags(Qt::ItemIsEnabled);
        nom->setFlags(Qt::ItemIsEnabled);
        prenom->setFlags(Qt::ItemIsEnabled);
        ui->EtudiantTable->setItem(i, 0, login);
        ui->EtudiantTable->setItem(i, 1, nom);
        ui->EtudiantTable->setItem(i, 2, prenom);

        //config du suppr
        QSignalMapper* sig = new QSignalMapper(this);
        QObject::connect(suppr, SIGNAL(clicked()), sig, SLOT(map()));
        sig->setMapping(suppr, i);
        QObject::connect(sig, SIGNAL(mapped(int)), this, SLOT(deleteEtudiant(int)));
        //config modif
        QSignalMapper* sig2 = new QSignalMapper(this);
        QObject::connect(modif, SIGNAL(clicked()), sig2, SLOT(map()));
        sig->setMapping(modif, i);
        QObject::connect(sig, SIGNAL(mapped(int)), this, SLOT(modifierEtudiant(int)));
    }
}



//Met à jour le tableau formation
void MainFenetre::updateFormation()
{
    TemplateManager<Formation>& tForm=TemplateManager<Formation>::getInstance();
    ui->FormationTable->setRowCount(tForm.size());
    for(unsigned int i=0; i<tForm.size(); i++)
    {
        QTableWidgetItem* nom=new QTableWidgetItem(tForm.getIterator()[i].getNom());
        QTableWidgetItem* description=new QTableWidgetItem(tForm.getIterator()[i].getDescription());
        QPushButton* modif=new QPushButton("Modifier");
        ui->FormationTable->setCellWidget(i, 2, modif);
        QPushButton* suppr=new QPushButton("Supprimer");
        ui->FormationTable->setCellWidget(i, 3, suppr);
        nom->setFlags(Qt::ItemFlag::ItemIsEnabled);
        description->setFlags( Qt::ItemFlag::ItemIsEnabled);
        ui->FormationTable->setItem(i, 0, nom);
        ui->FormationTable->setItem(i, 1, description);

        //config du suppr
        QSignalMapper* sig = new QSignalMapper(this);
        QObject::connect(suppr, SIGNAL(clicked()), sig, SLOT(map()));
        sig->setMapping(suppr, i);
        QObject::connect(sig, SIGNAL(mapped(int)), this, SLOT(deleteFormation(int)));
        //config modif
        QSignalMapper* sig2 = new QSignalMapper(this);
        QObject::connect(modif, SIGNAL(clicked()), sig2, SLOT(map()));
        sig->setMapping(modif, i);
        QObject::connect(sig, SIGNAL(mapped(int)), this, SLOT(modifierFormation(int)));
    }
}

void MainFenetre::save()
{
    QFileDialog* file= new QFileDialog();
    QString path = file->getOpenFileName(this, tr("Sauvegarder la base de données"),"C:/",tr("Fichier SQLite (*.db)"));
    Database db(path.toStdString());
    db.save();
}

void MainFenetre::load()
{
    QFileDialog* file= new QFileDialog();
    QString path = file->getOpenFileName(this, tr("Charger la base de données"),"C:/",tr("Fichier SQLite (*.db)"));
    Database db(path.toStdString());
    db.load();
    //on met à jour les tableaux
    updateUV();
    updateEtudiant();
    updateFormation();
}

void MainFenetre::deleteUV(int i)
{
    TemplateManager<UV>::getInstance().erase(i);
    updateUV();
}

void MainFenetre::deleteEtudiant(int i)
{
    TemplateManager<Etudiant>::getInstance().erase(i);
    updateEtudiant();
}

void MainFenetre::deleteFormation(int i)
{
    TemplateManager<Formation>::getInstance().erase(i);
    updateFormation();
}

void MainFenetre::modifierUV(int i)
{
    //fenModif=new Modifieruv_fen(uv);
    //fenModif.show();
    //updateUV();
}

void MainFenetre::modifierEtudiant(int i)
{
    TemplateManager<Etudiant>& tEtu=TemplateManager<Etudiant>::getInstance();
    Etudiant& etu=tEtu.getIterator()[i];
    ModifierEtudiant* fenModif=new ModifierEtudiant(etu);
    updateEtudiant();
}

void MainFenetre::modifierFormation(int i)
{
    //fenModif=new modifierformation(form);
    //fenModif.show();
    //updateFormation();
}

void MainFenetre::ajouterEtudiant()
{

}

MainFenetre::~MainFenetre()
{
    delete ui;
}
