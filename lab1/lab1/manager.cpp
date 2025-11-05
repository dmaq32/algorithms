#include "manager.h"
#include "pipe.h"
#include <iostream>
#include <chrono>
#include <set>
using namespace std;


bool IsFailed() {
    if (cin.fail()) {
        cout << "Error! Please enter a valid number." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        return true;
    }
    return false;
}
template <typename T>
void log_action(T action) {
    cerr << action << endl;
}

void Manager::display_search_menu() {
    cout << endl << "SEARCH MENU:" << endl
        << "1. Find pipes by name" << endl << "2. Find pipes by repair status" << endl << "3. Find stations by name" << endl << "4. Find stations by unused percentage" << endl << "0. Back to main menu" << endl << "Choose option: ";
}

void Manager::display_main_menu() {
    cout << endl << "MAIN MENU:" << endl<< "1. Add pipe" << endl<< "2. Add station" << endl<< "3. View all objects" << endl << "4. Edit pipe" << endl<< "5. Edit station" << endl << "6. Delete pipe" << endl << "7. Delete station" << endl << "8. View all pipes" << endl<< "9. View all stations" << endl << "10. Save to file" << endl << "11. Load from file" << endl << "12. Search objects" << endl <<"Batch edit pipes" << endl << "0. Exit" << endl
<< "Choose option: ";

}

void Manager::display_all_pipes() {
    if (pipes.empty()) {
        cout << "No pipes available." << endl;
        return;
    }

    cout << "ALL PIPES" << endl;

    for (auto& [id, pipe] : pipes) {
        pipe.output_pipe();
    }
}

void Manager::display_all_stations() {
    if (stations.empty()) {
        cout << "No stations available." << endl;
        return;
    }

    cout << "ALL STATIONS" << endl;
    for (auto& [id, station] : stations) {
        station.output_station();
    }
}

void Manager::display_all_objects() {
    display_all_pipes();
    display_all_stations();
}
void Manager::save_to_file(string& filename) {
    ofstream outputF(filename);
    if (outputF.is_open()) {
        outputF << "NEXT_IDS" << endl;
        outputF << nextPipeId << ' ' << nextStationId << endl;

        for (auto& [id, pipe] : pipes) {
            pipe.save_pipe(outputF);
        }

        for (auto& [id, station] : stations) {
            station.save_station(outputF);
        }

        cout << "Successfully saved to " << filename << endl;
    }
    else {
        cout << "Error opening file for writing!" << endl;
    }
}


void Manager::add_pipe() {
    Pipe newPipe;
    newPipe.set_station_id(nextPipeId);
    newPipe.add_pipe();
    pipes[nextPipeId] = newPipe;
    cout << "Pipe added with ID: " << nextPipeId << endl;
    nextPipeId++;
}

void Manager::edit_pipe(int id) {
    if (auto it = pipes.find(id); it != pipes.end()) {
        it->second.edit_pipe();
        cout << endl << "You successfully changed the fixing value of Pipe with ID " + to_string(id) + "to" + to_string(it->second.get_is_fixing()) << endl;
    }
    else {
        cout << "Pipe with ID " << id << " not found!" << endl;
    }
}

void Manager::delete_pipe(int id) {
    if (auto it = pipes.find(id); it != pipes.end()) {
        pipes.erase(it);
        cout << "Pipe with ID " << id << " deleted." << endl;
    }
    else {
        cout << "Pipe with ID " << id << " not found!" << endl;
    }
}

void Manager::add_station() {
    Station newStation;
    newStation.set_station_id(nextStationId);
    newStation.add_station();
    stations[nextStationId] = newStation;
    cout << "Station added with ID: " << nextStationId << endl;
    nextStationId++;
}

void Manager::edit_station(int id) {
    if (auto it = stations.find(id); it != stations.end()) {
        it->second.edit_station();
    }
    else {
        cout << "Station with ID " << id << " not found!" << endl;
    }
}

