#include "creerdossier.h"
#include "ui_creerdossier.h"

creerDossier::creerDossier(Etudiant& etu,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::creerDossier),
    e(etu)
{

    ui->setupUi(this);
    TemplateManager<Formation>& tForm=TemplateManager<Formation>::getInstance();
    ui->InscriptionTable->hide();
    ui->InscriptionText->hide();
    ui->Suivant->setEnabled(false);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
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
    QObject::connect(ui->Valider, SIGNAL(pressed()),  this, SLOT(validerFormation()));
    QObject::connect(ui->Suivant, SIGNAL(pressed()),  this, SLOT(suivant()));
}
void creerDossier::ajouterFormation(int i)
{
       formationToBeAdded.push_back(i);
}

void creerDossier::supprimerFormation(int i)
{
//        QMessageBox* test = new QMessageBox();
//        test->setText("supprimerFormation");
//        test->exec();
       std::vector<int>::iterator it = std::find(formationToBeAdded.begin(),formationToBeAdded.end(),i);
       formationToBeAdded.erase(it);
       if(formationToBeAdded.size()==0)
       {
           ui->Suivant->setEnabled(false);
       }
}
void creerDossier::ajouterInscription()
{
//        QMessageBox* test = new QMessageBox();
//        test->setText("supprimerFormation");
//        test->exec();
//       std::vector<int>::iterator it = std::find(formationToBeAdded.begin(),formationToBeAdded.end(),i);
//       formationToBeAdded.erase(it);
}

void creerDossier::validerFormation()
{
   if(formationToBeAdded.size()>0)
   {
       Dossier dos;
       TemplateManager<Formation>& tForm=TemplateManager<Formation>::getInstance();
       for(unsigned int i=0; i<formationToBeAdded.size();i++)
       {
           //qDebug()<<" test : "<<tForm.getIterator()[formationToBeAdded[i]].getNom();
           dos.addFormation(&(tForm.getIterator()[formationToBeAdded[i]]));
       }
       if(formationToBeAdded.size()>0)
       {
           ui->Suivant->setEnabled(true);
       }
       e.setDossier(dos);
   }
}

void creerDossier::suivant()
{
    TemplateManager<UV>& tUV=TemplateManager<UV>::getInstance();
    ui->FormationTable->hide();
    ui->FormationText->hide();
    ui->Suivant->hide();

    ui->InscriptionText->show();
    ui->InscriptionTable->show();
    QObject::disconnect(ui->Valider, SIGNAL(pressed()),  this, SLOT(ajouterInscription()));

    ui->InscriptionTable->setRowCount(tUV.size());
    for(unsigned int i=0; i<tUV.size(); i++)
    {
        QTableWidgetItem* code=new QTableWidgetItem(tUV.getIterator()[i].getCodeQString());
        MyCheckBox* choisir=new MyCheckBox(i);
        ui->InscriptionTable->setCellWidget(i, 3, choisir);
        code->setFlags(Qt::ItemFlag::ItemIsEnabled);
        ui->InscriptionTable->setItem(i, 0, code);

        //config du checkbox
//        QObject::connect(choisir, SIGNAL(stateChanged(int)),  choisir, SLOT(isChecked(int)));
//        QObject::connect(choisir, SIGNAL(addMyNumber(int)),  this, SLOT(ajouterFormation(int)));
//        QObject::connect(choisir, SIGNAL(removeMyNumber(int)),  this, SLOT(supprimerFormation(int)));
    }
//    QObject::connect(ui->Valider, SIGNAL(pressed()),  this, SLOT(validerFormation()));
//    QObject::connect(ui->Suivant, SIGNAL(pressed()),  this, SLOT(suivant()));
}

creerDossier::~creerDossier()
{
    delete ui;
}
