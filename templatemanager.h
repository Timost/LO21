//TEMPLATEMANAGER doivent utiliser des T qui sont sous le principe de TemplateStd. (Je pense que l'on pourra améliorer pas mal le système via un héritage.
#ifndef TEMPLATEMANAGER_H
#define TEMPLATEMANAGER_H
#include <vector>
#include <iterator>
#include <string>
#include <QDebug>

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

    typename vector<T>::const_iterator end() const
    {
        return elements.end();
    }

    void New(T element)
    {
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
            if(s==elements[i].getStrLabel()) break;
            n++;
        }
        if(n==nb)
            throw TemplateManagerException<T>("Valeur introuvable.");
        else
        {
            return elements[n];
        }
    }

    bool alreadyExist(std::string s)
    {
        int nb=this->size();
        if (nb==0)
            return false;
        unsigned int n=0;
        for(unsigned int i=0;i<nb; i++)
        {
            if(s==elements[i].getStrLabel()) break;
            n++;
        }
        if(n==nb-1 && s!=elements[n].getStrLabel())
            return false;
        else
            return true;
    }

    unsigned int size() const
    {
        return elements.size();
    }

    void clear()
    {
        elements.clear();
    }
};

#endif // TEMPLATEMANAGER_H