void Manager::delete_station(int id) {
    if (auto it = stations.find(id); it != stations.end()) {
        stations.erase(it);
        cout << "Station with ID " << id << " deleted." << endl;
    }
    else {
        cout << "Station with ID " << id << " not found!" << endl;
    }
}


void Manager::load_from_file(string& filename) {
    ifstream loadF(filename);
    if (loadF.is_open()) {
        pipes.clear();
        stations.clear();
        
        string marker;
        while (loadF >> marker) {
            if (marker == "NEXT_IDS") {
                loadF >> nextPipeId >> nextStationId;
            }
            else if (marker == "PIPE") {
                Pipe pipe;
                pipe.load_pipe(loadF);
                pipes[pipe.get_pipe_id()] = pipe;
            }
            else if (marker == "CS") {
                Station station;
                station.load_station(loadF);
                stations[station.get_station_id()] = station;
            }
        }
        
        cout << "Successfully loaded from " << filename << endl;
        cout << nextPipeId << " " <<  nextStationId << endl;
    } else {
        cout << "Error opening file for reading!" << endl;
    }
}
void Manager::handle_search() {
    int choice;
    string search_name;
    bool repair_status;
    double min_percent, max_percent;
    vector<int> found_ids;

    while (true) {
        display_search_menu();
        cin >> choice;
        log_action(choice);
        if (IsFailed()) continue;

        switch (choice) {
        case 0:
            return;
        case 1: {
            cout << "Enter pipe name to search: ";
            cin >> search_name;
            log_action(search_name);
            found_ids = find_pipes_by_name(search_name);
            cout << "Found " << found_ids.size() << " pipes:" << endl;
            for (int id : found_ids) {
                cout << "Pipe ID: " << id << endl;
            }
            break;
        }
        case 2: {
            cout << "Enter repair status (0 - working, 1 - in repair): ";
            cin >> repair_status;
            log_action(repair_status);
            found_ids = find_pipes_by_status(repair_status);
            cout << "Found " << found_ids.size() << " pipes:" << endl;
            for (int id : found_ids) cout << "Pipe ID: " << id << endl;
            break;
        }
        case 3: {
            cout << "Enter station name to search: ";
            cin >> search_name;
            log_action(search_name);
            found_ids = find_stations_by_name(search_name);
            cout << "Found " << found_ids.size() << " stations:" << endl;
            for (int id : found_ids) {
                cout << "Station ID: " << id << endl;
            }
            break;
        }
        case 4: {
            cout << "Enter minimum unused percentage: ";
            cin >> min_percent;
            log_action(min_percent);
            cout << "Enter maximum unused percentage: ";
            cin >> max_percent;
            log_action(max_percent);
            found_ids = find_stations_by_unused_percentage(min_percent, max_percent);
            cout << "Found " << found_ids.size() << " stations:" << endl;
            for (int id : found_ids) {
                cout << "Station ID: " << id << endl;
            }
            break;
        }
        }
    }
    }

vector<int> Manager::find_pipes_by_name(string& name){
    vector<int> result;
    for (auto& [id, pipe] : pipes) {
        if (pipe.get_pipe_name().find(name) != string::npos) {
            result.push_back(id);
        }
    }
    return result;
}

vector<int> Manager::find_pipes_by_status(bool fixing_status) {
    vector<int> result;
    for (auto& [id, pipe] : pipes) {
        if (pipe.get_is_fixing() == fixing_status) {
            result.push_back(id);
        }
    }
    return result;
}

vector<int> Manager::find_stations_by_name(string& name){
    vector<int> result;
    for (auto& [id, station] : stations) {
        if (station.get_station_name().find(name) != string::npos) {
            result.push_back(id);
        }
    }
    return result;
}


vector<int> Manager::find_stations_by_unused_percentage(double min_percent, double max_percent){
    vector<int> result;
    for (auto& [id, station] : stations) {
        if (station.get_unused_percentage() >= min_percent &&
            station.get_unused_percentage() <= max_percent) {
            result.push_back(id);
        }
    }
    return result;
}

