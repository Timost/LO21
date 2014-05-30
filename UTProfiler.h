//warning sur classe semestre borne sup de la conditions sur année

#ifndef UT_PROFILER_h
#define UT_PROFILER_h
#include <sstream>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QString>
#include <QTextStream>
#include <type_traits>
#include <iostream>
#include <map>
using namespace std;

//class UTProfilerException{
//public:
//    UTProfilerException(const QString& message):info(message){}
//    QString getInfo() const { return info; }
//private:
//    QString info;
//};

//enum class Categorie {
//	/* Connaissances Scientifiques */ CS,  /* Techniques et Méthodes */ TM,
//    /* Technologies et Sciences de l'Homme */ TSH, /* Stage et Projet */ SP,
//    first=CS, last=SP
//};

//QTextStream& operator<<(QTextStream& f, const Categorie& s);

//Categorie StringToCategorie(const QString& s);
//QString CategorieToString(Categorie c);
//QTextStream& operator>>(QTextStream& f, Categorie& cat);

//enum class Note { A, B, C, D, E, F, FX, RES, ABS, /* en cours */ EC, first=A, last=EC  };


/*class NoteIterator {
    Note value;
    NoteIterator(Note val):value(val){}
public:
    static NoteIterator getFirst() { return NoteIterator(first); }
    bool isDone() const { return value>last; }
    Note operator*() const { return value; }
    void next() { std::underlying_type<Note>::type(value)++; }
};*/

//enum class Saison { Automne, Printemps, first=Automne, last=Printemps };
//inline QTextStream& operator<<(QTextStream& f, const Saison& s) { if (s==Saison::Automne) f<<"A"; else f<<"P"; return f;}

//template<typename EnumType>
//class EnumIterator {
//    static_assert(is_enum<EnumType>::value, "EnumType has to be an enum");
//    EnumType value;
//    EnumIterator(EnumType val):value(val){}
//public:
//    static EnumIterator getFirst() { return EnumIterator(EnumType::first); }
//    bool isDone() const { return value>EnumType::last; }
//    EnumType operator*() const { return value; }
//    void next() { value=(EnumType)(std::underlying_type<EnumType>::type(value)+1); }
//};

//typedef EnumIterator<Note> NoteIterator;
//typedef EnumIterator<Categorie> CategorieIterator;
//typedef EnumIterator<Saison> SaisonIterator;


//class Semestre {
//	Saison saison;
//	unsigned int annee;
//public:
//    Semestre(Saison s, unsigned int a):saison(s),annee(a){ if (annee<1972||annee>2099) throw UTProfilerException("annee non valide"); }
//	Saison getSaison() const { return saison; }
//	unsigned int getAnnee() const { return annee; }
//};

/*
class UV {
    QString code;
    QString titre;
	unsigned int nbCredits;
	Categorie categorie;
    bool automne;
    bool printemps;
	UV(const UV& u);
	UV& operator=(const UV& u);
    UV(const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p):
      code(c),titre(t),nbCredits(nbc),categorie(cat),automne(a),printemps(p){}
	friend class UVManager;
    friend class UVManager2;
public:
    QString getCode() const { return code; }
    QString getTitre() const { return titre; }
	unsigned int getNbCredits() const { return nbCredits; }
	Categorie getCategorie() const { return categorie; }
    bool ouvertureAutomne() const { return automne; }
    bool ouverturePrintemps() const { return printemps; }
    void setCode(const QString& c) { code=c; }
    void setTitre(const QString& t) { titre=t; }
    void setNbCredits(unsigned int n) { nbCredits=n; }
    void setCategorie(Categorie c) { categorie=c; }
    void setOuvertureAutomne(bool b) { automne=b; }
    void setOuverturePrintemps(bool b) { printemps=b; }
};

QTextStream& operator<<(QTextStream& f, const UV& uv);

/*
 *
 *
 *
 *
 *
 *
 * Regarde après je t'ai mis mes idées pour le manager universel
 *
 *
 *
 *
 *
 *
 */

