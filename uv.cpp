#include "uv.h"
#include "templatemanager.h"
UV::UV(std::string c, std::string t, std::map<Categorie, unsigned int> cre, bool a, bool p)
{
    TemplateManager<UV>& tUV=TemplateManager<UV>::getInstance();
    if(!tUV.alreadyExist(c))
    {
        code=c;
        titre=t;
        credits=cre;
        automne=a;
        printemps=p;
        tUV.New(*this);
    }
    else
    {
        throw UvException("Erreur : l'UV ' "+c+" existe deja !");
    }
}

UV::UV(QString c, QString t, std::map<Categorie, unsigned int> cre, bool a, bool p)
{
    UV(c.toStdString(),t.toStdString(),cre,a,p);
}

UV::UV(const char* c,const char*t, std::map<Categorie, unsigned int> cre, bool a, bool p)
{
    UV(std::string(c),std::string(t),cre,a,p);
}

void UV::setCode(std::string c)
{
    TemplateManager<UV>& tUV=TemplateManager<UV>::getInstance();
    if(!tUV.alreadyExist(c) || tUV.getElement(c)==*this)
    {
        tUV.erase(*this);
        code=c;
        tUV.New(*this);
    }
    else
    {
        throw UvException("Erreur : l'UV ' "+c+" existe deja !");
    }
}

UV StringToUV(const QString& str){//renvoie une référence vers la catégorie si elle existe, exception sinon.
   TemplateManager<UV>& tUV=TemplateManager<UV>::getInstance();

   if(tUV.alreadyExist(str))
   {
       return tUV.getElement(str);
   }
   else
   {
       throw UvException("Erreur StringToUV l'uv "+str.toStdString()+" n'existe pas.");
   }
}




QTextStream& operator<<(QTextStream& f, const UV& uv){
    return f<<QString::fromStdString(uv.getCode())<<", "<<", "<<" credits, "<<QString::fromStdString(uv.getTitre());
}
std::ostream& operator<<(std::ostream& f, const UV& uv)
{
  return f<<uv.getCode()<<", "<<", "<<" credits, "<<uv.getTitre();
}
