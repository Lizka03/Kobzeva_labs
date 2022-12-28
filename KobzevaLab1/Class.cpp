#include "Class.h"
#include "graf.h"
#include "Pipe.h"
#include "CS.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <float.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;

int System::Graph::max_idg = 0;
bool CheckPipeName(Pipe p, string name) {
    return (p.Name.find(name) != string::npos);
}
bool CheckPipeStatus(Pipe p, int status) {
    return (p.Status == status);
}
bool CheckCsName(CS cs, string name) {
    return (cs.GetName().find(name) != string::npos);
}
bool CheckWorkingCs(CS cs, double p) {
    return (cs.GetNotWorkingCs() >= p);
}
unordered_set<int> System::SearchCs() {
    int x;
    unordered_set<int>  id;
    cout << "Search CS by 1.name 2.percentage of unused shops" << endl;
    x = CheckInputNumber(0, 2);
    if (x == 1) {
        string name;
        cout << "Enter the name of CS: " << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        getline(cin, name);
        id = SearchCsByParametr(CsGroup, CheckCsName, name);

    }
    else {
        double k;
        cout << "Enter the percentage of unused shops" << endl;
        k = CheckInputNumber(-1, 100);
        id = SearchCsByParametr(CsGroup, CheckWorkingCs, k);
    }
    return id;
}
unordered_set<int> System::SearchPipe() {
    unordered_set<int> ids;
    int x;
    cout << "Search pipe by 1.name 2.status" << endl;
    x = CheckInputNumber(0, 2);
    if (x == 1) {
        string name;
        cout << "Enter the name of pipe: " << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        getline(cin, name);
        ids = SearchPipeByParametr(PGroup, CheckPipeName, name);
    }
    else {
        int k;
        cout << "Enter status of pipe (1 if repairing, 2 if in work): " << endl;
        k = CheckInputNumber(0, 2);
        ids = SearchPipeByParametr(PGroup, CheckPipeStatus, k);
    }
    return ids;
}
void System::information() {
    for (auto& pipe : PGroup) {
        cout << pipe.second << endl;
    }
    for (auto& cs : CsGroup) {
        cout << cs.second << endl;
    }
}
void System::SaveData() {
    string x;
    cout << "Enter the name of file " << endl;
    cin >> x;
    ofstream file;
    file.open(x + ".txt");
    if (!file)
        cout << "Error" << endl;
    else {
        file << PGroup.size() << " " << CsGroup.size() << " " << graphs.size() << endl;
        for (auto pipe : PGroup)
            pipe.second.SavePipe(file);
        for (auto cs : CsGroup)
            cs.second.SaveCs(file);
        for (auto edge : graphs)
            edge.second.save_edge(file);
    }
}
void System::LoadData() {
    string x;
    int len1, len2, len3;
    Pipe newP;
    CS newCS;
    Graph newGr;
    cout << "Enter the name of file  " << endl;
    cin >> x;
    ifstream file;
    file.open(x + ".txt");
    if (!file)
        cout << "There is no such file";
    else {
        Pipe::MaxIdPipe = 0;
        CS::MaxIdCs = 0;
        PGroup.clear();
        CsGroup.clear();
        file >> len1 >> len2 >> len3;
        for (int i = 0; i < len1; i++) {
            newP.LoadPipe(file);
            PGroup.insert({ newP.GetId(),newP });
            pipe.insert(newP.GetId());
            if (Pipe::MaxIdPipe <= newP.GetId())
                Pipe::MaxIdPipe = newP.GetId() + 1;

        }
        for (int i = 0; i < len2; i++) {
            newCS.LoadCs(file);
            CsGroup.insert({ newCS.GetId(),newCS });
            cs.insert(newCS.GetId());
            if (CS::MaxIdCs <= newCS.GetId())
                CS::MaxIdCs = newCS.GetId() + 1;

        }
        for (int i = 0; i < len3; i++) {
            newGr.load_edge(file);
            graphs.insert({ newGr.id_pipe,newGr });
        }
    }
}
void System::EditCs() {
    vector <int> idcs;
    if (CsGroup.size() != 0) {
        cout << "1.Edit one CS 2.Edit CSs 3.Delete CS" << endl;
        int edit;
        int x;
        edit = CheckInputNumber(0, 3);
        if (edit == 1) {
            int id;
            cout << CsGroup;
            cout << "Choose CS to edit" << endl;
            id = CheckInputNumber(-1, (int)CsGroup.size());
            if (CsGroup.find(id) != CsGroup.end()) {
                CsGroup[id].EditCs();
                cout << "CS was edited";
            }
        }
        if (edit == 2) {
            unordered_set <int> idw;
            cout << "Choose  by 1.filter 2.id" << endl;
            int n;
            n = CheckInputNumber(0, 2);
            if (n == 2) {
                cout << CsGroup;
                cout << "Enter the number of cs you want to edit" << endl;
                int y;
                y = CheckInputNumber(0, (int)CsGroup.size());
                cout << "Enter idetifiers of CSs" << endl;
                for (int i = 0; idw.size() < y; i++) {
                    cin >> x;
                    if (CsGroup.find(x) != CsGroup.end())
                        idw.insert(x);
                    else {

                        cout << "There is no such cs" << endl;
                    }
                }
                for (auto& id : idw)

                    CsGroup[id].EditCs();
            }

            else {
                auto idp = SearchCs();
                if (idp.size() != 0) {
                    for (auto& i : idp)
                        CsGroup[i].EditCs();
                }

                else {
                    cout << "There is no such CS";

                }

            }
        }
        if (edit == 3) {
            cout << "1. identifier of one CS you want to delete 2.delete some CS" << endl;
            int d;
            d = CheckInputNumber(0, 2);
            if (d == 1) {
                cout << CsGroup;
                cout << "Enter id of CS you want to delete" << endl;
                int n;
                n = CheckInputNumber(-1, CS::MaxIdCs - 1);
                
                while (CsGroup.find(n) == CsGroup.end()) {
                    cout << "There is no such cs" << endl;
                    n = CheckInputNumber(-1, CS::MaxIdCs - 1);
                }
                CsGroup.erase(CsGroup.find(n));
                if (check_obj(n))
                    CsGroup.erase(CsGroup.find(n));
            }
            else {
                unordered_set <int> idd;
                cout << "1.delete by filter 2.delete by id" << endl;
                int n;
                n = CheckInputNumber(0, 2);
                if (n == 2) {
                    cout << CsGroup;
                    cout << "Enter the number of cs you want to edit" << endl;
                    int y;
                    int x;
                    y = CheckInputNumber(0, (int)CsGroup.size());
                    cout << "Enter idetifiers of CSs" << endl;
                    for (int i = 0; idd.size() < y; i++) {
                        x = CheckInputNumber(-1, CS::MaxIdCs);
                        if (CsGroup.find(x) != CsGroup.end())
                            idd.insert(x);
                        else cout << "There is no such cs";
                    }
                    for (auto& i : idd) {
                        if (check_obj(i))
                            CsGroup.erase(CsGroup.find(i));
                    }
                }
                else {
                    auto idp = SearchCs();
                    if (idp.size() != 0) {
                        for (auto& i : idp) {
                            if (check_obj(i))
                            CsGroup.erase(CsGroup.find(i));
                        }
                    }
                    else {
                        cout << "There is no such cs" << endl;


                    }
                }

            }
        }
    }
    else
        cout << "There is no CS to edit" << endl;
}
void System::EditPipe()
{
    if (PGroup.size() != 0) {
        cout << "1.Choose one pipe 2.Choose pipes 3.Delete pipe" << endl;;
        int edit = CheckInputNumber(0, 3);
        if (edit == 1) {
            cout << "1.Choose pipe to edit" << endl;
            cout << PGroup;
            int id = CheckInputNumber(-1, (int)PGroup.size());
            if (PGroup.find(id) != PGroup.end()) {
                PGroup[id].EditPipe();
                cout << "Pipe was edited" << endl;
            }
            else
                cout << "There is no such pipe";
        }
        if (edit == 2) {
            cout << "Choose pipes by 1.filter 2.id" << endl;
            int x = CheckInputNumber(0, 2);
            if (x == 1) {
                auto idp = SearchPipe();
                if (idp.size() != 0) {
                    cout << "Enter new status (0 if repairing, 1 if works)" << endl;
                    bool s;
                    s = CheckInputNumber(0, 1);
                    for (auto& i : idp)
                        PGroup[i].Status = s;
                }

                else {
                    cout << "There is no such pipe";

                }
            }


            if (x == 2) {
                unordered_set <int> ids;
                cout << PGroup;
                cout << "Enter the number of identifiers of pipe you want to edit" << endl;
                int n;
                int id;
                n = CheckInputNumber(0, (int)PGroup.size());
                cout << "Enter idetifiers of pipes" << endl;
                for (int i = 0; ids.size() < n; i++) {
                    id = CheckInputNumber(-1, Pipe::MaxIdPipe - 1);
                    if (PGroup.find(id) != PGroup.end()) {
                        if (PGroup.find(id) != PGroup.end())
                            ids.insert(id);
                    }
                    else
                    {
                        cout << "There is no such pipe" << endl;;
                    }
                }
                cout << "Enter new status (0 if repairing, 1 if works)" << endl;
                bool s;
                s = CheckInputNumber(-1, 1);
                for (auto& i : ids) {
                    PGroup[i].Status = s;
                }
            }
        }
        if (edit == 3) {
            cout << "1. identifier of one pipe you want to delete 2.delete some pipes" << endl;
            int d;
            d = CheckInputNumber(0, 2);
            if (d == 1) {
                cout << PGroup;
                cout << "Enter id of pipe you want to delete" << endl;
                int n;
                n = CheckInputNumber(-1, Pipe::MaxIdPipe - 1);
                while (PGroup.find(n) == PGroup.end()) {
                    cout << "There is no such pipe" << endl;
                    n = CheckInputNumber(-1, Pipe::MaxIdPipe - 1);
                }
                if (check_obj(n))
                PGroup.erase(PGroup.find(n));
            }

            else {
                unordered_set <int> ids;
                cout << "1.delete by filter 2.delete by id" << endl;
                int action = CheckInputNumber(0, 2);
                if (action == 2) {
                    cout << PGroup;
                    cout << "Enter the number of pipe you want to edit" << endl;;
                    int n = CheckInputNumber(1, (int)PGroup.size());
                    cout << "Enter idetifiers of pipes" << endl;

                    while (ids.size() < n)
                    {
                        int x = CheckInputNumber(-1, Pipe::MaxIdPipe - 1);
                        if (PGroup.find(x) != PGroup.end())
                            ids.insert(x);
                        else
                            cout << "There is no such pipe" << endl;
                    }

                    for (auto& id : ids) {
                        if (check_obj(id))
                        PGroup.erase(PGroup.find(id));
                    }

                }

                else {
                    auto idp = SearchPipe();
                    if (idp.size() != 0) {
                        for (auto& i : idp) {
                            if (check_obj(i))
                            PGroup.erase(PGroup.find(i));
                        }
                        cout << "Pipe was deleted";
                    }
                    else {
                        cout << "There is no such pipe";

                    }

                }
            }

        }
    }
    else
        cout << "There is no pipe to edit" << endl;
}
int System::check_pipe(int x) {
    int k = 0;
    if (graphs.size() != 0) {
        for (auto& i : graphs) {
            if ((i.second.id_entrance == x) or (i.second.id_exit == x))
                k++;
        }
    }
    return k;
}
ostream& operator<<(ostream& out, unordered_set<int> s) {
    cout << "Free objects: ";
    for (auto& i : s)
        cout << i << " ";
    cout << endl;
    return out;
}
istream& operator>> (istream& in, System& s) {
    bool k = 1;
    System::Graph gr;
    cout << s.cs;
    cout << "Choose CS (id) on entrance" << endl;
    gr.id_entrance = CheckInputNumber(-1, INT_MAX);
    while (s.check_pipe(gr.id_entrance) >= s.CsGroup[gr.id_entrance].getwork()) {
        cout << "Too much connections for this CS, choose another one" << endl;
        gr.id_entrance = CheckInputNumber(-1, INT_MAX);
    }
    while (s.CsGroup.find(gr.id_entrance) == s.CsGroup.end()) {
        cout << "There is no such CS, try again" << endl;
        gr.id_entrance = CheckInputNumber(-1, INT_MAX);
    }
    cout << s.cs;
    cout << "Choose CS(id) on exit" << endl;
    gr.id_exit = CheckInputNumber(-1, INT_MAX);
    while (s.check_pipe(gr.id_exit) >= s.CsGroup[gr.id_exit].getwork()) {
        cout << "Too much connections for this CS, choose another one" << endl;
        gr.id_entrance = CheckInputNumber(-1, INT_MAX);
    }
    while (gr.id_exit == gr.id_entrance) {
        cout << "You can't connect CS with itself" << endl;
        gr.id_exit = CheckInputNumber(-1, INT_MAX);
        while (s.CsGroup.find(gr.id_exit) == s.CsGroup.end()) {
            cout << "There is no such CS, try again" << endl;
            gr.id_exit = CheckInputNumber(-1, INT_MAX);
        }
    }
    if (s.graphs.size() != 0) {
        for (auto& i : s.graphs) {
            if (i.second.id_entrance == gr.id_entrance and i.second.id_exit == gr.id_exit) {
                cout << "This connection is already exists" << endl;
                k = 0;
            }
        }
    }
    if (k) {
        cout << "Choose diameter of pipe to connect: 500, 600 or 1400" << endl;
        double dia_pipe = CheckInputNumber(499.0, 1400.0);
        int k = -1;
        for (auto& i : s.PGroup) {
            if (s.graphs.size() != 0) {
                for (int j = i.first; j < s.graphs.size(); j++) {
                    if (s.graphs[j].id_pipe != i.first) {
                        k = i.first;
                    }
                    else {
                        k = -1;
                        break;
                    }

                }
            }
            else
            {
                k = i.first;
                break;
            }

        }
        if (k==-1){
            cout << "There is no such pipe, try again(1) or create it(2)" << endl;
            int choise = CheckInputNumber(0, 2);
            if (choise == 2) {
                Pipe p;
                cin >> p;
                s.PGroup.insert({ p.GetId(), p });
                gr.id_pipe = p.GetId()-1;
            }
            cout << "Choose diameter of pipe to connect: 500, 600 or 1400" << endl;
            dia_pipe = CheckInputNumber(-1.0, DBL_MAX);
            for (auto& i : s.PGroup) {
                if (i.second.GetD() == dia_pipe) {
                    for (auto& i : s.graphs) {
                        if (i.second.id_pipe != dia_pipe) {
                            k = i.first;
                            break;
                        }
                    }
                }

            }
            s.graphs.insert({ gr.id,gr });
        }
        //gr.id_pipe = k;
        //s.graphs.insert({ gr.id,gr});
    }
    else {
        return in;
    }
    return in;

}