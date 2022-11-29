#include "Pipe.h"
#include <iostream>
#include <fstream>
#include <string>
#include "utils.h"

using namespace std;

int Pipe::MaxIdPipe = 1;
int Pipe::GetId()
{
    return IdPipe;
}
int Pipe::GetStatus()
{
    return Status;
}


Pipe::Pipe()
{
    IdPipe = MaxIdPipe++;
}
void Pipe::EditPipe() {
    CheckStatus(Status);
    cout << "\nEnter 1 if the pipe is working \n Enter 2 if the pipe is being repaired:\n";
    Status = CheckInputNumber(0, 2);
    CheckStatus(Status);
}
void Pipe::SavePipe(ofstream& fout)
{
    fout << IdPipe << endl << Name << endl << Lenght << endl << Diameter << endl << Status << endl;
}
void Pipe::LoadPipe(ifstream& fin)
{
    fin >> IdPipe >> Name >> Lenght >> Diameter >> Status;
}
void Pipe::CheckStatus(int status)
{
        if (status == 1) cout << "\n Status:  Pipe is working\n";
        else cout << "\n Status: Pipe being repaired\n";
}
istream& operator >> (istream& in, Pipe& p) {
    cout << "\nEnter pipe name :\n";
    cin.clear();
    cin.ignore(10000, '\n');
    getline(in, p.Name);
    cout << "\nEnter pipe length:\n";
    p.Lenght = CheckInputNumber(0.0, DBL_MAX);
    cout << "\nEnter pipe diameter:\n";
    p.Diameter = CheckInputNumber(0.0, DBL_MAX);
    cout << "\nEnter 1 if the pipe is working \n Enter 2 if the pipe is being repaired:\n";
    p.Status = CheckInputNumber(0, 2);
    cout << "\nPipe added\n";
    return in;
}
ostream& operator << (ostream& out, const Pipe& p) {
    if (p.Lenght != 0) {
        out << "\n Pipe\n" <<" Id: "<< p.IdPipe <<"\n Name: " << p.Name << "\n Length:  " << p.Lenght << "\n Diametr:  " << p.Diameter;
        if (p.Status == 1) out << "\n Status:  Pipe is working\n";
        else out << "\n Status: Pipe being repaired\n";
    }
    else out << "\n The pipe has not been added\n";
    return out;
}