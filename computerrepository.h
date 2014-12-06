#ifndef COMPUTERREPOSITORY_H
#define COMPUTERREPOSITORY_H

#include <fstream>
#include <list>
#include "computer.h"
#include <stdexcept>
#include <string>
#include "utilities.h"
#include <vector>
#include "comparer.h"
#include <algorithm>
#include <QtSql>
#include "sql.h"


class ComputerRepository
{
public:
    ComputerRepository();
    ComputerRepository(std::string filename = "computers.csv");//
    ~ComputerRepository();//
    computer *search(std::string searchTerm);//
    void add(computer);//
    std::list<computer> list();//
    std::list<computer> list(std::string col, std::string mod);//
private:
    QSqlDatabase db;
    std::list<computer> computerList;
    std::string filename;
    std::list<computer> deepCopy();
    char delimiter;
    void save();



};

#endif // COMPUTERREPOSITORY_H

