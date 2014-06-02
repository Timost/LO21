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
    db.query("CREATE TABLE CreditsFormation (formation varchar(255), categorie varchar(255), nbCredits int);");
    db.query("CREATE TABLE Inscription (login varchar(255), code varchar(255), saison varchar(20), annee int, resultat varchar(3));");
    db.query("CREATE TABLE FormationEtudiant (login varchar(255), formation varchar(255));");
}

void Database::SaverLoader::save()
{
    init();
    vector<UV>::const_iterator it=tUV.getIterator();
    for(unsigned int i=0; i<tUV.size(); i++)
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

    vector<Etudiant>::const_iterator itEtu=tEtudiant.getIterator();
    for(unsigned int i=0; i<tEtudiant.size(); i++)
    {
        string q="INSERT INTO Etudiant (ine, login, nom, prenom, dateNaissance) VALUES ('"+to_string(itEtu[i].getIne())+"', '"+itEtu[i].getLogin().toStdString()+"', '"+itEtu[i].getNom().toStdString()+"', '"+itEtu[i].getPrenom().toStdString()+"', '"+itEtu[i].getDateNaissance().toString(QString("yyyy-MM-dd")).toStdString()+"');";
        db.query(q);
        vector<Inscription> it2=itEtu[i].getDossier().getInscription();
        for(unsigned int j=0; j<itEtu[i].getDossier().getInscription().size(); j++)
        {
            q="INSERT INTO Inscription (login, code, saison, annee, resultat) VALUES ('"+itEtu[i].getLogin().toStdString()+"', '"+it2[j].getUV().getCode()+"', '"+SaisonToString(it2[j].getSemestre().getSaison()).toStdString()+"', '"+to_string(it2[j].getSemestre().getAnnee())+"', '"+NoteToString(it2[j].getResultat()).toStdString()+"');";
            db.query(q);
        }

        vector<Formation*> it3=itEtu[i].getDossier().getFormation();
        for(unsigned int j=0; j<itEtu[i].getDossier().getInscription().size(); j++)
        {
            q="INSERT INTO FormationEtudiant (login, formation) VALUES ('"+itEtu[i].getLogin().toStdString()+"', '"+it3[j]->getNom().toStdString()+"');";
            db.query(q);
        }
    }

    vector<Formation>::const_iterator itForm=tFormation.getIterator();
    for(unsigned int i=0; i<tFormation.size(); i++)
    {
        string q="INSERT INTO Formation (nom, description) VALUES ('"+itForm[i].getNom().toStdString()+"', '"+itForm[i].getDescription().toStdString()+"');";
        db.query(q);
        map<UV*, bool> uvs=itForm[i].getUVs();
        for( map <UV*,bool>::const_iterator it2 = uvs.begin(); it2!=uvs.end(); it2++)
        {
            q="INSERT INTO FormationUV (formation, uv, obligatoire) VALUES ('"+itForm[i].getNom().toStdString()+"', '"+it2->first->getCode()+"', '"+to_string(int(it2->second))+"');";
            db.query(q);
        }
        map<Categorie, unsigned int> it3=itForm[i].getNbCreditsByCat();
        for(int j=0; j<4; j++)
        {
            q="INSERT INTO CreditsFormation (formation, categorie, nbCredits) VALUES ('"+itForm[i].getNom().toStdString()+"', '"+CategorieToString(IntToCategorie(j)).toStdString()+"', '"+to_string(it3[IntToCategorie(j)])+"');";
            db.query(q);
        }
    }
    qDebug()<<"fin save";
}

void Database::SaverLoader::load()
{
    tUV.clear();
    tEtudiant.clear();
    tFormation.clear();
    string q="SELECT code, titre, automne, printemps FROM UV;";
    QSqlQuery res=db.query(q);
    while(res.next())
    {
       map<Categorie, unsigned int> uvcre=map<Categorie, unsigned int>();
       string q1="SELECT code, categorie, nbCredits FROM CreditsUV WHERE code='"+res.value(0).toString().toStdString()+"';";
       QSqlQuery res1=db.query(q1);
       while(res1.next())
       {
           uvcre[StringToCategorie(res1.value(1).toString())]=res1.value(2).toInt();
       }
       UV uv=UV(res.value(0).toString().toStdString(), res.value(1).toString().toStdString(), uvcre, res.value(2).toBool(), res.value(3).toBool());
       tUV.New(uv);
    }
    q="SELECT nom, description FROM Formation;";
    res=db.query(q);
    while(res.next())
    {
        map<UV*, bool> uvs=map<UV*, bool>();
        string q1="SELECT formation, uv, obligatoire FROM FormationUV where formation='"+res.value(0).toString().toStdString()+"';";
        QSqlQuery res1=db.query(q1);
        while(res1.next())
        {
            UV& uv=tUV.getElement(res1.value(1).toString().toStdString());
            uvs[&uv]=res1.value(2).toBool();
        }
        map<Categorie, unsigned int> Cat=map<Categorie, unsigned int>();
        q1="SELECT formation, categorie, nbCredits FROM CreditsFormation where formation='"+res.value(0).toString().toStdString()+"';";
        res1=db.query(q1);
        while(res1.next())
        {
            Cat[StringToCategorie(res1.value(1).toString())]=res1.value(2).toInt();
        }
        Formation f=Formation(res.value(0).toString(), res.value(1).toString(), uvs, Cat);
        tFormation.New(f);
    }
    q="SELECT ine, login, nom, prenom, dateNaissance from Etudiant;";
    res=db.query(q);
    while(res.next())
    {
        vector<Inscription> insc= vector<Inscription>();
        string q1="SELECT login, code, saison, annee, resultat FROM Inscription WHERE login='"+res.value(1).toString().toStdString()+"';";
        QSqlQuery res1=db.query(q1);
        while(res1.next())
        {
            Semestre s=Semestre(StringToSaison(res1.value(2).toString()), res1.value(3).toInt());
            string code=res1.value(1).toString().toStdString();
            const UV& uv=tUV.getElement(code);
            Inscription inscription=Inscription(uv, s, StringToNote(res1.value(4).toString()));
            insc.push_back(inscription);
        }
        vector<Formation*> form= vector<Formation*>();
        q1="SELECT login, formation FROM FormationEtudiant WHERE login='"+res.value(1).toString().toStdString()+"';";
        res1=db.query(q1);
        while(res1.next())
        {
            Formation& F=tFormation.getElement(res1.value(1).toString().toStdString());
            form.push_back(&F);
        }
        Dossier dos=Dossier(insc, form);
        Etudiant etu=Etudiant(dos, res.value(0).toInt(), res.value(2).toString(), res.value(3).toString(), res.value(4).toDate(), res.value(1).toString());
        tEtudiant.New(etu);
        qDebug()<<"fin load";
    }
}
