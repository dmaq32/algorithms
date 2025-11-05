#include "pipe.h"
#include "Manager.h"


void Pipe::add_pipe() {
    cout << "Type name of pipe:";
    getline(cin >> ws, name);
    log_action(name);
    while (1) {
        cout << "Type length of pipe:";
        cin >> length;
        log_action(length);
        if (IsFailed()) {
            continue;
        }
        else if (length < 0 || length > 1500) {
            cout << "Enter existing length!" << endl;
        }
        else {
            break;
        }
    }

    while (1) {
        cout << "Type diameter of pipe:";
        cin >> diameter;
        log_action(diameter);
        if (IsFailed()) {
            continue;
        }
        else if (diameter < 0 || diameter > 1200) {
            cout << "Enter existing diameter!" << endl;
        }
        else {
            break;
        }
    }
}

void Pipe::output_pipe() {
    if (!name.empty()) {
        cout << endl << "PIPE PROPERTIES" << endl;
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl << "Length: " << length << endl
            << "Diameter: " << diameter << endl << "Fixing: " << fixing << endl << endl;
    }
    else {
        cout << "Pipe properties are empty!" << endl;
    }
}

void Pipe::edit_pipe() {
    if (name.empty()) {
        
    }
    else {
        fixing = !fixing;
       
    }
}

void Pipe::save_pipe(ofstream& outputF) {
    if (!name.empty()) {
        outputF << "PIPE" << endl;
        outputF << id << endl << name << endl << length << endl << diameter << endl << fixing << endl;
    }
}

void Pipe::load_pipe(ifstream& loadF) {
    loadF >> id;
    getline(loadF >> ws, name);
    loadF >> length;
    loadF >> diameter;
    loadF >> fixing;
}