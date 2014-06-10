#ifndef MAINFENETRE_H
#define MAINFENETRE_H
#include "templatemanager.h"
#include "uv.h"
#include "Formation.h"
#include "Etudiant.h"
#include "database.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QPushButton>
#include "modifieretudiant.h"
#include "modifierform.h"
#include "modifieruv_fen.h"
#include "editerdossier.h"
namespace Ui {
class MainFenetre;
}

class MainFenetre : public QMainWindow
{
    Q_OBJECT

    void updateUV();
    void updateEtudiant();
    void updateFormation();

private slots:
    void refresh();
    void save();
    void load();
    void deleteUV(int i);
    void deleteEtudiant(int i);
    void deleteFormation(int i);
    void modifierUV(int i);
    void modifierEtudiant(int i);
    void modifierFormation(int i);
    void ajouterEtudiant();
    void test();
    void ajouterUV();
public:
    explicit MainFenetre(QWidget *parent = 0);
    ~MainFenetre();

private:
    Ui::MainFenetre *ui;
};

#endif // MAINFENETRE_H
