#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <QObject>
#include <QSqlError>
#include <QSqlDatabase>

class dbHandler : public QObject
{
    Q_OBJECT
public:
    //singleton method
    static dbHandler *getDataBaseInstance();
    //get instance of QSqlDatabase
    const QSqlDatabase& getDB() const;
    //init db method
    void initDB(const QString &driverName);
    //set db name method
    void setDBName(const QString&);
    //is open or valid db method
    bool openDB();

private:
    //singleton instance
    static dbHandler *_instanceDB;
    //for db handler
    QSqlDatabase db;
    //making default, copy and assign constructor private to avoid instance
    explicit dbHandler(QObject *parent = nullptr);
    dbHandler(const dbHandler &instance);
    dbHandler& operator =(dbHandler &instance);
};

#endif // DBHANDLER_H
