#ifndef UVEDITEUR_H
#define UVEDITEUR_H

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QSpinBox>
#include <QLabel>
#include <QComboBox>
#include "UTProfiler.h"
#include <QString>
#define CREDITS_MAX 30
#define CREDITS_MIN 0
/*
class UVEditeur : public QWidget
{
    Q_OBJECT

    QLineEdit *code;
    QLabel* lCategorie;
    QComboBox* categorie;
    QLabel* lCredits;
    QSpinBox *credits;
    QTextEdit *titre;
    QPushButton *cancel;
    QPushButton *save;
    QVBoxLayout *Vlayout;
    QHBoxLayout* Hlayout1;
    QHBoxLayout* Hlayout2;
    QHBoxLayout* Hlayout3;
    QHBoxLayout* Hlayout4;
    QLabel* ouverture;
    QCheckBox* automne;
    QCheckBox* printemps;

    UV* uv;
    QString path;
public:
    explicit UVEditeur(UV& uvToEdit, QString chemin,QWidget *parent = 0);
public slots:
    void saveUV();


};*/

#endif // UVEDITEUR_H
