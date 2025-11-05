#include "station.h"
#include "Manager.h"

void Station::recalculate_unused_percentage() {
    unused_workshops_percentage = (workshop_amount - Inwork) / (double)workshop_amount * 100;
}

void Station::add_station() {
    cout << "Type name of station:";
    getline(cin >> ws, name);
    log_action(name);
    while (1) {
        cout << "Type amount of workshops in station:";
        cin >> workshop_amount;
        if (std::cin.eof()) break;  
        log_action(workshop_amount);
        if (IsFailed()) {
            continue;
        }
        else if (workshop_amount <= 0) {
            cout << "Enter existing amount!" << endl;
        }
        else {
            break;
        }
    }

    while (1) {
        cout << "Type amount of workshops in work:";
        cin >> Inwork;
        log_action(Inwork);
        if (IsFailed()) {
            continue;
        }
        else if (Inwork < 0 || Inwork > workshop_amount) {
            cout << "Enter amount from 0 to " << workshop_amount << "." << endl;
        }
        else {
            break;
        }
    }

    cout << "Type class of station:";
    getline(cin >> ws, cl4ss);
    log_action(cl4ss);
    recalculate_unused_percentage();
}

void Station::output_station() {
    if (!name.empty()) {
        cout << endl << "ID: " << id << endl;
        cout << "Name: " << name << endl << "Workshop amount: " << workshop_amount << endl
            << "Inwork: " << Inwork << endl << "Unused workshops percentage: "
            << unused_workshops_percentage << "%" << endl << "Class: " << cl4ss << endl;
    }
    else {
        cout << "CS properties are empty!" << endl;
    }
}

void Station::edit_station() {
    if (name.empty()) {
        cout << "Station options are empty" << endl;
        return;
    }

    int value;
    while (1) {
        cout << "Please enter new number of workshops in work from 0 to " << workshop_amount << ": ";
        cin >> value;
        log_action(value);

        if (IsFailed()) {
            continue;
        }
        else if (value < 0 || value > workshop_amount) {
            cout << "Error! Value must be between 0 and " << workshop_amount << "." << endl;
        }
        else {
            Inwork = value;
            recalculate_unused_percentage();
            cout << "Successfully updated workshops in work to: " << value << endl;
            return;
        }
    }
}

void Station::save_station(ofstream& outputF){
    if (!name.empty()) {
        outputF << "CS" << endl;
        outputF << id << endl << name << endl << workshop_amount << endl
            << Inwork << endl << cl4ss << endl;
    }
}

void Station::load_station(ifstream& loadF) {
    loadF >> id;
    getline(loadF >> ws, name);
    loadF >> workshop_amount;
    loadF >> Inwork;
    getline(loadF >> ws, cl4ss);
    recalculate_unused_percentage();

}