#ifndef ENUMS_H
#define ENUMS_H

#include <QString>
#include <QTextStream>
#include <type_traits>

enum class Categorie {
    /* Connaissances Scientifiques */ CS,  /* Techniques et Méthodes */ TM,
    /* Technologies et Sciences de l'Homme */ TSH, /* Stage et Projet */ SP,
    first=CS, last=SP
};

QTextStream& operator<<(QTextStream& f, const Categorie& s);

Categorie StringToCategorie(const QString& s);
QString CategorieToString(Categorie c);
QTextStream& operator>>(QTextStream& f, Categorie& cat);

enum class Note { A, B, C, D, E, F, FX, RES, ABS, /* en cours */ EC, first=A, last=EC  };

enum class Saison { Automne, Printemps, first=Automne, last=Printemps };
inline QTextStream& operator<<(QTextStream& f, const Saison& s) { if (s==Saison::Automne) f<<"A"; else f<<"P"; return f;}

template<typename EnumType>
class EnumIterator {
    static_assert(std::is_enum<EnumType>::value, "EnumType has to be an enum");
    EnumType value;
    EnumIterator(EnumType val):value(val){}
public:
    static EnumIterator getFirst() { return EnumIterator(EnumType::first); }
    bool isDone() const { return value>EnumType::last; }
    EnumType operator*() const { return value; }
    void next() { value=(EnumType)(std::underlying_type<EnumType>::type(value)+1); }
};

typedef EnumIterator<Note> NoteIterator;
typedef EnumIterator<Categorie> CategorieIterator;
typedef EnumIterator<Saison> SaisonIterator;


#endif // ENUMS_H
