#include "scientistrepository.h"

ScientistRepository::ScientistRepository(std::string fname) {
    filename = fname;
    delimiter = '\t';
    std::ifstream scientistFile;

    try {
        scientistFile.open(filename.c_str(),std::ios::in);
    } catch(...) {
        // Ignore the error, the file is non existent and will be created next time we save.
    }

    scientistList = std::list<Scientist>();

    if(scientistFile.is_open()) {
        std::string lineToRead = "";

        // Load all records into memory
        while(std::getline(scientistFile,lineToRead)) {
            Scientist scientist = Scientist();
            std::vector<std::string> fields = util::split(lineToRead,delimiter);
            scientist.name = fields.at(0);
            scientist.dateOfBirth = fields.at(1);
            scientist.dateOfDeath = fields.at(2);
            scientist.gender = fields.at(3);

            scientistList.push_back(scientist);
        }
        scientistFile.close();
    }
}
ScientistRepository::~ScientistRepository() {
}
QSqlDatabase ScientistRepository::openDatabase() {
    QString connectionName = "DatabaseConnection";
    QSqlDatabase db;

    if(QSqlDatabase::contains("DatabaseConnection")) {
        db = QSqlDatabase::database("DatabaseConnection");
    }
    else {
        db = QSqlDatabase::addDatabase("QSQLITE", "DatabaseConnection");
        QString dbName = "science_db.sqlite";
        db.setDatabaseName(dbName);
        db.open();
    }
    return db;
}

void ScientistRepository::connect(int sID, int cID)
{
    //connecta i toflunum
}
void ScientistRepository::add(Scientist scientist) {

    scientistDB = openDatabase();
    scientistDB.open();
    QSqlQuery query(scientistDB);

    query.prepare("INSERT INTO scientists (Name, BirthYear, DeathYear, Gender)"
                  "VALUES(:name, :dateOfBirth, :dateOfDeath, :gender)");
    query.bindValue(":name",        QString::fromStdString(scientist.name));
    query.bindValue(":dateOfBirth", QString::fromStdString(scientist.dateOfBirth));
    query.bindValue(":dateOfDeath", QString::fromStdString(scientist.dateOfDeath));
    query.bindValue(":gender",      QString::fromStdString(scientist.gender));

    query.exec();
    scientistDB.close();

//     Replace our chosen delimiter with space to avoid breaking the delimited format of the file
//    std::replace(scientist.name.begin(),scientist.name.end(),delimiter,' ');
//    scientistList.push_back(scientist);
//    save();
}
std::list<Scientist> ScientistRepository::list() {
    std::list<Scientist> scientist = std::list<Scientist>();

    scientistDB = openDatabase();
    scientistDB.open();
    QSqlQuery query(scientistDB);

    Scientist s = Scientist();
    query.exec("SELECT * FROM scientists");

    while(query.next()){
        s.name          = query.value("Name").toString().toStdString();
        s.gender        = query.value("Gender").toString().toStdString();
        s.dateOfBirth   = query.value("BirthYear").toString().toStdString();
        s.dateOfDeath   = query.value("DeathYear").toString().toStdString();

        scientist.push_back(s);
    }
    scientistDB.close();

    return scientist;
}
std::list<Scientist> ScientistRepository::orderBy(std::string order) {
    std::list<Scientist> scientist = std::list<Scientist>();

    scientistDB = openDatabase();
    scientistDB.open();
    QSqlQuery query(scientistDB);

    Scientist s = Scientist();
    if(order == "name") {
        query.exec("SELECT * FROM scientists ORDER BY Name");

        while(query.next()){
            s.name          = query.value("Name").toString().toStdString();
            s.gender        = query.value("Gender").toString().toStdString();
            s.dateOfBirth   = query.value("BirthYear").toString().toStdString();
            s.dateOfDeath   = query.value("DeathYear").toString().toStdString();

            scientist.push_back(s);
        }
        scientistDB.close();

        return scientist;
    }
    else if(order == "dob") {
        query.exec("SELECT * FROM scientists ORDER BY BirthYear");

        while(query.next()){
            s.name          = query.value("Name").toString().toStdString();
            s.gender        = query.value("Gender").toString().toStdString();
            s.dateOfBirth   = query.value("BirthYear").toString().toStdString();
            s.dateOfDeath   = query.value("DeathYear").toString().toStdString();

            scientist.push_back(s);
        }
        scientistDB.close();

        return scientist;
    }
    else if(order == "dod") {
        query.exec("SELECT * FROM scientists ORDER BY DeathYear");

        while(query.next()){
            s.name          = query.value("Name").toString().toStdString();
            s.gender        = query.value("Gender").toString().toStdString();
            s.dateOfBirth   = query.value("BirthYear").toString().toStdString();
            s.dateOfDeath   = query.value("DeathYear").toString().toStdString();

            scientist.push_back(s);
       }

        scientistDB.close();

        return scientist;
    }
    else if(order == "gender") {
        query.exec("SELECT * FROM scientists ORDER BY Gender");

        while(query.next()){
            s.name          = query.value("Name").toString().toStdString();
            s.gender        = query.value("Gender").toString().toStdString();
            s.dateOfBirth   = query.value("BirthYear").toString().toStdString();
            s.dateOfDeath   = query.value("DeathYear").toString().toStdString();

            scientist.push_back(s);
        }
        scientistDB.close();

        return scientist;
    }
    else {
        scientistDB.close();
        exit(0);
    }
}
std::list<Scientist> ScientistRepository::search(std::string searchField, std::string searchTerm) {
    std::list<Scientist> scientist = std::list<Scientist>();
    scientistDB = openDatabase();
    scientistDB.open();
    QSqlQuery query(scientistDB);
    Scientist s = Scientist();
    QString field = QString::fromStdString(searchField);
    QString term = QString::fromStdString(searchTerm);

    query.exec("SELECT * FROM scientists s WHERE s.\'" + field + "\' = \'" + term + "\'");

        while(query.next()){
            s.name          = query.value("Name").toString().toStdString();
            s.gender        = query.value("Gender").toString().toStdString();
            s.dateOfBirth   = query.value("BirthYear").toString().toStdString();
            s.dateOfDeath   = query.value("DeathYear").toString().toStdString();
            //s.computers = query.value("Computers").toString().toStdString();

            scientist.push_back(s);
        }
    scientistDB.close();

    return scientist;
}
