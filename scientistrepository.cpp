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
            scientist.computers = fields.at(4);
            scientistList.push_back(scientist);
        }
        scientistFile.close();
    }
}

ScientistRepository::~ScientistRepository() {
}

void ScientistRepository::add(Scientist scientist) {
    QSqlQuery query;

    query.prepare("INSERT INTO scientists (Name, Gender, BirthYear, DeathYear, Computers)"
                  "VALUES(:name, :dateOfBirth, :dateOfDeath, :gender, :computers)");
    query.bindValue(":name",        QString::fromStdString(scientist.name));
    query.bindValue(":dateOfBirth", QString::fromStdString(scientist.dateOfBirth));
    query.bindValue(":dateOfDeath", QString::fromStdString(scientist.dateOfDeath));
    query.bindValue(":gender",      QString::fromStdString(scientist.gender));
    query.bindValue(":computers",   QString::fromStdString(scientist.computers));

    query.exec();
//     Replace our chosen delimiter with space to avoid breaking the delimited format of the file
//    std::replace(scientist.name.begin(),scientist.name.end(),delimiter,' ');
//    scientistList.push_back(scientist);
//    save();
}


std::list<Scientist> ScientistRepository::list() {
    std::list<Scientist> scientist = std::list<Scientist>();


    QSqlQuery query;
    query.exec("SELECT * FROM scientists");

    query.exec("SELECT c.Name, j.c_ID AS 'ComputerID', j.s_ID AS 'ScientistID, FROM computers"
               "INNER JOIN Joined j"
               "ON j.c_ID = c.ID");
    while(query.next()){
        Scientist s = Scientist();
        s.name = query.value("Name").toString().toStdString();
        s.gender = query.value("Gender").toString().toStdString();
        s.dateOfBirth = query.value("BirthYear").toString().toStdString();
        s.dateOfDeath = query.value("DeathYear").toString().toStdString();
        s.computers = query.value("Computers").toString().toStdString();

        scientist.push_back(s);

    }
    return scientist;
}

std::list<Scientist> ScientistRepository::list(std::string col, std::string mod) {
    std::list<Scientist> outList = std::list<Scientist>();
    outList = deepCopy();
    Comparer comp = Comparer(col,mod);
    outList.sort(comp);
    return outList;
}
void ScientistRepository::openDatabase()
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbName = "science_db.sqlite";
    db.setDatabaseName(dbName);
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
        scientistFile << (*iter).name << delimiter << (*iter).dateOfBirth << delimiter << (*iter).dateOfDeath << delimiter << (*iter).gender << delimiter << (*iter).computers << std::endl;
    }
    scientistFile.flush();
    scientistFile.close();
}

Scientist* ScientistRepository::search(std::string searchTerm) {
    // Naive search implementation, finds the case sensitive substring in the name and returns first match
    for(std::list<Scientist>::iterator iter = scientistList.begin(); iter != scientistList.end(); iter++) {
        if(iter->name.find(searchTerm) != std::string::npos) {
            return new Scientist(*iter);
        }
    }
    return NULL;
}
