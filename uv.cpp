#include "uv.h"

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
