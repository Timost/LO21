#include "gererprevision.h"
#include "ui_gererprevision.h"

gererPrevision::gererPrevision(Etudiant &e, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gererPrevision),
    e(e)
{
    ui->setupUi(this);
    displayPrevision();
}

void gererPrevision::displayPrevision()
{
    Dossier currentDos= completeDossier(e.getDossier(),std::map<UV,int>());

    std::vector<Inscription> currentInscr = currentDos.getInscription();
    ui->InscriptionTable_2->setRowCount(currentInscr.size());
    for(unsigned int i=0 ; i!=currentInscr.size();i++)
    {
        QTableWidgetItem* uv=new QTableWidgetItem(currentInscr[i].getCode());
        QTableWidgetItem* semestre=new QTableWidgetItem(currentInscr[i].getSemestre().getCode());
        QTableWidgetItem* resultat=new QTableWidgetItem(currentInscr[i].getResultat().getNote());
        ui->InscriptionTable_2->setItem(i, 0, uv);
        ui->InscriptionTable_2->setItem(i, 1, semestre);
        ui->InscriptionTable_2->setItem(i, 2, resultat);

        if(currentInscr[i].getResultat().getNote()=="TMP")
        {
            uv->setBackground( Qt::green );
            semestre->setBackground( Qt::green );
            resultat->setBackground( Qt::green );
        }
    }
}
gererPrevision::~gererPrevision()
{
    delete ui;
}
