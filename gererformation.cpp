 #include "gererformation.h"
#include "ui_gererformation.h"
/*
 * Editeur de nombres de crédits par catégories (en fonction des catégories des UVs).
 * Récupérer les catégories des uvs
 * tableau 2 colonnes
 * Editeur de conditions
 */

gererFormation::gererFormation(Formation& f,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gererFormation)
{
    nom=f.getNom();
    description=f.getDescription();
    uvs=f.getUVs();
    nbCredits=f.getNbCreditsByCat();
    critereValidation=f.getConditions();
    nouvelle=false;

    ui->setupUi(this);

    init();
}
gererFormation::gererFormation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gererFormation)
{
    nom="";
    description="";
    uvs=std::map<UV*,bool>();
    nbCredits=std::map<Categorie, unsigned int>() ;
    critereValidation=std::vector<Condition>();
    nouvelle=true;
    ui->setupUi(this);

     init();
}

std::vector<UV*> gererFormation::getUVVector()
{
    vector<UV*> v;
    for(map<UV*,bool>::iterator it = uvs.begin(); it != uvs.end(); ++it)
    {
      v.push_back(it->first);
    }
    return v;
}

void gererFormation::init()
{
    ui->NomFormation->setText(nom);
    ui->textEditFormation->setText(description);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    if(nouvelle)
    {
//        ui->Suivant->setStyleSheet(QString::fromUtf8("QPushButton:disabled","{ color: gray }"));
//        ui->Valider->setStyleSheet(QString::fromUtf8("QPushButton:disabled","{ color: gray }"));
        ui->Suivant->setEnabled(false);
        ui->Valider->setEnabled(false);

    }
    else
    {
        ui->NomFormation->setEnabled(false);
        ui->Valider->setEnabled(true);
        ui->Suivant->setEnabled(false);
    }
    ui->AjouterLigne->hide();
    ui->TableUVAjouter->hide();
    ui->TableUVSupprimer->hide();
    ui->tableWidgetCategorie->hide();
    ui->LabelUvformation->hide();
    ui->labelCondition->hide();
    ui->labelConditionManuel->setWordWrap(true);
    ui->labelConditionManuel->hide();


    QObject::connect(ui->buttonBox->button(QDialogButtonBox::Ok),SIGNAL(clicked()),this,SLOT(validerTout()));
    QObject::connect(ui->NomFormation,SIGNAL(editingFinished()),this,SLOT(verifierFormationInfo()));
    QObject::connect(ui->Valider,SIGNAL(pressed()),this,SLOT(ajouterFormationInfo()));
}

void gererFormation::verifierFormationInfo()
{
    TemplateManager<Formation>& tFormation=TemplateManager<Formation>::getInstance();

    try
    {
        if(tFormation.size()>0)
        {
            tFormation.getElement(ui->NomFormation->text());

            QMessageBox* test = new QMessageBox();
            test->setText("Erreur une formation du même nom éxiste déjà,\n veuillez changer la valeur du champ nom");
            test->show();
            ui->NomFormation->setText("");
        }
        else
        {
           ui->Valider->setEnabled(true);
        }
    }
    catch(const std::exception& e)
    {
        if(std::string(e.what()).find("getElement")!= std::string::npos)
        {
            ui->Valider->setEnabled(true);
        }
        else
        {
            throw e;
        }
    }
}
void gererFormation::ajouterFormationInfo()
{
    nom=ui->NomFormation->text();
    description=ui->textEditFormation->toPlainText();

    ui->Suivant->setEnabled(true);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    QObject::connect( ui->Suivant,SIGNAL(pressed()),this,SLOT(initGererUVs()));

}

