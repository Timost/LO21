#include "Note.h"
#include "templatemanager.h"

Note::Note(std::string n, std::string d, unsigned int r, bool e)
{
   TemplateManager<Note>& tNote=TemplateManager<Note>::getInstance();
   if(!tNote.alreadyExist(n))
    {
       if(tNote.size()>0)
       {
          // qDebug()<<"taille  : "<<tNote.size();
            if((getEliminatoryNotes().size()>0)&&(getBestEliminatoryNote().getRang()<r)&&(!e))
            {
                throw NoteException("Erreur : cette Note doit etre eliminatoire etant donne son rang!");
            }
            if((getNotEliminatoryNotes().size()>0)&&(getWorstNotEliminatoryNote().getRang()>r)&&(e))
            {
                throw NoteException("Erreur : cette Note ne doit pas etre eliminatoire etant donne son rang!");
            }
       }
        note=QString::fromStdString(n);
        description=QString::fromStdString(d);
        rang=r;
        eliminatoire=e;

        tNote.New(*this);
    }
    else
    {
        throw NoteException("Erreur : la note "+n+" existe deja !");
    }
}
Note::Note(QString n, QString d, unsigned int r, bool e)
{
    Note(n.toStdString(),d.toStdString(),r,e);
}
Note::Note(const char* n, const char *d, unsigned int r, bool e)
{
    Note(std::string(n),std::string(d),r,e);
}

void Note::setRang(unsigned int r)
{
    TemplateManager<Note>& tNote=TemplateManager<Note>::getInstance();
    if(tNote.size()>1)
    {
       // qDebug()<<"taille  : "<<tNote.size();
         if((getEliminatoryNotes().size()>0)&&(getBestEliminatoryNote().getRang()<r)&&(!isEliminatory()))
         {//le nouveau rang la rend éliminatoire
            rang=r;
            eliminatoire=true;
         }
         if((getNotEliminatoryNotes().size()>0)&&(getWorstNotEliminatoryNote().getRang()>r)&&(isEliminatory()))
         { //le nouveau rang la rend non éliminatoire
             rang=r;
             eliminatoire=false;
         }
    }
}

Note getBestNote(std::vector<Note>::iterator begin,std::vector<Note>::iterator end)
{
    if(begin==end)
    {
        throw NoteException("Erreur getBestNote() les itérateurs sont egaux, vous iterez probablement sur un tableau vide");
    }
    Note max = *begin;
    begin++;
    for(std::vector<Note>::iterator itNote=begin;itNote != end;itNote++)
    {
        if(itNote->getRang()<max.getRang())
        {
            max=*itNote;
        }
    }
    return max;
}
Note getWorstNote(std::vector<Note>::iterator begin,std::vector<Note>::iterator end)
{
    if(begin==end)
    {
        throw NoteException("Erreur getBestNote() les itérateurs sont egaux, vous iterez probablement sur un tableau vide");
    }
    Note min = *begin;
    begin++;
    for(std::vector<Note>::iterator itNote=begin;itNote != end;itNote++)
    {
        if(itNote->getRang()>min.getRang())
        {
            min=*itNote;
        }
    }
    return min;
}

Note getBestNote()
{
    TemplateManager<Note>& tNote=TemplateManager<Note>::getInstance();
    std::vector<Note>::iterator begin =tNote.getIterator();
    std::vector<Note>::iterator end =tNote.end();
    return getBestNote(begin,end);
}
Note getWorstNote()
{
    TemplateManager<Note>& tNote=TemplateManager<Note>::getInstance();
    std::vector<Note>::iterator begin =tNote.getIterator();
    std::vector<Note>::iterator end =tNote.end();
    return getWorstNote(begin,end);
}

Note getBestEliminatoryNote()
{
    std::vector<Note> eliminatory=getEliminatoryNotes();

    return getBestNote(eliminatory.begin(),eliminatory.end());
}

Note getWorstNotEliminatoryNote()
{
    std::vector<Note> eliminatory=getNotEliminatoryNotes();

    return getBestNote(eliminatory.begin(),eliminatory.end());
}

std::vector<Note> getEliminatoryNotes()
{
    std::vector<Note> res;
    TemplateManager<Note>& tNote=TemplateManager<Note>::getInstance();
    for(std::vector<Note>::iterator itNote=tNote.getIterator();itNote != tNote.end();itNote++)
    {
        if(itNote->isEliminatory())
        {
            res.push_back(*itNote);
        }
    }
    return res;
}

std::vector<Note> getNotEliminatoryNotes()
{
    std::vector<Note> res;
    TemplateManager<Note>& tNote=TemplateManager<Note>::getInstance();
    for(std::vector<Note>::iterator itNote=tNote.getIterator();itNote != tNote.end();itNote++)
    {
        if(!itNote->isEliminatory())
        {
            res.push_back(*itNote);
        }
    }
    return res;
}

Note StringToNote(const QString& str){//renvoie une référence vers la catégorie si elle existe, exception sinon.
   TemplateManager<Note>& tNote=TemplateManager<Note>::getInstance();

   if(tNote.alreadyExist(str))
   {
       return tNote.getElement(str);
   }
   else
   {
       throw NoteException("Erreur la note "+str.toStdString()+" n'existe pas.");
   }
}


bool operator<(const Note n1,const Note n2)
{
    return n1.getRang()<n2.getRang();
}
bool operator>(const Note n1, const Note n2)
{
    return n1.getRang()>n2.getRang();
}
bool operator<=(const Note n1, const Note n2)
{
    return !(n1>n2);
}
bool operator>=(const Note n1, const Note n2)
{
    return !(n1<n2);
}
bool operator==(const Note n1, const Note n2)
{
    return (n1.getRang()==n2.getRang());
}
bool operator!=(const Note n1, const Note n2)
{
    return !(n1==n2);
}
