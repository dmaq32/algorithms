#include <iostream>
#include <iomanip>
#include <ostream>
using namespace std;

struct Pipe {
    string name;
    double length;
    double diameter;
    bool fixing = false;
};

struct Station {
    string name;
    int workshop_amount;
    string cl4ss;
    double Inwork;
};


void add_pipe(Pipe& pipe) {
    bool flag1 = false, flag2 = false;
    cout << "Type name of pipe:";
    cin >> pipe.name;
    while (!flag1) {
        cout << "Type length of pipe:";
        cin >> pipe.length;
        if(cin.fail()) {
            cout << "Error! Please enter a valid number." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else {
            flag1 = true;
        }
    }
    while (!flag2) {
        cout << "Type diameter of pipe:";
        cin >> pipe.diameter;
        if (cin.fail()) {
            cout << "Error! Please enter a valid number." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else {
            flag2 = true;
        }
    }

}

void add_station(Station& station) {
    bool flag1 = false, flag2 = false;
    cout << "Type name of station:";
    cin >> station.name;
    while (!flag1) {
        cout << "Type amount of workshops in station:";
        cin >> station.workshop_amount;
        if (cin.fail()) {
            cout << "Error! Please enter a valid number." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else {
            flag1 = true;
        }
    }
    while (!flag2) {
        cout << "Type amount of workshops in work:";
        cin >> station.Inwork;
        if (cin.fail()) {
            cout << "Error! Please enter a valid number." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else {
            flag2 = true;
        }
    }
    cout << "Type class of station:";
    cin >> station.cl4ss;
}

void output(Pipe& pipe, Station& station)
{
    cout << endl << "PIPE PROPERTIES" << endl;
    cout << "Name: " << pipe.name << endl << "Length: " << pipe.length << endl << "Diametr: " << pipe.diameter << endl << "Fixing: " << pipe.fixing << endl << endl;
    cout << "CS PROPERTIES" << endl;
    cout << "Name: " << station.name << endl << "Workshop amount: " << station.workshop_amount << endl << "Inwork: " << station.Inwork << endl << "Class:" << station.cl4ss << endl;
}

void edit_pipe(Pipe& pipe)
{
    pipe.fixing = !pipe.fixing;
        cout << endl << "You changed the value of fixing to " << pipe.fixing << "." << endl;
}

void edit_station(Station& station)
{
    int value;
    bool flag = false;

    while (!flag) {
        cout << "Please enter new number of workshops in work    from 0 to " << station.workshop_amount << ": ";
        cin >> value;

        if (cin.fail()) {
            cout << "Error! Please enter a valid number." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else if (value < 0 || value > station.workshop_amount) {
            cout << "Error! Value must be between 0 and " << station.workshop_amount << "." << endl;
        }
        else {
            flag = true;
        }
    }

    station.Inwork = value;
    cout << "Successfully updated workshops in work to: " << value << endl;
}

int main()
{
    Pipe pipe;
    Station station;
    int choice = 10;
    while (choice != 0) {
        cout << "MAIN MENU:" << endl << "1.Add pipe" << endl << "2.Add station" << endl << "3.View objects " << endl << "4.Edit pipe" << endl << "5.Edit CS" << endl << "0.Exit" << endl;
        cin >> choice;
        if (choice == 1)
            add_pipe(pipe);
        else if (choice == 2)
            add_station(station);
        else if (choice == 3)
            output(pipe, station);
        else if (choice == 4)
            edit_pipe(pipe);
        else if (choice == 5)
            edit_station(station);
        else if (choice == 0)
            break;
        else
            cout << "Invalid choice! Please try again." << endl;
    }
}
