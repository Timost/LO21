#include "uvediteur.h"
#include <QSignalMapper>

//void UVEditeur::saveUV()
//{
//    uv->setCategorie(StringToCategorie(categorie->itemText(categorie->currentIndex())));
//    uv->setCode(code->text());
//    uv->setNbCredits(credits->value());
//    uv->setOuvertureAutomne(automne->isChecked());
//    uv->setOuverturePrintemps(printemps->isChecked());
//    uv->setTitre(titre->toPlainText());
//    UVManager& myUv=UVManager::getInstance();
//    myUv.save(path);
//    this->close();
//}

//UVEditeur::UVEditeur(UV &uvToEdit,QString chemin, QWidget *parent) : QWidget(parent)
//{
//    path=chemin;
//    uv=&uvToEdit;
//    code = new QLineEdit(uvToEdit.getCode(),this);
//    titre = new QTextEdit(uvToEdit.getTitre(),this);
//    save = new QPushButton("Sauver",this);
//    cancel = new QPushButton("Annuler",this);
//    QObject::connect(cancel, SIGNAL(clicked()),qApp, SLOT(quit()));
//    QObject::connect(save, SIGNAL(clicked()),this, SLOT(saveUV()));
//    categorie =new QComboBox(this);
//    credits = new QSpinBox(this);
//    ouverture = new QLabel("ouverture",this);
//    lCategorie = new QLabel("catégorie",this);
//    lCredits = new QLabel("crédits",this);
//    automne = new QCheckBox("automne",this);
//    printemps = new QCheckBox("printemps",this);

//    if(uvToEdit.ouvertureAutomne())
//    {
//        automne->setChecked(true);
//    }
//    if(uvToEdit.ouverturePrintemps())
//    {
//        printemps->setChecked(true);
//    }

//    categorie->addItem(CategorieToString(uvToEdit.getCategorie()));

//    for(int i=0; i!=(int)Categorie::last; i++)
//    {
//        if((Categorie)i!=uvToEdit.getCategorie())
//        {
//            categorie->addItem(CategorieToString((Categorie)i));
//        }
//    }
//    credits->setValue(uvToEdit.getNbCredits());
//    credits->setMaximum(CREDITS_MAX);
//    credits->setMinimum(CREDITS_MIN);

//    Hlayout1=new QHBoxLayout;
//    Hlayout1->addWidget(code);
//    Hlayout1->addWidget(lCategorie);
//    Hlayout1->addWidget(categorie);
//    Hlayout1->addWidget(lCredits);
//    Hlayout1->addWidget(credits);

//    Hlayout2=new QHBoxLayout;
//    Hlayout2->addWidget(titre);

//    Hlayout3=new QHBoxLayout;
//    Hlayout3->addWidget(ouverture);
//    Hlayout3->addWidget(automne);
//    Hlayout3->addWidget(printemps);
//    Hlayout4=new QHBoxLayout;
//    Hlayout4->addWidget(save);
//    Hlayout4->addWidget(cancel);

//    Vlayout=new QVBoxLayout;
//    Vlayout->addLayout(Hlayout1);
//    Vlayout->addLayout(Hlayout2);
//    Vlayout->addLayout(Hlayout3);
//    Vlayout->addLayout(Hlayout4);

//    this->setLayout(Vlayout);

//}
