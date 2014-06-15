#include "modifiersemestre.h"
#include "ui_modifiersemestre.h"

ModifierSemestre::ModifierSemestre( QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifierSemestre)
{
    ui->setupUi(this);
    this->connect();
    ui->spinBox->setRange(1900, 23000);
    ui->spinBox->setValue(2014);
}

void ModifierSemestre::connect()
{
    TemplateManager<Saison>& tSai=TemplateManager<Saison>::getInstance();
    for(unsigned int i=0; i<tSai.size(); i++)
    {
        ui->comboBox->addItem(tSai.getIterator()[i].getNom());
    }
    QObject::connect(ui->Valider, SIGNAL(clicked()), this, SLOT(ok()) );
    QObject::connect(ui->Annuler, SIGNAL(clicked()), this, SLOT(cancel()) );
}

void ModifierSemestre::ok()
{
    try
    {
        TemplateManager<Saison>& tSai=TemplateManager<Saison>::getInstance();
        Semestre(tSai.getIterator()[ui->comboBox->currentIndex()], ui->spinBox->value());
        this->close();
    }
    catch(std::exception& e)
    {
        QMessageBox::warning(this, "Erreur", e.what());
    }
}

void ModifierSemestre::cancel()
{
    this->close();
}

ModifierSemestre::~ModifierSemestre()
{
    delete ui;
}