/*
template <class T>
class Manager{// manage un tableau de T*, doit inclure les fonctionnaltés suivantes :
    //Singleton (Celle ci j'ai un doute... mettre le constructeur en privé et tout... est-ce vraiment souhaitable ?): pour rendre un singleton héritable (utiliser un pointeur à la place d'une variable statique) cf : http://www.codeproject.com/Articles/4750/Singleton-Pattern-A-review-and-analysis-of-existin
    //Iterator : pour pouvoir naviguer le tableau d'entier
    //Load et Save du tableau dans une base de donnée à priori

    //Petit rappel pour les classes template :
    //Toutes les définitions de fonctions doivent être dans la mêm untité de compilation (à priori dans ce fichier, mais on peut aussi faire dans plusieurs fichiers .h).

    // ci-dessous mes idées :
protected:// ou privé à voir
    T** tab;
    unsigned int sizeMaxTab;
    unsigned int nbElements;
    //plus les attributs pour la base de donnée
    //QString username;
    //QString password;
    //QString DatabaseName;
    //QString Url ???

public:
    Manager();//à mettre en protected/privée ??? pour le singleton
    ~Manager();//doit gérer la sauvegarde si nécessaire
    unsigned int getSizeMaxTab()const{return sizeMaxTab;}//faire une version const unsigned int aussi ??
    unsigned int getNbElements()const{return nbElements;}
    T* getElement(unsigned int index);
    void addElement(T* e);//virtuelle pure ??? ajoute un élément au tableau
    void remove(unsigned int index);//virtuelle pure ??? enlêve l'élément à l'index index dans tab//faire une version avec un pointeur pour paramêtre??
    //void connect(QString ...);//se connecter à la base de données
    //void save();//Sauvegarder le tableau d'objet dans la base de données
    //void load();//Charger dans tab les champs de la base de données

    //Iterator
    //Cf ce qu'à fait le prof dans la classe UVManager

    //Singleton
    //Aucune idée...


};

/*class UVManager{
private:
	UV** uvs;
	unsigned int nbUV;
	unsigned int nbMaxUV;
	void addItem(UV* uv);
	bool modification;
    UV* trouverUV(const QString& c) const;
    UVManager(const UVManager& um);
    UVManager& operator=(const UVManager& um);
    UVManager();
    ~UVManager();
    QString file;
    friend struct Handler;
    struct Handler{
        UVManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;

public:

    void load(const QString& f);
    void save(const QString& f);
	static UVManager& getInstance();
	static void libererInstance();
    void ajouterUV(const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p);
    const UV& getUV(const QString& code) const;
    UV& getUV(const QString& code);

	class Iterator {
		friend class UVManager;
		UV** currentUV;
		unsigned int nbRemain;
        Iterator(UV** u, unsigned int nb):currentUV(u),nbRemain(nb){}
	public:
		Iterator():nbRemain(0),currentUV(0){}
		bool isDone() const { return nbRemain==0; }
		void next() { 
			if (isDone()) 
				throw UTProfilerException("error, next on an iterator which is done"); 
			nbRemain--; 
			currentUV++; 
		}
		UV& current() const { 
			if (isDone()) 
				throw UTProfilerException("error, indirection on an iterator which is done"); 
			return **currentUV; 
		}
	};
	Iterator getIterator() { 
		return Iterator(uvs,nbUV); 
	}

	class iterator {
		UV** current;
		iterator(UV** u):current(u){}
		friend class UVManager;
	public:
        iterator():current(0){}
		UV& operator*() const { return **current; }
		bool operator!=(iterator it) const { return current!=it.current; }
		iterator& operator++(){ ++current; return *this; }
	};
    iterator begin() { return iterator(uvs); }
	iterator end() { return iterator(uvs+nbUV); }

	class FilterIterator {
		friend class UVManager;
		UV** currentUV;
		unsigned int nbRemain;
		Categorie categorie;
        FilterIterator(UV** u, unsigned int nb, Categorie c):currentUV(u),nbRemain(nb),categorie(c){
			while(nbRemain>0 && (*currentUV)->getCategorie()!=categorie){
				nbRemain--; currentUV++;
			}
		}
	public:
		FilterIterator():nbRemain(0),currentUV(0){}
		bool isDone() const { return nbRemain==0; }
		void next() { 
			if (isDone()) 
				throw UTProfilerException("error, next on an iterator which is done"); 
			do {
				nbRemain--; currentUV++;
			}while(nbRemain>0 && (*currentUV)->getCategorie()!=categorie);
		}
		UV& current() const { 
			if (isDone()) 
				throw UTProfilerException("error, indirection on an iterator which is done"); 
			return **currentUV; 
		}
	};
	FilterIterator getFilterIterator(Categorie c) { 
		return FilterIterator(uvs,nbUV,c); 
	}
};


class Inscription {
	const UV* uv;
	Semestre semestre;
	Note resultat;
public:
    Inscription(const UV& u, const Semestre& s, Note res=Note::EC):uv(&u),semestre(s),resultat(res){}
	const UV& getUV() const { return *uv; }
	Semestre getSemestre() const { return semestre; }
	Note getResultat() const { return resultat; }
	void setResultat(Note newres) { resultat=newres; }
};

class Formation{
    QString nom;
    QString description;
    UV** uvs;//contient les Uvs Faisant partie de la formation
    UV** uvsObligatoires;//contient les UVS obligatoires pour une formation donnée
    std::map<Categorie, int> nbCredits;//Contient le nombre de crédits à valider pour chaque catégories d'UVS
public:
    /*A faire
        Formation(QString n,QString d,UV** uvs,UV** uvsO,std::map<Categorie, int> nbCred):nom(n),description(d),uvs(uvs),uvsObligatoires(uvsO),nbCredits(nbCred){}

        QString getNom() const;
        QString getDescription()const;
        int getNbCreditsCat(const Categorie cat) const;
        int getNbCreditsTotal()const;
        void addUv(UV* uv);
        void removeUv(UV* uv);
        void addRequiredUV(UV* uv);
        void removeRequiredUV(UV* uv);
    */

