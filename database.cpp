#include "database.h"
Database* Database::handler=0;

Database::Database(string dbname)
{
    this->db = QSqlDatabase::addDatabase(QString(dbname.c_str()));
    databaseName="c:/sqlite/lo21";
    this->db.setDatabaseName(QString(databaseName.c_str()));
    if(db.open())
    {
        cout << "Vous êtes maintenant connecté à " << q2c(db.hostName()) << endl;
    }
    else
    {
        throw DatabaseException("La connexion a échoué.");
    }
    db.close();
}

Database& Database::getInstance(string dbname)
{
    if (handler==0) handler = new Database(dbname);
    return *handler;
}

QSqlQuery Database::query(string q)
{
    if(!db.open())
        throw DatabaseException("Erreur lors de la connection.");
    QSqlQuery query;
    if(!query.exec(QString(q.c_str())))
        throw DatabaseException("Erreur lors de l'exéécution de la requête.");
    db.close();
    return query;
}
