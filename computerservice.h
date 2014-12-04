#ifndef COMPUTERSERVICE_H
#define COMPUTERSERVICE_H

#include "computer.h"
#include "ComputerRepository.h"
#include <list>

// Domain layer, services the presentation layer
class ComputerService {
public:
    ComputerService();
    ~ComputerService();
    void addComputer(computer cpu);
    // Returns the first scientist that matches the searchTerm
    computer* search(std::string searchTerm);
    std::list<computer> getAllComputers();
    std::list<computer> getComputersOrderedBy(std::string,std::string);
private:
    ComputerRepository computerRepository;
};

#endif // COMPUTERSERVICE_H


