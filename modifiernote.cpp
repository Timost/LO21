#include "modifiernote.h"
#include "ui_modifiernote.h"

ModifierNote::ModifierNote(QWidget *parent) :
    QDialog(parent), note(NULL), b(0),
    ui(new Ui::ModifierNote)
{
    ui->setupUi(this);
    this->connect();
}

ModifierNote::ModifierNote(Note& n, QWidget *parent) :
    QDialog(parent), note(&n), b(1),
    ui(new Ui::ModifierNote)
{
    ui->setupUi(this);
    ui->Nom->setText(note->getNote());
    ui->Nom->setDisabled(1);
    ui->Description->setText(note->getDescription());
    ui->Eliminatoire->setValue(note->getEliminatoire());
    ui->Rang->setValue(note->getRang());
    ui->Eliminatoire->setDisabled(1);
    this->connect();
}

void ModifierNote::connect()
{
    QObject::connect(ui->Valider, SIGNAL(clicked()), this, SLOT(ok()) );
    QObject::connect(ui->Annuler, SIGNAL(clicked()), this, SLOT(cancel()) );
    ui->Eliminatoire->setRange(0,2);
}

void ModifierNote::ok()
{
    if(b)
    {
        note->setDescription(ui->Description->toPlainText());
        note->setRang(ui->Rang->value());
    }
    else
    {
        note=new Note(ui->Nom->text(), ui->Description->toPlainText(), ui->Rang->value(), ui->Eliminatoire->value());
        delete note;
    }
    this->close();
}

void ModifierNote::cancel()
{
    this->close();
}

ModifierNote::~ModifierNote()
{
    delete ui;
}
