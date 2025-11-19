#include "pipe.h"
#include "Utils.h"

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
std::istream& operator>>(std::istream& in, Pipe& p) {
    std::cout << "Type pipe name: ";
    INPUT_LINE(in, p.name);

    std::cout << "Type pipe length: ";
    p.length = GetCorrectNumber<double>(0, 1500);

    std::cout << "Type pipe diameter: ";
    p.diameter = GetCorrectNumber<double>(0, 1200);

    return in;
}