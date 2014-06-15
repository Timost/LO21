#include "modifieruv_fen.h"
#include "ui_modifieruv_fen.h"


Modifieruv_fen::Modifieruv_fen(UV& uv, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Modifieruv_fen),
     uv(&uv)
{
    ui->setupUi(this);
    b=1;
    ui->code->setText(QString(uv.getCode().c_str()));
    ui->code->setDisabled(1);
    ui->nom->setText(QString(uv.getTitre().c_str()));
    ui->automne->setChecked(uv.ouvertureAutomne());
    ui->printemps->setChecked(uv.ouverturePrintemps());
    TemplateManager<Categorie>& tCat=TemplateManager<Categorie>::getInstance();
    for(unsigned int i=0; i<tCat.size(); i++)
    {
        ui->type_cat->addItem(tCat.getIterator()[i].getCode());
    }
    QObject::connect(ui->Ok, SIGNAL(clicked()), this, SLOT(ok()) );
    QObject::connect(ui->Cancel, SIGNAL(clicked()), this, SLOT(cancel()) );
    QObject::connect(ui->appliquer, SIGNAL(clicked()), this, SLOT(updateCredits()) );
    QObject::connect(ui->type_cat, SIGNAL(currentIndexChanged(QString)), this, SLOT(afficheCredits(QString)) );
}

Modifieruv_fen::Modifieruv_fen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Modifieruv_fen)
{
    uv=NULL;
    b=0;
    ui->setupUi(this);
    TemplateManager<Categorie>& tCat=TemplateManager<Categorie>::getInstance();
    for(unsigned int i=0; i<tCat.size(); i++)
    {
        ui->type_cat->addItem(tCat.getIterator()[i].getCode());
    }
    QObject::connect(ui->Ok, SIGNAL(clicked()), this, SLOT(ok()) );
    QObject::connect(ui->Cancel, SIGNAL(clicked()), this, SLOT(cancel()) );
    QObject::connect(ui->appliquer, SIGNAL(clicked()), this, SLOT(updateCredits()) );
    QObject::connect(ui->type_cat, SIGNAL(currentIndexChanged(QString)), this, SLOT(afficheCredits(QString)) );
}

Modifieruv_fen::~Modifieruv_fen()
{
    delete ui;
}

void Modifieruv_fen::ok()
{
    try
    {
        if(!b)
        {
            uv = new UV(ui->code->text().toStdString(), ui->nom->text().toStdString(), cat, ui->automne->isChecked(), ui->printemps->isChecked());
            delete uv;
        }
        else
        {
            uv->setTitre(ui->nom->text().toStdString());
            uv->setAutomne(ui->automne->isChecked());
            uv->setPrintemps(ui->printemps->isChecked());
        }
        this->close();
    }
    catch(std::exception& e)
    {
        QMessageBox::warning(this, "Erreur", e.what());
    }
}

void Modifieruv_fen::cancel()
{
    this->close();
}

void Modifieruv_fen::updateCredits()
{
    TemplateManager<Categorie>& tCat=TemplateManager<Categorie>::getInstance();
    if(b)
    {
        uv->setCredits(tCat.getElement(ui->type_cat->currentText()), ui->nb_credit->text().toUInt());
    }
    else
    {

        cat[tCat.getElement(ui->type_cat->currentText())]=ui->nb_credit->text().toUInt();
    }
}

void Modifieruv_fen::afficheCredits(QString q)
{
    TemplateManager<Categorie>& tCat=TemplateManager<Categorie>::getInstance();
    if(b)
    {
        const map<Categorie, unsigned int> cre=uv->getCredits();
        if(cre.find(tCat.getElement(q.toStdString()))!=cre.end())
        {
            ui->nb_credit->setText(QString::number(uv->getCredits().find(tCat.getElement(q.toStdString()))->second));
        }
        else
        {
           ui->nb_credit->setText("0");
        }
    }
    else
    {
        ui->nb_credit->setText(QString::number(cat[tCat.getElement(q.toStdString())]));
    }
}
