#ifndef TEMPLATESTD_H
#define TEMPLATESTD_H
#include <string>
#include <sstream>
#include <iostream>
/**
* @file EntityStd.h
* @version 1
* @brief Ce fichier est le header de la classe EntityStd.
**/


/**
 * @brief EntityStd class pour que les fonction du TemplateManager fonctionne bien il faut que les classes qu'il utilise hérite de cette dernière. C'est une classe abstraite.
 */
class EntityStd
{
public:
    /**
     * @brief EntityStd constructeur vide car classe abstraite
     */
    EntityStd(){}

    /**
     * @brief ~EntityStd Destructeur virtuel
     */
    virtual ~EntityStd(){}

    /**
     * @brief getStrLabel Fonction virtuel pure pour forcer l'utilisateur à la définir.
     * @return std::string
     */
    virtual std::string getStrLabel() const =0;
};

#endif // TEMPLATESTD_H
