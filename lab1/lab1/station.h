#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Station {
private:
    int id = 0;
    void recalculate_unused_percentage();
    string name;
    int workshop_amount;
    string cl4ss;
    int Inwork;
    double unused_workshops_percentage;

public:
    void add_station();
    void output_station();
    void edit_station();
    void save_station(ofstream& outputF);
    void load_station(ifstream& loadF);

    string get_station_name() { return name; }
    int get_station_id() { return id; }
    double get_unused_percentage() { return unused_workshops_percentage; }

    void set_station_id(int new_id) { id = new_id; }
};