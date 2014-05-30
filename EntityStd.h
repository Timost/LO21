#ifndef TEMPLATESTD_H
#define TEMPLATESTD_H
#include <string>
#include <sstream>
#include <iostream>

class EntityStd
{
public:
    EntityStd(){}
    virtual ~EntityStd(){}
    virtual std::string getStrLabel() const =0;
};

#endif // TEMPLATESTD_H
