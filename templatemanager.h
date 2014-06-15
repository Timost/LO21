//TEMPLATEMANAGER doivent utiliser des T qui sont sous le principe de TemplateStd. (Je pense que l'on pourra améliorer pas mal le système via un héritage.
#ifndef TEMPLATEMANAGER_H
#define TEMPLATEMANAGER_H
#include <vector>
#include <iterator>
#include <string>
#include <QDebug>
#include <QString>
using namespace std;
/**
* @file templatemanager.h
* @version 1
* @brief Ce fichier est le header de la classe templatemanager.
**/

/**
 * @brief la class T doit être du type EntityStd pour que TemplateManager fonctionne.
 */
template <class T>
/**
 * @brief TemplateManagerException class gère les exceptions
 */
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


/**
 * @brief la class T doit être du type EntityStd pour que TemplateManager fonctionne.
 */
template <class T>
/**
 * @brief TemplateManager class est singleton. Il fonctionne pour toutes les entité de notre programme tant qu'elles hérite de entityStd.
 */
class TemplateManager
{
     /**
     * @brief elements vecteur stockant tous les éléments
     */
    vector<T> elements;

    /**
     * @brief handler adresse du manager
     */
    static TemplateManager<T>* handler;

    /**
    * @brief Destructeur privé détrusant tous les éléments.
    */
    ~TemplateManager<T>()
    {
        elements.clear();
    }

    /**
     * @brief TemplateManager<T> constructeur privé
     */
    TemplateManager<T>()
    {
    }

public:

    /**
     * @brief getInstance
     * @return retourn l'adresse du manager.
     */
    static TemplateManager<T>& getInstance()
    {
        if (handler==0) handler = new TemplateManager<T>();
        return *handler;
    }

    /**
     * @brief destroyInstance détruit le manager
     */
    void destroyInstance()
    {
        delete handler;
    }

    /**
     * @brief getIterator
     * @return retourne un itérateur sur le premier élément du manager.
     */
    typename vector<T>::iterator getIterator()
    {
        return elements.begin();
    }

    /**
     * @brief getIterator
     * @return retourne un const_itérateur sur le premier élément du manager.
     */
    typename vector<T>::const_iterator getIterator() const
    {
        return elements.begin();
    }

    /**
     * @brief end
     * @return retourne un itérateur sur le dernier élément du manager
     */
    typename vector<T>::iterator end()
    {
        return elements.end();
    }


    /**
     * @brief end
     * @return retourne un const_itérateur sur le dernier élément du manager
     */
    typename vector<T>::const_iterator end() const
    {
        return elements.end();
    }

    /**
     * @brief New Crée un nouvel élément. \n
     *          on ne peut pas ajouter un élément ayant le même label qu'un autre dans le manager.\n
     * @param element
     */
    void New(T element)
    {
        elements.push_back(element);
    }

    /**
     * @brief getElement
     * @param s
     * @return retourne l'element qui a pour label s
     */
    T& getElement(std::string s)
    {

        unsigned int nb=this->size();
        if (nb==0)
            throw TemplateManagerException<T>("getElement : "+ s +"Pas d'elements dans le manager.");
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
        {
            throw TemplateManagerException<T>("Erreur getElement : Valeur introuvable. "+s);
        }
        else
        {
            return elements[n-1];
        }
    }

    /**
     * @brief getElement
     * @param s
     * @return
     */
    T& getElement(const char* s)
    {
        return getElement(std::string(s));
    }

    /**
     * @brief getElement
     * @param s
     * @return retourne l'element qui a pour label s
     */
    T& getElement(const QString& s)
    {
        return getElement(s.toStdString());
    }

    /**
     * @brief alreadyExist
     * @param s
     * @return retourne vrai si s existe déjà dans le manager
     */
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

    /**
     * @brief alreadyExist
     * @param s
     * @return retourne vrai si s existe déjà dans le manager
     */
    bool alreadyExist(QString s)
    {
        return alreadyExist(s.toStdString());
    }

    /**
     * @brief alreadyExist
     * @param s
     * @return retourne vrai si s existe déjà dans le manager
     */
    bool alreadyExist(const char* s)
    {
        return alreadyExist(std::string(s));
    }

    /**
     * @brief size
     * @return retourne le nombre d'element du manager
     */
    unsigned int size() const
    {
        return elements.size();
    }

    /**
     * @brief clear vide les elements!!! Detruit tous les elements du manager !!!
     */
    void clear()
    {
        elements.clear();
    }

    /**
     * @brief erase detruit l'element à l'index i du manager
     * @param i
     */
    void erase(int i)
    {
        elements.erase(elements.begin()+i);
    }

    /**
     * @brief erase detruit l'element e du manager
     * @param e
     */
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