void gererFormation::initGererUVs()
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->NomFormation->hide();
    ui->textEditFormation->hide();
    ui->TableUVAjouter->horizontalHeader()->setStretchLastSection(true);
    ui->TableUVAjouter->resizeColumnsToContents();
    ui->TableUVAjouter->show();
    ui->TableUVSupprimer->horizontalHeader()->setStretchLastSection(true);
    ui->TableUVSupprimer->resizeColumnsToContents();
    ui->TableUVSupprimer->show();
    ui->LabelNomFormation->hide();
    ui->LabelDecriptionFormation->hide();
    ui->LabelUvformation->show();
    if(nouvelle)
    {
        ui->Suivant->setEnabled(false);
    }
    QObject::disconnect( ui->Suivant,SIGNAL(pressed()),this,SLOT(initGererUVs()));
    QObject::disconnect(ui->Valider,SIGNAL(pressed()),this,SLOT(ajouterFormationInfo()));
    QObject::connect(ui->Valider,SIGNAL(pressed()),this,SLOT(validerUVFormation()));
    QObject::connect( ui->Suivant,SIGNAL(pressed()),this,SLOT(initGererCategories()));
    displayUvs();
}
void gererFormation::validerUVFormation()
{
    TemplateManager<UV>& tUV=TemplateManager<UV>::getInstance();
    uvs.clear();
    if(uvToSetNotRequired.size()>0)
    {

        for(unsigned int i=0; i<uvToSetNotRequired.size();i++)
        {
             uvs[&(tUV.getElement(ui->TableUVSupprimer->item(uvToSetNotRequired[i], 0)->text()))]=false;
        }
        uvToSetNotRequired.clear();
    }

    if(uvToSetRequired.size()>0)
    {
        for(unsigned int i=0; i<uvToSetRequired.size();i++)
        {
             uvs[&(tUV.getElement(ui->TableUVSupprimer->item(uvToSetRequired[i], 0)->text()))]=true;
        }
        uvToSetRequired.clear();
    }

    if(uvToBeRemoved.size()>0)
    {
        for(unsigned int i=0; i<uvToBeRemoved.size();i++)
        {
             uvs.erase(&(tUV.getElement(ui->TableUVSupprimer->item(uvToBeRemoved[i], 0)->text())));
        }
        uvToBeRemoved.clear();
    }

    if(uvToBeAdded.size()>0)
    {
        for(unsigned int i=0; i<uvToBeAdded.size();i++)
        {
             uvs[&(tUV.getElement(ui->TableUVAjouter->item(uvToBeAdded[i], 0)->text()))]=false;
        }
        uvToBeAdded.clear();
    }

    if(uvs.size()>0)
    {
        ui->Suivant->setEnabled(true);
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
    displayUvs();
}
void gererFormation::displayUvs()
{
    //Initialisation du tableau contenant les uvs actuelles de la formation
    ui->TableUVSupprimer->setRowCount(uvs.size());
    unsigned int j=0;
    for(std::map<UV*,bool>::iterator i=uvs.begin();i!=uvs.end();i++)
    {
        QTableWidgetItem* code=new QTableWidgetItem(i->first->getCodeQString());
        //code->setFlags(Qt::ItemFlag::ItemIsEnabled);
        code->setFlags(code->flags() ^ Qt::ItemIsEditable);

        MyCheckBox* supprimerUV=new MyCheckBox(j);
        MyCheckBox* obligatoireUV=new MyCheckBox(j);
        QObject::connect(obligatoireUV, SIGNAL(stateChanged(int)),  obligatoireUV, SLOT(isChecked(int)));
        QObject::connect(obligatoireUV, SIGNAL(addMyNumber(int)),  this, SLOT(ajouterObligatoireUV(int)));
        QObject::connect(obligatoireUV, SIGNAL(removeMyNumber(int)),  this, SLOT(supprimerObligatoireUV(int)));
        if(i->second)
        {
            obligatoireUV->setChecked(true);
            uvToSetRequired.push_back(j);
        }
        else
        {
            uvToSetNotRequired.push_back(j);
        }
        ui->TableUVSupprimer->setCellWidget(j, 2, supprimerUV);
        ui->TableUVSupprimer->setCellWidget(j, 1, obligatoireUV);

        ui->TableUVSupprimer->setItem(j, 0, code);

        //config du checkbox

        QObject::connect(supprimerUV, SIGNAL(stateChanged(int)),  supprimerUV, SLOT(isChecked(int)));
        QObject::connect(supprimerUV, SIGNAL(addMyNumber(int)),  this, SLOT(ajouterUVToBeRemoved(int)));
        QObject::connect(supprimerUV, SIGNAL(removeMyNumber(int)),  this, SLOT(supprimerUVToBeRemoved(int)));
        j++;
    }




    std::vector<UV*> uvNotInFormation = uvNotIn(getUVVector());

    //Uvs à ajouter
    ui->TableUVAjouter->setRowCount(uvNotInFormation.size());
    for(unsigned int i=0; i<uvNotInFormation.size(); i++)
    {
        QTableWidgetItem* code=new QTableWidgetItem(uvNotInFormation[i]->getCodeQString());
        MyCheckBox* ajouter=new MyCheckBox(i);
        code->setFlags(code->flags() ^ Qt::ItemIsEditable);
        ui->TableUVAjouter->setItem(i, 0, code);
        ui->TableUVAjouter->setCellWidget(i, 1, ajouter);

        QObject::connect(ajouter, SIGNAL(stateChanged(int)),  ajouter, SLOT(isChecked(int)));
        QObject::connect(ajouter, SIGNAL(addMyNumber(int)),  this, SLOT(ajouterUVToBeAdded(int)));
        QObject::connect(ajouter, SIGNAL(removeMyNumber(int)),  this, SLOT(supprimerUVToBeAdded(int)));
    }

    ui->TableUVAjouter->resizeColumnsToContents();
    ui->TableUVSupprimer->resizeColumnsToContents();
}
void gererFormation::ajouterObligatoireUV(int i)
{
     uvToSetRequired.push_back(i);
}
void gererFormation::supprimerObligatoireUV(int i)
{
    std::vector<int>::iterator it = std::find(uvToSetRequired.begin(),uvToSetRequired.end(),i);
    uvToSetRequired.erase(it);
}
void gererFormation::supprimerUVToBeRemoved(int i)
{
    std::vector<int>::iterator it = std::find(uvToBeRemoved.begin(),uvToBeRemoved.end(),i);
    uvToBeRemoved.erase(it);
    if((uvToBeRemoved.size()==0)&&(uvToBeAdded.size()==0)&&(uvToSetNotRequired.size()==0)&&(uvToSetRequired.size()==0))
    {
        ui->Suivant->setEnabled(false);
    }
}
void gererFormation::ajouterUVToBeRemoved(int i)
{
    uvToBeRemoved.push_back(i);
}
void gererFormation::supprimerUVToBeAdded(int i)
{
    std::vector<int>::iterator it = std::find(uvToBeAdded.begin(),uvToSetRequired.end(),i);
    uvToBeAdded.erase(it);
    if((uvToBeRemoved.size()==0)&&(uvToBeAdded.size()==0)&&(uvToSetNotRequired.size()==0)&&(uvToSetRequired.size()==0))
    {
        ui->Suivant->setEnabled(false);
    }
}
void gererFormation::ajouterUVToBeAdded(int i)
{
    uvToBeAdded.push_back(i);
}


void  gererFormation::initGererCategories()
{
    validerUVFormation();
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->tableWidgetCategorie->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetCategorie->resizeColumnsToContents();
    ui->tableWidgetCategorie->show();
    ui->TableUVAjouter->setRowCount(0);
    ui->TableUVSupprimer->setRowCount(0);
    ui->TableUVAjouter->hide();
    ui->TableUVSupprimer->hide();
    ui->LabelUvformation->hide();
    if(nouvelle)
    {
        ui->Suivant->setEnabled(false);
    }
    QObject::disconnect(ui->Valider,SIGNAL(pressed()),this,SLOT(validerUVFormation()));
    QObject::disconnect( ui->Suivant,SIGNAL(pressed()),this,SLOT(initGererCategories()));
    QObject::connect(ui->Valider,SIGNAL(pressed()),this,SLOT(validerCategoriesFormation()));
    QObject::connect( ui->Suivant,SIGNAL(pressed()),this,SLOT(initGererConditions()));

    displayCategories();
}
void gererFormation::validerCategoriesFormation()
{
    TemplateManager<Categorie>& tCategorie=TemplateManager<Categorie>::getInstance();
    for(int i=0; i<ui->tableWidgetCategorie->rowCount();i++)
    {
          QSpinBox *creds = qobject_cast<QSpinBox*>(ui->tableWidgetCategorie->cellWidget(i,1));
          if(creds!=0)
          {
              nbCredits[tCategorie.getElement(ui->tableWidgetCategorie->item(i,0)->text())]=creds->text().toUInt();
          }
          else
          {
              throw FormationException("Erreur gérerFormation : le qobject_cast n'a pas marché");
          }
    }
     ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    ui->Suivant->setEnabled(true);
}
void gererFormation::displayCategories()
{
    std::map<Categorie, unsigned int> Cats=getCategorieOfUV(getUVVector());
    ui->tableWidgetCategorie->setRowCount(Cats.size());
    unsigned int i=0;
    for(std::map<Categorie, unsigned int>::iterator it=Cats.begin(); it!=Cats.end();it++)
    {
        QTableWidgetItem* code=new QTableWidgetItem(it->first.getCode());
        code->setFlags(code->flags() ^ Qt::ItemIsEditable);
        QSpinBox* creds=new QSpinBox();
        creds->setMinimum(0);
        creds->setMaximum(it->second);
        ui->tableWidgetCategorie->setItem(i, 0, code);
        ui->tableWidgetCategorie->setCellWidget(i,1,creds);
        i++;
    }
}

void gererFormation::initGererConditions()
{
    validerCategoriesFormation();
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->tableWidgetCategorie->hide();
    ui->tableWidgetCategorie->setRowCount(0);
    ui->Suivant->hide();

    ui->TableUVSupprimer->setColumnCount(2);
    ui->TableUVAjouter->setColumnCount(2);
    QStringList changeHeader;

    changeHeader << "Condition" << "Ajouter";
    ui->TableUVAjouter->setHorizontalHeaderLabels(changeHeader);
    changeHeader.clear();
    changeHeader << "Condition" << "Supprimer";
    ui->TableUVSupprimer->setHorizontalHeaderLabels(changeHeader);

    ui->TableUVAjouter->resizeColumnsToContents();
    ui->TableUVSupprimer->resizeColumnsToContents();
    ui->labelConditionManuel->show();
    ui->TableUVAjouter->show();
    ui->TableUVSupprimer->show();
    ui->AjouterLigne->show();
    QObject::disconnect(ui->Valider,SIGNAL(pressed()),this,SLOT(validerCategoriesFormation()));
    QObject::disconnect( ui->Suivant,SIGNAL(pressed()),this,SLOT(initGererConditions()));
    QObject::connect(ui->Valider,SIGNAL(pressed()),this,SLOT(validerCondition()));
    QObject::connect(ui->AjouterLigne, SIGNAL(clicked()),  this, SLOT(addRowInscription()));
    displayConditions();
}

void gererFormation::displayConditions()
{
    QObject::disconnect( ui->TableUVSupprimer,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(testerCondition(QTableWidgetItem*)));
    ui->TableUVSupprimer->setRowCount(critereValidation.size());
    unsigned int j=0;
    for(std::vector<Condition>::iterator i=critereValidation.begin();i!=critereValidation.end();i++)
    {
        QTableWidgetItem* code=new QTableWidgetItem(i->getCond());
        //code->setFlags(Qt::ItemFlag::ItemIsEnabled);
        code->setFlags(code->flags() |= Qt::ItemIsEditable);

        MyCheckBox* supprimerCondition=new MyCheckBox(j);
        QObject::connect(supprimerCondition, SIGNAL(stateChanged(int)),  supprimerCondition, SLOT(isChecked(int)));
        QObject::connect(supprimerCondition, SIGNAL(addMyNumber(int)),  this, SLOT(ajouterConditionToBeRemoved(int)));
        QObject::connect(supprimerCondition, SIGNAL(removeMyNumber(int)),  this, SLOT(supprimerConditionToBeRemoved(int)));

        ui->TableUVSupprimer->setCellWidget(j, 1, supprimerCondition);
        ui->TableUVSupprimer->setItem(j, 0, code);
        j++;
    }
    fillConditionTable(0);
    ui->TableUVAjouter->resizeColumnsToContents();
    ui->TableUVSupprimer->resizeColumnsToContents();
    QObject::connect( ui->TableUVSupprimer,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(testerCondition(QTableWidgetItem*)));
}
void gererFormation::fillConditionTable(int i)
{
    QObject::disconnect( ui->TableUVAjouter,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(testerCondition(QTableWidgetItem*)));
    ui->TableUVAjouter->insertRow(ui->TableUVAjouter->rowCount());
    QTableWidgetItem* cond=new QTableWidgetItem("");
    //cond->setFlags(Qt::ItemFlag::ItemIsEnabled);
    cond->setFlags(cond->flags() |= Qt::ItemIsEditable);
    MyCheckBox* ajouterCondition=new MyCheckBox(i);
    QObject::connect(ajouterCondition, SIGNAL(stateChanged(int)),  ajouterCondition, SLOT(isChecked(int)));
    QObject::connect(ajouterCondition, SIGNAL(addMyNumber(int)),  this, SLOT(ajouterConditionToBeAdded(int)));
    QObject::connect(ajouterCondition, SIGNAL(removeMyNumber(int)),  this, SLOT(supprimerConditionToBeAdded(int)));


    ui->TableUVAjouter->setCellWidget(i, 1, ajouterCondition);
    ui->TableUVAjouter->setItem(i, 0, cond);
    QObject::connect( ui->TableUVAjouter,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(testerCondition(QTableWidgetItem*)));

}
void gererFormation::addRowInscription()
{
    int nbLignes = ui->TableUVAjouter->rowCount();
    fillConditionTable(nbLignes);
}

void gererFormation::validerCondition()
{
      Dossier dos();
      std::vector<Condition> testConds;

      //Réalisation des modifications

      if(conditionToBeRemoved.size()>0)
      {
          for(unsigned int i=0; i<conditionToBeRemoved.size();i++)
          {
               critereValidation.erase(critereValidation.begin()+conditionToBeRemoved[i]);
          }
          conditionToBeRemoved.clear();
      }

      if(conditionToBeAdded.size()>0)
      {
          for(unsigned int i=0; i<conditionToBeAdded.size();i++)
          {
              if(ui->TableUVAjouter->item(conditionToBeAdded[i],0)->text() != "")
              {
                    critereValidation.push_back(Condition(ui->TableUVAjouter->item(conditionToBeAdded[i],0)->text()));
              }
          }
          conditionToBeAdded.clear();
      }
      ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

      ui->TableUVAjouter->setRowCount(0);
      displayConditions();
}

void gererFormation::testerCondition(QTableWidgetItem* item)
{
    if(item->text()!="")
    {
        Dossier dos;

        std::vector<Condition> conds;
        conds.push_back(item->text());

        try
        {
            dos.conditionsChecked(conds);
        }
        catch(std::exception& e)
        {
            QMessageBox* err = new QMessageBox();
            err->setText("Erreur la condition"+item->text()+" , n'est pas valide : "+QString(e.what()));
            err->show();

            item->setText("");
        }
    }
}

void gererFormation::ajouterConditionToBeRemoved(int i)
{
    conditionToBeRemoved.push_back(i);
}
void gererFormation::supprimerConditionToBeRemoved(int i)
{
    std::vector<int>::iterator it = std::find(conditionToBeRemoved.begin(),conditionToBeRemoved.end(),i);
    conditionToBeRemoved.erase(it);
}
void gererFormation::ajouterConditionToBeAdded(int i)
{
     conditionToBeAdded.push_back(i);
}
void gererFormation::supprimerConditionToBeAdded(int i)
{
    std::vector<int>::iterator it = std::find(conditionToBeAdded.begin(),conditionToBeAdded.end(),i);
    conditionToBeAdded.erase(it);
}
void gererFormation::validerTout()
{

    if(nouvelle)
    {
        Formation F(nom,description,uvs,nbCredits,critereValidation);
    }
    else
    {
        TemplateManager<Formation>& tFormation=TemplateManager<Formation>::getInstance();
        tFormation.getElement(nom.toStdString()).setDescription(description);
        tFormation.getElement(nom.toStdString()).setConditions(critereValidation);
        tFormation.getElement(nom.toStdString()).setUVs(uvs);
        tFormation.getElement(nom.toStdString()).setNbsCredsRequired(nbCredits);
    }

}
gererFormation::~gererFormation()
{
    delete ui;
}
