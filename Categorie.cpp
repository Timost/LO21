#include "Categorie.h"
#include "templatemanager.h"

Categorie::Categorie(std::string c, std::string d)
{
    TemplateManager<Categorie>& tCat=TemplateManager<Categorie>::getInstance();
   if(!tCat.alreadyExist(c))
    {
        code=QString::fromStdString(c);
        description=QString::fromStdString(d);
        tCat.New(*this);
    }
    else
    {
        throw CategorieException("Erreur : la categorie "+c+" existe deja !");
    }
}
Categorie::Categorie(QString c, QString d)
{
    Categorie(c.toStdString(),d.toStdString());
}
Categorie::Categorie(const char* c, const char *d)
{
    Categorie(std::string(c),std::string(d));
}

Categorie StringToCategorie(const QString& str){//renvoie une référence vers la catégorie si elle existe, exception sinon.
   TemplateManager<Categorie>& tCat=TemplateManager<Categorie>::getInstance();

   if(tCat.alreadyExist(str))
   {
       return tCat.getElement(str);
   }
   else
   {
       throw CategorieException("Erreur la categorie "+str.toStdString()+" n'existe pas.");
   }
}

bool operator<(const Categorie c1,const Categorie c2)
{
    return c1.getCode()<c2.getCode();
}
