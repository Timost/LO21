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

#define q2c(string) string.toStdString()

using namespace std;

class Database
{
    QSqlDatabase db;
    string databaseName;

    bool open()
    {
        return this->db.open();
    }
    void close()
    {
        db.close();
    }
public:
    QSqlQuery query(string q);
    Database(string path, string dbname="QSQLITE");
    ~Database(){}

    class SaverLoader //gere sauvegarde et chargement de la bdd
    {
        //on recupere tous les manager
        TemplateManager<UV>& tUV=TemplateManager<UV>::getInstance();
        TemplateManager<Formation>& tFormation=TemplateManager<Formation>::getInstance();
        TemplateManager<Etudiant>& tEtudiant=TemplateManager<Etudiant>::getInstance();
        Database& db;
        void init();

    public:
        SaverLoader(Database& database):db(database){}
        void save();
    };

    bool save()
    {
        SaverLoader(*this).save();
    }
};

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
