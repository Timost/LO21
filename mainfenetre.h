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
    void save();
    void load();
    void deleteUV(int i);
    void deleteEtudiant(int i);
    void deleteFormation(int i);
public:
    explicit MainFenetre(QWidget *parent = 0);
    ~MainFenetre();

private:
    Ui::MainFenetre *ui;
};

#endif // MAINFENETRE_H
