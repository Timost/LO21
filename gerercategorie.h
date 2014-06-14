#ifndef GERERCATEGORIE_H
#define GERERCATEGORIE_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "Categorie.h"
#include "templatemanager.h"
#include <QMessageBox>
namespace Ui {
class gererCategorie;
}

class gererCategorie : public QDialog
{
    Q_OBJECT

public:
    explicit gererCategorie(QWidget *parent = 0);
    //explicit gererCategorie(QWidget *parent = 0,std::vector<Categorie>& cats);
    ~gererCategorie();

public slots:
    void displayTree();
    void validerTree();

private:
    Ui::gererCategorie *ui;
    QTreeWidgetItem *addTreeRoot(QString name, QString description);
    QTreeWidgetItem *addTreeChild(QTreeWidgetItem *parent,QString name, QString description);
    std::map<Categorie, QTreeWidgetItem *> tree;

    //std::vector<Categorie>& sousCategorie;

};

#endif // GERERCATEGORIE_H
