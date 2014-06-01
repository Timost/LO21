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
        QString s="erreur, StringToCategorie, categorie "+str+" inexistante";
        throw EnumException(s.toStdString());
    }
}

Categorie IntToCategorie(const int n){
    if (n==0) return Categorie::CS;
    else
    if (n==1) return Categorie::TM;
    else
    if (n==2) return Categorie::SP;
    else
    if (n==3) return Categorie::TSH;
    else {
        QString s="erreur, StringToCategorie, categorie inexistante";
        throw EnumException(s.toStdString());
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
        throw EnumException("erreur, lecture categorie");
    }
    return f;
}

QString CategorieToString(Categorie c){
    switch(c){
    case Categorie::CS : return "CS";
    case Categorie::TM : return "TM";
    case Categorie::SP : return "SP";
    case Categorie::TSH : return "TSH";
    default: throw EnumException("erreur, categorie non traitee");
    }
}

Saison StringToSaison(const QString& str){
    if (str=="A" || str=="Automne") return Saison::Automne;
    else
    if (str=="P" || str=="Printemps") return Saison::Printemps;
    else {
        QString s="erreur, StringToSaison, saison "+str+" inexistante";
        throw EnumException(s.toStdString());
    }
}

QString SaisonToString(Saison c){
    switch(c){
    case Saison::Automne : return "Automne";
    case Saison::Printemps : return "Printemps";
    default: throw EnumException("erreur, categorie non traitee");
    }
}

QTextStream& operator<<(QTextStream& f, const Categorie& cat){
    switch(cat){
    case Categorie::CS: f<<"CS"; break;
    case Categorie::TM: f<<"TM"; break;
    case Categorie::SP: f<<"SP"; break;
    case Categorie::TSH: f<<"TSH"; break;
    default: throw EnumException("erreur, categorie non traitee");
    }
    return f;
}

inline QDebug& operator<<(QDebug& f, const Note& n){
    switch(n){
    case Note::A : f<<"A"; break;
    case Note::B: f<<"B"; break;
    case Note::C: f<<"C"; break;
    case Note::D: f<<"D"; break;
    case Note::E: f<<"E"; break;
    case Note::F: f<<"F"; break;
    case Note::FX: f<<"FX"; break;
    case Note::RES: f<<"RES"; break;
    case Note::ABS: f<<"ABS"; break;
    case Note::EC: f<<"EC"; break;
    default: throw EnumException("erreur, Note non traitee");
    }
    return f;
}

QString NoteToString(Note c){
    switch(c){
    case Note::A : return "A";
    case Note::B: return "B";
    case Note::C: return "C";
    case Note::D: return "D";
    case Note::E: return "E";
    case Note::F: return "F";
    case Note::FX: return "FX";
    case Note::RES: return "RES";
    case Note::ABS: return "ABS";
    case Note::EC: return "EC";
    default: throw EnumException("erreur, Note non traitee");
    }
}

Note StringToNote(const QString& str)
{
    if (str=="A") return Note::A;
    else
    if (str=="ABS") return Note::ABS;
    else
    if (str=="B") return Note::B;
    else
    if (str=="C") return Note::C;
    else
    if (str=="D") return Note::D;
    else
    if (str=="E") return Note::E;
    else
    if (str=="FX") return Note::FX;
    else
    if (str=="F") return Note::F;
    else
    if (str=="EC") return Note::EC;
    else
    if (str=="RES") return Note::RES;
    else {
        QString s="erreur, StringToCategorie, categorie "+str+" inexistante";
        throw EnumException(s.toStdString());
    }
}

QString NoteToString(Note c);
