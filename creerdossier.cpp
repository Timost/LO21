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
    ui->AjouterLigne->hide();
    ui->Suivant->setEnabled(false);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->buttonBox->button(QDialogButtonBox::Cancel)->hide();
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

       std::vector<int>::iterator it = std::find(formationToBeAdded.begin(),formationToBeAdded.end(),i);
       formationToBeAdded.erase(it);
       if(formationToBeAdded.size()==0)
       {
           ui->Suivant->setEnabled(false);
       }
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

void creerDossier::fillInscriptionTable(int i)
{
    TemplateManager<UV>& tUV=TemplateManager<UV>::getInstance();
    TemplateManager<Semestre>& tSemestre=TemplateManager<Semestre>::getInstance();
    TemplateManager<Note>& tNote=TemplateManager<Note>::getInstance();

     ui->InscriptionTable->insertRow(ui->InscriptionTable->rowCount());
    qDebug()<<"test";
    QComboBox* uv= new QComboBox(ui->InscriptionTable);
    for(unsigned int j=0; j<tUV.size(); j++)
    {
        uv->addItem(tUV.getIterator()[j].getCodeQString());
    }

    QComboBox* semestre= new QComboBox(ui->InscriptionTable);
    for(unsigned int j=0; j<tSemestre.size(); j++)
    {
        semestre->addItem(tSemestre.getIterator()[j].getCode());
    }

    QComboBox* note= new QComboBox(ui->InscriptionTable);
    for(unsigned int j=0; j<tNote.size(); j++)
    {
        note->addItem(tNote.getIterator()[j].getNote());
    }


    MyCheckBox* choisir=new MyCheckBox(0);
    ui->InscriptionTable->setCellWidget(i, 3, choisir);
    ui->InscriptionTable->setCellWidget(i,1, semestre);
    ui->InscriptionTable->setCellWidget(i, 2, note);
    ui->InscriptionTable->setCellWidget(i, 0, uv);

    //config du checkbox
    QObject::connect(choisir, SIGNAL(stateChanged(int)),  choisir, SLOT(isChecked(int)));
    QObject::connect(choisir, SIGNAL(addMyNumber(int)),  this, SLOT(ajouterInscription(int)));
    QObject::connect(choisir, SIGNAL(removeMyNumber(int)),  this, SLOT(supprimerInscription(int)));

}

void creerDossier::addRowInscription()
{
    int nbLignes = ui->InscriptionTable->rowCount();
    fillInscriptionTable(nbLignes);
}


void creerDossier::suivant()
{
    ui->FormationTable->hide();
    ui->FormationText->hide();
    ui->Suivant->hide();
    ui->Valider->setEnabled(false);

    QObject::disconnect(ui->Valider, SIGNAL(pressed()),  this, SLOT(validerFormation()));
    QObject::disconnect(ui->Suivant, SIGNAL(pressed()),  this, SLOT(suivant()));

    QObject::connect(ui->Valider, SIGNAL(pressed()),  this, SLOT(validerInscription()));

    QObject::connect(ui->AjouterLigne, SIGNAL(clicked()),  this, SLOT(addRowInscription()));
    ui->InscriptionText->show();
    ui->InscriptionTable->show();
    ui->AjouterLigne->show();
    ui->InscriptionTable->setRowCount(0);
    fillInscriptionTable(0);
}

void creerDossier::ajouterInscription(int i)
{
    inscriptionsToBeAdded.push_back(i);
    ui->Valider->setEnabled(true);
}

void creerDossier::supprimerInscription(int i)
{
    std::vector<int>::iterator it = std::find(inscriptionsToBeAdded.begin(),inscriptionsToBeAdded.end(),i);
    inscriptionsToBeAdded.erase(it);
    if(inscriptionsToBeAdded.size()==0)
    {
        ui->Valider->setEnabled(false);
    }
}

void creerDossier::validerInscription()
{
    TemplateManager<UV>& tUV=TemplateManager<UV>::getInstance();
    TemplateManager<Semestre>& tSemestre=TemplateManager<Semestre>::getInstance();
    TemplateManager<Note>& tNote=TemplateManager<Note>::getInstance();

    Dossier dos=e.getDossier();

    if(inscriptionsToBeAdded.size()>0)
    {

        for(unsigned int i=0; i<inscriptionsToBeAdded.size();i++)
        {
            QComboBox *uv = qobject_cast<QComboBox*>(ui->InscriptionTable->cellWidget(i,0));
            QComboBox *semestre = qobject_cast<QComboBox*>(ui->InscriptionTable->cellWidget(i,1));
            QComboBox *note = qobject_cast<QComboBox*>(ui->InscriptionTable->cellWidget(i,2));
            if((uv!=0)&&(semestre!=0)&&(note!=0))
            {
                Inscription ins(tUV.getElement(uv->currentText()),tSemestre.getElement(semestre->currentText()),tNote.getElement(note->currentText()));
                if(!dos.containsInscription(ins))
                {
                    dos.addInscription(ins);
                }
                else
                {
                    QMessageBox* err= new QMessageBox(this);
                    err->setText("Vous avez entré deux inscriptions identiques, une seule sera prise en compte.");
                    err->exec();
                }
            }
            else
            {
                throw DossierException("Erreur créerdossier : le qobject_cast n'a pas marché");
            }
        }
    }
    e.setDossier(dos);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}


creerDossier::~creerDossier()
{
    delete ui;
}
