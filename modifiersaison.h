#ifndef MODIFIERSAISON_H
#define MODIFIERSAISON_H

#include <QDialog>
#include "Saison.h"

namespace Ui {
class ModifierSaison;
}

class ModifierSaison : public QDialog
{
    Q_OBJECT

public:
    explicit ModifierSaison(QWidget *parent = 0);
    explicit ModifierSaison(Saison& s, QWidget *parent = 0);
    ~ModifierSaison();

private:
    Ui::ModifierSaison *ui;
};

#endif // MODIFIERSAISON_H
