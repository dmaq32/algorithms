#include <iostream>
#include <fstream>
#include <string>
#include "pipe.h"
#include "station.h"
#include "Utils.h"
#include "manager.h"
#include <format>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main()
{
    redirect_output_wrapper cerr_out(cerr);
    string time = format("{:%d_%m_%Y_%H_%M_%OS}", zoned_time{ current_zone(), system_clock::now() });
    ofstream logfile("logs/log_" + time);
    if (logfile)
        cerr_out.redirect(logfile);

    Manager manager;
  //  string filename;

    while (1) {
        manager.display_main_menu();
        int choice = GetCorrectNumber(0, 17);
        switch (choice) {
        case 0: {
            return 0;
        }
        case 1: {
            manager.add_pipe();
            break;
        }
        case 2: {
            manager.add_station();
            break;
        }
        case 3: {
            manager.display_all_objects();
            break;
        }
        case 4: {
            cout << "Enter pipe ID to edit: ";
            int id = GetCorrectNumber(1, INT_MAX);
            manager.edit_pipe(id);
            break;
        }
        case 5: {
            cout << "Enter station ID to edit: ";
            int id = GetCorrectNumber(1, INT_MAX);
            manager.edit_station(id);
            break;
        }
        case 6: {
            cout << "Enter pipe ID to delete: ";
            int id = GetCorrectNumber(1, INT_MAX);
            manager.delete_pipe(id);
            break;
        }
        case 7: {
            cout << "Enter station ID to delete: ";
            int id = GetCorrectNumber(1, INT_MAX);
            manager.delete_station(id);
            break;
        }
        case 8:
            manager.display_all_pipes();
            break;
        case 9:
            manager.display_all_stations();
            break;
        case 10: {
            string filename;
            cout << "Enter filename to save: ";
            INPUT_LINE(cin, filename);
            manager.save_to_file(filename);
            break;
        }
        case 11: {
            string filename;
            cout << "Enter filename to load: ";
            INPUT_LINE(cin, filename);
            manager.load_from_file(filename);
            break;
        }
        case 12:
            manager.handle_search();
            break;

        case 13:
            manager.handle_pipes_batch_menu();
            break;

        case 14:
            manager.connect_station();
            break;

        case 15:
            manager.topological_sort();
            break;
        case 16:
            manager.max_flow();
            break;
        case 17:
            manager.shortest_path();
        }
    }

}
