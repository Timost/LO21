 #include "gererformation.h"
#include "ui_gererformation.h"
/*
 * Charger les uvs de la formations
 * Charger les uvs
 * Ajouter supprimer Uvs de la formation
 * Changer le fait qu'une Uv soit obligatoire ou non
 * Editeur de nombres de crédits par catégories (en fonction des catégories des UVs).
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

    ui->TableUVAjouter->hide();
    ui->TableUVSupprimer->hide();
    ui->tableWidgetCategorie->hide();
    ui->LabelUvformation->hide();



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

    QObject::connect( ui->Suivant,SIGNAL(pressed()),this,SLOT(initGererUVs()));

}

void gererFormation::initGererUVs()
{
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
        code->setFlags(Qt::ItemFlag::ItemIsEnabled);

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
        code->setFlags(Qt::ItemIsEnabled);
        ui->TableUVAjouter->setItem(i, 0, code);
        ui->TableUVAjouter->setCellWidget(i, 1, ajouter);

        QObject::connect(ajouter, SIGNAL(stateChanged(int)),  ajouter, SLOT(isChecked(int)));
        QObject::connect(ajouter, SIGNAL(addMyNumber(int)),  this, SLOT(ajouterUVToBeAdded(int)));
        QObject::connect(ajouter, SIGNAL(removeMyNumber(int)),  this, SLOT(supprimerUVToBeAdded(int)));
    }
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

gererFormation::~gererFormation()
{
    delete ui;
}
