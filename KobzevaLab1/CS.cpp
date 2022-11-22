#include "CS.h"
#include <string>
#include <iostream>
#include <fstream>
#include "utils.h"

using namespace std;

int CS::MaxIdCs = 1;
istream& operator >> (istream& in, CS& cs) {
    cout << "\nEnter the name of CS\n";
    cin.clear();
    cin.ignore(10000, '\n');
    getline(cin, cs.Name);
    cout << "\nEnter the number of workshops\n";
    cs.Workshop = CheckInputNumber(0, INT_MAX);
    cout << "\nEnter the number of working workshops\n";
    cs.WorkingWorkshop = CheckInputNumber(0, cs.Workshop);
    cout << "\n Enter CS efficiency\n";
    cs.Efficiency = CheckInputNumber(0.0, 100.0);
    cout << "\nCs added\n";
    return in;
}
ostream& operator << (ostream& out, const CS& cs) {
    if (cs.WorkingWorkshop != -1) out << "\n CS\n" << " Id:  " << cs.IdCs << "\n Name:  " << cs.Name << "\n Number of workshops:  " << cs.Workshop << "\n Number of working workshops:  " << cs.WorkingWorkshop << "\n Efficiency:  " << cs.Efficiency;
    else out << "\n The CS has not been added\n";
    return out;
}

CS::CS()
{
    IdCs = MaxIdCs++;
}

int CS::GetId()
{
    return IdCs;
}

string CS::GetName()
{
    return string Name;
}

void CS::EditCs()
{
    cout << "\nWorkshops: \n" << Workshop << endl;
    cout << "\nWorking workshop: \n" << WorkingWorkshop;
    cout << "\nEnter new number of working workshops\n" << endl;
    WorkingWorkshop = CheckInputNumber(-1, Workshop);
}

void CS::SaveCs(ofstream& fout)
{
    fout <<IdCs << endl << Name << endl << Workshop << endl << WorkingWorkshop << endl << Efficiency << endl;
}

void CS::LoadCs(ifstream& fin)
{
    fin >>IdCs>> Name >> Workshop >> WorkingWorkshop >> Efficiency;
}
