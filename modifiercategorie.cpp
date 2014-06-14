#include "modifiercategorie.h"
#include "ui_modifiercategorie.h"

ModifierCategorie::ModifierCategorie(QWidget *parent) :
    QDialog(parent), b(0), cat(NULL),
    ui(new Ui::ModifierCategorie)
{
    ui->setupUi(this);
    this->connect();
}

ModifierCategorie::ModifierCategorie(Categorie& c, QWidget *parent) :
    QDialog(parent), b(1),
    ui(new Ui::ModifierCategorie)
{
    ui->setupUi(this);
    cat=&c;
    ui->code->setText(cat->getCode());
    ui->code->setDisabled(1);
    ui->description->setText(cat->getDescription());
    this->connect();
}

void ModifierCategorie::connect()
{
    QObject::connect(ui->Valider, SIGNAL(clicked()), this, SLOT(ok()) );
    QObject::connect(ui->Annuler, SIGNAL(clicked()), this, SLOT(cancel()) );
}

void ModifierCategorie::ok()
{
    if(b)
    {
        cat->setDescription(ui->description->toPlainText());
    }
    else
    {
        cat=new Categorie(ui->code->text(), ui->description->toPlainText(), std::vector<Categorie>());
        delete cat;
    }
    this->close();
}

void ModifierCategorie::cancel()
{
    this->close();
}

ModifierCategorie::~ModifierCategorie()
{
    delete ui;
}
