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
    return (p.GetStatus() == status);
}

bool CheckingHavePipe(const unordered_map<int, Pipe>& PGroup) {
    if (PGroup.size() == 0) {
        cout << "\nNo added pipe\n";
        return false;
    }
    else return true;
}
bool CheckCsName(CS& cs, string name) {
    return (cs.GetName().find(name) != string::npos);
}
bool CheckWorkingCs(CS& cs, double p) {
    return (cs.GetNotWorkingCs() == p);
}
bool CheckingHaveCs(const unordered_map<int, CS>& CsGroup) {
    if (CsGroup.size() == 0) {
        cout << "\nNo added cs\n";
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
    ShowPipe(PGroup);
    cout << "\nSearch pipe by: \n1.Name\n 2.Status\n";
    int choice = CheckInputNumber(0, 2);
    if (choice == 1) {
        string name;
        cout << "\nEnter the name of pipe:\n " << endl;
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
    ShowCs(CsGroup);
    cout << "\nSearch CS by \n1.Name\n 2.Percentage of not working shops\n";
    int choice = CheckInputNumber(0, 2);
    if (choice == 1) {
        string name;
        cout << "\n Enter the name of CS: \n";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        getline(cin, name);
        Id = SearchCsByParametr(CsGroup, CheckCsName, name);
    }
    else {
        cout << "\nEnter the percentage of not working shops\n";
        double k = CheckInputNumber(-1.0, 100.0);
        Id = SearchCsByParametr(CsGroup, CheckWorkingCs, k);
    }
    return Id;
}
void EditPipe(unordered_map<int, Pipe>& PGroup) {
    if (CheckingHavePipe(PGroup)) {
        cout << "\n1.Edit one pipe \n2.Edit pipes\n";
        switch (CheckInputNumber(0, 2)) {
        case 1:
        {
            ShowPipe(PGroup);
            cout << "\nEnter Id pipe:\n";
            int id = CheckInputNumber(0, Pipe::MaxIdPipe-1);
            if (PGroup.find(id) != PGroup.end()) {
                PGroup[id].EditPipe();
                cout << "Pipe was edited\n" << endl;
            }
            else cout << "\nThere is no such pipe\n";
            break;
        }
        case 2:
        {
            cout << "Edit pipes by: \n 1.Name/Status \n2.Id\n";
            int choice = CheckInputNumber(0, 2);
            if (choice == 1) {
                auto IdP = SearchPipeByFilter(PGroup);
                if (IdP.size() != 0) {
                    cout << "\n Enter 1 if the pipe is working \n Enter 2 if the pipe is being repaired:\n";
                    for (auto& i : IdP) { PGroup[i].EditPipe(); };
                }
                else cout << "\n There is no such pipe\n";
                break;
            }
            else {
                unordered_set <int> IdP;
                ShowPipe(PGroup);
                cout << "\n Enter the id of the pipes you want to edit(press 0 to finish selecting the id)\n";
                int id = CheckInputNumber(-1, Pipe::MaxIdPipe - 1);
                while (id != 0) {
                    if (PGroup.find(id) != PGroup.end()) {
                        if (PGroup.find(id) != PGroup.end())
                            IdP.insert(id);
                    }
                    else  cout << "There is no such pipe" << endl;
                    id = CheckInputNumber(-1, Pipe::MaxIdPipe - 1);
                }
                //cout << "\nEnter 1 if the pipe is working \n Enter 2 if the pipe is being repaired:\n";
                //int status = CheckInputNumber(0, 2);
                for (auto& i : IdP) {
                    //for (auto& i : IdP)
                    PGroup[i].EditPipe();
                }
            }
        }

        }
    }
}
void EditCs(unordered_map<int, CS>& CsGroup) {
    if (CheckingHaveCs(CsGroup)) {
        cout << "\n 1.Edit one CS\n 2.Edit CSs\n";
        switch (CheckInputNumber(0, 2)) {
        case 1:
        {
            ShowCs(CsGroup);
            cout << "\n Choose CS to edit:  \n";
            int Id = CheckInputNumber(0, CS::MaxIdCs - 1);
            if (CsGroup.find(Id) != CsGroup.end()) {
                CsGroup[Id].EditCs();
                cout << "\nCS was edited\n";
            }
            break;
        }
        case 2:
        {
            unordered_set <int> IdCs;
            cout << "\n Edit  by: \n 1.Name\NoWorkingShop\n 2.Id\n";
            int n = CheckInputNumber(0, 2);
            if (n == 1) {
                auto idcs = SearchCsByFilter(CsGroup);
                if (idcs.size() != 0) {
                    for (auto& i : idcs)
                        CsGroup[i].EditCs();
                }
                else cout << "\n There is no such CS\n";
            }
            else {
                ShowCs(CsGroup);
                cout << "\n Enter the id of the CSs you want to edit(press 0 to finish selecting the id)\n";
                int id = CheckInputNumber(-1, CS::MaxIdCs - 1);
                while (id != 0) {
                    if (CsGroup.find(id) != CsGroup.end()) {
                            IdCs.insert(id);
                    }
                    else  cout << "\n There is no such CS\n" << endl;
                    id = CheckInputNumber(-1, CS::MaxIdCs - 1);
                }
                for (auto& id : IdCs)
                    CsGroup[id].EditCs();
                break;
            }
        }
        }
    }
}
void DeletePipe(unordered_map<int, Pipe>& PGroup) {
    unordered_set <int> IdP;
    ShowPipe(PGroup);
    cout << "\n 1.Delete by filter\n 2.Delete by id\n" << endl;
    int n = CheckInputNumber(0, 2);
    if (n == 2)
    {
        cout << "\n Enter the id of the pipes you want to delete (press 0 to finish selecting the id)\n";
        int id = CheckInputNumber(-1, Pipe::MaxIdPipe -1);
        while (id != 0) {
            if (PGroup.find(id) != PGroup.end()) {
                    IdP.insert(id);
            }
            else  cout << "\n There is no such pipe\n" << endl;
            id = CheckInputNumber(-1, Pipe::MaxIdPipe-1);
        }
        for (auto& i : IdP) { PGroup.erase(PGroup.find(i)); };
    }
    else
    {
        auto idf = SearchPipeByFilter(PGroup);
        for (auto& i : idf) {PGroup.erase(PGroup.find(i));};
    }
    cout << "\nPipe was deleted\n";

}
void DeleteCs(unordered_map<int, CS>& CsGroup) {
    ShowCs(CsGroup);
    cout << "\n 1.Delete be filter\n 2.Delete by id\n" << endl;
    int n = CheckInputNumber(0, 2);
    if (n == 1) {
        auto idf = SearchCsByFilter(CsGroup);
        for (auto& i : idf)
            CsGroup.erase(CsGroup.find(i));
    }
    else {
        unordered_set <int> IdCs;
        cout << "\nEnter the id of the CSs you want to delete(press 0 to finish selecting the id)\n";
        int id = CheckInputNumber(-1, CS::MaxIdCs - 1);
        while (id != 0) {
            if (CsGroup.find(id) != CsGroup.end()) {
                IdCs.insert(id);
            }
            else  cout << "There is no such CS" << endl;
            id = CheckInputNumber(-1, CS::MaxIdCs - 1);
        }
        for (auto& i : IdCs)
            CsGroup.erase(CsGroup.find(i));
    }
    cout << "CS was deleted";
}
void SaveData(const unordered_map<int, Pipe> PGroup,const unordered_map<int, CS> CsGroup) {
    ofstream fout;
    string name;
    cout << "Enter the name file to save the data" << endl;
    cin >> name;
    fout.open(name + ".txt", ios::out);
    fout << PGroup.size() << endl << CsGroup.size() << endl;
    for (auto p : PGroup) {
        p.second.SavePipe(fout);
    }
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
        int  NumberPipe, NumberCs;
        fin.open(name + ".txt");
        fin >> NumberPipe  >> NumberCs;
        for (int i = 1; i < NumberPipe+1; i++)
        {
            newP.LoadPipe(fin);
            PGroup.insert({ newP.GetId(),newP });
            if (Pipe::MaxIdPipe < newP.GetId())
                Pipe::MaxIdPipe = newP.GetId();
        }
        Pipe::MaxIdPipe++;
        for (int i = 1; i < NumberCs+1; i++)
        {
            newCS.LoadCs(fin);
            CsGroup.insert({ newCS.GetId(),newCS });
            if (CS::MaxIdCs < newCS.GetId())
                CS::MaxIdCs = newCS.GetId();
        }
        CS::MaxIdCs++;
        fin.close();
    }
}


int main() { 
    unordered_map<int, Pipe> PGroup;
    unordered_map<int, CS> CsGroup;
    while (1) {
        cout << "\n    Menu\n 1. Add pipe\n 2. Add CS\n 3. View all objects\n 4. Edit pipe\n 5. Edit CS\n 6. Delete pipe \n 7. Delete CS\n 8. Save\n 9. Load\n 0. Exit\n";
        switch (CheckInputNumber(-1, 9)) {
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
            EditCs(CsGroup);
            break;
        case 6:
            DeletePipe(PGroup);
            break;
        case 7:
            DeleteCs(CsGroup);
            break;
        case 8:
            SaveData(PGroup, CsGroup);
            break;
        case 9:
            LoadData(PGroup, CsGroup);
            break;
        }
       
    }
}