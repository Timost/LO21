#include "uv.h"
#include "templatemanager.h"
#include "Etudiant.h"
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

void UV::destroy()
{
    TemplateManager<UV>& tUV=TemplateManager<UV>::getInstance();
    TemplateManager<Etudiant>& tEtudiant=TemplateManager<Etudiant>::getInstance();
     if(tEtudiant.size()>0)//pour chaque étudiant, on enlève les isncriptions
     {
         for(std::vector<Etudiant>::iterator it = tEtudiant.getIterator();it!=tEtudiant.end();it++)//on supprime toutes les uvs de cette catégorie
         {
             Dossier dos=it->getDossier();
             std::vector<Inscription> inscr = dos.getInscription();
             for(std::vector<Inscription>::iterator it2= inscr.begin();it2 != inscr.end();it2++)
             {
                 if(it2->getUV()==*this)
                 {
                     dos.deleteInscription(*it2);
                     it->setDossier(dos);
                 }
             }
         }
     }
}


QTextStream& operator<<(QTextStream& f, const UV& uv){
    return f<<QString::fromStdString(uv.getCode())<<", "<<", "<<" credits, "<<QString::fromStdString(uv.getTitre());
}
std::ostream& operator<<(std::ostream& f, const UV& uv)
{
  return f<<uv.getCode()<<", "<<", "<<" credits, "<<uv.getTitre();
}
