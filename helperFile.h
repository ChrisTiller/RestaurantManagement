#ifndef HELPERFILE_H_INCLUDED
#define HELPERFILE_H_INCLUDED

#include <iostream>

using std::cout;
using std::string;

struct Command
{
    string mainCommand;
    string commandArguments;
};

void parseCommand(Command&, string);
std::string trim(std::string);
int stringToInt(std::string);
std::string intToString(int);


#endif // HELPERFILE_H_INCLUDED
