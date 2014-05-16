#ifndef DATABASE_H
#define DATABASE_H
#include <QCoreApplication>
#include <QtSql>
#include <QString>
#include <string>
#include <iostream>
#include <QDebug>

#define q2c(string) string.toStdString()

using namespace std;

class Database
{
    static Database* handler;
    QSqlDatabase db;
    string databaseName;
    Database(string dbname);

    ~Database();
    bool open()
    {
        return this->db.open();
    }
    void close()
    {
        db.close();
    }
public:
    static Database& getInstance(string dbname="QSQLITE");
    void destroyInstance()
    {
        delete handler;
        handler=0;
    }
    QSqlQuery query(string q);

};

class DatabaseException : public std::exception
{
protected :
    std::string info;
public:
    DatabaseException(const std::string& i="") throw() :info(i) {}
    const char* what() const throw()
    {
        return info.c_str();
    }
    ~DatabaseException()throw() {}
};
#endif // DATABASE_H
