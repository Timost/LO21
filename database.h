#ifndef DATABASE_H
#define DATABASE_H
#include <QCoreApplication>
#include <QtSql>
#include <QString>
#include <string>
#include <iostream>
#include <QDebug>
#include "templatemanager.h"
#include "Formation.h"
#include "Etudiant.h"
#include "uv.h"
#include "Categorie.h"
#include "Note.h"
#include "Saison.h"
#define q2c(string) string.toStdString()

/**
* @file Categorie.h
* @version 1
* @brief Ce fichier est le header de la classe database.
**/


using namespace std;

/**
 * @brief Database class gère tous les échanges avec la base de données.
 */
class Database
{
    /**
     * @brief db base de données
     */
    QSqlDatabase db;
    /**
     * @brief databaseName Chemin vers la base de données à laquelle on souhaite accéder.
     */
    string databaseName;

    /**
     * @brief open ouvre la connection à la base de donnée.
     * @return booleen vrai si cel a fonctionné.
     */
    bool open()
    {
        return this->db.open();
    }

    /**
     * @brief close ferme la connection à la db.
     */
    void close()
    {
        db.close();
    }
public:
    /**
     * @brief query effectue une requete vers la bdd.
     * @param q requete
     * @return resultat de la requete
     */
    QSqlQuery query(string q);

    /**
     * @brief Database Constructeur de la classe
     * @param path chemin vers la bdd sera stocké dans databasename
     * @param dbname type de base de données. par défaut SQLITE
     */
    Database(string path, string dbname="QSQLITE");

    /**
    * @brief détruit la base en fermant la connection.
    *
    */
    ~Database(){db.close();}

    /**
     * @brief The SaverLoader class Classe imbriqué à database gère toutes les sauvegardes et chargement de la base de données.
     */
    class SaverLoader //gere sauvegarde et chargement de la bdd
    {
        //on recupere tous les manager
        /**
         * @brief tUV tFormation tEtudiant tCategorie tNote tSaison tSemestre
         *        manager sur les différents élément à sauvegarder.
         */
        TemplateManager<UV>& tUV=TemplateManager<UV>::getInstance();
        TemplateManager<Formation>& tFormation=TemplateManager<Formation>::getInstance();
        TemplateManager<Etudiant>& tEtudiant=TemplateManager<Etudiant>::getInstance();
        TemplateManager<Categorie>& tCategorie=TemplateManager<Categorie>::getInstance();
        TemplateManager<Note>& tNote=TemplateManager<Note>::getInstance();
        TemplateManager<Saison>& tSaison=TemplateManager<Saison>::getInstance();
        TemplateManager<Semestre>& tSemestre=TemplateManager<Semestre>::getInstance();
        Database& db;

        /**
         * @brief init initialise une base de données propre avec toutes les tables nécessaires.
         */
        void init();

    public:
        /**
         * @brief SaverLoader constructeur
         * @param database
         */
        SaverLoader(Database& database):db(database){}
        /**
         * @brief save enregistre toutes les entités des managers dans une base de données.
         */
        void save();
        /**
         * @brief load charge toutes les entités dans les managers respectifs.
         */
        void load();
    };

    /**
     * @brief save appelle le save du saverLoader
     */
    void save()
    {
        SaverLoader(*this).save();
    }

    /**
     * @brief load appelle le load du saver loader.
     */
    void load()
    {
        SaverLoader(*this).load();
    }
};

/**
 * @brief DatabaseException class permet d'envoyer des exceptions de la base de données.
 */
class DatabaseException : public std::exception
{
protected :
    std::string info;
public:
    DatabaseException(const std::string& i="") throw() :info(i) {}
    const char* what() const throw()
    {
        return info.c_str();
    }
    ~DatabaseException()throw() {}
};
#endif // DATABASE_H
