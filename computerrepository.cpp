#include "computerrepository.h"

ComputerRepository::ComputerRepository() {
}

void ComputerRepository::openDatabase() {
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbName = "science_db.sqlite";
    db.setDatabaseName(dbName);
    db.open();
}

void ComputerRepository::add(computer comp) {
    openDatabase();
    QSqlQuery query;
    query.prepare("INSERT INTO Computers (Name, ConstuctionYear, Type, Constructed)"
                  "VALUES(:name, :constructionYear, :type, :constructed)");
    query.bindValue(":name",        QString::fromStdString(comp.name));
    query.bindValue(":constructionYear", QString::fromStdString(comp.constructionYear));
    query.bindValue(":type", QString::fromStdString(comp.type));
    query.bindValue(":constructed",      QString::fromStdString(comp.constructed));

    query.exec();
//     Replace our chosen delimiter with space to avoid breaking the delimited format of the file
//    std::replace(scientist.name.begin(),scientist.name.end(),delimiter,' ');
//    scientistList.push_back(scientist);
//    save();
}
std::list<computer> ComputerRepository::orderBy(std::string order) {

    std::list<computer> comp = std::list<computer>();
    openDatabase();
    QSqlQuery query;
    computer c = computer();
    if(order == "name") {
        query.exec("SELECT * FROM Computers ORDER BY Name");

        while(query.next()){
            c.name = query.value("Name").toString().toStdString();
            c.constructionYear = query.value("ConstuctionYear").toString().toStdString();
            c.type = query.value("Type").toString().toStdString();
            c.constructed = query.value("Constructed").toString().toStdString();
            //s.computers = query.value("Computers").toString().toStdString();

            comp.push_back(c);
        }
        return comp;
    } else if(order == "construction year") {
        query.exec("SELECT * FROM Computers ORDER BY ConstructionYear");

        while(query.next()){
            c.name = query.value("Name").toString().toStdString();
            c.constructionYear = query.value("ConstuctionYear").toString().toStdString();
            c.type = query.value("Type").toString().toStdString();
            c.constructed = query.value("Constructed").toString().toStdString();
            //s.computers = query.value("Computers").toString().toStdString();

            comp.push_back(c);
        }
        return comp;
    } else if(order == "type") {
        query.exec("SELECT * FROM Computers ORDER BY Type");

        while(query.next()){
            c.name = query.value("Name").toString().toStdString();
            c.constructionYear = query.value("ConstuctionYear").toString().toStdString();
            c.type = query.value("Type").toString().toStdString();
            c.constructed = query.value("Constructed").toString().toStdString();
            //s.computers = query.value("Computers").toString().toStdString();

            comp.push_back(c);
        }
        return comp;
    } else if(order == "constructed") {
        query.exec("SELECT * FROM Computers ORDER BY Constructed");

        while(query.next()) {
            c.name = query.value("Name").toString().toStdString();
            c.constructionYear = query.value("ConstuctionYear").toString().toStdString();
            c.type = query.value("Type").toString().toStdString();
            c.constructed = query.value("Constructed").toString().toStdString();
            //s.computers = query.value("Computers").toString().toStdString();

            comp.push_back(c);
            }
            return comp;
        }
    else
        {
            exit(0);
        }
}
