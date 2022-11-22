#pragma once
#include <string>
#include <iostream>
class CS
{
    std::string Name = "";
    int  Workshop = 0, WorkingWorkshop = -1, IdCs = -1;
    float Efficiency = 0;
public:
    static int MaxIdCs;
    CS();
    friend std::istream& operator >> (std::istream& in, CS& cs);
    friend std::ostream& operator << (std::ostream& out, const CS& cs);
    int GetId();
    std::string GetName();
    void EditCs();
    void SaveCs(std::ofstream& fout);
    void LoadCs(std::ifstream& fin);
};

