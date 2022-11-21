#include "Pipe.h"
#include <iostream>
#include <fstream>
#include "utils.h"
Pipe::Pipe()
{
}
void Pipe::EditPipe()
{
    std::cout << "\nEnter 1 if the pipe is working \n Enter 2 if the pipe is being repaired:\n";
    if (Status != 0) {
        Status = CheckInputNumber(1, 2);
        std::cout << "\nPipe edited\n";
    }
    else std::cout << "\n The pipe has not been added\n";
}
void Pipe::SavePipe(std::ofstream& file)
{
    file << Lenght << std::endl << Diameter << std::endl << Status << std::endl;
}
void Pipe::ShowPipe() const
{
    if (Lenght != 0) {
        std::cout << "\n Pipe\n" << " Length:  " << Lenght << "\n Diametr:  " << Diameter;
        if (Status == 1) std::cout << "\n Status:  Pipe is working\n";
        else std::cout << "\n Status: Pipe being repaired\n";
    }
    else std::cout << "\n The pipe has not been added\n";
}
void Pipe::LoadPipe(std::ifstream& file)
{
    file >> Lenght >> Diameter >> Status;
}
void Pipe::SetStatus(int NewStatus)
{
    Status = NewStatus;
}
std::istream& operator >> (std::istream& in, Pipe& p) {
    std::cout << "\nEnter pipe length:\n";
    p.Lenght = CheckInputNumber(0.0, DBL_MAX);
    std::cout << "\nEnter pipe diameter:\n";
    p.Diameter = CheckInputNumber(0.0, DBL_MAX);
    std::cout << "\nEnter 1 if the pipe is working \n Enter 2 if the pipe is being repaired:\n";
    p.Status = CheckInputNumber(0, 2);
    std::cout << "\nPipe added\n";
    return in;
}
std::ostream& operator << (std::ostream& out, const Pipe& p) {
    if (p.Lenght != 0) {
        out << "\n Pipe\n" << " Length:  " << p.Lenght << "\n Diametr:  " << p.Diameter;
        if (p.Status == 1) out << "\n Status:  Pipe is working\n";
        else out << "\n Status: Pipe being repaired\n";
    }
    else out << "\n The pipe has not been added\n";
    return out;
}