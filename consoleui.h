#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include "Scientist.h"
#include "computer.h"
#include <stack>
#include <list>
#include "scienceservice.h"

// Display layer for the console application
class ConsoleUI {
public:
    ConsoleUI();
    ~ConsoleUI();
    int start();
    void addScientist();
private:
    ScienceService scienceService;
    void clear();
    void waitForPrompt();
    int respondToMessage();
};

#endif // CONSOLEUI_H
