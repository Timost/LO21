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
}

QSqlQuery Database::query(string q)
{
    QSqlQuery query;
    if(!query.exec(QString(q.c_str())))
    {
        QString e=QString("Erreur lors de l'exécution de la requête ");
        e+=QString(q.c_str());
        throw DatabaseException(e.toStdString());
    }
    return query;
}

void Database::SaverLoader::init()
{
    //on drop toutes les tables
    try
    {
        db.query("DROP Table Saison;");
    }
    catch (const DatabaseException& e)
    {
    }
    try
    {
        db.query("DROP Table Note;");
    }
    catch (const DatabaseException& e)
    {
    }
    try
    {
        db.query("DROP Table Categorie;");
    }
    catch (const DatabaseException& e)
    {
    }
    try
    {
        db.query("DROP Table SousCategorie;");
    }
    catch (const DatabaseException& e)
    {
    }
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
       db.query("DROP Table ConditionsFormation;");
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
    db.query("CREATE TABLE Saison (nom varchar(255), description varchar(255));");
    db.query("CREATE TABLE Note (note varchar(255), description varchar(255),rang int,eliminatoire int);");
    db.query("CREATE TABLE Categorie (code varchar(255), description varchar(255));");
    db.query("CREATE TABLE SousCategorie (codeParent varchar(255), codeFille varchar(255));");
    db.query("CREATE TABLE UV (code varchar(255), titre varchar(255), automne int, printemps int);");
    db.query("CREATE TABLE CreditsUV (code varchar(255), categorie varchar(255), nbCredits int);");
    db.query("CREATE TABLE Etudiant (ine int , login varchar(255), nom varchar(255), prenom varchar(255), dateNaissance date);");
    db.query("CREATE TABLE Formation (nom varchar(255), description varchar(255));");
    db.query("CREATE TABLE FormationUV (formation varchar(255), uv varchar(255), obligatoire int);");
    db.query("CREATE TABLE CreditsFormation (formation varchar(255), categorie varchar(255), nbCredits int);");
    db.query("CREATE TABLE ConditionsFormation (formation varchar(255), condition varchar (255));");
    db.query("CREATE TABLE Inscription (login varchar(255), code varchar(255), saison varchar(20), annee int, resultat varchar(3));");
    db.query("CREATE TABLE FormationEtudiant (login varchar(255), formation varchar(255));");
}

void Database::SaverLoader::save()
{
    init();
    vector<UV>::const_iterator it=tUV.getIterator();
    //sauvegarde des UVs
    for(unsigned int i=0; i<tUV.size(); i++)
    {
        string q="INSERT INTO UV (code, titre, automne, printemps) VALUES ('"+it[i].getCode()+"', '"+it[i].getTitre()+"', '"+to_string(int(it[i].ouvertureAutomne()))+"', '"+to_string(int(it[i].ouverturePrintemps()))+"');";
        db.query(q);

        map<Categorie, unsigned int> creditsUvI=it[i].getCredits();
        typedef map<Categorie, unsigned int>::iterator iteratorCat;

        for(iteratorCat itCat=creditsUvI.begin(); itCat!=creditsUvI.end(); itCat++)
        {
            q="INSERT INTO CreditsUV (code, categorie, nbCredits) VALUES ('"+it[i].getCode()+"', '"+itCat->first.getCodeStdString()+"', '"+std::to_string(itCat->second)+"');";
            db.query(q);
        }
    }
    //sauvegarde des étudiants, inscription et formations par étudiants
    vector<Etudiant>::const_iterator itEtu=tEtudiant.getIterator();
    for(unsigned int i=0; i<tEtudiant.size(); i++)
    {
        string q="INSERT INTO Etudiant (ine, login, nom, prenom, dateNaissance) VALUES ('"+to_string(itEtu[i].getIne())+"', '"+itEtu[i].getLogin().toStdString()+"', '"+itEtu[i].getNom().toStdString()+"', '"+itEtu[i].getPrenom().toStdString()+"', '"+itEtu[i].getDateNaissance().toString(QString("yyyy-MM-dd")).toStdString()+"');";
        db.query(q);
        vector<Inscription> it2=itEtu[i].getDossier().getInscription();
        for(unsigned int j=0; j<itEtu[i].getDossier().getInscription().size(); j++)
        {
            q="INSERT INTO Inscription (login, code, saison, annee, resultat) VALUES ('"+itEtu[i].getLogin().toStdString()+"', '"+it2[j].getUV().getCode()+"', '"+it2[j].getSemestre().getSaison().getNom().toStdString()+"', '"+to_string(it2[j].getSemestre().getAnnee())+"', '"+it2[j].getResultat().getNote().toStdString()+"');";
            db.query(q);
        }

        vector<Formation*> it3=itEtu[i].getDossier().getFormation();
        for(unsigned int j=0; j<itEtu[i].getDossier().getInscription().size(); j++)
        {
            q="INSERT INTO FormationEtudiant (login, formation) VALUES ('"+itEtu[i].getLogin().toStdString()+"', '"+it3[j]->getNom().toStdString()+"');";
            db.query(q);
        }
    }
    //Sauvegarde des formations
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
        map<Categorie, unsigned int> creditsFormationI=itForm[i].getNbCreditsByCat();
        typedef map<Categorie, unsigned int>::iterator iteratorCat;

        for(iteratorCat itCat=creditsFormationI.begin(); itCat!=creditsFormationI.end(); itCat++)
        {
            q="INSERT INTO CreditsFormation (formation, categorie, nbCredits) VALUES ('"+itForm[i].getNom().toStdString()+"', '"+itCat->first.getCodeStdString()+"', '"+std::to_string(itCat->second)+"');";
            db.query(q);
        }

        std::vector<Condition> conditionFormation=itForm[i].getConditions();
        for( std::vector<Condition>::iterator it3 = conditionFormation.begin(); it3!=conditionFormation.end(); it3++)
        {
            q="INSERT INTO ConditionsFormation (formation, condition) VALUES ('"+itForm[i].getNom().toStdString()+"', '"+it3->getCond().toStdString()+"');";
            db.query(q);
        }
    }

    //Sauvegarde des Catégories
    vector<Categorie>::iterator itCat = tCategorie.getIterator();
    for(; itCat != tCategorie.end(); itCat++)
    {
        string q="INSERT INTO Categorie (code, description) VALUES ('"+itCat->getCodeStdString()+"', '"+itCat->getDescriptionStdString()+"');";
        db.query(q);

        vector<Categorie> temp=itCat->getSousCategorie();

        for(vector<Categorie>::iterator itCat2 = temp.begin(); itCat2 != temp.end(); itCat2++)
        {
            string q="INSERT INTO SousCategorie (codeParent, codeFille) VALUES ('"+itCat->getCode().toStdString()+"', '"+itCat2->getCode().toStdString()+"');";
            db.query(q);
        }
    }



    //Sauvegarde des Saisons
    vector<Saison>::iterator itSaison = tSaison.getIterator();
    for(; itSaison != tSaison.end(); itSaison++)
    {
        string q="INSERT INTO Saison (nom, description) VALUES ('"+itSaison->getNomStdString()+"', '"+itSaison->getDescriptionStdString()+"');";
        db.query(q);
    }

    //Sauvegarde des Notes
    vector<Note>::iterator itNote = tNote.getIterator();
    for(; itNote != tNote.end(); itNote++)
    {
        int boo=itNote->getEliminatoire();
        string q="INSERT INTO Note (note, description,rang, eliminatoire ) VALUES ('"+itNote->getNoteStdString()+"', '"+itNote->getDescriptionStdString()+"','"+std::to_string(itNote->getRang())+"','"+std::to_string(boo)+"');";
        db.query(q);
    }





    qDebug()<<"fin save";
}

