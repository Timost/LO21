#ifndef MODIFIERETUDIANT_H
#define MODIFIERETUDIANT_H
#include <QDialog>
#include "templatemanager.h"
#include "Dossier.h"
#include "Etudiant.h"

namespace Ui {
class ModifierEtudiant;
}

class ModifierEtudiant : public QDialog
{
    Q_OBJECT

public:
    explicit ModifierEtudiant(Etudiant& etu, QWidget *parent = 0);
    explicit ModifierEtudiant(QWidget *parent = 0);
    ~ModifierEtudiant();

private:
    Etudiant* etudiant;
    bool b;
    Ui::ModifierEtudiant *ui;
};

#endif // MODIFIERETUDIANT_H
