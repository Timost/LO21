#include "enums.h"
#include "Exception.h"

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

//inline QDebug& operator<<(QDebug& f, const Note& n){
//    switch(n){
//    case Note::A : f<<"A"; break;
//    case Note::B: f<<"B"; break;
//    case Note::C: f<<"C"; break;
//    case Note::D: f<<"D"; break;
//    case Note::E: f<<"E"; break;
//    case Note::F: f<<"F"; break;
//    case Note::FX: f<<"FX"; break;
//    case Note::RES: f<<"RES"; break;
//    case Note::ABS: f<<"ABS"; break;
//    case Note::EC: f<<"EC"; break;
//    default: throw EnumException("erreur, Note non traitee");
//    }
//    return f;
//}

//QString NoteToString(Note c){
//    switch(c){
//    case Note::A : return "A";
//    case Note::B: return "B";
//    case Note::C: return "C";
//    case Note::D: return "D";
//    case Note::E: return "E";
//    case Note::F: return "F";
//    case Note::FX: return "FX";
//    case Note::RES: return "RES";
//    case Note::ABS: return "ABS";
//    case Note::EC: return "EC";
//    default: throw EnumException("erreur, Note non traitee");
//    }
//}

//Note StringToNote(const QString& str)
//{
//    if (str=="A") return Note::A;
//    else
//    if (str=="ABS") return Note::ABS;
//    else
//    if (str=="B") return Note::B;
//    else
//    if (str=="C") return Note::C;
//    else
//    if (str=="D") return Note::D;
//    else
//    if (str=="E") return Note::E;
//    else
//    if (str=="FX") return Note::FX;
//    else
//    if (str=="F") return Note::F;
//    else
//    if (str=="EC") return Note::EC;
//    else
//    if (str=="RES") return Note::RES;
//    else {
//        QString s="erreur, StringToCategorie, categorie "+str+" inexistante";
//        throw EnumException(s.toStdString());
//    }
//}

//QString NoteToString(Note c);