void Manager::edit_pipes_batch(vector<int>& ids) {
    if (ids.empty()) {
        cout << "No pipes selected for editing." << endl;
        return;
    }

    cout << "Choose editing mode:"<< endl << "1. Toggle fixing status for all selected pipes" << endl << "2. Set specific fixing status (0 - working, 1 - under repair)" << endl << "Enter option: ";

    int choice;
    cin >> choice;
    log_action(choice);

    if (IsFailed()) return;

    bool new_status = false;
    if (choice == 2) {
        cout << "Enter status (0 - working, 1 - under repair): ";
        cin >> new_status;
        log_action(new_status);
        if (IsFailed()) return;
    }

    int edited_count = 0;
    for (int id : ids) {
        auto it = pipes.find(id);
        if (it != pipes.end()) {
            if (choice == 1)
                it->second.set_is_fixing(!it->second.get_is_fixing());
            else if (choice == 2)
                it->second.set_is_fixing(new_status);
            edited_count++;
        }
    }
    cout << "Successfully edited " << edited_count << " pipes." << endl;
}

void Manager::delete_pipes_batch(vector<int>& ids) {
    if (ids.empty()) {
        cout << "No pipes selected for deletion." << endl;
        return;
    }

    cout << "Are you sure you want to delete " << ids.size() << " pipes? (1 - yes, 0 - no): ";
    int confirm;
    cin >> confirm;
    log_action(confirm);
    if (IsFailed() || confirm != 1) {
        cout << "Operation canceled." << endl;
        return;
    }

    int deleted_count = 0;
    for (int id : ids) {
        if (pipes.erase(id)) {
            deleted_count++;
        }
    }
    cout << "Deleted " << deleted_count << " pipes." << endl;
}

void Manager::pipes_batch_menu(vector<int>& ids) {
    int choice;
    cout << "Choose operation:" << endl << "1 - batch delete." << endl << "2 - batch edit." << endl;
    cin >> choice;
    log_action(choice);
    if (IsFailed() || choice < 1 || choice > 2) return;

    switch (choice) {
        case 1:
            delete_pipes_batch(ids);
            break;
        case 2:
            edit_pipes_batch(ids);
            break;
    }
}
void Manager::handle_pipes_batch_menu() {
    if (pipes.empty()) {
        cout << "No pipes available for batch editing.\n";
        return;
    }

    vector<int> selected_ids;
    cout << endl << "Batch Operation Mode" << endl << "1 - Select all pipes" << endl << "2 - Select by name" << endl << "3 - Select by status" << endl << "4 - Select manually by ID" << endl << "0 - Cancel" << endl << "Enter option: ";

    int choice;
    cin >> choice;
    log_action(choice);

    if (IsFailed() || choice == 0)
        return;
    switch (choice) {
    case 1:
        for (auto& [id, _] : pipes)
            selected_ids.push_back(id);
        break;
    case 2: {
        string name;
        cout << "Enter name: ";
        cin >> name;
        log_action(name);
        selected_ids = find_pipes_by_name(name);
        break;
    }
    case 3: {
        bool status;
        cout << "Enter status (0 - working, 1 - under repair): ";
        cin >> status;
        log_action(status);
        selected_ids = find_pipes_by_status(status);
        break;
    }
    case 4: {
        set<int> selected_ids_set;
        int id;
        cout << "Enter pipe IDs separated by spaces (0 to finish): ";
        while (cin >> id && id != 0) {
            log_action(id);
            selected_ids_set.insert(id);
        }
        IsFailed();

        selected_ids.assign(selected_ids_set.begin(), selected_ids_set.end());

        break;
        }
    }

    if (selected_ids.empty()) {
        cout << "No pipes selected for batch operation." << endl;
        return;
    }

    cout << endl << "Selected " << selected_ids.size() << " pipes: ";
    for (int id : selected_ids) cout << id << ' ';
    cout << endl;
    pipes_batch_menu(selected_ids);
}