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

    /**
     * @brief isValidatory
     * @return retourne vrai si la note n'est pas eliminatoire
     */
    bool isValidatory()const{return (eliminatoire==0);}

    /**
     * @brief setNote setter sur note
     * @param n
     */
    void setNote(QString n){note = n;}
    /**
     * @brief setNote setter sur note
     * @param n
     */
    void setNote(std::string n){setNote(QString::fromStdString(n));}
    /**
     * @brief setNote setter sur note
     * @param n
     */
    void setNote(const char* n){setNote(std::string(n));}

    /**
     * @brief setDescription setter sur description
     * @param d
     */
    void setDescription(QString d){description = d;}

    /**
     * @brief setDescription setter sur description
     * @param d
     */
    void setDescription(std::string d){setDescription(QString::fromStdString(d));}

    /**
     * @brief setDescription setter sur description
     * @param d
     */
    void setDescription(const char* d){setDescription(std::string(d));}

    /**
     * @brief setRang setter sur rang
     * @param r
     */
    void setRang(unsigned int r);

};

/**
 * @brief StringToNote convert string en Note
 * @param str
 * @return
 */
Note StringToNote(const QString& str);

/**
 * @brief getBestNote
 * @return retourne la meilleur Note
 */
Note getBestNote();

/**
 * @brief getWorstNote
 * @return retourne la pire Note
 */
Note getWorstNote();

/**
 * @brief getBestNote
 * @param begin
 * @param end
 * @return
 */

/**
 * @brief getBestNote
 * @param begin
 * @param end
 * @return retourne la meilleur note entre begin et end
 */
Note getBestNote(std::vector<Note>::iterator begin,std::vector<Note>::iterator end);

/**
 * @brief getWorstNote
 * @param begin
 * @param end
 * @return retourne la pire note entre begin et end
 */
Note getWorstNote(std::vector<Note>::iterator begin,std::vector<Note>::iterator end);

/**
 * @brief getBestEliminatoryNote
 * @return retourne la meilleur Note éliminatoire
 */
Note getBestEliminatoryNote();

/**
 * @brief getWorstValidatoryNote
 * @return  * @return retourne la pire Note qui valide l'UV.
 */
Note getWorstValidatoryNote();

/**
 * @brief getBestEliminatoryNote
 * @param begin
 * @param end
 * @return retourne la meilleur note eliminatoire entre begin et end
 */
Note getBestEliminatoryNote(std::vector<Note>::iterator begin,std::vector<Note>::iterator end);

/**
 * @brief getWorstValidatoryNote
 * @param begin
 * @param end
 * @return retourne la pire note qui valide l'UV entre begin et end
 */
Note getWorstValidatoryNote(std::vector<Note>::iterator begin,std::vector<Note>::iterator end);

/**
 * @brief getValidatoryNotes
 * @return retourne les notes qui valide les UV.
 */
std::vector<Note> getValidatoryNotes();

/**
 * @brief getValidatoryNotes
 * @param begin
 * @param end
 * @return retourne les notes qui valide les UV entrebegin et end.
 */
std::vector<Note> getValidatoryNotes(std::vector<Note>::iterator begin,std::vector<Note>::iterator end);

/**
 * @brief getEliminatoryNotes
 * @return retourne les notes éliminatoires.
 */
std::vector<Note> getEliminatoryNotes();

/**
 * @brief getEliminatoryNotes
 * @param begin
 * @param end
 * @return retourne les notes qui éliminatoires entre begin et end.
 */
std::vector<Note> getEliminatoryNotes(std::vector<Note>::iterator begin,std::vector<Note>::iterator end);

/**
 * @brief getDeterminantNotes
 * @return Ensemble des notes qui permettent de déterminer si un étudiant a obtenu l'UV.
 */
std::vector<Note> getDeterminantNotes();

/**
 * @brief getDeterminantNotes
 * @param begin
 * @param end
 *@return Ensemble des notes qui permettent de déterminer si un étudiant a obtenu l'UV. Entre deux iterateurs.
 */
std::vector<Note> getDeterminantNotes(std::vector<Note>::iterator begin,std::vector<Note>::iterator end);

/**
 * @brief getNonDeterminantNotes
 * @return Ensemble des notes qui ne permettent pas de déterminer si un étudiant a obtenu l'UV.
 */
std::vector<Note> getNonDeterminantNotes();

/**
 * @brief getNonDeterminantNotes
 * @param begin
 * @param end
 * @return Ensemble des notes qui ne permettent pas de déterminer si un étudiant a obtenu l'UV. Entre deux iterateurs.
 */
std::vector<Note> getNonDeterminantNotes(std::vector<Note>::iterator begin,std::vector<Note>::iterator end);

/**
 * @brief operator <
 * @param n1
 * @param n2
 * @return
 */
bool operator<(const Note n1, const Note n2);

/**
 * @brief operator >
 * @param n1
 * @param n2
 * @return
 */
bool operator>(const Note n1, const Note n2);

/**
 * @brief operator ==
 * @param n1
 * @param n2
 * @return
 */
bool operator==(const Note n1, const Note n2);

/**
 * @brief operator <=
 * @param n1
 * @param n2
 * @return
 */
bool operator<=(const Note n1, const Note n2);

/**
 * @brief operator >=
 * @param n1
 * @param n2
 * @return
 */
bool operator>=(const Note n1, const Note n2);

/**
 * @brief operator !=
 * @param n1
 * @param n2
 * @return
 */
bool operator!=(const Note n1, const Note n2);
#endif // NOTE_H
