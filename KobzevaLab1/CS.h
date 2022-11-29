#pragma once
#include <string>
#include <iostream>
class CS
{
    std::string Name = "";
    int  Workshop = -1, WorkingWorkshop = -1, IdCs = -1;
    double Efficiency = 0;
public:
    static int MaxIdCs;
    CS();
    friend std::istream& operator >> (std::istream& in, CS& cs);
    friend std::ostream& operator << (std::ostream& out, const CS& cs);
    int GetId();
    double GetNotWorkingCs();
    std::string GetName();
    void EditCs();
    void SaveCs(std::ofstream& fout);
    void LoadCs(std::ifstream& fin);
};

