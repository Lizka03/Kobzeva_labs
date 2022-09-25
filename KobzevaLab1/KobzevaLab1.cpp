#include <iostream>
using namespace std;
struct Pipe {
    float Lenght = 0, Diameter = 0;
    int Status = -1;
};
struct CS {
    string Name = "";
    int  Workshop = 0, WorkingWorkshop = -1;
    float Efficiency = 0;
};

int main() { 
    CS cs;
    Pipe p;
    int choice = -1;

    while (choice) {
        cout << "    Menu\n 1. Add pipe\n 2. Add CS\n 3. View all objects\n 4. Edit pipe\n 5. Edit CS\n 6. Save\n 7. Load\n 0. Exit";
        cin >> choice;
        switch (choice) {
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        case 5:

            break;
        case 6:

            break;
        case 7:

            break;
        }
    }
}