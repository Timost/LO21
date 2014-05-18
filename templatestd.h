#ifndef TEMPLATESTD_H
#define TEMPLATESTD_H
#include <string>
#include <sstream>
#include <iostream>

class TemplateStd
{
    int i;
public:
    TemplateStd(int t):i(t)
    {
    }

    std::string getStrLabel()
    {
        std::ostringstream convert;
        convert << i;
        return convert.str();
    }

    void display()
    {
        std::cout<<i;
    }
};

#endif // TEMPLATESTD_H
