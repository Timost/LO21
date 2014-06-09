//TEMPLATEMANAGER doivent utiliser des T qui sont sous le principe de TemplateStd. (Je pense que l'on pourra améliorer pas mal le système via un héritage.
#ifndef TEMPLATEMANAGER_H
#define TEMPLATEMANAGER_H
#include <vector>
#include <iterator>
#include <string>
#include <QDebug>
#include <QString>
using namespace std;

template <class T>
class TemplateManagerException : public exception
{
protected :
    string info;
public:
    TemplateManagerException<T>(const string& i="") throw() :info(i) {}
    const char* what() const throw()
    {
        return info.c_str();
    }
    ~TemplateManagerException<T>()throw() {}
};



template <class T>
class TemplateManager
{
vector<T> elements;
static TemplateManager<T>* handler;

    ~TemplateManager<T>()
    {
        elements.clear();
    }

    TemplateManager<T>()
    {
    }

public:
    static TemplateManager<T>& getInstance()
    {
        if (handler==0) handler = new TemplateManager<T>();
        return *handler;
    }

    void destroyInstance()
    {
        delete handler;
    }

    typename vector<T>::iterator getIterator()
    {
        return elements.begin();
    }

    typename vector<T>::const_iterator getIterator() const
    {
        return elements.begin();
    }

    typename vector<T>::iterator end()
    {
        return elements.end();
    }


    typename vector<T>::const_iterator end() const
    {
        return elements.end();
    }

    void New(T element)
    {//on ne peut pas ajouter un élément ayant le même label qu'un autre dans le manager
     //Néenmoins les tests sont à faire dans les constructeurs des objets
        elements.push_back(element);
    }

    T& getElement(std::string s)
    {

        unsigned int nb=this->size();
        if (nb==0)
            throw TemplateManagerException<T>("Pas d'elements dans le manager.");
        unsigned int n=0;
        for(unsigned int i=0;i<nb; i++)
        {
            //qDebug()<<QString::fromStdString(s)<<"="<<QString::fromStdString(elements[i].getStrLabel())<<" : "<<(s==elements[i].getStrLabel());
            if(s==elements[i].getStrLabel())
            {
                n++;
                break;
            }
            else
            {
                n++;
            }
        }
        if(n==nb && s!=elements[n-1].getStrLabel())
        {
            throw TemplateManagerException<T>("Erreur getElement : Valeur introuvable.");
        }
        else
        {
            return elements[n-1];
        }
    }
    T& getElement(const char* s)
    {
        return getElement(std::string(s));
    }

    T& getElement(const QString& s)
    {
        return getElement(s.toStdString());
    }

    bool alreadyExist(std::string s)
    {
        int nb=this->size();
        if (nb==0)
            return false;
        unsigned int n=0;
        for(unsigned int i=0;i<nb; i++)
        {
            if(s==elements[i].getStrLabel())
            {
                n++;
                break;
            }
            else
            {
                n++;
            }
        }

        if(n==nb && s!=elements[n-1].getStrLabel())
            return false;
        else
            return true;
    }

    bool alreadyExist(QString s)
    {
        return alreadyExist(s.toStdString());
    }

    bool alreadyExist(const char* s)
    {
        return alreadyExist(std::string(s));
    }

    unsigned int size() const
    {
        return elements.size();
    }

    void clear()
    {
        elements.clear();
    }

    void erase(int i)
    {
        elements.erase(elements.begin()+i);
    }

    void erase(T e)
    {
        typename std::vector<T>::iterator it = find(getIterator(),end(),e);
        if(it==end())
        {
            throw TemplateManagerException<T>("Erreur erase(T e) : l'élément "+e.getStrLabel()+" n'est pas dans le manager");
        }
        else
        {
            elements.erase(it);
        }
    }

};

#endif // TEMPLATEMANAGER_H
