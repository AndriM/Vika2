#ifndef COMPUTERREPOSITORY_H
#define COMPUTERREPOSITORY_H
#include "computer.h"
#include <QtSql>

class ComputerRepository {
public:
    ComputerRepository();
    void openDatabase();
    void add(computer comp);
    std::list<computer> orderBy(std::string order);
};

#endif // COMPUTERREPOSITORY_H
