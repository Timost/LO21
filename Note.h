#ifndef NOTE_H
#define NOTE_H

#include <QString>
#include <string>
#include <QDebug>
#include <vector>
#include "EntityStd.h"

/**
* @file note.h
* @version 1
* @brief Ce fichier est le header de la classe note.
**/

/**
 * @brief NoteException class exception sur les notes.
 */
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

/**
 * @brief Note class permet de stocker une note sont rang et si elle est eliminatoire.
 */
class Note : public EntityStd
{
private :
    /*
     * @brief note
     */
    QString note;

    /**
     * @brief description
     */
    QString description;

    /**
     * @brief rang plus il est faible plus la note est bonne
     */
    unsigned int rang;
    /**
     * @brief eliminatoire 0 pas éliminatoire, 1 éliminatoire, 2 en attente
     */
    unsigned int eliminatoire;
public :
    /**
     * @brief getStrLabel
     * @return retourne la note
     */
    std::string getStrLabel() const
    {
        return note.toStdString();
    }

    /**
     * @brief Note
     * @param n note
     * @param d description
     * @param r rang
     * @param e eliminatoire
     */
    Note(std::string n, std::string d, unsigned int r, unsigned int e);

    /**
     * @brief Note
     * @param n note
     * @param d description
     * @param r rang
     * @param e eliminatoire
     */
    Note(QString n,QString d, unsigned int r, unsigned int e);

    /**
     * @brief Note
     * @param n note
     * @param d description
     * @param r rang
     * @param e eliminatoire
     */
    Note(const char* c, const char*d, unsigned int r, unsigned int e);

    /**
     * @brief getNote getter sur note
     * @return
     */
    QString getNote() const {return note;}

    /**
     * @brief getNoteStdString getter sur note
     * @return
     */
    std::string getNoteStdString() const {return note.toStdString();}

    /**
     * @brief getDescription getter sur description
     * @return
     */
    QString getDescription() const {return description;}

    /**
     * @brief getDescription getter sur description
     * @return
     */
    std::string getDescriptionStdString() const {return description.toStdString();}

    /**
     * @brief getRang getter sur rang
     * @return
     */
    unsigned int getRang()const{return rang;}

    /**
     * @brief getEliminatoire getter sur eliminatoire
     * @return
     */
    unsigned int getEliminatoire()const{return eliminatoire;}

    /**
     * @brief isEliminatory
     * @return retourne vrai si la note est eliminatoire
     */
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
