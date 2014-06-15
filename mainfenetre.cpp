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
    QObject::connect(ui->actionAjouter_UV, SIGNAL(triggered()), this, SLOT(ajouterUV()) );
    QObject::connect(ui->actionAjouter_Formation, SIGNAL(triggered()), this, SLOT(ajouterFormation()) );
    QObject::connect(ui->actionCategorie, SIGNAL(triggered()), this, SLOT(ajouterCategorie()) );
    QObject::connect(ui->actionSaison, SIGNAL(triggered()), this, SLOT(ajouterSaison()) );
    QObject::connect(ui->actionNote, SIGNAL(triggered()), this, SLOT(ajouterNote()) );
    QObject::connect(ui->actionSemestre, SIGNAL(triggered()), this, SLOT(ajouterSemestre()) );
    //Rafraichir
    QObject::connect(ui->actionRafraichir, SIGNAL(triggered()), this, SLOT(refresh()) );

    //Test des fenêtres de Timothée
    QObject::connect(ui->actionTest, SIGNAL(triggered()), this, SLOT(test()) );


    //Affichage UV
    updateUV();
    //Affichage Etudiant
    updateEtudiant();
    //Affichage Formation
    updateFormation();
    //Affichage Catégorie
    updateCategorie();
    //Affichage note
    updateNote();
    //Affichage Saison
    updateSaison();
    //Affichage Semestre
    updateSemestre();
}

//rafraichit tout
void MainFenetre::refresh()
{
    updateUV();
    updateEtudiant();
    updateFormation();
    updateCategorie();
    updateNote();
    updateSaison();
    updateSemestre();
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
        sig2->setMapping(modif, i);
        QObject::connect(sig2, SIGNAL(mapped(int)), this, SLOT(modifierUV(int)));
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
        sig2->setMapping(modif, i);
        QObject::connect(sig2, SIGNAL(mapped(int)), this, SLOT(modifierEtudiant(int)));
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
        sig2->setMapping(modif, i);
        QObject::connect(sig2, SIGNAL(mapped(int)), this, SLOT(modifierFormation(int)));
    }
}

//met à jour le tableau de catégorie
void MainFenetre::updateCategorie()
{
    TemplateManager<Categorie>& tCat=TemplateManager<Categorie>::getInstance();
    ui->CategorieTable->setRowCount(tCat.size());
    for(unsigned int i=0; i<tCat.size(); i++)
    {
        QTableWidgetItem* nom=new QTableWidgetItem(tCat.getIterator()[i].getCode());
        QTableWidgetItem* description=new QTableWidgetItem(tCat.getIterator()[i].getDescription());
        QPushButton* modif=new QPushButton("Modifier");
        ui->CategorieTable->setCellWidget(i, 2, modif);
        QPushButton* suppr=new QPushButton("Supprimer");
        ui->CategorieTable->setCellWidget(i, 3, suppr);
        description->setFlags(Qt::ItemIsEnabled);
        nom->setFlags(Qt::ItemIsEnabled);
        ui->CategorieTable->setItem(i, 1, description);
        ui->CategorieTable->setItem(i, 0, nom);

        //config du suppr
        QSignalMapper* sig = new QSignalMapper(this);
        QObject::connect(suppr, SIGNAL(clicked()), sig, SLOT(map()));
        sig->setMapping(suppr, i);
        QObject::connect(sig, SIGNAL(mapped(int)), this, SLOT(deleteCategorie(int)));
        //config modif
        QSignalMapper* sig2 = new QSignalMapper(this);
        QObject::connect(modif, SIGNAL(clicked()), sig2, SLOT(map()));
        sig2->setMapping(modif, i);
        QObject::connect(sig2, SIGNAL(mapped(int)), this, SLOT(modifierCategorie(int)));
    }
}

//met à jour le tableau de note
void MainFenetre::updateNote()
{
    TemplateManager<Note>& tNot=TemplateManager<Note>::getInstance();
    ui->NoteTable->setRowCount(tNot.size());
    for(unsigned int i=0; i<tNot.size(); i++)
    {
        QTableWidgetItem* note=new QTableWidgetItem(tNot.getIterator()[i].getNote());
        QTableWidgetItem* description=new QTableWidgetItem(tNot.getIterator()[i].getDescription());
        QTableWidgetItem* rang=new QTableWidgetItem(QString::number(tNot.getIterator()[i].getRang()));
        QPushButton* modif=new QPushButton("Modifier");
        ui->NoteTable->setCellWidget(i, 3, modif);
        QPushButton* suppr=new QPushButton("Supprimer");
        ui->NoteTable->setCellWidget(i, 4, suppr);
        description->setFlags(Qt::ItemIsEnabled);
        note->setFlags(Qt::ItemIsEnabled);
        rang->setFlags(Qt::ItemIsEnabled);
        ui->NoteTable->setItem(i, 1, description);
        ui->NoteTable->setItem(i, 0, note);
        ui->NoteTable->setItem(i, 2, rang);

        //config du suppr
        QSignalMapper* sig = new QSignalMapper(this);
        QObject::connect(suppr, SIGNAL(clicked()), sig, SLOT(map()));
        sig->setMapping(suppr, i);
        QObject::connect(sig, SIGNAL(mapped(int)), this, SLOT(deleteNote(int)));
        //config modif
        QSignalMapper* sig2 = new QSignalMapper(this);
        QObject::connect(modif, SIGNAL(clicked()), sig2, SLOT(map()));
        sig2->setMapping(modif, i);
        QObject::connect(sig2, SIGNAL(mapped(int)), this, SLOT(modifierNote(int)));
    }
}

