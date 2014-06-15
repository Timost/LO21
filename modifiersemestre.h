#ifndef MODIFIERSEMESTRE_H
#define MODIFIERSEMESTRE_H

#include <QDialog>
#include <QMessageBox>
#include "Semestre.h"

namespace Ui {
class ModifierSemestre;
}

class ModifierSemestre : public QDialog
{
    Q_OBJECT

    void connect();
private slots:
    void ok();
    void cancel();

public:
    explicit ModifierSemestre(QWidget *parent = 0);
    explicit ModifierSemestre(Semestre& s, QWidget *parent = 0);
    ~ModifierSemestre();

private:
    Ui::ModifierSemestre *ui;
};

#endif // MODIFIERSEMESTRE_H
