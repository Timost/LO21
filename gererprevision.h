#ifndef GERERPREVISION_H
#define GERERPREVISION_H

#include <QDialog>
#include <QTableWidget>
#include "Etudiant.h"
#include <QMessageBox>
namespace Ui {
class gererPrevision;
}

class gererPrevision : public QDialog
{
    Q_OBJECT

public:
    explicit gererPrevision(Etudiant& e,QWidget *parent = 0);
    ~gererPrevision();
public slots:
    void displayPrevision();
private:
    Ui::gererPrevision *ui;
    Etudiant& e;
};

#endif // GERERPREVISION_H