//met à jour le tableau de saison
void MainFenetre::updateSaison()
{
    TemplateManager<Saison>& tSai=TemplateManager<Saison>::getInstance();
    ui->SaisonTable->setRowCount(tSai.size());
    for(unsigned int i=0; i<tSai.size(); i++)
    {
        QTableWidgetItem* nom=new QTableWidgetItem(tSai.getIterator()[i].getNom());
        QTableWidgetItem* description=new QTableWidgetItem(tSai.getIterator()[i].getDescription());
        QPushButton* modif=new QPushButton("Modifier");
        ui->SaisonTable->setCellWidget(i, 2, modif);
        QPushButton* suppr=new QPushButton("Supprimer");
        ui->SaisonTable->setCellWidget(i, 3, suppr);
        description->setFlags(Qt::ItemIsEnabled);
        nom->setFlags(Qt::ItemIsEnabled);
        ui->SaisonTable->setItem(i, 1, description);
        ui->SaisonTable->setItem(i, 0, nom);

        //config du suppr
        QSignalMapper* sig = new QSignalMapper(this);
        QObject::connect(suppr, SIGNAL(clicked()), sig, SLOT(map()));
        sig->setMapping(suppr, i);
        QObject::connect(sig, SIGNAL(mapped(int)), this, SLOT(deleteSaison(int)));
        //config modif
        QSignalMapper* sig2 = new QSignalMapper(this);
        QObject::connect(modif, SIGNAL(clicked()), sig2, SLOT(map()));
        sig2->setMapping(modif, i);
        QObject::connect(sig2, SIGNAL(mapped(int)), this, SLOT(modifierSaison(int)));
    }
}

//met à jour le tableau de semestre
void MainFenetre::updateSemestre()
{
    TemplateManager<Semestre>& tSem=TemplateManager<Semestre>::getInstance();
    ui->SemestreTable->setRowCount(tSem.size());
    for(unsigned int i=0; i<tSem.size(); i++)
    {
        QTableWidgetItem* saison=new QTableWidgetItem(tSem.getIterator()[i].getSaison().getNom());
        QTableWidgetItem* annee=new QTableWidgetItem(QString::number(tSem.getIterator()[i].getAnnee()));
        QTableWidgetItem* code=new QTableWidgetItem(tSem.getIterator()[i].getCode());
        QPushButton* suppr=new QPushButton("Supprimer");
        ui->SemestreTable->setCellWidget(i, 3, suppr);
        saison->setFlags(Qt::ItemIsEnabled);
        annee->setFlags(Qt::ItemIsEnabled);
        ui->SemestreTable->setItem(i, 2, annee);
        ui->SemestreTable->setItem(i, 1, saison);
        ui->SemestreTable->setItem(i, 0, code);
        //config du suppr
        QSignalMapper* sig = new QSignalMapper(this);
        QObject::connect(suppr, SIGNAL(clicked()), sig, SLOT(map()));
        sig->setMapping(suppr, i);
        QObject::connect(sig, SIGNAL(mapped(int)), this, SLOT(deleteSemestre(int)));
    }
}

void MainFenetre::save()
{
    try
    {
        QFileDialog* file= new QFileDialog();
        QString path = file->getOpenFileName(this, tr("Sauvegarder la base de données"),"C:/",tr("Fichier SQLite (*.db)"));
        Database db(path.toStdString());
        db.save();
    }
    catch(std::exception& e)
    {
        QMessageBox::warning(this, "Erreur", e.what());
    }
}

void MainFenetre::load()
{
    try
    {
        QFileDialog* file= new QFileDialog();
        QString path = file->getOpenFileName(this, tr("Charger la base de données"),"C:/",tr("Fichier SQLite (*.db)"));
        Database db(path.toStdString());
        db.load();
    }
    catch(std::exception &e)
    {
        QMessageBox::warning(this, "Erreur", e.what());
    }
    //on met à jour les tableaux
    updateUV();
    updateEtudiant();
    updateFormation();
    updateCategorie();
    updateNote();
    updateSaison();
    updateSemestre();
}

