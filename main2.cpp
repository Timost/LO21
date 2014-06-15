
#include <QApplication>
#include <QtGui>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <string>
#include <iostream>

#include "mainfenetre.h"
#include "database.h"
#include "templatemanager.h"
#include "EntityStd.h"
#include "uv.h"
#include "Formation.h"
#include "enums.h"
#include "Dossier.h"
#include "Semestre.h"
#include "Inscription.h"
#include "Exception.h"
#include "Etudiant.h"
#include "Categorie.h"
#include "Note.h"
#include "Saison.h"
#include "Condition.h"
#include "ConditionChecker.h"


template<> TemplateManager<UV>* TemplateManager<UV>::handler=0;
template<> TemplateManager<Formation>* TemplateManager<Formation>::handler=0;
template<> TemplateManager<Etudiant>* TemplateManager<Etudiant>::handler=0;
template<> TemplateManager<Categorie>* TemplateManager<Categorie>::handler=0;
template<> TemplateManager<Note>* TemplateManager<Note>::handler=0;
template<> TemplateManager<Saison>* TemplateManager<Saison>::handler=0;
template<> TemplateManager<Semestre>* TemplateManager<Semestre>::handler=0;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainFenetre fen;
    fen.show();
    try
    {
        return app.exec();
    }
    catch(std::exception& e)
    {
        qDebug()<<e.what()<<"\n";
    }
}
