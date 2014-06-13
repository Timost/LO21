#include "modifiernote.h"
#include "ui_modifiernote.h"

ModifierNote::ModifierNote(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifierNote)
{
    ui->setupUi(this);
}

ModifierNote::ModifierNote(Note& n, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifierNote)
{
    ui->setupUi(this);
}

ModifierNote::~ModifierNote()
{
    delete ui;
}
