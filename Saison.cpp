#include "Saison.h"


Saison::Saison(std::string n, std::string d)
{
    TemplateManager<Saison>& tSaison=TemplateManager<Saison>::getInstance();
   if(!tSaison.alreadyExist(n))
    {
        nom=QString::fromStdString(n);
        description=QString::fromStdString(d);
        tSaison.New(*this);
    }
    else
    {
        throw SaisonException("Erreur : la saison "+n+" existe deja !");
    }
}
Saison::Saison(QString n, QString d)
{
    Saison(n.toStdString(),d.toStdString());
}
Saison::Saison(const char* n, const char *d)
{
    Saison(std::string(n),std::string(d));
}

Saison StringToSaison(const QString& str){//renvoie une référence vers la catégorie si elle existe, exception sinon.
    TemplateManager<Saison>& tSaison=TemplateManager<Saison>::getInstance();
   if(tSaison.alreadyExist(str))
   {
       return tSaison.getElement(str);
   }
   else
   {
       throw SaisonException("Erreur la categorie "+str.toStdString()+" n'existe pas.");
   }
}

bool operator ==(Saison s1,Saison s2)
{
    return (s1.getNom()==s2.getNom());
}
bool operator >(Saison s1,Saison s2)
{
    if((s1.getNom()=="Automne")&&(s2.getNom()=="Printemps"))
    {
        return true;
    }
    else
    {
        return false;
    }
}

