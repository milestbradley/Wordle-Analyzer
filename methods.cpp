#include <iostream>
#include <fstream>
#include <string>

std::ifstream myfile; myfile.open("ANSWERS.txt");
std::cout << mystring;

if (myfile.is_open())
{
    while (myfile.good())
    {
        myfile >> mystring;
        std::cout << mystring;
    }
}


