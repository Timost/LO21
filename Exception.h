#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>

class UException{
public:
    UException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};
#endif // EXCEPTION_H
