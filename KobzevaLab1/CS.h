#pragma once
#include <string>
#include <iostream>
class CS
{
    std::string Name = "";
    int  Workshop = 0, WorkingWorkshop = -1;
    float Efficiency = 0;
public:
    friend std::istream& operator >> (std::istream& in, CS& cs);
    friend std::ostream& operator << (std::ostream& out, const CS& cs);
    void ShowCs() const;
    void EditCs();
    void SaveCs(std::ofstream& file);
    void LoadCs(std::ifstream& file);
};

