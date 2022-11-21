#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Pipe.h"
#include "CS.h"
#include "utils.h"

using namespace std;


/*Pipe& ChoosePipe(vector <Pipe>& g) {
    cout << "Enter index: ";
    int x = g.size();
    int index = CheckInputNumber(1, x);
    return g[index - 1];
}*/

int main() { 
    CS cs;
    Pipe p;
    while (1) {
        cout << "\n    Menu\n 1. Add pipe\n 2. Add CS\n 3. View all objects\n 4. Edit pipe\n 5. Edit CS\n 6. Save\n 7. Load\n 0. Exit\n";
        switch (CheckInputNumber(-1,7)) {
        case 0:
            break;
        case 1:
            cin >> p;
            break;
        case 2:
            cin >> cs;
            break;
        case 3:
            p.ShowPipe();
            cs.ShowCs();
            //cout << ChoosePipe(p);
            break;
        case 4:
            p.EditPipe();
            break;
        case 5:
            cs.EditCs();
            break;
        case 6:
        {
            ofstream file;
            string name;
            cout << "Enter the name file to save the data" << endl;
            cin >> name;
            file.open(name+".txt");
            p.SavePipe(file);
            cs.SaveCs(file);
            file.close();
            break;
        }
        case 7:
        {
            ifstream file;
            string name;
            cout << "Enter the name file to load the data" << endl;
            cin >> name;
            file.open(name + ".txt");
            p.LoadPipe(file);
            cs.LoadCs(file);
            file.close();
            break;
        }
        }
    }
}