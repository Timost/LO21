#ifndef MODIFIERETUDIANT_H
#define MODIFIERETUDIANT_H
#include <QDialog>
#include <QObject>
#include "templatemanager.h"
#include "Dossier.h"
#include "Etudiant.h"
#include "creerdossier.h"
#include <QMessageBox>

namespace Ui {
class ModifierEtudiant;
}

class ModifierEtudiant : public QDialog
{
    Q_OBJECT

private slots:
    void ok();
    void cancel();
    void editDossier();

public:
    explicit ModifierEtudiant(Etudiant& etu, QWidget *parent = 0);
    explicit ModifierEtudiant(QWidget *parent = 0);
    ~ModifierEtudiant();
    void closeEvent(QCloseEvent *event);


private:
    Etudiant* etudiant;
    bool b;
    Ui::ModifierEtudiant *ui;

};

#endif // MODIFIERETUDIANT_H
