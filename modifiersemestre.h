#ifndef MODIFIERSEMESTRE_H
#define MODIFIERSEMESTRE_H

#include <QDialog>
#include "Semestre.h"

namespace Ui {
class ModifierSemestre;
}

class ModifierSemestre : public QDialog
{
    Q_OBJECT

public:
    explicit ModifierSemestre(QWidget *parent = 0);
    explicit ModifierSemestre(Semestre& s, QWidget *parent = 0);
    ~ModifierSemestre();

private:
    Ui::ModifierSemestre *ui;
};

#endif // MODIFIERSEMESTRE_H
