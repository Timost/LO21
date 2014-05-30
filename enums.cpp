#include "enums.h"
#include "Exception.h"

Categorie StringToCategorie(const QString& str){
    if (str=="CS") return Categorie::CS;
    else
    if (str=="TM") return Categorie::TM;
    else
    if (str=="SP") return Categorie::SP;
    else
    if (str=="TSH") return Categorie::TSH;
    else {
        throw UException(QString("erreur, StringToCategorie, categorie ")+str+" inexistante");
    }
}


QTextStream& operator>>(QTextStream& f, Categorie& cat){
    QString str;
    f>>str;
    if (str=="CS") cat=Categorie::CS;
    else
    if (str=="TM") cat=Categorie::TM;
    else
    if (str=="SP") cat=Categorie::SP;
    else
    if (str=="TSH") cat=Categorie::TSH;
    else {
        throw UException("erreur, lecture categorie");
    }
    return f;
}

QString CategorieToString(Categorie c){
    switch(c){
    case Categorie::CS: return "CS";
    case Categorie::TM: return "TM";
    case Categorie::SP: return "SP";
    case Categorie::TSH: return "TSH";
    default: throw UException("erreur, categorie non traitee");
    }
}

QTextStream& operator<<(QTextStream& f, const Categorie& cat){
    switch(cat){
    case Categorie::CS: f<<"CS"; break;
    case Categorie::TM: f<<"TM"; break;
    case Categorie::SP: f<<"SP"; break;
    case Categorie::TSH: f<<"TSH"; break;
    default: throw UException("erreur, categorie non traitee");
    }
    return f;
}
