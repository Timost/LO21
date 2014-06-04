#ifndef MODIFIERETUDIANT_H
#define MODIFIERETUDIANT_H

#include <QDialog>

namespace Ui {
class ModifierEtudiant;
}

class ModifierEtudiant : public QDialog
{
    Q_OBJECT

public:
    explicit ModifierEtudiant(QWidget *parent = 0);
    ~ModifierEtudiant();

private:
    Ui::ModifierEtudiant *ui;
};

#endif // MODIFIERETUDIANT_H
