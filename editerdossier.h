#ifndef EDITERDOSSIER_H
#define EDITERDOSSIER_H

#include <QDialog>
#include "Formation.h"
#include "templatemanager.h"
#include <QCheckBox>
namespace Ui {
class editerDossier;
}

class editerDossier : public QDialog
{
    Q_OBJECT

public:
    explicit editerDossier(QWidget *parent = 0);
    ~editerDossier();

private:
    Ui::editerDossier *ui;
};

#endif // EDITERDOSSIER_H
