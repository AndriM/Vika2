#ifndef SCIENTIST_H
#define SCIENTIST_H

#include <ctime>
#include <string>

// DTO for scientists
class Scientist {
public:
    Scientist();
    // This is required for the remove functionality
    bool operator==(const Scientist &rhs);
    std::string name;
    std::string dateOfBirth;
    std::string dateOfDeath;
    std::string gender;
    std::string ID;
    //std::string computers;
};

#endif // SCIENTIST_H
