#include <iostream>
#include <fstream>
#include <string>
#include "pipe.h"
#include "station.h"
#include "manager.h"
#include <format>
#include <chrono>

using namespace std;
using namespace std::chrono;    

int main()
{
    redirect_output_wrapper cerr_out(cerr);
    // string time = format("{:%d_%m_%Y %H_%M_%OS}", zoned_time{ current_zone(), system_clock::now() });
    ofstream logfile("log52");
    if (logfile)
        cerr_out.redirect(logfile);


    Manager manager;
    int choice;
    string filename;


    while (1) {
        manager.display_main_menu();
        cin >> choice;
        log_action(choice);
        if (choice >= 0 && choice <= 13) {
            switch (choice) {
            case 0:
                return 0;
            case 1:
                manager.add_pipe();
                break;
            case 2:
                manager.add_station();
                break;
            case 3:
                manager.display_all_objects();
                break;
            case 4: {
                int id;
                cout << "Enter pipe ID to edit: ";
                cin >> id;
                log_action(id);
                if (IsFailed()) break;
                manager.edit_pipe(id);
                break;
            }
            case 5: {
                int id;
                cout << "Enter station ID to edit: ";
                cin >> id;
                log_action(id);
                if (IsFailed()) break;
                manager.edit_station(id);
                break;
            }
            case 6:
                int id;
                cout << "Enter pipe ID to delete: ";
                cin >> id;
                log_action(id);
                if (IsFailed()) break;
                manager.delete_pipe(id);
                break;

            case 7: {
                int id;
                cout << "Enter station ID to delete: ";
                cin >> id;
                log_action(id);
                if (IsFailed()) break;
                manager.delete_station(id);
                break;
            }
            case 8:
                manager.display_all_pipes();
                break;
            case 9:
                manager.display_all_stations();
                break;
            case 10:
                cout << "Enter filename to save: ";
                cin >> filename;
                log_action(filename);
                manager.save_to_file(filename);
                break;

            case 11:
                cout << "Enter filename to load: ";
                cin >> filename;
                log_action(filename);
                manager.load_from_file(filename);
                break;

            case 12:
                manager.handle_search();
                break;

            case 13:
                manager.handle_pipes_batch_menu();
                break;
            }
        }

        else {
            cout << endl << "Error, enter value between 0 and 13." << endl;
            IsFailed();
            cerr << "[DBG] fail=" << cin.fail() << " eof=" << cin.eof() << '\n';
        }
    }

}
