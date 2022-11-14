#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
struct Pipe {
    float Lenght = 0, Diameter = 0;
    int Status = 0;
};
struct CS {
    string Name = "";
    int  Workshop = 0, WorkingWorkshop = -1;
    float Efficiency = 0;
};
template <typename T>
T TryInputNumber(T min,T max) {
    T x;
    while (!((cin >> x).good()) || (x <min) ||(x>max) ) {
        cout << "\nError. Try again\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    return x;
}

istream& operator >> (istream& in, Pipe& p) {
    cout << "\nEnter pipe length:\n";
    p.Lenght=TryInputNumber(0.0,DBL_MAX);
    cout << "\nEnter pipe diameter:\n";
    p.Diameter = TryInputNumber(0.0,DBL_MAX);
    cout << "\nEnter 1 if the pipe is working \n Enter 2 if the pipe is being repaired:\n";
    p.Status = TryInputNumber(1,2);
    cout << "\nPipe added\n";
    return in;
}
istream& operator >> (istream& in, CS& cs) {
    cout << "\nEnter the name of CS\n";
    getline(cin >> ws, cs.Name);
    cout << "\nEnter the number of workshops\n";
    cs.Workshop = TryInputNumber(0,INT_MAX);
    cout << "\nEnter the number of working workshops\n";
    cs.WorkingWorkshop = TryInputNumber(0, cs.Workshop);
    cout << "\n Enter CS efficiency\n";
    cs.Efficiency = TryInputNumber(0.0,DBL_MAX);
    cout << "\nCs added\n";
    return in;
}
ostream& operator << (ostream& out, const Pipe& p) {
    if (p.Lenght != 0) {
        out << "\n Pipe\n" << " Length:  " << p.Lenght << "\n Diametr:  " << p.Diameter;
        if (p.Status == 1)
            out << "\n Status:  Pipe is working\n";
        else
            out << "\n Status: Pipe being repaired\n";
    }
    else {
        out << "\n The pipe has not been added\n";
    }
    return out;
}
ostream& operator << (ostream& out, const CS& cs) {
    if (cs.WorkingWorkshop != -1) {
        out << "\n CS\n" << " Name:  " << cs.Name << "\n Number of workshops:  " << cs.Workshop << "\n Number of working workshops:  " << cs.WorkingWorkshop << "\n Efficiency:  " << cs.Efficiency;
    }
    else {
        out << "\n The CS has not been added\n";
    }
    return out;
}

void ShowPipe(const Pipe p) {
    if (p.Lenght != 0 ) {
        cout << "\n Pipe\n" << " Length:  " << p.Lenght << "\n Diametr:  " << p.Diameter;
        if (p.Status == 1)
            cout << "\n Status:  Pipe is working\n";
        else
            cout << "\n Status: Pipe being repaired\n";
    }
    else {
        cout << "\n The pipe has not been added\n";
    }
}
void ShowCs(const CS cs) {
    if (cs.WorkingWorkshop != -1) {
        cout << "\n CS\n" << " Name:  " << cs.Name << "\n Number of workshops:  " << cs.Workshop << "\n Number of working workshops:  " << cs.WorkingWorkshop << "\n Efficiency:  " << cs.Efficiency;
    }
    else {
        cout << "\n The CS has not been added\n";
    }
}
void EditPipe(Pipe & p) {
    cout << "\nEnter 1 if the pipe is working \n Enter 2 if the pipe is being repaired:\n";
    if (p.Status != 0) {
        TryInputNumber(1,2);
        cout << "\nPipe edited\n";
    }
    else {
        cout << "\n The pipe has not been added\n";
    }
}
void EditCs(CS& cs) {
    if (cs.WorkingWorkshop != -1) {
        cout << "\nEnter the number of working workshops\n";
        TryInputNumber(0,cs.Workshop);
    }
    else {
        cout << "\n The CS has not been added\n";
    }
}
void SaveData(Pipe& p, CS& cs) {
    ofstream fout;
    fout.open("data.txt", 'w');
    fout  << p.Lenght << endl << p.Diameter << endl << p.Status << endl;
    fout  << cs.Name << endl << cs.Workshop << endl <<cs.WorkingWorkshop << endl << cs.Efficiency << endl;
    fout.close();

}
void LoadData(Pipe& p, CS& cs) {
    ifstream fin;
    string line;
    fin.open("data.txt");
    fin >> p.Lenght;
    fin >> p.Diameter;
    fin >> p.Status;
    getline(fin, line);
    cs.Name = line;
    fin >> cs.Workshop;
    fin >> cs.WorkingWorkshop;
    fin >> cs.Efficiency;
    fin.close();
}

int main() { 
    CS cs;
    Pipe p;
    while (1) {
        cout << "\n    Menu\n 1. Add pipe\n 2. Add CS\n 3. View all objects\n 4. Edit pipe\n 5. Edit CS\n 6. Save\n 7. Load\n 0. Exit\n";
        switch (TryInputNumber(0,7)) {
        case 0:
            break;
        case 1:
            cin >> p;
            break;
        case 2:
            cin >> cs;
            break;
        case 3:
            cout << cs;
            cout << p;
            break;
        case 4:
            EditPipe(p);
            break;
        case 5:
            EditCs(cs);
            break;
        case 6:
            SaveData(p, cs);
            break;
        case 7:
            LoadData(p, cs);
            break;  
        }
    }
}