/*
class FormationManager{
    Formation** formations;
    unsigned int nbFormations;
    unsigned int nbMaxFormations;
    FormationManager(const FormationManager& fm);
    FormationManager& operator=(const FormationManager& fm);
    FormationManager();
    ~FormationManager();
    QString file;
};


class Dossier {//dossier d'un étudiant cf. etuProfiler
    Inscription** inscri;
    Formation** forma;
    unsigned int nbInsc;
    unsigned int nbMaxInsc;
    unsigned int nbForm;
    unsigned int nbMaxForm;
    Dossier(Inscription** i,int nbi, int nbimax, Formation** f, int nbf, int nbfmax ){}


public:

    Dossier(){
        nbInsc=0;
        nbMaxInsc=7;
        nbForm=0;
        nbMaxForm=7;
        inscri=new Inscription*[nbMaxInsc];
        forma=new Formation*[nbMaxInsc];
    }
    /*A faire
        bool formationExists(const QString name);
        void addFormation(Formation* f);//ajoute une formation
        void deleteFormation(const unsigned int index);//supprime la formation à l'index i dans le tableau forma
        Formation* getFormation(const QString name);//retourne un pointeur sur la formation de nom name
        int getFormationIndex(const QString name);//retourne l'index d'une formation de nom name

        void addInscription(Inscription* f);//ajoute une inscription
        void deleteInscription(const unsigned int index);//supprime l'inscription à l'index i dans le tableau inscri
        Formation* getInscription(const UV* uv, const Semestre s);//retourne un pointeur sur la formation correspondante
        int getInscriptionIndex(const UV* uv, const Semestre s);//retourne l'index d'une formation de nom name

        class InscIterator {//iterator sur les inscriptions
            friend class Dossier;
            Inscription** inscri;
            unsigned int index;
            unsigned int nbMax;
            InscIterator(Inscription** i):inscri(i){}
        public:
            Inscription* first();
            Inscription* next ();
            Inscription* current ();
            bool isDone();
        };

        InscIterator getInscrIterator(){return InscIterator(inscri);}

        class FormIterator {//iterator sur les formations
            friend class Dossier;
            Formation** forma;
            int index;
            int nbMax;
        public:

        };
    */

//};




#endif


//class UVManager2 : public ManagerFile<UV>{
//private:
//    friend struct Handler;
//    struct Handler{
//        UVManager2* instance;
//        Handler():instance(0){}
//        ~Handler(){ if (instance) delete instance; instance=0; }
//    };
//   public:
//    static Handler handler;
//    static UVManager2 <T> & getInstance(){
//        if (!handler.instance) handler.instance = new BaseManager; /* instance créée une seule fois lors de la première utilisation*/
//        return *handler.instance;
//    }

//    static void libererInstance(){
//        if (handler.instance) { delete handler.instance; handler.instance=0; }
//    }
//public:

//    void load(const QString& f);
//    virtual void save(const QString& f){

//        /*QMessageBox msgBox;
//         msgBox.setText("Debut The document has been saved.");
//         msgBox.exec();*/

//        file=f;

