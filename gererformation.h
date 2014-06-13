#ifndef GERERFORMATION_H
#define GERERFORMATION_H

#include <QDialog>
#include "Formation.h"
#include <QMessageBox>
#include "templatemanager.h"
#include "QTgraphTools.h"
#include <QSpinBox>
#include <QTableWidgetItem>
#include "Dossier.h"
namespace Ui {
class gererFormation;
}

class gererFormation : public QDialog
{
    Q_OBJECT

public:
    explicit gererFormation(Formation& f,QWidget *parent = 0);
    explicit gererFormation(QWidget *parent = 0);
    std::vector<UV*> getUVVector();
    ~gererFormation();
private slots:
    void init();
    void verifierFormationInfo();
    void ajouterFormationInfo();
    void initGererUVs();
    void displayUvs();
    void ajouterObligatoireUV(int i);
    void supprimerObligatoireUV(int i);
    void supprimerUVToBeRemoved(int i);
    void ajouterUVToBeRemoved(int i);
    void supprimerUVToBeAdded(int i);
    void ajouterUVToBeAdded(int i);
    void validerUVFormation();
    void initGererCategories();
    void validerCategoriesFormation();
    void displayCategories();
    void initGererConditions();
    void displayConditions();
    void validerCondition();
    void ajouterConditionToBeRemoved(int i);
    void supprimerConditionToBeRemoved(int i);
    void ajouterConditionToBeAdded(int i);
    void supprimerConditionToBeAdded(int i);
    void fillConditionTable(int i);
    void addRowInscription();
    void testerCondition(QTableWidgetItem *item);
    void validerTout();

private:
    Ui::gererFormation *ui;
    bool nouvelle;
    QString nom;
    QString description;
    std::map<UV*,bool> uvs;//contient les Uvs Faisant partie de la formation et si elles sont obligatoires ou pas.
    std::map<Categorie, unsigned int> nbCredits;//Contient le nombre de crédits à valider pour chaque catégories d'UVS
    std::vector<Condition> critereValidation;

    std::vector<int> uvToSetNotRequired;
    std::vector<int> uvToSetRequired;
    std::vector<int> uvToBeAdded;
    std::vector<int> uvToBeRemoved;
    std::vector<int> conditionToBeAdded;
    std::vector<int> conditionToBeRemoved;
};

#endif // GERERFORMATION_H
