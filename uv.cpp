#include "uv.h"



QTextStream& operator<<(QTextStream& f, const UV& uv){
    return f<<QString::fromStdString(uv.getCode())<<", "<<", "<<" credits, "<<QString::fromStdString(uv.getTitre());
}
std::ostream& operator<<(std::ostream& f, const UV& uv)
{
  return f<<uv.getCode()<<", "<<", "<<" credits, "<<uv.getTitre();
}
