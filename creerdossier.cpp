#include "creerdossier.h"
#include "ui_creerdossier.h"



creerDossier::creerDossier(Etudiant& etu,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::creerDossier),
    e(etu)
{
    ui->setupUi(this);
//    TemplateManager<Formation>& tForm=TemplateManager<Formation>::getInstance();
    ui->InscriptionTable->hide();
    ui->InscriptionTable_2->hide();
    ui->InscriptionText->hide();
    ui->InscriptionText2->hide();
    ui->AjouterLigne->hide();
    if(e.getDossier().getFormation().size()==0)
    {
        ui->Suivant->setEnabled(false);
    }

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->buttonBox->button(QDialogButtonBox::Cancel)->hide();

    displayFormationTables();

    QObject::connect(ui->Valider, SIGNAL(pressed()),  this, SLOT(validerFormation()));
    QObject::connect(ui->Suivant, SIGNAL(pressed()),  this, SLOT(suivant()));
}

void creerDossier::displayFormationTables()
{
    std::vector<Formation *> availableForms=e.getDossier().getFormationsNotInDossier();
    ui->FormationTable->setRowCount(0);
    ui->FormationTable->setRowCount(availableForms.size());

    for(unsigned int i=0; i<availableForms.size(); i++)
    {
        QTableWidgetItem* nom=new QTableWidgetItem(availableForms[i]->getNom());
        MyCheckBox* choisir=new MyCheckBox(i);
        ui->FormationTable->setCellWidget(i, 1, choisir);
        nom->setFlags(Qt::ItemFlag::ItemIsEnabled);
        ui->FormationTable->setItem(i, 0, nom);

        //config du checkbox
        QObject::connect(choisir, SIGNAL(stateChanged(int)),  choisir, SLOT(isChecked(int)));
        QObject::connect(choisir, SIGNAL(addMyNumber(int)),  this, SLOT(ajouterFormationTobeAdded(int)));
        QObject::connect(choisir, SIGNAL(removeMyNumber(int)),  this, SLOT(supprimerFormationTobeAdded(int)));
    }

    std::vector<Formation*> formaDos=e.getDossier().getFormation();
    ui->FormationTable_2->setRowCount(0);
    ui->FormationTable_2->setRowCount(formaDos.size());
    for(unsigned int i=0; i<formaDos.size(); i++)
    {
        QTableWidgetItem* nom=new QTableWidgetItem(formaDos[i]->getNom());
        MyCheckBox* choisir=new MyCheckBox(i);
        ui->FormationTable_2->setCellWidget(i, 1, choisir);
        nom->setFlags(Qt::ItemFlag::ItemIsEnabled);
        ui->FormationTable_2->setItem(i, 0, nom);

        //config du checkbox
        QObject::connect(choisir, SIGNAL(stateChanged(int)),  choisir, SLOT(isChecked(int)));
        QObject::connect(choisir, SIGNAL(addMyNumber(int)),  this, SLOT(ajouterFormationToBeRemoved(int)));
        QObject::connect(choisir, SIGNAL(removeMyNumber(int)),  this, SLOT(supprimerFormationToBeRemoved(int)));
    }
}

void creerDossier::ajouterFormationTobeAdded(int i)
{
       formationToBeAdded.push_back(i);
}

void creerDossier::supprimerFormationTobeAdded(int i)
{
       std::vector<int>::iterator it = std::find(formationToBeAdded.begin(),formationToBeAdded.end(),i);
       formationToBeAdded.erase(it);
       if(formationToBeAdded.size()==0)
       {
           ui->Suivant->setEnabled(false);
       }
}
void creerDossier::ajouterFormationToBeRemoved(int i)
{
    formationToBeRemoved.push_back(i);
}
void creerDossier::supprimerFormationToBeRemoved(int i)
{
    std::vector<int>::iterator it = std::find(formationToBeRemoved.begin(),formationToBeRemoved.end(),i);
    formationToBeRemoved.erase(it);
}


void creerDossier::validerFormation()
{
   if(formationToBeAdded.size()>0)
   {
       std::vector<Formation *> availableForms=e.getDossier().getFormationsNotInDossier();
       Dossier dos=e.getDossier();
       for(unsigned int i=0; i<formationToBeAdded.size();i++)
       {
           //qDebug()<<" test formationToBeAdded: "<<availableForms[formationToBeAdded[i]]->getNom();
           dos.addFormation(availableForms[formationToBeAdded[i]]);
       }
       if(dos.getFormation().size()>0)
       {
           ui->Suivant->setEnabled(true);
       }
       e.setDossier(dos);
       formationToBeAdded.clear();
   }

   if(formationToBeRemoved.size()>0)
   {
       Dossier dos=e.getDossier();
       std::vector<Formation*> forms=dos.getFormation();
       for(unsigned int i=0; i<formationToBeRemoved.size();i++)
       {
           //qDebug()<<" test formationToBeRemoved: "<<forms[formationToBeRemoved[i]]->getNom();
           dos.deleteFormation(forms[formationToBeRemoved[i]]->getNom());

       }
       if(dos.getFormation().size()>0)
       {
           ui->Suivant->setEnabled(true);
       }
       else
       {
           ui->Suivant->setEnabled(false);
       }
       //qDebug()<<" test : ";
       e.setDossier(dos);
       //qDebug()<<" test : ";
       formationToBeRemoved.clear();
   }
   displayFormationTables();
}

