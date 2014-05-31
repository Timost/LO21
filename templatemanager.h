//TEMPLATEMANAGER doivent utiliser des T qui sont sous le principe de TemplateStd. (Je pense que l'on pourra améliorer pas mal le système via un héritage.
#ifndef TEMPLATEMANAGER_H
#define TEMPLATEMANAGER_H
#include <vector>
#include <iterator>
#include <string>

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

    void New(T element)
    {
        elements.push_back(element);
    }

    T& getElement(std::string s)
    {
        typename vector<T>::iterator it=getIterator();
        int nb=size();
        if (nb==0)
            throw TemplateManagerException<T>("Pas d'elements dans le manager.");
        int i;
        for(i=0; s!=it[i].getStrLabel() && i<nb; i++);
        if(i!=0 && s!=it[i].getStrLabel())
            throw TemplateManagerException<T>("Valeur introuvable.");
        else
            return it[i];
    }

    bool alreadyExist(std::string s)
    {
        typename vector<T>::iterator it=getIterator();
        int nb=size();
        if (nb==0)
            throw TemplateManagerException<T>("Pas d'elements dans le manager.");
        int i;
        for(i=0; s!=it[i].getStrLabel() && i<nb; i++);
        if(i!=0 && s!=it[i].getStrLabel())
            return false;
        else
            return true;
    }

    const int size() const
    {
        return distance(elements.begin(), elements.end());
    }
};

#endif // TEMPLATEMANAGER_H
