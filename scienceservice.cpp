#include "scienceservice.h"

ScienceService::ScienceService() {
    scientistRepository = ScientistRepository();
}

ScienceService::~ScienceService() {
}

void ScienceService::addScientist(Scientist scientist) {
    scientistRepository.add(scientist);
}

void ScienceService::addComputer(computer comp) {
    computerRepository.add(comp);
}

std::list<Scientist> ScienceService::orderScientists(std::string orderby) {
    return scientistRepository.orderBy(orderby);
}

std::list<computer> ScienceService::orderComputers(std::string orderby) {
    return computerRepository.orderBy(orderby);
}

std::list<Scientist> ScienceService::getAllScientists() {
    std::list<Scientist> l = scientistRepository.list();
    return l;
}
std::list<computer> ScienceService::getAllComputers() {
    std::list<computer> l = computerRepository.list();
    return l;
}

std::list<Scientist> ScienceService::searchScientists(std::string searchField, std::string searchTerm) {
    return scientistRepository.search(searchField, searchTerm);
}

std::list<computer> ScienceService::searchComputers(std::string searchField, std::string searchTerm) {
    return computerRepository.search(searchField, searchTerm);
}

void ScienceService::connectScientists(int sID, int cID) {
    scientistRepository.connect(sID, cID);
}

void ScienceService::connectComputers(int cID, int sID) {
    computerRepository.connect(cID,sID);
}
std::list<Scientist> ScienceService::connectedScientists(int sID) {
    return scientistRepository.connectedScientists(sID);
}

std::list<computer> ScienceService::listComputerID() {
    return computerRepository.listID();
}

std::list<Scientist> ScienceService::listScientistID() {
    return scientistRepository.listID();
}
