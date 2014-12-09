#include "consoleui.h"
#include <iostream>
#include <string>
#include "menus.h"
#include <stdexcept>
#include <sstream>

ConsoleUI::ConsoleUI() {
    scienceService = ScienceService();
}

ConsoleUI::~ConsoleUI() {
}

int ConsoleUI::start() {
    // REPL
    while(true) {
        int response = respondToMessage();
        if( response == 0) {
            return 0;
        }
    }
    return 1;
}

void ConsoleUI::clear() {
    // Not pretty, but it is platform independant
    std::cout << std::string( 100, '\n' );
}

void ConsoleUI::waitForPrompt() {
    std::cout << "\nPress enter to continue..." << std::endl;
    std::cin.ignore();
    std::cin.get();
}

int ConsoleUI::respondToMessage() {

    //std::cout << MAIN_MENU << std::endl;

    /*std::string userRequest;
    std::cin >> userRequest;*/
    char wantToGoAgain;
    int answer;
    do {
        std::cout <<"Choose:\n\t1: Computer scientist.\n\t2: Computer" <<endl;
        std::cin >> answer;

        if(answer == 1) {
            std::cout << MAIN_MENU << std::endl;
            std::string userRequest;
            std::cin >> userRequest;
        try {
            // Handle all available commands and throw error on unknown ones
            if(userRequest.find("add") != std::string::npos) { //baeta við hvort vid viljum adda scientist eda computer
                clear();
                Scientist additionalScientist = Scientist();
                std::cout << "Enter the name of the scientist: ";
                std::cin.ignore();
                std::getline(std::cin, additionalScientist.name);
                clear();
                std::cout << "Enter the date of birth of the scientist: ";
                std::cin >> additionalScientist.dateOfBirth;
                clear();
                std::cout << "Enter the date of death of the scientist: ";
                std::cin >> additionalScientist.dateOfDeath;
                clear();
                std::cout << "Enter the gender of the scientist: ";
                std::cin >> additionalScientist.gender;
                clear();
                /*std::cout << "Enter computer(s) that the scientist has worked on: ";
                std::cin >> additionalScientist.computers;*/
                scienceService.addScientist(additionalScientist);
            } else if(userRequest.find("search") != std::string::npos) {
                clear();
                std::string searchField = "";
                std::string searchTerm = "";
                std::cout << "Enter a search field: ";
                std::cin >> searchField;
                clear();
                std::cout << "Enter what you want to search for: ";
                std::cin >> searchTerm;
                clear();
                std::list<Scientist> s = scienceService.searchScientists(searchField, searchTerm);
                unsigned int i = 0;
                    for(;i < s.size(); i++) {
                        i++;
                    }
                if(i != 0) {
                    std::cout << "Scientist found!!" << std::endl;
                    std::cout << "Name:\t\tDateOfBirth:\tDateOfDeath:\tGender:\n";
                    //std::cout << searchResult->name << "\t" << searchResult->dateOfBirth << "\t\t" << searchResult->dateOfDeath << "\t\t" << searchResult->gender << "\t\t" << "\t\t" << std::endl;
                    for(std::list<Scientist>::iterator iter = s.begin(); iter != s.end(); iter ++) {
                        std::cout << iter->name << "\t\t" << iter->dateOfBirth << "\t\t" << iter->dateOfDeath << "\t\t" << iter->gender << std::endl;
                    }
                }
                else {
                    std::cout << "No results found for the term: " << searchTerm << std::endl;
                }
              } else if(userRequest.find("connect") != std::string::npos){

                    int sID = 0;
                    int cID = 0;
                    clear();
                    std::list<Scientist> sciID = scienceService.listScientistID();
                    std::cout << "Name:\t\t\tID:\n";
                        for(std::list<Scientist>::iterator iter = sciID.begin(); iter != sciID.end(); iter ++) {
                            std::cout << iter->name << "\t\t" << iter->ID << std::endl;
                        }
                    std::cout <<"Which scientist do you want to connect a computer to?" <<endl;
                    std::cout <<"Enter the Scientist ID: ";
                    std::cin >> sID;
                    clear();
                    std::list<computer> compID = scienceService.listComputerID();
                    std::cout << "Name:\t\t\tID:\n";
                        for(std::list<computer>::iterator iter = compID.begin(); iter != compID.end(); iter ++) {
                            std::cout << iter->name << "\t\t" << iter->ID << std::endl;
                        }
                    std::cout <<"Which computer do you want to connect to the scientist?" <<endl;
                    std::cout <<"Enter the Computer ID: ";
                    std::cin >> cID;

                    scienceService.connectScientists(sID,cID);
            } else if(userRequest.find("order") != std::string::npos) {
                clear();
                std::string orderby;
                std::list<Scientist> l;
                std::cout << FILTER_MENU << std::endl;
                cin >> orderby;
                l = scienceService.orderScientists(orderby);

                std::cout << "Name:\t\t\tDate Of Birth:\tDate Of Death:\tGender:\n";
                    for(std::list<Scientist>::iterator iter = l.begin(); iter != l.end(); iter ++) {
                        std::cout << iter->name << "\t\t" << iter->dateOfBirth << "\t\t" << iter->dateOfDeath << "\t\t" << iter->gender << std::endl;
                    }
            } else if(userRequest.find("display") != std::string::npos) {
                std::list<Scientist> s = scienceService.getAllScientists();

                std::cout << "Name:\t\t\tDate Of Birth:\tDate Of Death:\tGender:\n";
                    for(std::list<Scientist>::iterator iter = s.begin(); iter != s.end(); iter ++) {
                        std::cout << iter->name << "\t\t" << iter->dateOfBirth << "\t\t" << iter->dateOfDeath << "\t\t" << iter->gender << std::endl;
                    }
            }
            else if(userRequest.find("dc") != std::string::npos)
            {
                int cID;

                std::list<Scientist> sciID = scienceService.listScientistID();
                std::cout << "Name:\t\t\tID:\n";
                    for(std::list<Scientist>::iterator iter = sciID.begin(); iter != sciID.end(); iter ++) {
                        std::cout << iter->name << "\t\t" << iter->ID << std::endl;
                    }
                std::cout << "Show computers connected to scientist nr: ";
                std::cin >> cID;
                std::list<computer> c = scienceService.connectedComputers(cID);
                    for(std::list<computer>::iterator iter = c.begin(); iter != c.end(); iter ++) {
                        std::cout << iter->name << std::endl;
                    }
                //prenta út computer lista
            }
            else if (userRequest.find("exit") != std::string::npos) {
                return 0;
            } else {
                throw std::runtime_error( userRequest + " is not a valid command.");
            }

           } catch(std::runtime_error e) {
            clear();
            std::cout << "Command caused an error: " << e.what() << std::endl;
            std::cout << "Please try another command" << std::endl;
            waitForPrompt();
            clear();
          }

}
        if(answer == 2) { //tarf ad breyta ollu herna ur scientist i computer
            std::cout << MAIN_MENU << std::endl;
            std::string userRequest;
            std::cin >> userRequest;
        try {
            //Handle all available commands and throw error on unknown ones
            if(userRequest.find("add") != std::string::npos) { //baeta við hvort vid viljum adda scientist eda computer
                clear();
                computer additionalComputer = computer();
                std::cout << "Enter the name of the computer: ";
                std::cin.ignore();
                std::getline(std::cin, additionalComputer.name);
                clear();
                std::cout << "Enter the year that the computer was created: ";
                std::cin >> additionalComputer.constructionYear;
                clear();
                std::cout << "Enter the type of the computer: ";
                std::cin >> additionalComputer.type;
                clear();
                std::cout << "Was the computer constructed (Yes/No): ";
                std::cin >> additionalComputer.constructed;
                clear();
                scienceService.addComputer(additionalComputer);
            }

            else if(userRequest.find("search") != std::string::npos) {
                clear();
                std::string searchField = "";
                std::string searchTerm = "";
                std::cout << "Enter a search field: ";
                std::cin >> searchField;
                clear();
                std::cout << "Enter what you want to search for: ";
                std::cin >> searchTerm;
                clear();
                std::list<computer> c = scienceService.searchComputers(searchField, searchTerm);
                unsigned int i = 0;
                    for(;i < c.size(); i++) {
                        i++;
                    }
                if(i != 0) {
                    std::cout << "Computer found!!" << std::endl;
                    std::cout << "Name:\t\tConstruction Year:\tType:\tConstructed:\n";
                    for(std::list<computer>::iterator iter = c.begin(); iter != c.end(); iter ++) {
                        std::cout << iter->name << "\t\t" << iter->constructionYear << "\t\t" << iter->type << "\t\t" << iter->constructed << std::endl;
                    }
                }
                else {
                    std::cout << "No results found for the term: " << searchTerm << std::endl;
                }
            }
            else if(userRequest.find("order") != std::string::npos) {
                clear();

                std::string orderby;
                std::list<computer> l;
                std::cout << FILTER_MENU2 << std::endl;
                cin >> orderby;
                l = scienceService.orderComputers(orderby);

                std::cout << "Name:\t\tConstruction Year:\tType:\tComputer constructed:\n";
                    for(std::list<computer>::iterator iter = l.begin(); iter != l.end(); iter ++) {
                        std::cout << iter->name << "\t\t" << iter->constructionYear << "\t\t" << iter->type << "\t\t" << iter->constructed << std::endl;
                    }
                }
                else if(userRequest.find("display") != std::string::npos) {
                    std::list<computer> c = scienceService.getAllComputers();

                    std::cout << "Name:\t\t\tConstruction Year:\tType:\tConstructed:\n";
                        for(std::list<computer>::iterator iter = c.begin(); iter != c.end(); iter ++) {
                            std::cout << iter->name << "\t\t" << iter->constructionYear << "\t\t" << iter->type << "\t\t" << iter->constructed << std::endl;
                        }
                }
                else if(userRequest.find("connect") != std::string::npos) {

                    int sID = 0;
                    int cID = 0;
                    clear();
                    std::list<computer> compID = scienceService.listComputerID();
                    std::cout << "Name:\t\t\tID:\n";
                        for(std::list<computer>::iterator iter = compID.begin(); iter != compID.end(); iter ++) {
                            std::cout << iter->name << "\t\t" << iter->ID << std::endl;
                        }
                    std::cout <<"Which computer do you want to connect to a scientist?" <<endl;
                    std::cout <<"Enter the Computer ID: ";
                    std::cin >> cID;
                    clear();
                    std::list<Scientist> sciID = scienceService.listScientistID();
                    std::cout << "Name:\t\t\tID:\n";
                        for(std::list<Scientist>::iterator iter = sciID.begin(); iter != sciID.end(); iter ++) {
                            std::cout << iter->name << "\t\t" << iter->ID << std::endl;
                        }
                    std::cout <<"Which scientist do you want to connect to the computer?" <<endl;
                    std::cout <<"Enter the Scientist ID: ";
                    std::cin >> sID;

                    scienceService.connectComputers(cID, sID);
                }

            else if(userRequest.find("dc") != std::string::npos)
            {
                //prenta ut lista til ad velja ur og lata velja ID

                int cID;

                std::list<Scientist> s = scienceService.connectedScientists(cID);

                //prenta út computer lista
            }

             else if (userRequest.find("exit") != std::string::npos) {
                return 0;
            } else {
                throw std::runtime_error( userRequest + " is not a valid command.");
        }
        //return 1;
            } catch(std::runtime_error e) {
                clear();
                std::cout << "Command caused an error: " << e.what() << std::endl;
                std::cout << "Please try another command" << std::endl;
                waitForPrompt();
                clear();
            }
        }
        std::cout << "Do you want to go again? (y/n): ";
        std::cin >> wantToGoAgain;
    }while(wantToGoAgain == 'Y' || wantToGoAgain =='y');
    return 0;
}
