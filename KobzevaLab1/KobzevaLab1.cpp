#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "Pipe.h"
#include "CS.h"
#include "utils.h"

using namespace std;

bool CheckPipeName(Pipe& p, string name) {
    return (p.Name.find(name) != string::npos);
}
bool CheckPipeStatus(Pipe& p, int status) {
    return (p.Status == status);
}

bool CheckingHavePipe(const unordered_map<int, Pipe>& PGroup) {
    if (PGroup.size() == 0) {
        cout << "No added pipe";
        return false;
    }
    else return true;
}
bool CheckCsName(CS& cs, string name) {
    return (cs.GetName().find(name) != string::npos);
}
bool CheckingHaveCs(const unordered_map<int, CS>& CsGroup) {
    if (CsGroup.size() == 0) {
        cout << "No added cs";
        return false;
    }
    else return true;
}
void AddPipe(unordered_map<int, Pipe>& PGroup) {
    Pipe p;
    cin >> p;
    PGroup.insert({ p.GetId(), p });
}
void AddCs(unordered_map<int, CS>& CsGroup) {
    CS cs;
    cin >> cs;
    CsGroup.insert({ cs.GetId(), cs });
}

void ShowPipe(const unordered_map<int, Pipe> PGroup) {
    if (PGroup.size() != 0) {
        for (auto& p : PGroup) {
            cout << p.second << endl;
        }
    }
    else cout << "\nNo pipes added \n";
}
void ShowCs(const unordered_map<int, CS> CsGroup) {
    if (CsGroup.size() != 0) {
        for (auto& cs : CsGroup) {
            cout << cs.second << endl;
        }
    }
    else cout << "\nNo cs added \n";
}
unordered_set <int> SearchPipeByFilter(unordered_map <int, Pipe> PGroup) {
    unordered_set<int> Id;
    cout << "Search pipe by: \n1.Name\n 2.Status\n";
    int choice = CheckInputNumber(1, 2);
    if (choice == 1) {
        string name;
        cout << "Enter the name of pipe: " << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        getline(cin, name);
        Id = SearchPipeByParametr(PGroup, CheckPipeName, name);
    }
    else {
        cout << "\nEnter 1 if the pipe is working \n Enter 2 if the pipe is being repaired:\n ";
        int status = CheckInputNumber(0, 2);
        Id = SearchPipeByParametr(PGroup, CheckPipeStatus, status);
    }
    return Id;
}
unordered_set<int> SearchCsByFilter(unordered_map <int, CS>& CsGroup) {
    unordered_set <int> Id;
    cout << "\nSearch CS by \n1.name\n 2.percentage of unused shops\n";
    int choice = CheckInputNumber(0, 2);
    if (choice == 1) {
        string name;
        cout << "\nEnter the name of CS: \n";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        getline(cin, name);
        Id = SearchCsByParametr(CsGroup, CheckCsName, name);
    }
    else {
        cout << "\nEnter the percentage of unused shops\n";
        double k = CheckInputNumber(-1, 100);
        Id = SearchCsByParametr(CsGroup, check_unworking, k);
    }
    return Id;
}
void EditPipe(unordered_map<int, Pipe>& PGroup) {
    if (CheckingHavePipe(PGroup)) {
        cout << "1.Edit one pipe \n2.Edit pipes\n";
        switch (CheckInputNumber(0, 2)) {
        case 1:
        {
            ShowPipe(PGroup);
            cout << "\nEnter Id pipe:\n";
            int id = CheckInputNumber(0, (int)PGroup.size());
            if (PGroup.find(id) != PGroup.end()) {
                PGroup[id].EditPipe();
                cout << "Pipe was edited" << endl;
            }
            else
                cout << "There is no such pipe";
            break;
        }
        case 2:
        {
            cout << "Edit pipes by: \n 1.Name/Status \n2.Id\n";
            int choice = CheckInputNumber(0, 2);
            if (choice == 1) {
                auto IdP = SearchPipeByFilter(PGroup);
                if (IdP.size() != 0) {
                    cout << "\nEnter 1 if the pipe is working \n Enter 2 if the pipe is being repaired:\n";
                    int s = CheckInputNumber(0, 2);
                    for (auto& i : IdP)
                        PGroup[i].Status = s;
                }
                else {
                    cout << "There is no such pipe";

                }
                break;
            }
            else {
                unordered_set <int> IdP;
                ShowPipe(PGroup);
                cout << "\nEnter the number of identifiers of pipe you want to edit\n";
                int id;
                int n = CheckInputNumber(0, (int)PGroup.size());
                cout << "\nEnter idetifiers of pipes\n";
                for (int i = 0; IdP.size() < n; i++) {
                    id = CheckInputNumber(0, Pipe::MaxIdPipe - 1);
                    if (PGroup.find(id) != PGroup.end()) {
                        if (PGroup.find(id) != PGroup.end())
                            IdP.insert(id);
                    }
                    else
                    {
                        cout << "There is no such pipe" << endl;;
                    }
                }
                cout << "\nEnter 1 if the pipe is working \n Enter 2 if the pipe is being repaired:\n";
                int status = CheckInputNumber(0, 2);
                for (auto& i : IdP) {
                    for (auto& i : IdP)
                        PGroup[i].Status = status;
                }
            }
        }

        }
    }
}
void EditCs(unordered_map<int, CS>& CsGroup) {
    if (CheckingHaveCs(CsGroup)) {
        //unordered_set <int> IdCs;
        cout << "\n1.Edit one CS\n 2.Edit CSs\n";
        switch (CheckInputNumber(0, 2)) {
        case 1:
        {
            ShowCs(CsGroup);
            cout << "/nChoose CS to edit/n";
            int Id = CheckInputNumber(0, (int)CsGroup.size());
            if (CsGroup.find(Id) != CsGroup.end()) {
                CsGroup[Id].EditCs();
                cout << "CS was edited";
            }
            break;
        }
        case 2:
        {
            unordered_set <int> IdCs;
            cout << "\nChoose  by \n1.Name\WorkingShop\n 2.Id\n";
            int n = CheckInputNumber(0, 2);
            if (n == 1) {
                auto idcs = SearchCs(CsGroup);
                if (idcs.size() != 0) {
                    for (auto& i : idcs)
                        CsGroup[i].edit_cs();
                }
                else cout << "There is no such CS";
            }
            else {
                int id;
                ShowCs(CsGroup);
                cout << "\nEnter the number of cs you want to edit\n";
                int count = CheckInputNumber(0, (int)CsGroup.size());
                cout << "\nEnter idetifiers of CSs\n";
                for (int i = 0; IdCs.size() < count; i++) {
                    cin >> id;
                    if (CsGroup.find(id) != CsGroup.end())
                        IdCs.insert(id);
                    else cout << "\nThere is no such cs\n";
                }
                for (auto& id : IdCs)
                    CsGroup[id].EditCs();
                break;
            }
        }
        }
    }
}
void SaveData(const unordered_map<int, Pipe> PGroup,const unordered_map<int, CS> CsGroup) {
    ofstream fout;
    string name;
    cout << "Enter the name file to save the data" << endl;
    cin >> name;
    fout.open(name + ".txt", ios::out);
    for (auto p : PGroup) {
        p.second.SavePipe(fout);
    }
    fout << endl;
    for (auto cs : CsGroup) {
        cs.second.SaveCs(fout);
    }
    fout.close();
}
void LoadData(unordered_map<int, Pipe>& PGroup, unordered_map<int, CS>& CsGroup) {
    ifstream fin;
    string name;
    cout << "Enter the name file to load the data" << endl;
    cin >> name;
    if (!fin) cout << "Error! No file with name";
    else {
        Pipe newP;
        CS newCS;
        PGroup.clear();
        CsGroup.clear();
        Pipe::MaxIdPipe = 1;
        CS::MaxIdCs = 1;
        fin.open(name + ".txt");
        for (auto p : PGroup) {
            p.second.LoadPipe(fin);
        }
        for (auto cs : CsGroup) {
            cs.second.LoadCs(fin);
        }
        fin.close();
    }
}


int main() { 
    unordered_map<int, Pipe> PGroup;
    unordered_map<int, CS> CsGroup;
    while (1) {
        cout << "\n    Menu\n 1. Add pipe\n 2. Add CS\n 3. View all objects\n 4. Edit pipe\n 5. Edit CS\n 6. Save\n 7. Load\n 0. Exit\n";
        switch (CheckInputNumber(-1, 7)) {
        case 0:
            break;
        case 1:
            AddPipe(PGroup);
            break;
        case 2:
            AddCs(CsGroup);
            break;
        case 3:
            ShowPipe(PGroup);
            ShowCs(CsGroup);
            break;
        case 4:
            EditPipe(PGroup);
            break;
        case 5:
            //cs.EditCs();
            break;
        case 6:
            //SaveData(PGroup, CsGroup);
            break;
        case 7:
            //LoadData();
            break;
        }
       
    }
}