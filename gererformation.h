#ifndef GERERFORMATION_H
#define GERERFORMATION_H

#include <QDialog>
#include "Formation.h"
namespace Ui {
class gererFormation;
}

class gererFormation : public QDialog
{
    Q_OBJECT

public:
    explicit gererFormation(Formation& f,QWidget *parent = 0);
    explicit gererFormation(QWidget *parent = 0);

    ~gererFormation();
private slots:
    void init();
private:
    Ui::gererFormation *ui;
    bool nouvelle;
    QString nom;
    QString description;
    std::map<UV*,bool> uvs;//contient les Uvs Faisant partie de la formation et si elles sont obligatoires ou pas.
    std::map<Categorie, unsigned int> nbCredits;//Contient le nombre de crédits à valider pour chaque catégories d'UVS
    std::vector<Condition> critereValidation;
};

#endif // GERERFORMATION_H
