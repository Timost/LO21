#ifndef MODIFIERCATEGORIE_H
#define MODIFIERCATEGORIE_H

#include <QDialog>
#include "Categorie.h"

namespace Ui {
class ModifierCategorie;
}

class ModifierCategorie : public QDialog
{
    Q_OBJECT

    void connect();
private slots:
    void ok();
    void cancel();

public:
    explicit ModifierCategorie(QWidget *parent = 0);
    explicit ModifierCategorie(Categorie& cat, QWidget *parent = 0);
    ~ModifierCategorie();

private:
    Ui::ModifierCategorie *ui;
    bool b;
    Categorie* cat;
};

#endif // MODIFIERCATEGORIE_H