//        QFile newfile( file);
//        if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text)) throw UTProfilerException(QString("erreur ouverture fichier xml"));
//         QXmlStreamWriter stream(&newfile);
//         stream.setAutoFormatting(true);
//         stream.writeStartDocument();
//         stream.writeStartElement("uvs");
//         for(unsigned int i=0; i<nbItems; i++){
//             stream.writeStartElement("uv");
//             stream.writeAttribute("automne", (items[i]->ouvertureAutomne())?"true":"false");
//             stream.writeAttribute("printemps", (items[i]->ouverturePrintemps())?"true":"false");
//             stream.writeTextElement("code",items[i]->getCode());
//             stream.writeTextElement("titre",items[i]->getTitre());
//             QString cr; cr.setNum(items[i]->getNbCredits());
//             stream.writeTextElement("credits",cr);
//             stream.writeTextElement("categorie",CategorieToString(items[i]->getCategorie()));
//             stream.writeEndElement();
//         }
//         stream.writeEndElement();
//         stream.writeEndDocument();

//         newfile.close();

//    }
//    void ajouterUV(const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p);
//    const UV& getUV(const QString& code) const;
//    UV& getUV(const QString& code);

//    class FilterIterator {
//        friend class UVManager2;
//        UV** currentUV;
//        unsigned int nbRemain;
//        Categorie categorie;
//        FilterIterator(UV** u, unsigned int nb, Categorie c):currentUV(u),nbRemain(nb),categorie(c){
//            while(nbRemain>0 && (*currentUV)->getCategorie()!=categorie){
//                nbRemain--; currentUV++;
//            }
//        }
//    public:
//        FilterIterator():nbRemain(0),currentUV(0){}
//        bool isDone() const { return nbRemain==0; }
//        void next() {
//            if (isDone())
//                throw UTProfilerException("error, next on an iterator which is done");
//            do {
//                nbRemain--; currentUV++;
//            }while(nbRemain>0 && (*currentUV)->getCategorie()!=categorie);
//        }
//        UV& current() const {
//            if (isDone())
//                throw UTProfilerException("error, indirection on an iterator which is done");
//            return **currentUV;
//        }
//    };
//    FilterIterator getFilterIterator(Categorie c) {
//        return FilterIterator(items,nbItems,c);
//    }
//private:
//    UV* trouverUV(const QString& c) const;
//    ~UVManager2();
//};

//template<class T>
//class BaseManager{
//protected:
//    T** items;
//    unsigned int nbItems;
//    unsigned int nbMaxItems;
//    bool modification;
//    void addItem(T* item){
//        if (nbItems==nbMaxItems){
//            T** newtab=new T*[nbMaxItems+10];
//            for(unsigned int i=0; i<nbItems; i++) newtab[i]=items[i];
//            nbMaxItems+=10;
//            T** old=items;
//            items=newtab;
//            delete[] old;
//        }
//        items[nbItems++]=item;
//    }
//    BaseManager(const BaseManager& um);
//    BaseManager& operator=(const BaseManager& um);
//    ~BaseManager(){
//        for(unsigned int i=0; i<nbItems; i++) delete items[i];
//        delete[] items;
//    }

//public :
//    BaseManager():items(0),nbItems(0),nbMaxItems(0),modification(false){}

//    class Iterator {
//        friend class BaseManager;
//        T** currentItem;
//        unsigned int nbRemain;
//        Iterator(T** i, unsigned int nb):currentItem(i),nbRemain(nb){}
//    public:
//        Iterator():nbRemain(0),currentItem(0){}
//        bool isDone() const { return nbRemain==0; }
//        void next() {
//            if (isDone())
//                throw UTProfilerException("error, next on an iterator which is done");
//            nbRemain--;
//            currentItem++;
//        }
//        T& current() const {
//            if (isDone())
//                throw UTProfilerException("error, indirection on an iterator which is done");
//            return **currentItem;
//        }
//    };
//    Iterator getIterator() {
//        return Iterator(items,nbItems);
//    }

//    class iterator {
//        T** current;
//        iterator(T** u):current(u){}
//        friend class BaseManager;
//    public:
//        iterator():current(0){}
//        T& operator*() const { return **current; }
//        bool operator!=(iterator it) const { return current!=it.current; }
//        iterator& operator++(){ ++current; return *this; }
//    };
//    iterator begin() { return iterator(items); }
//    iterator end() { return iterator(items+nbItems); }
//};

//template<class T>
//class ManagerFile : public BaseManager <T>{
//protected:
//    QString file;
//    ManagerFile():file(""){}
//    ~ManagerFile(){
//        if (file!="") save(file);
//    }
//public:
//    virtual void save(const QString& f){throw UTProfilerException("This function should not be called");}//doit être redéfini en fonction de T
//};
