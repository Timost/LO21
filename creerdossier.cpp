#include "creerdossier.h"
#include "ui_creerdossier.h"

creerDossier::creerDossier(Etudiant& etu,QWidget *parent) :
    e(etu),
    QDialog(parent),
    ui(new Ui::creerDossier)
{
    ui->setupUi(this);
    TemplateManager<Formation>& tForm=TemplateManager<Formation>::getInstance();

    ui->FormationTable->setRowCount(tForm.size());
    for(unsigned int i=0; i<tForm.size(); i++)
    {
        QTableWidgetItem* nom=new QTableWidgetItem(tForm.getIterator()[i].getNom());
        MyCheckBox* choisir=new MyCheckBox(i);
        ui->FormationTable->setCellWidget(i, 1, choisir);
        nom->setFlags(Qt::ItemFlag::ItemIsEnabled);
        ui->FormationTable->setItem(i, 0, nom);

        //config du checkbox
        QObject::connect(choisir, SIGNAL(stateChanged(int)),  choisir, SLOT(isChecked(int)));
        QObject::connect(choisir, SIGNAL(addMyNumber(int)),  this, SLOT(ajouterFormation(int)));
        QObject::connect(choisir, SIGNAL(removeMyNumber(int)),  this, SLOT(supprimerFormation(int)));
    }
    QObject::connect(ui->Valider, SIGNAL(pressed()),  this, SLOT(valider()));
}
void creerDossier::ajouterFormation(int i)
{
       formationToBeAdded.push_back(i);
}

void creerDossier::supprimerFormation(int i)
{
        QMessageBox* test = new QMessageBox();

        test->setText("supprimerFormation");
        test->exec();
       std::vector<int>::iterator it = std::find(formationToBeAdded.begin(),formationToBeAdded.end(),i);
       formationToBeAdded.erase(it);
}

void creerDossier::valider()
{
   Dossier dos;
   TemplateManager<Formation>& tForm=TemplateManager<Formation>::getInstance();
   for(int i=0; i<formationToBeAdded.size();i++)
   {
      //qDebug()<<" test : "<<tForm.getIterator()[formationToBeAdded[i]].getNom();
       dos.addFormation(&(tForm.getIterator()[formationToBeAdded[i]]));
   }
    e.setDossier(dos);
}



creerDossier::~creerDossier()
{
    delete ui;
}
