
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
//int todo(int argc, char *argv[])
//{
//    try
//        {
//            //Dossier d();
//           // BaseManager m()
//            //UVManager2& m= UVManager2::getInstance();
//            /*QApplication app(argc, argv);
//            Profiler p;
//            p.show();
//            return app.exec();*/

//        }
//        catch(UTProfilerException& e)
//        {
//           cout<<e.getInfo().toStdString()<<"\n";
//        }
//        catch(std::exception& e)
//        {
//            qDebug()<<e.what()<<"\n";
//        }
//    return -1;
//}

//il faut init tout les handler de tempalte std (crade mais pas de meilleures sol)
//chaque manager doit être ajouter dans le saver loader de la classe database !!
template<> TemplateManager<UV>* TemplateManager<UV>::handler=0;
template<> TemplateManager<Formation>* TemplateManager<Formation>::handler=0;
template<> TemplateManager<Etudiant>* TemplateManager<Etudiant>::handler=0;
template<> TemplateManager<Categorie>* TemplateManager<Categorie>::handler=0;
template<> TemplateManager<Note>* TemplateManager<Note>::handler=0;
int main(int argc, char *argv[]) {
    //QApplication app(argc, argv);
    try
    {
        TemplateManager<UV>& tUV=TemplateManager<UV>::getInstance();
        TemplateManager<Formation>& tFormation=TemplateManager<Formation>::getInstance();
        TemplateManager<Etudiant>& tEtudiant=TemplateManager<Etudiant>::getInstance();
        TemplateManager<Categorie>& tCat=TemplateManager<Categorie>::getInstance();
        TemplateManager<Note>& tNote=TemplateManager<Note>::getInstance();

        Note A("A","A",1,false);

        Note B("B","B",2,false);
        Note C("C","C",3,false);
        Note D("D","D",4,false);
        Note E("E","E",5,false);
        Note F("F","F",6,true);
        Note FX("FX","FX",7,true);
        Note RES("RES","Reservé",8,true);
        Note ABS("ABS","Absent",9,true);
        Note EC("EC","En cours",1,false);

        qDebug()<<"A == F"<<(A==F);


        Categorie CS("CS","Connaissance Scientifiques");
        Categorie TM("TM","Techniques et méthodes");
        Categorie TSH("TSH","Technologies et Sciences Humaines");
        Categorie SP("SP","Spéciales");

        tCat.getElement("SP").setCode("SPC");
        tCat.getElement("SPC").setDescription("essai");
        qDebug()<<"Code : "<< tCat.getElement("SPC").getCode()<<" Description : ";//<<tCat.getElement("SPC").getDescription();

        Categorie test = StringToCategorie("TM");

        //création d'une UV directement
        map<Categorie,unsigned int> m;
        m.insert(pair<Categorie, unsigned int> (tCat.getElement("CS"),12));
        std::string s1="EE32";
        std::string s2="titre";
        UV newUV(s1,s2,m,true,true);
        UV* pUV= &newUV;

        UV uv2=newUV;//copie
        uv2.addCategorie(tCat.getElement("TM"),5);
        uv2.setCredits(tCat.getElement("TM"),2);
        uv2.setTitre("titre2");
        UV* pUV2= &uv2;
        tUV.New(*pUV2);
        //pour afficher dans la console...
        newUV.display();

        //Création d'une formation directement
        std::map<UV*,bool>m1;
        //m1.insert(std::pair<UV*,bool> (pUV,false));
        std::map<Categorie,unsigned int>m2;
        //m2.insert(std::pair<Categorie,unsigned int> (Categorie::CS,12));

        Formation nF("Nom Formation1","Description Formation1",m1,m2);

        Formation nF2=nF;

        nF.display();
        nF.addUv(pUV,false);
        nF.display();
        nF.addCategorie(tCat.getElement("TM"),52);
        nF.display();
        nF.addUv(pUV2,true);
        nF.display();

        nF2.setNom("Nom Formation2");
        nF2.setDescription("Description Formation2");
        nF2.addUv(pUV,true);
        tFormation.New(nF);
        tFormation.New(nF2);
        //Création d'une Inscription directement

        Inscription nI(uv2,Semestre(Saison::Automne,2012),StringToNote("A"));
        Inscription nI2(newUV,Semestre(Saison::Automne,2011),StringToNote("B"));

        nI.display();
        qDebug() << QString(nI.getUV().getCode().c_str());
        //qDebug()<<nI.validee();

        //création d'un dossier
        std::vector<Inscription> vInscr;
        vInscr.push_back(nI);
        vInscr.push_back(nI2);

        std::vector<Formation*> vForme;
        vForme.push_back(&nF);
        vForme.push_back(&nF2);

        Dossier dos(vInscr,vForme);
        std::map<std::pair<Formation*,Categorie>, std::pair<unsigned int,unsigned int> >  res=dos.getDossierCurrentStatus();
        for(std::map<std::pair<Formation*,Categorie>, std::pair<unsigned int,unsigned int> > ::iterator it=res.begin();it!=res.end();it++)
        {


            qDebug()<<"Formation : "<< std::get<0>(it->first)->getNom()<<"Catégorie : "<< std::get<1>(it->first).getCode()<<", crédits à valider : "<< std::get<0>(it->second)<<" crédits supplémentaires : "<<std::get<1>(it->second);
        }

       //création d'un étudiant
       QDate date(2014,5,3);
       Etudiant e1(dos,1320123,"nom","prenom",date);
       tEtudiant.New(e1);
       //Database db=Database("c:/sqlite/lo21");
       Database db=Database("e:/sqlite/lo21");
       db.save();
       db.load();
       tUV.getElement("EE32").display();
       qDebug() <<tUV.size();
       tUV.clear();
       qDebug() <<tUV.size();
       tFormation.getElement("Nom Formation1");
       if(tFormation.alreadyExist("Nom Formation2")) qDebug()<<"marche";
       if(tFormation.alreadyExist("Nom Forgrrgrgrgmation1")) qDebug()<<"marchepas";
       tEtudiant.getElement("nompreno");
       qDebug()<<"Ca marche";
    }
    catch(std::exception& e)
    {
        qDebug()<<e.what()<<"\n";
    }
    /*TemplateManager<UV>& tUV=TemplateManager<UV>::getInstance();
    TemplateManager<Formation>& tFormation=TemplateManager<Formation>::getInstance();
    TemplateManager<Etudiant>& tEtudiant=TemplateManager<Etudiant>::getInstance();

    //création d'une UV directement
    map<Categorie,unsigned int> m;
    m.insert(pair<Categorie, unsigned int> (Categorie::CS,12));
    std::string s1="EE32";
    std::string s2="titre";
    UV newUV(s1,s2,m,true,true);
    UV* pUV= &newUV;
    tUV.New(*pUV);
    tUV.New(UV("LO21", "Prog", m, false, true));
    std::map<UV*,bool>m1;
    //m1.insert(std::pair<UV*,bool> (pUV,false));
    std::map<Categorie,unsigned int>m2;
    //m2.insert(std::pair<Categorie,unsigned int> (Categorie::CS,12));

    Formation nF("Nom Formation1","Description Formation1",m1,m2);
    tFormation.New(nF);
    Inscription nI2(newUV,Semestre(Saison::Automne,2011),Note::B);

    //qDebug()<<nI.validee();

    //création d'un dossier
    std::vector<Inscription> vInscr;
    vInscr.push_back(nI2);

    Formation nF2=nF;

    nF.display();
    nF.addUv(pUV,false);
    nF.display();
    nF.addCategorie(Categorie::CS,52);

    nF2.setNom("Nom Formation2");
    nF2.setDescription("Description Formation2");
    nF2.addUv(pUV,true);
    tFormation.New(nF);
    tFormation.New(nF2);
    std::vector<Formation*> vForme;
    vForme.push_back(&nF);
    vForme.push_back(&nF2);

    Dossier dos(vInscr,vForme);
           QDate date(2014,5,3);
    Etudiant e1(dos,1320123,"nom","prenom",date);
    tEtudiant.New(e1);*/

//    MainFenetre fen;
//    fen.show();
//    return app.exec();
    return 0;
}

//première partie
//    QLineEdit code(&fenetre);
//    code.setFixedWidth(180);
//    code.move(10,10);

//    QTextEdit titre(&fenetre);
//    titre.setFixedSize(180,110);
//    titre.move(10,45);

//    QPushButton save ("Sauver",&fenetre);
//    save.setFixedWidth(80);
//    save.move(10,170);
//    fenetre.show();
