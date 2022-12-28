#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "Pipe.h"
#include "CS.h"
#include "utils.h"
#include "graf.h"

using namespace std;
bool System::check_only(int x, int y) {
    int k = 0;
    for (auto& i : graphs) {
        if ((i.second.id_entrance == x and i.second.id_exit == y) or (i.second.id_entrance == y and i.second.id_exit == x)) {
            k++;
            cout << "This connection is already exists" << endl;
        }
        if (k == 0)
            return true;
        else return false;
    }
}
bool System::check_obj(int x) {
    int k = 0;
    for (auto& i : graphs) {
        if (i.second.id_entrance == x or i.second.id_exit == x or i.second.id_pipe == x) {
            k++;
            cout << "You can't delete object in connection" << endl;
        }
    }
    if (k == 0) return true;
    else return false;
}
bool System::checking(int x) {
    int n = 0;
    for (auto& i : graphs)
        if (i.second.id_pipe == x)
            n++;
    if (n == 0)
        return true;
    else return false;
}
int System::check_graph(int x) {
    while (check_pipe(x) >= CsGroup[x].getwork()) {
        cout << "Too much connections for this CS, choose another one" << endl;
        x = CheckInputNumber(-1, INT_MAX);
    }
    return x;
}
int System::check_existing(int x) {
    while (CsGroup.find(x) == CsGroup.end()) {
        cout << "There is no such CS, try again" << endl;
        x = CheckInputNumber(-1, INT_MAX);
    }
    return x;
}
int System::edge(int x) {
    int k = -1;
    for (auto& i : PGroup) {
        if (i.second.GetD() == x) {
            if (checking(i.first)) {
                k = i.first;
                return k;
            }
        }
    }
    return k;
}
void System::Graph::save_edge(ofstream& file) {
    file << id_entrance << endl << id_exit << endl << id_pipe << endl;
}
void System::Graph::load_edge(ifstream& file) {
    file >> id_entrance;
    file >> id_exit;
    file >> id_pipe;
}
void AddPipe(System &network) {
    Pipe p;
    cin >> p;
    network.PGroup.insert({ p.GetId(), p });
    network.pipe.insert(p.GetId());
}
void AddCs(System& network) {
    CS cs;
    cin >> cs;
    network.CsGroup.insert({ cs.GetId(), cs });
    network.cs.insert(cs.GetId());
}

int main() {
    System network;
    while (1) {
        cout << "\n    Menu\n 1. Add pipe\n 2. Add CS\n 3. View all objects\n 4. Edit pipe\n 5. Edit CS\n 6. Search pipe \n 7. Search CS\n 8. Save\n 9. Load\n 10. Create a gas transportation system\n 0. Exit\n";
        switch (CheckInputNumber(-1, 10)) {
        case 0:
            break;
        case 1:
            AddPipe(network);
            break;
        case 2:
            AddCs(network);
            break;
        case 3:
            network.information();
            break;
        case 4:
            network.EditPipe();
            break;
        case 5:
            network.EditCs();
            break;
        case 6:
            if (network.PGroup.size() != 0) {
                auto x = network.SearchPipe();
                if (x.size() != 0) {
                    for (auto& i : x)
                        cout << network.PGroup[i] << endl;
                }
                else
                    cout << "There is no such pipe" << endl;
            }
            break;
        case 7:
            if (network.CsGroup.size() != 0) {
                auto x = network.SearchCs();
                if (x.size() != 0) {
                    for (auto& i : x)
                        cout << network.CsGroup[i] << endl;
                }
                else
                    cout << "There is no such CS";
                cout << "There is no CS to find" << endl;

            }
            break;
        case 8:
            network.SaveData();
            break;
        case 9:
            network.LoadData();
            break;
        case 10: {
            cout << "1.Connect 2.Disconnect 3.Show" << endl;
            int choise = CheckInputNumber(0, 3);
            if (choise == 1) {
                if ((network.cs.size() < 2) or (network.pipe.size() < 1))
                    cout << "Not enough objects to create system" << endl;
                else
                    cin >> network;
            }
            else if (choise ==2){
                if (network.graphs.size() != 0) {
                    cout << "Input the entering CS" << endl;
                    int x = CheckInputNumber(-1, INT_MAX);
                    x = network.check_existing(x);
                    cout << "Input the exiting CS" << endl;
                    int y = CheckInputNumber(-1, INT_MAX);
                    y = network.check_existing(y);
                    while (x == y) {
                        cout << "You can't disconnect same CS" << endl;
                        y = CheckInputNumber(-1, INT_MAX);
                        y = network.check_existing(y);
                    }
                    auto i = network.graphs.cbegin();
                    while (i != network.graphs.cend()) {
                        if (((*i).second.id_entrance == x) and ((*i).second.id_exit == y)) {
                            network.graphs.erase(i);
                            break;
                        }
                        i++;
                    }
                }
                else
                    cout << "There is no any system" << endl;
                for (auto& [i, j] : network.graphs)
                    cout <<i<< j.id_entrance << " " << j.id_exit << " " << j.id_pipe << endl;
                break;
            }
            else {
                for (auto& [i, j] : network.graphs) {
                    cout << i << ' ' << j.id_entrance << " " << j.id_exit << " " << j.id_pipe << endl;
                }
                break;
            }

        }
        }
    }
}