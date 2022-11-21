#include "CS.h"
#include <string>
#include <iostream>
#include <fstream>
#include "utils.h"

std::istream& operator >> (std::istream& in, CS& cs) {
    std::cout << "\nEnter the name of CS\n";
    std::getline(std::cin, cs.Name);
    std::cout << "\nEnter the number of workshops\n";
    cs.Workshop = CheckInputNumber(0, INT_MAX);
    std::cout << "\nEnter the number of working workshops\n";
    cs.WorkingWorkshop = CheckInputNumber(0, cs.Workshop);
    std::cout << "\n Enter CS efficiency\n";
    cs.Efficiency = CheckInputNumber(0.0, 100.0);
    std::cout << "\nCs added\n";
    return in;
}
std::ostream& operator << (std::ostream& out, const CS& cs) {
    if (cs.WorkingWorkshop != -1) out << "\n CS\n" << " Name:  " << cs.Name << "\n Number of workshops:  " << cs.Workshop << "\n Number of working workshops:  " << cs.WorkingWorkshop << "\n Efficiency:  " << cs.Efficiency;
    else out << "\n The CS has not been added\n";
    return out;
}

void CS::ShowCs() const
{
    if (WorkingWorkshop != -1) std::cout << "\n CS\n" << " Name:  " << Name << "\n Number of workshops:  " << Workshop << "\n Number of working workshops:  " << WorkingWorkshop << "\n Efficiency:  " << Efficiency;
    else std::cout << "\n The CS has not been added\n";
}

void CS::EditCs()
{
    if (WorkingWorkshop != -1) {
        std::cout << "\nEnter the number of working workshops\n";
        CheckInputNumber(0, Workshop);
    }
    else std::cout << "\n The CS has not been added\n";
}

void CS::SaveCs(std::ofstream& file)
{
    file << Name << std::endl << Workshop << std::endl << WorkingWorkshop << std::endl << Efficiency << std::endl;
}

void CS::LoadCs(std::ifstream& file)
{
    file >> Name >> Workshop >> WorkingWorkshop >> Efficiency;
}
