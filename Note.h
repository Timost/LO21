#ifndef NOTE_H
#define NOTE_H

#include <QString>
#include <string>
#include <QDebug>
#include <vector>
#include "EntityStd.h"

//enum class Note { A, B, C, D, E, F, FX, RES, ABS, /* en cours */ EC, first=A, last=EC  };
//Note StringToNote(const QString& s);
//QString NoteToString(Note c);

class NoteException : public std::exception
{
protected :
    std::string info;
public:
    NoteException(const std::string& i="") throw() :info(i) {}
    const char* what() const throw()
    {
        return info.c_str();
    }
    ~NoteException()throw() {}
};

class Note : public EntityStd
{
private :
    QString note;
    QString description;
    unsigned int rang; //permet d'implémenter la relation d'ordre entre les notes
    unsigned int eliminatoire;//0 pas éliminatoire, 1 éliminatoire, 2 en attente
public :
    std::string getStrLabel() const
    {
        return note.toStdString();
    }

    Note(std::string n, std::string d, unsigned int r, unsigned int e);
    Note(QString n,QString d, unsigned int r, unsigned int e);
    Note(const char* c, const char*d, unsigned int r, unsigned int e);

    QString getNote() const {return note;}
    std::string getNoteStdString() const {return note.toStdString();}

    QString getDescription() const {return description;}
    std::string getDescriptionStdString() const {return description.toStdString();}

    unsigned int getRang()const{return rang;}
    unsigned int getEliminatoire()const{return eliminatoire;}

    bool isEliminatory()const{return (eliminatoire==1);}
    bool isValidatory()const{return (eliminatoire==0);}

    void setNote(QString n){note = n;}
    void setNote(std::string n){setNote(QString::fromStdString(n));}
    void setNote(const char* n){setNote(std::string(n));}

    void setDescription(QString d){description = d;}
    void setDescription(std::string d){setDescription(QString::fromStdString(d));}
    void setDescription(const char* d){setDescription(std::string(d));}

    void setRang(unsigned int r);


};
Note StringToNote(const QString& str);
Note getBestNote();
Note getWorstNote();
Note getBestNote(std::vector<Note>::iterator begin,std::vector<Note>::iterator end);
Note getWorstNote(std::vector<Note>::iterator begin,std::vector<Note>::iterator end);
Note getBestEliminatoryNote();//retourne la "meilleure" note éliminatoire
Note getWorstValidatoryNote();
Note getBestEliminatoryNote(std::vector<Note>::iterator begin,std::vector<Note>::iterator end);
Note getWorstValidatoryNote(std::vector<Note>::iterator begin,std::vector<Note>::iterator end);
std::vector<Note> getValidatoryNotes();
std::vector<Note> getValidatoryNotes(std::vector<Note>::iterator begin,std::vector<Note>::iterator end);
std::vector<Note> getEliminatoryNotes();//retourne un vecteur contenant les notes éliminatoires
std::vector<Note> getEliminatoryNotes(std::vector<Note>::iterator begin,std::vector<Note>::iterator end);
std::vector<Note> getDeterminantNotes();
std::vector<Note> getDeterminantNotes(std::vector<Note>::iterator begin,std::vector<Note>::iterator end);
std::vector<Note> getNonDeterminantNotes();
std::vector<Note> getNonDeterminantNotes(std::vector<Note>::iterator begin,std::vector<Note>::iterator end);
bool operator<(const Note n1, const Note n2);
bool operator>(const Note n1, const Note n2);
bool operator==(const Note n1, const Note n2);
bool operator<=(const Note n1, const Note n2);
bool operator>=(const Note n1, const Note n2);
bool operator!=(const Note n1, const Note n2);
#endif // NOTE_H
