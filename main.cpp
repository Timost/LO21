/*Ce qu'il te reste à faire :
- OK. L'affichage de l'édition d'UVS (s'affiche et se ferme tout de suite...)
- ne sauvegarde pas les changements qui ont été faits...
*/
#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include "UTProfiler.h"
#include "uvediteur.h"
#include "profiler.h"
#include <iostream>


int todo(int argc, char *argv[])
{
    try
        {
            //cout<<"test";
            QApplication app(argc, argv);

            //m.load("E:\\sauvegarde\\ordi_tim\\autres\\Tim\\UTC\\P14\\LO21\\TDs\\TD6\\Exercice2\\build-exercice2-Desktop_Qt_5_2_1_MinGW_32bit-Debug\\debug\\UV_XML.xml");
            //UV& mUv= m.getUV("NF16");



            //UVEditeur fenetre(mUv);
            //fenetre.show();
            Profiler p;
            p.show();
            return app.exec();
//            QWidget fenetre;
//            fenetre.setFixedSize(200, 200);
//            QLineEdit *code = new QLineEdit(mUv.getCode());
//            QTextEdit *titre = new QTextEdit(mUv.getTitre());
//            QPushButton *save = new QPushButton("Sauver");

//            QVBoxLayout *layout = new QVBoxLayout;

//            layout->addWidget(code);
//            layout->addWidget(titre);
//            layout->addWidget(save);

//            fenetre.setLayout(layout);
//            fenetre.show();
//            return app.exec();
        }
        catch(UTProfilerException& e)
        {
           std::cout<<e.getInfo().toStdString()<<"\n";
        }
        catch(std::exception& e)
        {
            qDebug()<<e.what()<<"\n";
        }
    return -1;
}
int main(int argc, char *argv[]) {

     return todo(argc,argv);
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
