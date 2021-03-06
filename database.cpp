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
        e+=" Erreur : "+query.lastError().databaseText();
        throw DatabaseException(e.toStdString());
    }
    return query;
}

void Database::SaverLoader::init()
{

    qDebug()<<"debut init";
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
        db.query("DROP Table Semestre;");
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
    db.query("CREATE TABLE Semestre (code varchar(255), saison varchar(255), year int);");
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
    qDebug()<<"Save : init() Debut";
    init();
    qDebug()<<"Save : init() Fin";
    qDebug()<<"Save : UV() Debut";
    vector<UV>::const_iterator it=tUV.getIterator();
    //sauvegarde des UVs
    for(unsigned int i=0; i<tUV.size(); i++)
    {
        QSqlQuery query;
        query.prepare("INSERT INTO UV (code, titre, automne, printemps) VALUES (:code, :titre, :automne,:printemps)");
        query.bindValue(":code", QString::fromStdString(it[i].getCode()));
        query.bindValue(":titre", QString::fromStdString(it[i].getTitre()));
        query.bindValue(":automne", QString::fromStdString(to_string(int(it[i].ouvertureAutomne()))));
        query.bindValue(":printemps", QString::fromStdString(to_string(int(it[i].ouverturePrintemps()))));
        query.exec();


        map<Categorie, unsigned int> creditsUvI=it[i].getCredits();
        typedef map<Categorie, unsigned int>::iterator iteratorCat;

        for(iteratorCat itCat=creditsUvI.begin(); itCat!=creditsUvI.end(); itCat++)
        {
            QSqlQuery query;
            query.prepare("INSERT INTO CreditsUV (code, categorie, nbCredits) VALUES (:code, :categorie, :nbCredits)");
            query.bindValue(":code", QString::fromStdString(it[i].getCode()));
            query.bindValue(":categorie", QString::fromStdString(itCat->first.getCodeStdString()));
            query.bindValue(":nbCredits", QString::fromStdString(std::to_string(itCat->second)));
            query.exec();
        }
    }
    qDebug()<<"Save : UV() Fin";
    qDebug()<<"Save : Etudiant() Debut";
    //sauvegarde des étudiants, inscription et formations par étudiants
    vector<Etudiant>::const_iterator itEtu=tEtudiant.getIterator();
    for(unsigned int i=0; i<tEtudiant.size(); i++)
    {
        qDebug()<<"Etudiant : INSERT INTO Etudiant";
        QSqlQuery query;
        query.prepare("INSERT INTO Etudiant (ine, login, nom, prenom, dateNaissance) VALUES (:ine, :login, :nom,:prenom,:dateNaissance)");
        query.bindValue(":ine", QString::fromStdString(to_string(itEtu[i].getIne())));
        query.bindValue(":login", itEtu[i].getLogin());
        query.bindValue(":nom", QString::fromStdString(itEtu[i].getNom().toStdString()));
        query.bindValue(":prenom", QString::fromStdString(itEtu[i].getPrenom().toStdString()));
        query.bindValue(":dateNaissance", itEtu[i].getDateNaissance().toString(QString("yyyy-MM-dd")));
        query.exec();

        vector<Inscription> it2=itEtu[i].getDossier().getInscription();
        for(unsigned int j=0; j<itEtu[i].getDossier().getInscription().size(); j++)
        {
            QSqlQuery query;
            query.prepare("INSERT INTO Inscription (login, code, saison, annee, resultat) VALUES (:login, :code, :saison,:annee,:resultat)");
            query.bindValue(":login",itEtu[i].getLogin());
            query.bindValue(":code", QString::fromStdString(it2[j].getUV().getCode()));
            query.bindValue(":saison", it2[j].getSemestre().getSaison().getNom());
            query.bindValue(":annee", QString::number(it2[j].getSemestre().getAnnee()));
            query.bindValue(":resultat", it2[j].getResultat().getNote());
            query.exec();
        }
        qDebug()<<"Etudiant : INSERT INTO Inscription";

        vector<Formation*> it3=itEtu[i].getDossier().getFormation();
        //qDebug()<<"TEst";
        for(unsigned int j=0; j<itEtu[i].getDossier().getFormation().size(); j++)
        {
            //qDebug()<<"TEst";
//           std::string q="INSERT INTO FormationEtudiant (login, formation) VALUES ('"+itEtu[i].getLogin().toStdString()+"', '"+it3[j]->getNom().toStdString()+"');";
//            db.query(q);

            QSqlQuery query;
            query.prepare("INSERT INTO FormationEtudiant (login, formation) VALUES (:login, :formation)");
            query.bindValue(":login",itEtu[i].getLogin());
            query.bindValue(":formation", it3[j]->getNom());
            query.exec();
        }
        qDebug()<<"Etudiant : INSERT INTO FormationEtudiant";
    }
    qDebug()<<"Save : Etudiant() Fin";
    qDebug()<<"Save : Formations() Debut";
    //Sauvegarde des formations
    vector<Formation>::const_iterator itForm=tFormation.getIterator();
    for(unsigned int i=0; i<tFormation.size(); i++)
    {
//        string q="INSERT INTO Formation (nom, description) VALUES ('"+itForm[i].getNom().toStdString()+"', '"+itForm[i].getDescription().toStdString()+"');";
//        db.query(q);
        QSqlQuery query;
        query.prepare("INSERT INTO Formation (nom, description) VALUES (:nom, :description)");
        query.bindValue(":nom",itForm[i].getNom());
        query.bindValue(":description", itForm[i].getDescription());
        query.exec();

        map<UV*, bool> uvs=itForm[i].getUVs();
        for( map <UV*,bool>::const_iterator it2 = uvs.begin(); it2!=uvs.end(); it2++)
        {
//            q="INSERT INTO FormationUV (formation, uv, obligatoire) VALUES ('"+itForm[i].getNom().toStdString()+"', '"+it2->first->getCode()+"', '"+to_string(int(it2->second))+"');";
//            db.query(q);
            QSqlQuery query;
            query.prepare("INSERT INTO FormationUV (formation, uv, obligatoire) VALUES (:formation, :uv, :obligatoire)");
            query.bindValue(":formation",itForm[i].getNom());
            query.bindValue(":uv", QString::fromStdString(it2->first->getCode()));
            query.bindValue(":obligatoire", QString::fromStdString(to_string(int(it2->second))));
            query.exec();
        }
        map<Categorie, unsigned int> creditsFormationI=itForm[i].getNbCreditsByCat();
        typedef map<Categorie, unsigned int>::iterator iteratorCat;

        for(iteratorCat itCat=creditsFormationI.begin(); itCat!=creditsFormationI.end(); itCat++)
        {
//            q="INSERT INTO CreditsFormation (formation, categorie, nbCredits) VALUES ('"+itForm[i].getNom().toStdString()+"', '"+itCat->first.getCodeStdString()+"', '"+std::to_string(itCat->second)+"');";
//            db.query(q);
            QSqlQuery query;
            query.prepare("INSERT INTO CreditsFormation (formation, categorie, nbCredits) VALUES (:formation, :categorie, :nbCredits)");
            query.bindValue(":formation",itForm[i].getNom());
            query.bindValue(":categorie", itCat->first.getCode());
            query.bindValue(":nbCredits", QString::number(itCat->second));
            query.exec();
        }

        std::vector<Condition> conditionFormation=itForm[i].getConditions();
        for( std::vector<Condition>::iterator it3 = conditionFormation.begin(); it3!=conditionFormation.end(); it3++)
        {
//            q="INSERT INTO ConditionsFormation (formation, condition) VALUES ('"+itForm[i].getNom().toStdString()+"', '"+it3->getCond().toStdString()+"');";
//            db.query(q);
            QSqlQuery query;
            query.prepare("INSERT INTO ConditionsFormation (formation, condition) VALUES (:formation, :condition)");
            query.bindValue(":formation",itForm[i].getNom());
            query.bindValue(":condition", it3->getCond());
            query.exec();
        }
    }
    qDebug()<<"Save : Formations() Fin";
    qDebug()<<"Save : Catégories() Debut";

    //Sauvegarde des Catégories
    vector<Categorie>::iterator itCat = tCategorie.getIterator();
    for(; itCat != tCategorie.end(); itCat++)
    {
//        string q="INSERT INTO Categorie (code, description) VALUES ('"+itCat->getCodeStdString()+"', '"+itCat->getDescriptionStdString()+"');";
//        db.query(q);

        QSqlQuery query;
        query.prepare("INSERT INTO Categorie (code, description) VALUES (:code, :description)");
        query.bindValue(":code",itCat->getCode());
        query.bindValue(":description", itCat->getDescription());
        query.exec();

        vector<Categorie> temp=itCat->getSousCategorie();

        for(vector<Categorie>::iterator itCat2 = temp.begin(); itCat2 != temp.end(); itCat2++)
        {
//            string q="INSERT INTO SousCategorie (codeParent, codeFille) VALUES ('"+itCat->getCode().toStdString()+"', '"+itCat2->getCode().toStdString()+"');";
//            db.query(q);

            QSqlQuery query;
            query.prepare("INSERT INTO SousCategorie (codeParent, codeFille) VALUES (:codeParent, :codeFille)");
            query.bindValue(":codeParent",itCat->getCode());
            query.bindValue(":codeFille", itCat2->getCode());
            query.exec();
        }
    }
    qDebug()<<"Save : Catégories() Fin";
    qDebug()<<"Save : Saisons() Debut";


    //Sauvegarde des Saisons
    vector<Saison>::iterator itSaison = tSaison.getIterator();
    for(; itSaison != tSaison.end(); itSaison++)
    {
//        string q="INSERT INTO Saison (nom, description) VALUES ('"+itSaison->getNomStdString()+"', '"+itSaison->getDescriptionStdString()+"');";
//        db.query(q);

        QSqlQuery query;
        query.prepare("INSERT INTO Saison (nom, description) VALUES (:nom, :description)");
        query.bindValue(":nom",itSaison->getNom());
        query.bindValue(":description", itSaison->getDescription());
        query.exec();
    }

    qDebug()<<"Save : Saisons() Fin";
    qDebug()<<"Save : Notes() Debut";

    //Sauvegarde des Notes
    vector<Note>::iterator itNote = tNote.getIterator();
    for(; itNote != tNote.end(); itNote++)
    {
        int boo=itNote->getEliminatoire();
//        string q="INSERT INTO Note (note, description,rang, eliminatoire ) VALUES ('"+itNote->getNoteStdString()+"', '"+itNote->getDescriptionStdString()+"','"+std::to_string(itNote->getRang())+"','"+std::to_string(boo)+"');";
//        db.query(q);

        QSqlQuery query;
        query.prepare("INSERT INTO Note (note, description,rang, eliminatoire ) VALUES (:note, :description, :rang ,:eliminatoire)");
        query.bindValue(":note",itNote->getNote());
        query.bindValue(":description", itNote->getDescription());
        query.bindValue(":rang", QString::number(itNote->getRang()));
        query.bindValue(":eliminatoire", QString::number(boo));
        query.exec();
    }

    qDebug()<<"Save : Notes() Fin";
    qDebug()<<"Save : Semestres() Debut";

    //Sauvegarde des Semestre
    vector<Semestre>::iterator itSemestre = tSemestre.getIterator();
    for(; itSemestre != tSemestre.end(); itSemestre++)
    {
        int temp=itSemestre->getAnnee();
//        string q="INSERT INTO Semestre (code, saison, year) VALUES ('"+itSemestre->getCode().toStdString() +"', '"+itSemestre->getSaison().getNomStdString()+"', '"+ std::to_string(temp)+"');";
//        db.query(q);

        QSqlQuery query;
        query.prepare("INSERT INTO Semestre (code, saison, year) VALUES (:code, :saison, :year)");
        query.bindValue(":code",itSemestre->getCode());
        query.bindValue(":saison", itSemestre->getSaison().getNom());
        query.bindValue(":year", QString::number(temp));
        query.exec();
    }
    qDebug()<<"Save : Semestres() Fin";


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
    tSemestre.clear();
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

    //load Semestres
     q="SELECT code, saison, year FROM Semestre;";
     res=db.query(q);
    while(res.next())
    {
        Semestre sem(tSaison.getElement(res.value(1).toString()),res.value(2).toInt());
    }
    qDebug()<<"test";

    //load Catégories

    q="SELECT code, description FROM Categorie;";
    res=db.query(q);
    while(res.next())
    {
        Categorie cat(res.value(0).toString(),res.value(1).toString());
    }
    qDebug()<<"test";
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
    qDebug()<<"test";

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
           conds.push_back(Condition(res1.value(1).toString()));
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
            //Semestre s=Semestre(StringToSaison(res1.value(2).toString()), res1.value(3).toInt());
            string code=res1.value(1).toString().toStdString();
            const UV& uv=tUV.getElement(code);
            Inscription inscription=Inscription(uv, tSemestre.getElement(res1.value(2).toString()+res1.value(3).toString()), StringToNote(res1.value(4).toString()));
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
