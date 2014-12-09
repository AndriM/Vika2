#ifndef SCIENCESERVICE_H
#define SCIENCESERVICE_H

#include "Scientist.h"
#include "computer.h"
#include "ScientistRepository.h"
#include "computerrepository.h"
#include <list>

// Domain layer, services the presentation layer
class ScienceService {
public:
    ScienceService();
    ~ScienceService();
    void addScientist(Scientist scientist);
    // Returns the first scientist that matches the searchTerm
    std::list<Scientist> searchScientists(string searchField, string searchTerm);
    std::list<Scientist> getAllScientists();
    void addComputer(computer comp);
    std::list<computer> orderComputers(std::string orderby);
    std::list<Scientist> orderScientists(std::string orderby);
    std::list<computer> getAllComputers();
    std::list<computer> searchComputers(std::string searchField, std::string searchTerm);
    void connectScientists(int sID, int cID);
    void connectComputers(int cID, int sID);
    std::list<computer> listComputerID();
    std::list<Scientist> listScientistID();
    std::list<Scientist> connectedScientists(int sID);
    std::list<computer> connectedComputers(int cID);
private:
    ScientistRepository scientistRepository;
    ComputerRepository computerRepository;
};

#endif // SCIENCESERVICE_H
