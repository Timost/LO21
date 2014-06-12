#include "gererformation.h"
#include "ui_gererformation.h"

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

void gererFormation::init()
{
    ui->NomFormation->setText(nom);
    ui->textEditFormation->setText(description);

    if(nouvelle)
    {
        ui->Suivant->setDisabled(true);
        ui->Valider->setDisabled(true);
    }

    ui->TableUV->hide();
    ui->tableWidgetCategorie->hide();
}


gererFormation::~gererFormation()
{
    delete ui;
}
