#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void loadConfig(const std::string& filname)
{
    std::ifstream file(filname);
    if (!file.is_open())
    {
        std::cout << "Failed to open the file." << std::endl;
        return;
    }


    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string command;
        iss >> command;

        if (command == "window")
        {
         
        }
        else if (command == "font")
        {
        }
        else if (command == "circle")
        {
         
        }
        else if (command == "rectangle")
        {
         
        }
    }

}
