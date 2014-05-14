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
            //Dossier d();
           // BaseManager m()
            UVManager2& m= UVManager2::getInstance();
            /*QApplication app(argc, argv);
            Profiler p;
            p.show();
            return app.exec();*/

        }
        catch(UTProfilerException& e)
        {
           cout<<e.getInfo().toStdString()<<"\n";
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
