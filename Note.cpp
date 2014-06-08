#include "Note.h"
#include "templatemanager.h"

Note::Note(std::string n, std::string d, unsigned int r, unsigned int e)
{
    if(e>2)
    {
        throw NoteException("Erreur : le dernier parametres doit etre compris entre 0 et 2 inclus :(0:pas eliminatoire,1 eliminatoire, 2 non determinante)");
    }
   TemplateManager<Note>& tNote=TemplateManager<Note>::getInstance();
   if(!tNote.alreadyExist(n))
    {
       if(tNote.size()>0)
       {
          // qDebug()<<"taille  : "<<tNote.size();
            if((getEliminatoryNotes().size()>0)&&(getBestEliminatoryNote().getRang()<r)&&(e!=1))
            {
                throw NoteException("Erreur : cette Note "+n+" doit etre eliminatoire etant donne son rang!");
            }
            if((getValidatoryNotes().size()>0)&&(getWorstValidatoryNote().getRang()>r)&&(e==1))
            {
                throw NoteException("Erreur : cette Note "+n+" ne doit pas etre eliminatoire etant donne son rang!");
            }
            if((e==2)&&(r!=0))
            {
                throw NoteException("Erreur : Une note non determinante doit etre de rang 0!("+n+")");
            }
            if((e!=2)&&(r==0))
            {
                throw NoteException("Erreur : Une note determinante doit etre de rang > 0!("+n+")");
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
Note::Note(QString n, QString d, unsigned int r, unsigned int e)
{
    Note(n.toStdString(),d.toStdString(),r,e);
}
Note::Note(const char* n, const char *d, unsigned int r, unsigned int e)
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
            eliminatoire=1;
         }
         if((getValidatoryNotes().size()>0)&&(getWorstValidatoryNote().getRang()>r)&&(isEliminatory()))
         { //le nouveau rang la rend non éliminatoire

             rang=r;
             if(r==0)
             {
                  eliminatoire=2;//rang 0 implique non déterminante
             }
             else
             {
                 eliminatoire=0;
             }

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
    bool foundDeterminantNote=false;//les notes non déterminantes ne comptes pas.
    for(std::vector<Note>::iterator itNote=begin;itNote != end;itNote++)
    {
        if((!foundDeterminantNote)&&(itNote->getRang()>0))
        {
            foundDeterminantNote=true;
            min=*itNote;
        }
        if((foundDeterminantNote)&&(itNote->getRang()>min.getRang()))
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
    TemplateManager<Note>& tNote=TemplateManager<Note>::getInstance();
    std::vector<Note>::iterator begin =tNote.getIterator();
    std::vector<Note>::iterator end =tNote.end();
    return getBestEliminatoryNote(begin,end);
}

Note getWorstValidatoryNote()
{
    TemplateManager<Note>& tNote=TemplateManager<Note>::getInstance();
    std::vector<Note>::iterator begin =tNote.getIterator();
    std::vector<Note>::iterator end =tNote.end();
    return getWorstValidatoryNote(begin,end);
}

Note getBestEliminatoryNote(std::vector<Note>::iterator begin,std::vector<Note>::iterator end)
{
    std::vector<Note> test=getEliminatoryNotes(begin,end);
    if(test.size()==0)
    {
        throw NoteException("Erreur getBestEliminatoryNote(...,...), il n'y a pas de notes eliminatoires dans ce tableau");
    }
    return getBestNote(begin,end);
}

Note getWorstValidatoryNote(std::vector<Note>::iterator begin,std::vector<Note>::iterator end)
{
    std::vector<Note> test=getValidatoryNotes(begin,end);
    if(test.size()==0)
    {
        throw NoteException("Erreur getWorstValidatoryNote(...,...), il n'y a pas de notes validantes dans ce tableau");
    }
    return getWorstNote(begin,end);
}

std::vector<Note> getEliminatoryNotes()
{
    TemplateManager<Note>& tNote=TemplateManager<Note>::getInstance();
    std::vector<Note>::iterator begin =tNote.getIterator();
    std::vector<Note>::iterator end =tNote.end();
    return getEliminatoryNotes(begin,end);
}

std::vector<Note> getEliminatoryNotes(std::vector<Note>::iterator begin,std::vector<Note>::iterator end)
{
    std::vector<Note> res;
    for(std::vector<Note>::iterator itNote=begin;itNote !=end;itNote++)
    {
        if(itNote->isEliminatory())
        {
            res.push_back(*itNote);
        }
    }
    return res;
}

std::vector<Note> getValidatoryNotes()
{
    TemplateManager<Note>& tNote=TemplateManager<Note>::getInstance();
    std::vector<Note>::iterator begin =tNote.getIterator();
    std::vector<Note>::iterator end =tNote.end();
    return getValidatoryNotes(begin,end);
}

std::vector<Note> getValidatoryNotes(std::vector<Note>::iterator begin,std::vector<Note>::iterator end)
{
    std::vector<Note> res;
    for(std::vector<Note>::iterator itNote=begin;itNote !=end;itNote++)
    {
        if(itNote->isValidatory())
        {
            res.push_back(*itNote);
        }
    }
    return res;
}
std::vector<Note> getDeterminantNotes()
{
    TemplateManager<Note>& tNote=TemplateManager<Note>::getInstance();
    std::vector<Note>::iterator begin =tNote.getIterator();
    std::vector<Note>::iterator end =tNote.end();
    return getDeterminantNotes(begin,end);
}
std::vector<Note> getDeterminantNotes(std::vector<Note>::iterator begin,std::vector<Note>::iterator end)
{
    std::vector<Note> res;
    for(std::vector<Note>::iterator itNote=begin;itNote != end;itNote++)
    {
        if((itNote->isValidatory())||(itNote->isEliminatory()))
        {
            res.push_back(*itNote);
        }
    }
    return res;
}

std::vector<Note> getNonDeterminantNotes()
{
    TemplateManager<Note>& tNote=TemplateManager<Note>::getInstance();
    std::vector<Note>::iterator begin =tNote.getIterator();
    std::vector<Note>::iterator end =tNote.end();
    return getNonDeterminantNotes(begin,end);
}

std::vector<Note> getNonDeterminantNotes(std::vector<Note>::iterator begin,std::vector<Note>::iterator end)
{
    std::vector<Note> res;

    for(std::vector<Note>::iterator itNote=begin;itNote != end;itNote++)
    {
        if((!itNote->isValidatory())&&(!itNote->isEliminatory()))
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
