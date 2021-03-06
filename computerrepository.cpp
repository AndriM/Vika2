#include "computerrepository.h"

ComputerRepository::ComputerRepository() {
}

QSqlDatabase ComputerRepository::openDatabase() {

    QString connectionName = "DatabaseConnection";
    QSqlDatabase db;

    if(QSqlDatabase::contains("DatabaseConnection")) //ef gagnagrunnurinn er nu tegar opinn tha viljum vid ekki opna hann aftur aftvi ad ta gaetum vid fengid duplicate connection.
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

    //tetta fall saekir gogn ur toflunni fyrir tolvur ur gagnagrunninum og setur thau i lista
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
    query.bindValue(":name",             QString::fromStdString(comp.name));
    query.bindValue(":constructionYear", QString::fromStdString(comp.constructionYear));
    query.bindValue(":type",             QString::fromStdString(comp.type));
    query.bindValue(":constructed",      QString::fromStdString(comp.constructed));

    query.exec();

    computerDB.close();
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
            c.name              = query.value("Name").toString().toStdString();
            c.constructionYear  = query.value("ConstuctionYear").toString().toStdString();
            c.type              = query.value("Type").toString().toStdString();
            c.constructed       = query.value("Constructed").toString().toStdString();

            comp.push_back(c);
        }

        computerDB.close();

        return comp;
    } else if(order == "construction year") {
        query.exec("SELECT * FROM Computers ORDER BY ConstructionYear");

        while(query.next()){
            c.name              = query.value("Name").toString().toStdString();
            c.constructionYear  = query.value("ConstuctionYear").toString().toStdString();
            c.type              = query.value("Type").toString().toStdString();
            c.constructed       = query.value("Constructed").toString().toStdString();

            comp.push_back(c);
        }
        computerDB.close();

        return comp;
    } else if(order == "type") {
        query.exec("SELECT * FROM Computers ORDER BY Type");

        while(query.next()){
            c.name              = query.value("Name").toString().toStdString();
            c.constructionYear  = query.value("ConstuctionYear").toString().toStdString();
            c.type              = query.value("Type").toString().toStdString();
            c.constructed       = query.value("Constructed").toString().toStdString();

            comp.push_back(c);
        }
        computerDB.close();
        return comp;
    } else if(order == "constructed") {
        query.exec("SELECT * FROM Computers ORDER BY Constructed");

        while(query.next()) {
            c.name              = query.value("Name").toString().toStdString();
            c.constructionYear  = query.value("ConstuctionYear").toString().toStdString();
            c.type              = query.value("Type").toString().toStdString();
            c.constructed       = query.value("Constructed").toString().toStdString();

            comp.push_back(c);
            }

        computerDB.close();
        return comp;
        }
       else {
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
            c.name              = query.value("Name").toString().toStdString();
            c.constructionYear  = query.value("ConstuctionYear").toString().toStdString();
            c.type              = query.value("Type").toString().toStdString();
            c.constructed       = query.value("Constructed").toString().toStdString();

            comp.push_back(c);
        }
    computerDB.close();

    return comp;
}

void ComputerRepository::connect(int cID, int sID) {

            computerDB = openDatabase();
            computerDB.open();
            QSqlQuery query(computerDB);

            query.exec(QString("INSERT INTO Joined (c_ID, s_ID) VALUES (%1,%2);")
                            .arg(cID)
                            .arg(sID));

           computerDB.close();
}


std::list<computer> ComputerRepository::listID() {

    std::list<computer> comp = std::list<computer>();

    computerDB = openDatabase();
    computerDB.open();
    QSqlQuery query(computerDB);

    computer c = computer();
    query.exec("SELECT * FROM Computers");

    while(query.next()){
        c.name = query.value("Name").toString().toStdString();
        c.ID = query.value("ID").toString().toStdString();

        comp.push_back(c);
    }

    computerDB.close();

    return comp;
}

std::list<computer> ComputerRepository::connectedComputers(int cID) {

    std::list<computer> comp = std::list<computer>();
    computer c = computer();
    computerDB = openDatabase();
    computerDB.open();
    QSqlQuery query(computerDB);
    QString c_ID = QString::number(cID);

    query.exec(QString("SELECT ID, Name FROM Computers JOIN Joined ON Joined.c_ID = Computers.ID WHERE Joined.s_ID = %1")
                      .arg(cID));

    while(query.next()){
        c.name                    = query.value("Name").toString().toStdString();

        comp.push_back(c);
    }
        computerDB.close();

    return comp;
}
