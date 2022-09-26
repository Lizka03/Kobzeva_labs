#include <iostream>
#include <fstream>

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
int TryInputInt(int& input) {
    while (!((cin >> input).good()) || (input < 0)) {
        cout << "\nError. Try again\n";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return input;
}

float TryInputFloat(float& input) {
    while (!((cin >> input).good()) || (input <= 0)) {
        cout << "\nError. Try again\n";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return input;
}
int TryInputStatus(int &status) {
    do {
        TryInputInt(status);
        if (status == 1) {
            cout << "Pipe is working";
        }
        else if (status == 2) {
            cout << "Pipe is being repaired";
        }
        else {
            cout << "\nError. Try again\n";
        }
    } while ((status < 1) || (status > 2));
    return status;
}
Pipe NewPipe() {
    Pipe newP;
    cout << "\nEnter pipe length:\n";
    TryInputFloat(newP.Lenght);
    cout << "\nEnter pipe diameter:\n";
    TryInputFloat(newP.Diameter);
    cout << "\nEnter 1 if the pipe is working \n Enter 2 if the pipe is being repaired:\n";
    TryInputStatus(newP.Status);
    return newP;
}

CS NewCs() {
    CS newCs;
    cout << "\nEnter the name of CS\n";
    cin >> newCs.Name;
    cout << "\nEnter the number of workshops\n";
    TryInputInt(newCs.Workshop);
    cout << "\nEnter the number of working workshops\n";
    while (TryInputInt(newCs.WorkingWorkshop) > newCs.Workshop) {
        cout << "\nError. Try again\n";
    }
    cout << "\n Enter CS efficiency\n";
    TryInputFloat(newCs.Efficiency);
    return newCs;
}
void ShowPipe(const Pipe p) {
    if (p.Lenght != 0 && p.Diameter != 0 && p.Status != -1) {
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
    if (cs.Name != "" && cs.Workshop != 0 && cs.WorkingWorkshop != -1 && cs.Efficiency != 0) {
        cout << "\n CS\n" << " Name:  " << cs.Name << "\n Number of workshops:  " << cs.Workshop << "\n Number of working workshops:  " << cs.WorkingWorkshop << "\n Efficiency:  " << cs.Efficiency;
    }
    else {
        cout << "\n The CS has not been added\n";
    }
}
void EditPipe(Pipe & p) {
    if (p.Status != 0) {
        TryInputStatus(p.Status);
    }
    else {
        cout << "\n The pipe has not been added\n";
    }
}
void EditCs(CS& cs) {
    if (cs.WorkingWorkshop != -1) {
        cout << "\nEnter the number of working workshops\n";
        cin >> cs.WorkingWorkshop;
    }
    else {
        cout << "\n The CS has not been added\n";
    }
}
void SaveData(const Pipe p, const CS cs) {
    ofstream fout;
    fout.open("data.txt", 'w');
}

int main() { 
    CS cs;
    Pipe p;
    int choice = -1;

    while (choice) {
        cout << "\n    Menu\n 1. Add pipe\n 2. Add CS\n 3. View all objects\n 4. Edit pipe\n 5. Edit CS\n 6. Save\n 7. Load\n 0. Exit\n";
        TryInputInt(choice);
        switch (choice) {
        case 0:
            break;
        case 1:
            p = NewPipe();
            break;
        case 2:
            cs = NewCs();
            break;
        case 3:
            ShowPipe(p);
            ShowCs(cs);
            break;
        case 4:
            EditPipe(p);
            break;
        case 5:
            EditCs(cs);
            break;
        case 6:

            break;
        case 7:
            break;
        default:
            cout << "\nError. Try again\n";
        }
    }
}