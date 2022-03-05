#include "databasemodel.h"
#include <QDebug>

dataBaseModel::dataBaseModel(QObject *parent): QSqlQueryModel(parent)
{
    //updating table to show data when program is loaded
    updateTable();
}

void dataBaseModel::updateTable()
{
    setQuery(m_query);

    if(lastError().isValid())
        qDebug()<<lastError().text();
}

QVariant dataBaseModel::data(const QModelIndex &index, int role) const
{
    if(! index.isValid()) return QVariant();
    //verfying roles
    switch(role)
    {
    case Id: //if role is one of those then
    case Name:
    case Age:
    case Salary:
        //retrieving index
        QModelIndex idx = index.model()->index(index.row(), role);
        //retrieving data from index
        QVariant dbData = QSqlQueryModel::data(idx, Qt::DisplayRole);
        //returning data
        return dbData;
    }
    //if non of the above return empty QVariant
    return QVariant();
}

QHash<int, QByteArray> dataBaseModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    //adding roles
    roles.insert(qRoles::Id, "id");
    roles.insert(qRoles::Name, "name");
    roles.insert(qRoles::Age, "age");
    roles.insert(qRoles::Salary, "salary");
    //returning roles
    return roles;
}

bool dataBaseModel::dbOperations(int uiRow, const QString &_name, int _age, double _salary, bool _option)
{
    //insert or  update
    QSqlQuery query; //for query later on
    bool added = false;
    //retrieving index in column 0 of UI. column 0 = ID
    QModelIndex idx = QSqlQueryModel::index(uiRow, 0);
    //retrieving data fron UI at index idx
    int uiId = QSqlQueryModel::data(idx).toInt();
    //verifying if it is insert/update option _option = true then update
    //if true then                             _option = false then insert
    if(_option){
        query.prepare(updateQuery);
        //binding values
        query.bindValue(":name", _name);
        query.bindValue(":age", _age);
        query.bindValue(":salary", _salary);
        query.bindValue(":id", uiId);
        //executing query and if changes were made then return true
        added = query.exec();
        //update QSqlQueryModel results
        updateTable();
        return added;
    }
    //preparing query for insert/update
    query.prepare(insertQuery);
    //binding values
    query.bindValue(":name", _name);
    query.bindValue(":age", _age);
    query.bindValue(":salary", _salary);
    //executing query and if changes were made then return true
    added = query.exec();
    //update QSqlQueryModel results
    updateTable();
    return added;
}

bool dataBaseModel::dbOperations(int uiRow, int id, bool _option)
{
    //search or delete
    QSqlQuery query; //for query later on
    bool added = false;
    //retrieving index in column 0 of UI. column 0 = ID
    QModelIndex idx = QSqlQueryModel::index(uiRow, 0);
    //retrieving data fron UI at index idx
    int uiId = QSqlQueryModel::data(idx).toInt();
    //verifying if it is insert/update option _option = true then update
    //if true then                             _option = false then insert
    if(_option){
        //search
        QString q = tr("SELECT * FROM people WHERE id = %1").arg(QString::number(id));
        setQuery(q);
        return true;
    }
    //preparing query for deletion
    query.prepare(deleteQuery);
    //binding values
    query.bindValue(":id", uiId);
    //executing query and if changes were made then return true
    added = query.exec();
    //update QSqlQueryModel results
    updateTable();
    return added;
}

void dataBaseModel::loadRowData(int uiRow)
{
    //retrieving index for column 0 = ID in the UI.
    QModelIndex idxId = QSqlQueryModel::index(uiRow, 0);
    //retrieving index for column 1 = NAME in the UI.
    QModelIndex idxName = QSqlQueryModel::index(uiRow, 1);
    //retrieving index for column 2 = AGE in the UI.
    QModelIndex idxAge = QSqlQueryModel::index(uiRow, 2);
    //retrieving index for column 3 = SALARY in the UI.
    QModelIndex idxSalary = QSqlQueryModel::index(uiRow, 3);
    //retrieving data from UI
    QString name = QSqlQueryModel::data(idxName).toString();
    double salary = QSqlQueryModel::data(idxSalary).toDouble();
    int age = QSqlQueryModel::data(idxAge).toInt();
    int id = QSqlQueryModel::data(idxId).toInt();
    //emiting signal to UI
    emit rowLoaded(id, name, age, salary);
}
