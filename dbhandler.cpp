#include "dbhandler.h"
#include <QDebug>
//initializing static instance
dbHandler *dbHandler::_instanceDB;

dbHandler *dbHandler::getDataBaseInstance()
{
    if(! _instanceDB) _instanceDB = new dbHandler;
    return _instanceDB;
}

const QSqlDatabase &dbHandler::getDB() const
{
    return db;
}

void dbHandler::initDB(const QString &driverName)
{
    db = QSqlDatabase::addDatabase(driverName);
    //verifying driver is loaded
    if(! db.isValid()) qDebug()<< db.lastError();

    else qDebug()<<"driver is loaded successfull !";
}

void dbHandler::setDBName(const QString &dbName)
{
    db.setDatabaseName(dbName);
}

bool dbHandler::openDB()
{
    if(! db.open()) {
        qDebug()<< db.lastError();
        return false;
    }
    return true;
}

dbHandler::dbHandler(QObject *parent) : QObject(parent){/*constructor*/}
