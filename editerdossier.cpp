#include "editerdossier.h"
#include "ui_editerdossier.h"

editerDossier::editerDossier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editerDossier)
{

    ui->setupUi(this);
    TemplateManager<Formation>& tForm=TemplateManager<Formation>::getInstance();

    ui->FormationTable->setRowCount(tForm.size());
    //ui->FormationTable->setColumnCount(2);
    for(unsigned int i=0; i<tForm.size(); i++)
    {
        QTableWidgetItem* nom=new QTableWidgetItem(tForm.getIterator()[i].getNom());
        QCheckBox* choisir=new QCheckBox();
        ui->FormationTable->setCellWidget(i, 1, choisir);
        nom->setFlags(Qt::ItemFlag::ItemIsEnabled);
        ui->FormationTable->setItem(i, 0, nom);

        //config du suppr
        //        QSignalMapper* sig = new QSignalMapper(this);
        //        QObject::connect(suppr, SIGNAL(clicked()), sig, SLOT(map()));
        //        sig->setMapping(suppr, i);
        //        QObject::connect(sig, SIGNAL(mapped(int)), this, SLOT(deleteFormation(int)));
        //        //config modif
        //        QSignalMapper* sig2 = new QSignalMapper(this);
        //        QObject::connect(modif, SIGNAL(clicked()), sig2, SLOT(map()));
        //        sig->setMapping(modif, i);
        //        QObject::connect(sig, SIGNAL(mapped(int)), this, SLOT(modifierFormation(int)));}
    }

}

editerDossier::~editerDossier()
{
    delete ui;
}
