#include "computerrepository.h"

ComputerRepository::ComputerRepository()
{
}

void ComputerRepository::openDatabase()
{
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
    if(order == "name")
    {
        query.exec("SELECT * FROM scientists ORDER BY Name");

        while(query.next()){ //fer aldrei herna inn!
            computer c = computer();
            c.name = query.value("Name").toString().toStdString();
            c.constructionYear = query.value("ConstructionYear").toString().toStdString();
            c.type = query.value("Type").toString().toStdString();
            c.constructed = query.value("Constructed").toString().toStdString();
            //s.computers = query.value("Computers").toString().toStdString();

            comp.push_back(c);
        }
    }
    else if(order == "construction year")
    {
        query.exec("SELECT * FROM scientists ORDER BY ConstructionYear");

        while(query.next()){ //fer aldrei herna inn!
            computer c = computer();
            c.name = query.value("Name").toString().toStdString();
            c.constructionYear = query.value("ConstructionYear").toString().toStdString();
            c.type = query.value("Type").toString().toStdString();
            c.constructed = query.value("Constructed").toString().toStdString();
            //s.computers = query.value("Computers").toString().toStdString();

            comp.push_back(c);
        }
    }
    else if(order == "type")
    {
        query.exec("SELECT * FROM scientists ORDER BY Type");

        while(query.next()){ //fer aldrei herna inn!
            computer c = computer();
            c.name = query.value("Name").toString().toStdString();
            c.constructionYear = query.value("ConstructionYear").toString().toStdString();
            c.type = query.value("Type").toString().toStdString();
            c.constructed = query.value("Constructed").toString().toStdString();
            //s.computers = query.value("Computers").toString().toStdString();

            comp.push_back(c);
        }
    }
    else if(order == "constructed")
        {
            query.exec("SELECT * FROM scientists ORDER BY Constructed");

            while(query.next()){ //fer aldrei herna inn!
                computer c = computer();
                c.name = query.value("Name").toString().toStdString();
                c.constructionYear = query.value("ConstructionYear").toString().toStdString();
                c.type = query.value("Type").toString().toStdString();
                c.constructed = query.value("Constructed").toString().toStdString();
                //s.computers = query.value("Computers").toString().toStdString();

                comp.push_back(c);
            }
        }
    else
        {
            exit(0);
        }

    return comp;
}