void creerDossier::fillInscriptionTable(int i)
{
    TemplateManager<UV>& tUV=TemplateManager<UV>::getInstance();
    TemplateManager<Semestre>& tSemestre=TemplateManager<Semestre>::getInstance();
    TemplateManager<Note>& tNote=TemplateManager<Note>::getInstance();


    ui->InscriptionTable->insertRow(ui->InscriptionTable->rowCount());
    //qDebug()<<"test";
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
    QObject::connect(choisir, SIGNAL(addMyNumber(int)),  this, SLOT(ajouterInscriptionTobeAdded(int)));
    QObject::connect(choisir, SIGNAL(removeMyNumber(int)),  this, SLOT(supprimerInscriptionTobeAdded(int)));



    Dossier currentDos= e.getDossier();
    std::vector<Inscription> currentInscr = currentDos.getInscription();
    ui->InscriptionTable_2->setRowCount(currentInscr.size());
    for(unsigned int i=0 ; i!=currentInscr.size();i++)
    {
        QTableWidgetItem* uv=new QTableWidgetItem(currentInscr[i].getCode());
        QTableWidgetItem* semestre=new QTableWidgetItem(currentInscr[i].getSemestre().getCode());
        QTableWidgetItem* resultat=new QTableWidgetItem(currentInscr[i].getResultat().getNote());
        MyCheckBox* choisir=new MyCheckBox(i);
        ui->InscriptionTable_2->setItem(i, 0, uv);
        ui->InscriptionTable_2->setItem(i, 1, semestre);
        ui->InscriptionTable_2->setItem(i, 2, resultat);
        ui->InscriptionTable_2->setCellWidget(i, 3, choisir);
        //nom->setFlags(Qt::ItemFlag::ItemIsEnabled);
       // ui->FormationTable->setItem(i, 0, nom);
        QObject::connect(choisir, SIGNAL(stateChanged(int)),  choisir, SLOT(isChecked(int)));
        QObject::connect(choisir, SIGNAL(addMyNumber(int)),  this, SLOT(ajouterInscriptionToBeRemoved(int)));
        QObject::connect(choisir, SIGNAL(removeMyNumber(int)),  this, SLOT(supprimerInscriptionToBeRemoved(int)));

    }


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
    ui->FormationTable_2->hide();
    ui->FormationText2->hide();
    ui->Suivant->hide();
    ui->Valider->setEnabled(false);

    QObject::disconnect(ui->Valider, SIGNAL(pressed()),  this, SLOT(validerFormation()));
    QObject::disconnect(ui->Suivant, SIGNAL(pressed()),  this, SLOT(suivant()));

    QObject::connect(ui->Valider, SIGNAL(pressed()),  this, SLOT(validerInscription()));

    QObject::connect(ui->AjouterLigne, SIGNAL(clicked()),  this, SLOT(addRowInscription()));
    ui->InscriptionTable->show();
    ui->InscriptionTable_2->show();
    ui->InscriptionText->show();
    ui->InscriptionText2->show();
    ui->AjouterLigne->show();
    ui->InscriptionTable->setRowCount(0);
    fillInscriptionTable(0);
}

void creerDossier::ajouterInscriptionTobeAdded(int i)
{
    inscriptionsToBeAdded.push_back(i);
    ui->Valider->setEnabled(true);
}

void creerDossier::supprimerInscriptionTobeAdded(int i)
{
    std::vector<int>::iterator it = std::find(inscriptionsToBeAdded.begin(),inscriptionsToBeAdded.end(),i);
    inscriptionsToBeAdded.erase(it);
    if(inscriptionsToBeAdded.size()==0)
    {
        ui->Valider->setEnabled(false);
    }
}

void creerDossier::ajouterInscriptionToBeRemoved(int i)
{
    inscriptionsToBeRemoved.push_back(i);
    ui->Valider->setEnabled(true);
}
void creerDossier::supprimerInscriptionToBeRemoved(int i)
{
    std::vector<int>::iterator it = std::find(inscriptionsToBeRemoved.begin(),inscriptionsToBeRemoved.end(),i);
    inscriptionsToBeRemoved.erase(it);
    if((inscriptionsToBeRemoved.size()>0)||(inscriptionsToBeAdded.size()>0))
    {
        ui->Valider->setEnabled(true);
    }
    else
    {
        ui->Valider->setEnabled(false);
    }
}

void creerDossier::validerInscription()
{
    TemplateManager<UV>& tUV=TemplateManager<UV>::getInstance();
    TemplateManager<Semestre>& tSemestre=TemplateManager<Semestre>::getInstance();
    TemplateManager<Note>& tNote=TemplateManager<Note>::getInstance();



    if(inscriptionsToBeAdded.size()>0)
    {
        Dossier dos=e.getDossier();

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
        e.setDossier(dos);
    }

    inscriptionsToBeAdded.clear();

    if(inscriptionsToBeRemoved.size()>0)
    {

        Dossier dos=e.getDossier();

        for(unsigned int i=0; i<inscriptionsToBeRemoved.size();i++)
        {
            QString InscrUv= ui->InscriptionTable_2->item(inscriptionsToBeRemoved[i],0)->text();
            QString InscrSem= ui->InscriptionTable_2->item(inscriptionsToBeRemoved[i],1)->text();
            QString InscrRes= ui->InscriptionTable_2->item(inscriptionsToBeRemoved[i],2)->text();

            Inscription inscr(tUV.getElement(InscrUv),tSemestre.getElement(InscrSem),tNote.getElement(InscrRes));

            if(dos.containsInscription(inscr))
            {
                dos.deleteInscription(inscr);
            }
            else
            {
                throw DossierException("Erreur validerInscription : L'inscription "+inscr.getCode().toStdString()+" "+inscr.getSemestre().getCode().toStdString()+" "+inscr.getResultat().getStrLabel()+" N'est pas dans le dossier");
            }
        }

        e.setDossier(dos);
    }

    inscriptionsToBeRemoved.clear();

    fillInscriptionTable(0);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}


creerDossier::~creerDossier()
{
    delete ui;
}
