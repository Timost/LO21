#ifndef OPERANDE_H
#define OPERANDE_H
#include  <QString>
#include <string>
class Operande
{
private :
    QString symbol;
public:
    Operande(QString s):symbol(s){}
    Operande(std::string s){Operande(QString::fromStdString(s));}
    Operande(const char* s){Operande(std::string(s));}
}

#endif // OPERANDE_H
