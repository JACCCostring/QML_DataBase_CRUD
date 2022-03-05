#ifndef DATABASEMODEL_H
#define DATABASEMODEL_H

#include <QSqlQueryModel>
#include <QSqlQuery> //for QSqlQuery
#include <QSqlRecord> //for records
#include <QSqlResult>
#include <QSqlError> //for QSql Errs

class dataBaseModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    dataBaseModel(QObject *parent = nullptr);
    //method to refresh table
    Q_INVOKABLE void updateTable();
    //override methods because it subclass QSqlQueryModel
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    //overloaded methods to operate db insert, search, update and deletion
    Q_INVOKABLE bool dbOperations(int, const QString &, int, double, bool); //insert/update operations
    Q_INVOKABLE bool dbOperations(int, int, bool); //search/delete operations
    //method to load deta from UI on each clicked
    Q_INVOKABLE void loadRowData(int);

private:
    bool checkFieldContent(QVariant &) const;

signals:
    void rowLoaded(int id, const QString &name, int age, double salary);

private:
    const QString m_query = "SELECT * FROM people";
    const QString insertQuery = "INSERT INTO people (name, age, salary) VALUES(:name, :age, :salary)";
    const QString updateQuery = "UPDATE people SET name = :name, age = :age, salary = :salary WHERE id = :id";
    const QString loadRowQuery = "SELECT name, age, salary FROM people WHERE id = :id";
    const QString searchQuery = "SELECT * FROM people WHERE id = :id";
    const QString deleteQuery = "DELETE FROM people WHERE id = :id";
    enum qRoles{Id, Name, Age, Salary};
};

#endif // DATABASEMODEL_H