void Database::SaverLoader::load()
{
    tUV.clear();
    tEtudiant.clear();
    tFormation.clear();
    tCategorie.clear();
    tNote.clear();
    tSaison.clear();

    //load Notes
    string q="SELECT note, description, rang, eliminatoire FROM Note;";
    QSqlQuery res=db.query(q);
    while(res.next())
    {
        Note note(res.value(0).toString(),res.value(1).toString(),res.value(2).toUInt(),res.value(3).toUInt());
    }

    //load Saisons
     q="SELECT nom, description FROM Saison;";
     res=db.query(q);
    while(res.next())
    {
        Saison Sais(res.value(0).toString(),res.value(1).toString());
    }


    //load Catégories

    q="SELECT code, description FROM Categorie;";
    res=db.query(q);
    while(res.next())
    {
        Categorie cat(res.value(0).toString(),res.value(1).toString());
    }

    //Mise en place des sous Catégories
    for(std::vector<Categorie>::iterator it_cat=tCategorie.getIterator();it_cat!=tCategorie.end();it_cat++)
    {
        q="SELECT codeParent, codeFille FROM SousCategorie where codeParent='"+it_cat->getCode().toStdString()+"';";
        res=db.query(q);
        while(res.next())
        {
            tCategorie.getElement(res.value(0).toString()).addSousCategorie(tCategorie.getElement(res.value(1).toString()));
        }
    }

    //load UVS
    q="SELECT code, titre, automne, printemps FROM UV;";
    res=db.query(q);
    while(res.next())
    {
       map<Categorie, unsigned int> uvcre=map<Categorie, unsigned int>();
       string q1="SELECT code, categorie, nbCredits FROM CreditsUV WHERE code='"+res.value(0).toString().toStdString()+"';";
       QSqlQuery res1=db.query(q1);
       while(res1.next())
       {
           uvcre[StringToCategorie(res1.value(1).toString())]=res1.value(2).toInt();
       }
       UV(res.value(0).toString().toStdString(), res.value(1).toString().toStdString(), uvcre, res.value(2).toBool(), res.value(3).toBool());

    }
    //load Formation
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

        std::vector<Condition> conds;
        q1="SELECT formation, condition FROM conditionsFormation where formation='"+res.value(0).toString().toStdString()+"';";
        res1=db.query(q1);
        while(res1.next())
        {
           conds.push_back(Condition(res1.value(2).toString()));
        }
        Formation(res.value(0).toString(), res.value(1).toString(), uvs, Cat,conds);
    }

    //load Etudiants
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
        qDebug()<<"fin load";
    }
}
