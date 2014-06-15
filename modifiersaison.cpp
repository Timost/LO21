#include "modifiersaison.h"
#include "ui_modifiersaison.h"

ModifierSaison::ModifierSaison(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifierSaison),
     b(0),sai(NULL)
{
    ui->setupUi(this);
    this->connect();
}

ModifierSaison::ModifierSaison(Saison& s, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifierSaison),
     b(1),sai(&s)
{
    ui->setupUi(this);
    ui->Nom->setText(sai->getNom());
    ui->Nom->setDisabled(1);
    ui->Description->setText(sai->getDescription());
    this->connect();
}

void ModifierSaison::connect()
{
    QObject::connect(ui->Valider, SIGNAL(clicked()), this, SLOT(ok()) );
    QObject::connect(ui->Annuler, SIGNAL(clicked()), this, SLOT(cancel()) );
}

void ModifierSaison::ok()
{
    if(b)
    {
        sai->setDescription(ui->Description->toPlainText());
    }
    else
    {
        sai=new Saison(ui->Nom->text().toStdString(), ui->Description->toPlainText().toStdString());
        delete sai;
    }
    this->close();
}

void ModifierSaison::cancel()
{
    this->close();
}

ModifierSaison::~ModifierSaison()
{
    delete ui;
}
