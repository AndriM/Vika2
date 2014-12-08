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
            //scientist.computers = fields.at(4);
            scientistList.push_back(scientist);
        }
        scientistFile.close();
    }
}

ScientistRepository::~ScientistRepository() {
}

//void ScientistRepository::openDatabase() {
QSqlDatabase ScientistRepository::openDatabase() {

    QString connectionName = "DatabaseConnection";

    QSqlDatabase db;

    if(QSqlDatabase::contains(connectionName))
    {
        db = QSqlDatabase::database(connectionName);
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
        QString dbName = "science_db.sqlite";
        db.setDatabaseName(dbName);

        db.open();
    }

    return db;

    /*QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbName = "science_db.sqlite";
    db.setDatabaseName(dbName);
    db.open();*/
}

void ScientistRepository::add(Scientist scientist) {
    openDatabase();
    QSqlQuery query;

    query.prepare("INSERT INTO scientists (Name, BirthYear, DeathYear, Gender)"
                  "VALUES(:name, :dateOfBirth, :dateOfDeath, :gender)");
    query.bindValue(":name",        QString::fromStdString(scientist.name));
    query.bindValue(":dateOfBirth", QString::fromStdString(scientist.dateOfBirth));
    query.bindValue(":dateOfDeath", QString::fromStdString(scientist.dateOfDeath));
    query.bindValue(":gender",      QString::fromStdString(scientist.gender));
    //query.bindValue(":computers",   QString::fromStdString(scientist.computers));

    query.exec();
//     Replace our chosen delimiter with space to avoid breaking the delimited format of the file
//    std::replace(scientist.name.begin(),scientist.name.end(),delimiter,' ');
//    scientistList.push_back(scientist);
//    save();
}

std::list<Scientist> ScientistRepository::list() {

    std::list<Scientist> scientist = std::list<Scientist>();
    openDatabase();
    QSqlQuery query;
    Scientist s = Scientist();
    query.exec("SELECT * FROM scientists");

    while(query.next()){
        s.name = query.value("Name").toString().toStdString();
        s.gender = query.value("Gender").toString().toStdString();
        s.dateOfBirth = query.value("BirthYear").toString().toStdString();
        s.dateOfDeath = query.value("DeathYear").toString().toStdString();
        //s.computers = query.value("Computers").toString().toStdString();

        scientist.push_back(s);
    }
    return scientist;
}

std::list<Scientist> ScientistRepository::orderBy(std::string order) {

    std::list<Scientist> scientist = std::list<Scientist>();
    openDatabase();
    QSqlQuery query;
    Scientist s = Scientist();
    if(order == "name") {
        query.exec("SELECT * FROM scientists ORDER BY Name");

        while(query.next()){
            s.name = query.value("Name").toString().toStdString();
            s.gender = query.value("Gender").toString().toStdString();
            s.dateOfBirth = query.value("BirthYear").toString().toStdString();
            s.dateOfDeath = query.value("DeathYear").toString().toStdString();
            //s.computers = query.value("Computers").toString().toStdString();

            scientist.push_back(s);
        }
        return scientist;
    }
    else if(order == "dob") {
        query.exec("SELECT * FROM scientists ORDER BY BirthYear");

        while(query.next()){
            s.name = query.value("Name").toString().toStdString();
            s.gender = query.value("Gender").toString().toStdString();
            s.dateOfBirth = query.value("BirthYear").toString().toStdString();
            s.dateOfDeath = query.value("DeathYear").toString().toStdString();
            //s.computers = query.value("Computers").toString().toStdString();

            scientist.push_back(s);
        }
        return scientist;
    }
    else if(order == "dod") {
        query.exec("SELECT * FROM scientists ORDER BY DeathYear");

        while(query.next()){
            s.name = query.value("Name").toString().toStdString();
            s.gender = query.value("Gender").toString().toStdString();
            s.dateOfBirth = query.value("BirthYear").toString().toStdString();
            s.dateOfDeath = query.value("DeathYear").toString().toStdString();
            //s.computers = query.value("Computers").toString().toStdString();

            scientist.push_back(s);
       }
        return scientist;
    }
    else if(order == "gender") {
        query.exec("SELECT * FROM scientists ORDER BY Gender");

        while(query.next()){
            s.name = query.value("Name").toString().toStdString();
            s.gender = query.value("Gender").toString().toStdString();
            s.dateOfBirth = query.value("BirthYear").toString().toStdString();
            s.dateOfDeath = query.value("DeathYear").toString().toStdString();
            //s.computers = query.value("Computers").toString().toStdString();

            scientist.push_back(s);
        }
        return scientist;
    }
    else {
        exit(0);
    }
}
std::list<Scientist> ScientistRepository::list(std::string col, std::string mod) {
    std::list<Scientist> outList = std::list<Scientist>();
    outList = deepCopy();
    Comparer comp = Comparer(col,mod);
    outList.sort(comp);
    return outList;
}

std::list<Scientist> ScientistRepository::deepCopy() {
    std::list<Scientist> outList = std::list<Scientist>();
    for(std::list<Scientist>::iterator iter = scientistList.begin(); iter != scientistList.end(); iter++) {
        outList.push_back(Scientist(*iter));
    }
    return outList;
}

void ScientistRepository::save() {
    std::ofstream scientistFile;
    scientistFile.open(filename.c_str());

    if(!scientistFile.is_open()) {
        throw std::runtime_error("Failed to open " + filename);
    }

    for(std::list<Scientist>::iterator iter = scientistList.begin(); iter != scientistList.end(); iter++) {
        scientistFile << (*iter).name << delimiter << (*iter).dateOfBirth << delimiter << (*iter).dateOfDeath << delimiter << (*iter).gender << std::endl;
    }
    scientistFile.flush();
    scientistFile.close();
}

//Scientist* ScientistRepository::search(std::string searchTerm) {
//    // Naive search implementation, finds the case sensitive substring in the name and returns first match
//    for(std::list<Scientist>::iterator iter = scientistList.begin(); iter != scientistList.end(); iter++) {
//        if(iter->name.find(searchTerm) != std::string::npos) {
//            return new Scientist(*iter);
//        }
//    }
//    return NULL;
//}

std::list<Scientist> ScientistRepository::search(std::string searchTerm) {
    std::list<Scientist> scientist = std::list<Scientist>();
    openDatabase();
    QSqlQuery query;
    Scientist s = Scientist();
    QString qstr = QString::fromStdString(searchTerm);
        query.exec("SELECT * FROM scientists s WHERE s.Name = \'" + qstr + "\'");

        while(query.next()){
            s.name = query.value("Name").toString().toStdString();
            s.gender = query.value("Gender").toString().toStdString();
            s.dateOfBirth = query.value("BirthYear").toString().toStdString();
            s.dateOfDeath = query.value("DeathYear").toString().toStdString();
            //s.computers = query.value("Computers").toString().toStdString();

            scientist.push_back(s);
        }
    return scientist;
}
