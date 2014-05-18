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
#include "database.h"
#include "templatemanager.h"
#include "templatestd.h"
#include <iostream>


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
template<> TemplateManager<TemplateStd>* TemplateManager<TemplateStd>::handler=0;
int main(int argc, char *argv[]) {
     QCoreApplication app(argc, argv);
     Database& db=Database::getInstance();
     db.destroyInstance();
     TemplateManager<TemplateStd>& t=TemplateManager<TemplateStd>::getInstance();
     TemplateStd eletest(3);
     t.New(eletest);
     t.getElement("3").display();
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
