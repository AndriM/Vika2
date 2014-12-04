#include "sql.h"

SQL::SQL()
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbName = "science_db.sqlite";
    db.setDatabaseName(dbName);
}
