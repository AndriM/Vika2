#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include "Scientist.h"
#include "computer.h"
#include <stack>
#include <list>
#include "scienceservice.h"
//#include "computerservice.h"

// Display layer for the console application
class ConsoleUI {
public:
    ConsoleUI();
    ~ConsoleUI();
    int start();
private:
    ScienceService scienceService;
    //ComputerService computerService;
    void clear();
    void waitForPrompt();
    int respondToMessage();
};

#endif // CONSOLEUI_H
