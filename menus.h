#ifndef MENUS_H
#define MENUS_H

// Long strings and ASCII art here below \/ \/

std::string MAIN_MENU = "Please use the following commands to interface with this AWESOME DATABASE\n\n\
        add     : Add a record to the database\n\
        order   : Order and dislay the records in the database\n\
        search  : Searches for a scientist\n\
        display : Display scientists.\n\
        connect : Connect scientists and computers. \n\
        dc      : Display connected.\n\
        exit    : Exit the program";

std::string FILTER_MENU = "Enter one of the following commands to order by the corresponding column\n\
        name    : Name\n\
        dob     : Date of birth\n\
        dod     : Date of death\n\
        gender  : Gender";

std::string FILTER_MENU2 = "Enter one of the following commands to order by the corresponding column\n\
        name                  : Name\n\
        construction year     : Construction Year\n\
        type                  : Type\n\
        constructed           : Constructed";

std::string SEARCH_MENU1 = "What do you want to search by? \n\
        Name              : name\n\
        Gender            : gender\n\
        BirthYear         : birth year\n\
        DeathYear         : death year";

std::string SEARCH_MENU2 = "What do you want to search by? \n\
        Name              : name\n\
        ConstuctionYear   : construction year\n\
        Type              : type\n\
        Constructed       : constructed";


#endif // MENUS_H
