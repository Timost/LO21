#include "Categorie.h"
#include "templatemanager.h"

Categorie::Categorie(QString c,QString d,std::vector<Categorie>sc)
{
    TemplateManager<Categorie>& tCat=TemplateManager<Categorie>::getInstance();
   if(!tCat.alreadyExist(c))
    {
        code=c;
        description=d;
        sousCategorie=sc;
        tCat.New(*this);
    }
    else
    {
        throw CategorieException("Erreur : la categorie "+c.toStdString()+" existe deja !");
    }
}
Categorie::Categorie(std::string c,std::string d,std::vector<Categorie>sc)
{
    Categorie(QString::fromStdString(c),QString::fromStdString(d),sc);
}
Categorie::Categorie(const char* c,const char* d,std::vector<Categorie>sc)
{
    Categorie(std::string(c),std::string(d),sc);
}

Categorie::Categorie(QString c, QString d)
{
    TemplateManager<Categorie>& tCat=TemplateManager<Categorie>::getInstance();
   if(!tCat.alreadyExist(c))
    {
      // qDebug()<<"c :"<<c<<" d : "<<d;
        code=c;
        description=d;
        tCat.New(*this);
    }
    else
    {
        throw CategorieException("Erreur : la categorie "+c.toStdString()+" existe deja !");
    }
}

Categorie::Categorie(std::string c, std::string  d)
{
    Categorie(QString::fromStdString(c),QString::fromStdString(d));
}
Categorie::Categorie(const char* c, const char *d)
{
    Categorie(std::string(c),std::string(d));
}

bool Categorie::hasSousCategorie(Categorie c)
{
    typedef std::vector<Categorie>::iterator my_it;
    my_it begin=sousCategorie.begin();
    my_it end=sousCategorie.end();

    my_it res= std::find(begin,end, c);

    if(res==end)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Categorie::addSousCategorie(Categorie c)
{
    if(!hasSousCategorie(c))
    {
        sousCategorie.push_back(c);
    }
    else
    {
        throw CategorieException("Erreur addSousCategorie : La categorie :"+c.getCode().toStdString()+" Fait déjà partie des sous catégories de "+this->getCode().toStdString());
    }
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

std::vector<Categorie> getFullSousCat(QString c)
{//fonction recursive
    TemplateManager<Categorie>& tCat=TemplateManager<Categorie>::getInstance();
    if(!tCat.getElement(c).hasSousCategorie())//condition d'arrêt
    {
        return std::vector<Categorie>();
    }
    std::vector<Categorie> temp=tCat.getElement(c).getSousCategorie();
    std::vector<Categorie> res;

    std::vector<Categorie> temp3=tCat.getElement(c).getSousCategorie();
    res.insert( res.end(), temp3.begin(), temp3.end() );
    for(std::vector<Categorie>::iterator it=temp.begin();it!=temp.end();it++)
    {
        std::vector<Categorie> temp2=getFullSousCat(it->getCode());
        res.reserve( res.size() + temp2.size() );
        res.insert( res.end(), temp2.begin(), temp2.end() );
    }
    return res;
}

std::map<Categorie,std::vector<Categorie> > getCatsWithSousCat()
{
    TemplateManager<Categorie>& tCat=TemplateManager<Categorie>::getInstance();

    std::map<Categorie,std::vector<Categorie> > res;

    for(std::vector<Categorie>::iterator it=tCat.getIterator(); it!=tCat.end();it++)
    {
        std::vector<Categorie> temp=getFullSousCat(it->getCode());

        if(temp.size()>0)
        {
           res[*it]=temp;
        }
    }
    return res;
}

std::vector<Categorie> getCatsWithoutSousCat()
{
    TemplateManager<Categorie>& tCat=TemplateManager<Categorie>::getInstance();

    std::vector<Categorie> res;

    for(std::vector<Categorie>::iterator it=tCat.getIterator(); it!=tCat.end();it++)
    {


        if(!it->hasSousCategorie())
        {
           res.push_back(*it);
        }
    }
    return res;
}
QString getParentCat(QString c)
{
    TemplateManager<Categorie>& tCat=TemplateManager<Categorie>::getInstance();
    std::map<Categorie,std::vector<Categorie> > SousCatStruct = getCatsWithSousCat();
    QString res="";

    for(std::vector<Categorie>::iterator it= tCat.getIterator();it != tCat.end() ; it++)
    {
        std::vector<Categorie> t=it->getSousCategorie();
        std::vector<Categorie>::iterator temp = std::find(t.begin(),t.end(),tCat.getElement(c));
        if(temp!= t.end())
        {
            res= it->getCode();
            break;
        }
    }
    return res;
}
std::vector<Categorie> getOriginCat()
{
   std::vector<Categorie> res;
   TemplateManager<Categorie>& tCat=TemplateManager<Categorie>::getInstance();

   for(std::vector<Categorie>::iterator it=tCat.getIterator(); it!=tCat.end();it++)
   {
       if(getParentCat(it->getCode())=="")
       {
           if(std::find(res.begin(),res.end(),*it)==res.end())
           {
               res.push_back(*it);
           }
       }
       else
       {

           QString s = getParentCat(it->getCode());
           QString s2 = it->getCode();
           while(s!="")
           {
               s2=s;
               s=getParentCat(s);
           }

           if(std::find(res.begin(),res.end(),tCat.getElement(s2))==res.end())
           {
               res.push_back(tCat.getElement(s2));
           }
       }
   }
    return res;
}


bool operator<(const Categorie c1,const Categorie c2)
{
    return c1.getCode()<c2.getCode();
}

bool operator==(const Categorie c1, const Categorie c2)
{
    return c1.getCode()==c2.getCode();
}
