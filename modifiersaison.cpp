#include "modifiersaison.h"
#include "ui_modifiersaison.h"

ModifierSaison::ModifierSaison(QWidget *parent) :
    QDialog(parent), sai(NULL), b(0),
    ui(new Ui::ModifierSaison)
{
    ui->setupUi(this);
    this->connect();
}

ModifierSaison::ModifierSaison(Saison& s, QWidget *parent) :
    QDialog(parent), sai(&s), b(1),
    ui(new Ui::ModifierSaison)
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
    try
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
    catch(std::exception& e)
    {
        QMessageBox::warning(this, "Erreur", e.what());
    }
}

void ModifierSaison::cancel()
{
    this->close();
}

ModifierSaison::~ModifierSaison()
{
    delete ui;
}
