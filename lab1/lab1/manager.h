#pragma once
#include <vector>
#include <unordered_map>
#include "pipe.h"
#include "station.h"

template <typename T>
void log_action(T action);
bool IsFailed();

using namespace std;


class redirect_output_wrapper
{
    std::ostream& stream;
    std::streambuf* const old_buf;

public:
    redirect_output_wrapper(std::ostream& src)
        : stream(src), old_buf(src.rdbuf()) {
    }

    ~redirect_output_wrapper() {
        stream.rdbuf(old_buf);
    }

    void redirect(const std::ostream& dest) const {
        stream.rdbuf(dest.rdbuf());
    }
};


class Manager {
private:
    unordered_map<int, Pipe> pipes;
    unordered_map<int, Station> stations;
    int nextStationId = 1;
    int nextPipeId = 1;

public:
    void add_pipe();
    void display_all_pipes();
    void edit_pipe(int id);
    void delete_pipe(int id);

    void add_station();
    void display_all_stations() ;
    void edit_station(int id);
    void delete_station(int id);

    void handle_search();
    void display_main_menu();
    void display_search_menu();
    void display_all_objects();
    void save_to_file(string& filename) ;
    void load_from_file(string& filename);
    void edit_pipes_batch(vector<int>& ids);
    void delete_pipes_batch(vector<int>& ids);
    void pipes_batch_menu(vector<int>& ids);
    void handle_pipes_batch_menu();

    vector<int> find_pipes_by_name(string& name);
    vector<int> find_pipes_by_status(bool fixing_status);
    vector<int> find_stations_by_name(string& name);
    vector<int> find_stations_by_unused_percentage(double min_percent, double max_percent);
    
};

