#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Pipe {
private:
    int id = 0;
    string name;
    double length;
    double diameter;
    bool fixing = false;
public:
    void add_pipe();
    void output_pipe();
    void edit_pipe();
    void save_pipe(ofstream& outputF);
    void load_pipe(ifstream& loadF);

    string get_pipe_name() { return name; }
    bool get_is_fixing() { return fixing; }
    int get_pipe_id() { return id; }

    void set_station_id(int new_id) { id = new_id; }
    void set_is_fixing(bool new_fixing) { fixing = new_fixing; }
};
