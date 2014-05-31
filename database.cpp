#include "database.h"

Database::Database(string path, string dbname)
{
    this->db = QSqlDatabase::addDatabase(QString(dbname.c_str()));
    databaseName=path;
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

QSqlQuery Database::query(string q)
{
    if(!db.open())
        throw DatabaseException("Erreur lors de la connection.");
    QSqlQuery query;
    if(!query.exec(QString(q.c_str())))
    {
        QString e=QString("Erreur lors de l'exécution de la requête ");
        e+=QString(q.c_str());
        throw DatabaseException(e.toStdString());
    }
    db.close();
    return query;
}

void Database::SaverLoader::init()
{
    //on drop toutes les tables
    try
    {
        db.query("DROP Table UV;");
    }
    catch (const DatabaseException& e)
    {
    }
    try
    {
       db.query("DROP Table Credits;");
    }
    catch (const DatabaseException& e)
    {
    }
    try
    {
        db.query("DROP TABLE Etudiant;");
    }
    catch (const DatabaseException& e)
    {
    }
    try
    {
        db.query("DROP TABLE Formation;");
    }
    catch (const DatabaseException& e)
    {
    }
    try
    {
        db.query("DROP TABLE Inscription;");
    }
    catch (const DatabaseException& e)
    {
    }
    try
    {
        db.query("DROP TABLE FormationEtudiant;");
    }
    catch (const DatabaseException& e)
    {
    }
    try
    {
        db.query("DROP TABLE FormationUV;");
    }
    catch (const DatabaseException& e)
    {
    }
    try
    {
       db.query("DROP Table CreditsFormation;");
    }
    catch (const DatabaseException& e)
    {
    }
    try
    {
       db.query("DROP Table CreditsUV;");
    }
    catch (const DatabaseException& e)
    {
    }
    //On recree les tables
    db.query("CREATE TABLE UV (code varchar(255), titre varchar(255), automne int, printemps int);");
    db.query("CREATE TABLE CreditsUV (code varchar(255), categorie varchar(255), nbCredits int);");
    db.query("CREATE TABLE Etudiant (ine int , login varchar(255), nom varchar(255), prenom varchar(255), dateNaissance date);");
    db.query("CREATE TABLE Formation (nom varchar(255), description varchar(255));");
    db.query("CREATE TABLE FormationUV (formation varchar(255), uv varchar(255), obligatoire int);");
    db.query("CREATE TABLE CreditsFormation (formation varchar(255), categorie varchar(255), nbCresits int);");
    db.query("CREATE TABLE Inscription (login varchar(255), code varchar(255), saison varchar(20), annee int, resultat varchar(3));");
    db.query("CREATE TABLE FormationEtudiant (login varchar(255), formation varchar(255));");
}

void Database::SaverLoader::save()
{
    init();
    vector<UV>::const_iterator it=tUV.getIterator();
    for(int i=0; i<tUV.size(); i++)
    {
        string q="INSERT INTO UV (code, titre, automne, printemps) VALUES ('"+it[i].getCode()+"', '"+it[i].getTitre()+"', '"+to_string(int(it[i].ouvertureAutomne()))+"', '"+to_string(int(it[i].ouverturePrintemps()))+"');";
        map<Categorie, unsigned int> it2=it[i].getCredits();
        db.query(q);
        for(int j=0; j<4; j++)
        {
            q="INSERT INTO CreditsUV (code, categorie, nbCredits) VALUES ('"+it[i].getCode()+"', '"+CategorieToString(IntToCategorie(j)).toStdString()+"', '"+to_string(it2[IntToCategorie(j)])+"');";
            db.query(q);
        }

    }
}
