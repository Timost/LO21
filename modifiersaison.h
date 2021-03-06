#ifndef MODIFIERSAISON_H
#define MODIFIERSAISON_H

#include <QDialog>
#include <QMessageBox>
#include "Saison.h"

namespace Ui {
class ModifierSaison;
}

class ModifierSaison : public QDialog
{
    Q_OBJECT

    void connect();
private slots:
    void ok();
    void cancel();

public:
    explicit ModifierSaison(QWidget *parent = 0);
    explicit ModifierSaison(Saison& s, QWidget *parent = 0);
    ~ModifierSaison();

private:
    Ui::ModifierSaison *ui;
    bool b;
    Saison* sai;
};

#endif // MODIFIERSAISON_H
