#include "computerrepository.h"

ComputerRepository::ComputerRepository() {
}

QSqlDatabase ComputerRepository::openDatabase() {

    QString connectionName = "DatabaseConnection";

    QSqlDatabase db;

    if(QSqlDatabase::contains("DatabaseConnection"))
    {
        db = QSqlDatabase::database("DatabaseConnection");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE", "DatabaseConnection");
        QString dbName = "science_db.sqlite";
        db.setDatabaseName(dbName);
        db.open();
    }
    return db;
}

std::list<computer> ComputerRepository::list() {

    std::list<computer> comp = std::list<computer>();

    computerDB = openDatabase();
    computerDB.open();
    QSqlQuery query(computerDB);

    computer c = computer();
    query.exec("SELECT * FROM Computers");

    while(query.next()){
        c.name = query.value("Name").toString().toStdString();
        c.constructionYear = query.value("ConstuctionYear").toString().toStdString();
        c.type = query.value("Type").toString().toStdString();
        c.constructed = query.value("Constructed").toString().toStdString();

        comp.push_back(c);
    }

    computerDB.close();

    return comp;
}

void ComputerRepository::add(computer comp) {

    computerDB = openDatabase();
    computerDB.open();
    QSqlQuery query(computerDB);

    query.prepare("INSERT INTO Computers (Name, ConstuctionYear, Type, Constructed)"
                  "VALUES(:name, :constructionYear, :type, :constructed)");
    query.bindValue(":name",        QString::fromStdString(comp.name));
    query.bindValue(":constructionYear", QString::fromStdString(comp.constructionYear));
    query.bindValue(":type", QString::fromStdString(comp.type));
    query.bindValue(":constructed",      QString::fromStdString(comp.constructed));

    query.exec();

    computerDB.close();

//     Replace our chosen delimiter with space to avoid breaking the delimited format of the file
//    std::replace(scientist.name.begin(),scientist.name.end(),delimiter,' ');
//    scientistList.push_back(scientist);
//    save();
}
std::list<computer> ComputerRepository::orderBy(std::string order) {

    std::list<computer> comp = std::list<computer>();

    computerDB = openDatabase();
    computerDB.open();
    QSqlQuery query(computerDB);

    computer c = computer();
    if(order == "name") {
        query.exec("SELECT * FROM Computers ORDER BY Name");

        while(query.next()){
            c.name = query.value("Name").toString().toStdString();
            c.constructionYear = query.value("ConstuctionYear").toString().toStdString();
            c.type = query.value("Type").toString().toStdString();
            c.constructed = query.value("Constructed").toString().toStdString();

            comp.push_back(c);
        }

        computerDB.close();

        return comp;
    } else if(order == "construction year") {
        query.exec("SELECT * FROM Computers ORDER BY ConstructionYear");

        while(query.next()){
            c.name = query.value("Name").toString().toStdString();
            c.constructionYear = query.value("ConstuctionYear").toString().toStdString();
            c.type = query.value("Type").toString().toStdString();
            c.constructed = query.value("Constructed").toString().toStdString();

            comp.push_back(c);
        }
        computerDB.close();

        return comp;
    } else if(order == "type") {
        query.exec("SELECT * FROM Computers ORDER BY Type");

        while(query.next()){
            c.name = query.value("Name").toString().toStdString();
            c.constructionYear = query.value("ConstuctionYear").toString().toStdString();
            c.type = query.value("Type").toString().toStdString();
            c.constructed = query.value("Constructed").toString().toStdString();

            comp.push_back(c);
        }
        computerDB.close();
        return comp;
    } else if(order == "constructed") {
        query.exec("SELECT * FROM Computers ORDER BY Constructed");

        while(query.next()) {
            c.name = query.value("Name").toString().toStdString();
            c.constructionYear = query.value("ConstuctionYear").toString().toStdString();
            c.type = query.value("Type").toString().toStdString();
            c.constructed = query.value("Constructed").toString().toStdString();

            comp.push_back(c);
            }

        computerDB.close();
        return comp;
        }
    else
        {
            computerDB.close();
            exit(0);
        }
}
std::list<computer> ComputerRepository::search(std::string searchField, std::string searchTerm) {
    std::list<computer> comp = std::list<computer>();
    computerDB = openDatabase();
    computerDB.open();
    QSqlQuery query(computerDB);
    computer c = computer();
    QString field = QString::fromStdString(searchField);
    QString term = QString::fromStdString(searchTerm);

    query.exec("SELECT * FROM Computers s WHERE s.\'" + field + "\' = \'" + term + "\'");

        while(query.next()){
            c.name = query.value("Name").toString().toStdString();
            c.constructionYear = query.value("ConstuctionYear").toString().toStdString();
            c.type = query.value("Type").toString().toStdString();
            c.constructed = query.value("Constructed").toString().toStdString();

            comp.push_back(c);
        }
    computerDB.close();

    return comp;
}
