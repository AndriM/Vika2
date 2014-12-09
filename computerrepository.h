#ifndef COMPUTERREPOSITORY_H
#define COMPUTERREPOSITORY_H
#include "computer.h"
#include <QtSql>

class ComputerRepository {
public:
    ComputerRepository();
    QSqlDatabase openDatabase();
    void add(computer comp);
    std::list<computer> orderBy(std::string order);
    std::list<computer> list();
    std::list<computer> search(std::string searchField, std::string searchTerm);
    void connect(int cID, int sID);
    std::list<computer> listID();
    std::list<computer> connectedComputers(int cID);
private:
    QSqlDatabase computerDB;
};

#endif // COMPUTERREPOSITORY_H
