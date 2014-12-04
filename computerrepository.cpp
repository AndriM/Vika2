#include "computerrepository.h"

/*    string name;
    string constructionYear;
    string type;
    bool constructed;*/

ComputerRepository::ComputerRepository(std::string fname) {
    filename = fname;
    delimiter = '\t';
    std::ifstream computerFile;

    try {
        computerFile.open(filename.c_str(),std::ios::in);
    } catch(...) {
        // Ignore the error, the file is non existent and will be created next time we save.
    }

    computerList = std::list<computer>();

    if(computerFile.is_open()) {
        std::string lineToRead = "";

        // Load all records into memory
        while(std::getline(computerFile,lineToRead)) {
            computer cpu = computer();
            std::vector<std::string> fields = util::split(lineToRead,delimiter);
            cpu.name = fields.at(0);
            cpu.constructionYear = fields.at(1);
            cpu.type = fields.at(2);
            cpu.constructed = fields.at(3);
            computerList.push_back(cpu);
        }
        computerFile.close();
    }
}

ComputerRepository::~ComputerRepository() {
}

void ComputerRepository::add(computer cpu) {
    // Replace our chosen delimiter with space to avoid breaking the delimited format of the file
    std::replace(cpu.name.begin(),cpu.name.end(),delimiter,' ');
    computerList.push_back(cpu);
    save();
}


std::list<computer> ComputerRepository::list() {
    return deepCopy();
}

std::list<computer> ComputerRepository::list(std::string col, std::string mod) {
    std::list<computer> outList = std::list<computer>();
    outList = deepCopy();
    Comparer comp = Comparer(col,mod);
    outList.sort(comp);
    return outList;
}

std::list<computer> ComputerRepository::deepCopy() {
    std::list<computer> outList = std::list<computer>();
    for(std::list<computer>::iterator iter = computerList.begin(); iter != computerList.end(); iter++) {
        outList.push_back(computer(*iter));
    }
    return outList;
}

void ComputerRepository::save() {
    std::ofstream computerFile;
    computerFile.open(filename.c_str());

    if(!computerFile.is_open()) {
        throw std::runtime_error("Failed to open " + filename);
    }

    for(std::list<computer>::iterator iter = computerList.begin(); iter != computerList.end(); iter++) {
        computerFile << (*iter).name << delimiter << (*iter).constructionYear << delimiter << (*iter).type << delimiter << (*iter).constructed << std::endl;
    }
    computerFile.flush();
    computerFile.close();
}

computer* ComputerRepository::search(std::string searchTerm) {
    // Naive search implementation, finds the case sensitive substring in the name and returns first match
    for(std::list<computer>::iterator iter = computerList.begin(); iter != computerList.end(); iter++) {
        if(iter->name.find(searchTerm) != std::string::npos) {
            return new computer(*iter);
        }
    }
    return NULL;
}
