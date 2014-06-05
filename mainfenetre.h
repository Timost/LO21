#ifndef MAINFENETRE_H
#define MAINFENETRE_H
#include "templatemanager.h"
#include "uv.h"
#include "Formation.h"
#include "Etudiant.h"
#include <QMainWindow>

namespace Ui {
class MainFenetre;
}

class MainFenetre : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainFenetre(QWidget *parent = 0);
    ~MainFenetre();

private:
    Ui::MainFenetre *ui;
};

#endif // MAINFENETRE_H