void MainFenetre::deleteUV(int i)
{
    try
    {
         TemplateManager<UV>::getInstance().erase(i);
    }
    catch(std::exception e)
    {
        QMessageBox::warning(this, "Erreur", e.what());
    }

    updateUV();
}

void MainFenetre::deleteEtudiant(int i)
{
    try
    {
         TemplateManager<Etudiant>::getInstance().erase(i);
    }
    catch(std::exception e)
    {
        QMessageBox::warning(this, "Erreur", e.what());
    }

    updateEtudiant();
}

void MainFenetre::deleteFormation(int i)
{
    TemplateManager<Formation>::getInstance().erase(i);
    updateFormation();
}

void MainFenetre::modifierUV(int i)
{
    TemplateManager<UV>& tUV=TemplateManager<UV>::getInstance();
    UV& uv=tUV.getIterator()[i];
    Modifieruv_fen* fenModif=new Modifieruv_fen(uv);
    fenModif->exec();
    delete fenModif;
    updateUV();
}

void MainFenetre::modifierEtudiant(int i)
{
    TemplateManager<Etudiant>& tEtu=TemplateManager<Etudiant>::getInstance();
    Etudiant& etu=tEtu.getIterator()[i];
    ModifierEtudiant* fenModif=new ModifierEtudiant(etu);
    fenModif->exec();
    delete fenModif;
    updateEtudiant();
}

void MainFenetre::modifierCategorie(int i)
{
    TemplateManager<Categorie>& tCat=TemplateManager<Categorie>::getInstance();
    Categorie& cat=tCat.getIterator()[i];
    ModifierCategorie* fenModif=new ModifierCategorie(cat);
    fenModif->exec();
    delete fenModif;
    updateCategorie();
}

void MainFenetre::deleteCategorie(int i)
{
    TemplateManager<Categorie>& tCat=TemplateManager<Categorie>::getInstance();
    (tCat.getIterator()+i)->destroy();

    tCat.getInstance().erase(i);
    updateCategorie();
}

void MainFenetre::modifierNote(int i)
{
    TemplateManager<Note>& tNot=TemplateManager<Note>::getInstance();
    Note& note=tNot.getIterator()[i];
    ModifierNote* fenModif=new ModifierNote(note);
    fenModif->exec();
    delete fenModif;
    updateNote();
}

void MainFenetre::deleteNote(int i)
{
    TemplateManager<Note>::getInstance().erase(i);
    updateNote();
}

void MainFenetre::modifierSaison(int i)
{
    TemplateManager<Saison>& tSai=TemplateManager<Saison>::getInstance();
    Saison& sai=tSai.getIterator()[i];
    ModifierSaison* fenModif=new ModifierSaison(sai);
    fenModif->exec();
    delete fenModif;
    updateSaison();
}

void MainFenetre::deleteSaison(int i)
{
    TemplateManager<Saison>::getInstance().erase(i);
    updateSaison();
}

void MainFenetre::deleteSemestre(int i)
{
    TemplateManager<Semestre>::getInstance().erase(i);
    updateSemestre();
}

void MainFenetre::ajouterFormation()
{
    gererFormation* fenModif=new gererFormation();
    fenModif->exec();
    updateFormation();
}

void MainFenetre::modifierFormation(int i)
{
    TemplateManager<Formation>& tFor=TemplateManager<Formation>::getInstance();
    gererFormation* fenModif=new gererFormation(tFor.getIterator()[i]);
    fenModif->exec();
    updateFormation();
}

void MainFenetre::ajouterEtudiant()
{
    ModifierEtudiant* fenModif=new ModifierEtudiant();
    fenModif->exec();
    delete fenModif;
    updateEtudiant();
}

void MainFenetre::ajouterUV()
{
    Modifieruv_fen* fenModif=new Modifieruv_fen();
    fenModif->exec();
    delete fenModif;
    updateUV();
}

void MainFenetre::ajouterCategorie()
{
    ModifierCategorie* fenModif=new ModifierCategorie();
    fenModif->exec();
    delete fenModif;
    updateCategorie();
}

void MainFenetre::ajouterSemestre()
{
    ModifierSemestre* fenModif=new ModifierSemestre();
    fenModif->exec();
    delete fenModif;
    updateSemestre();
}

void MainFenetre::ajouterSaison()
{
    ModifierSaison* fenModif=new ModifierSaison();
    fenModif->exec();
    delete fenModif;
    updateSaison();
}

void MainFenetre::ajouterNote()
{
    ModifierNote* fenModif=new ModifierNote();
    fenModif->exec();
    delete fenModif;
    updateNote();
}

void MainFenetre::test()
{
//    TemplateManager<Formation>& tForm=TemplateManager<Formation>::getInstance();
//    Formation& f=tForm.getIterator()[0];
    //gererFormation* fenModif=new gererFormation(f);
    gererCategorie* fenModif = new gererCategorie();
    fenModif->exec();
    delete fenModif;
}


MainFenetre::~MainFenetre()
{
    delete ui;
}
