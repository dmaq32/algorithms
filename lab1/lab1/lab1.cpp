    #include <iostream>
    #include <fstream>
    #include <string>

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
        int Inwork;
    };

    const string filename = "data.txt"; 

    bool IsFailed() {
        if (cin.fail()) {
            cout << "Error! Please enter a valid number." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            return true; 
        }
        return false; 
    }

    void add_pipe(Pipe& pipe) {
        string name;
        cout << "Type name of pipe:";
        getline(cin >> ws,name);//!!!!!!!!!!!
        pipe.name = name;
        IsFailed();
        while (1) {
            cout << "Type length of pipe:";
            cin >> pipe.length;
            if (IsFailed()) {
                continue;
            }
            else if (pipe.length < 0 || pipe.length > 1500) {
                cout << "Enter existing length!" << endl;
            }
            else {
                break;
            }
        }
        while (1) {
            cout << "Type diameter of pipe:";
            cin >> pipe.diameter;
            if (IsFailed()) {
                continue;
            }
            else if (pipe.diameter < 0 || pipe.diameter > 1200) {
                cout << "Enter existing diameter!" << endl;
            }
            else {
                break;
            }
        }

    }

    void add_station(Station& station) {
        cout << "Type name of station:";
        getline(cin>>ws, station.name);
        IsFailed();
        while (1) {
            cout << "Type amount of workshops in station:";
            cin >> station.workshop_amount;
            if (IsFailed()) {
                continue;
            }
            else if (station.workshop_amount <= 0) {
                cout << "Enter existing amount!" << endl;
            }
            else {
                break;
            }
        }
        while (1) {
            cout << "Type amount of workshops in work:";
            cin >> station.Inwork;
            if (IsFailed()){
                continue;
            }
            else if (station.Inwork < 0 || station.Inwork > station.workshop_amount){
                cout << "Enter amount from 0 to " << station.workshop_amount << "." << endl;
            }
        
            else {
                break;
            }
        }
        cout << "Type class of station:";
        getline(cin >> ws, station.cl4ss);
        IsFailed();

    }

    void save_pipe(Pipe &pipe) {
        ofstream outputF(filename);
        string line;
        if (outputF.is_open()) {
            if (!pipe.name.empty()) {
                outputF << "PIPE PROPERTIES" << endl;
                outputF << pipe.name << endl << pipe.length << endl << pipe.diameter << endl << pipe.fixing << endl;
            }
            else {
                cout << "Check out properties of pipe" << endl;
            }
        }
    }


    void save_station(Station& station) {
        ofstream outputF(filename, ::std::ios::app);
        string line;
        if (outputF.is_open()) {
            if (!station.name.empty()) {
                outputF << "CS PROPERTIES" << endl;
                outputF << station.name << endl << station.workshop_amount << endl << station.Inwork << endl << station.cl4ss << endl;
                cout << "Successfully saved to " << filename << endl;
            }
            else {
                cout << "Check out properties of station" << endl;
                outputF << "CS PROPERTIES" << endl;
            }
        }
    }


    void loadF_pipe(Pipe& pipe) {
        ifstream loadF;
        loadF.open(filename);
        string word, start_marker = "PIPE", end_marker = "CS";
        bool reading = false;

        while (loadF >> word) {
            if (!reading) {
                if (word.find(start_marker) != std::string::npos) {
                    reading = true;
                    loadF >> word; 
                    getline(loadF >> ws,word);
                    pipe.name = word;
                    loadF >> pipe.length; 
                    loadF >> pipe.diameter; 
                    loadF >> pipe.fixing; 
                }
            }
            else {
                
                if (word.find(end_marker) != std::string::npos) {
                    break;
                }
            }
        }
        if (!reading) {
            cout << "Pipe marker not found!" << endl;
            return;
        }
        loadF.close();
    }

    void loadF_station(Station& station) {
        ifstream loadF;
        loadF.open(filename);
        string word, start_marker = "CS";
        bool reading = false;


        while (loadF >> word) {
            if (!reading) {
                if (word.find(start_marker) != std::string::npos) {
                    reading = true;
                    loadF >> word; 
                    getline(loadF >> ws, word);
                    station.name = word;
                    loadF >> station.workshop_amount; 
                    loadF >> station.Inwork;
                    loadF >> station.cl4ss; 
                    break;
                }
            }
        }
        if (!reading) {
            cout << "Station marker not found!" << endl;
            return;
        }
        cout << "Successfully loaded from " << filename << endl;
        loadF.close();
    }

    void output_pipe(Pipe& pipe)
    {
        if (!pipe.name.empty()) {
            cout << "PIPE PROPERTIES" << endl;
            cout << "Name: " << pipe.name << endl << "Length: " << pipe.length << endl << "Diametr: " << pipe.diameter << endl << "Fixing: " << pipe.fixing << endl << endl;
        }
        else {
            cout << "Pipe properties are empty!" << endl;
        }
    }
    void output_station(Station& station)
    {
        if (!station.name.empty()) {
            cout << "CS PROPERTIES" << endl;
            cout << "Name: " << station.name << endl << "Workshop amount: " << station.workshop_amount << endl << "Inwork: " << station.Inwork << endl << "Class:" << station.cl4ss << endl;
        }
        else {
            cout << "Cs properties are empty!" << endl;
        }
    }

    void edit_pipe(Pipe& pipe)
    {
        if (!pipe.name.empty()) {
            pipe.fixing = !pipe.fixing;
            cout << endl << "You changed the value of fixing to " << pipe.fixing << "." << endl;
            }
        else {
            cout << "Pipe options are empty" << endl;
        }
        }

    void edit_station(Station& station)
    {
        if (station.name.empty())
        {
            cout << "Station options are empty" << endl;
            return;
        }

        int value;
        while (1) {
            cout << "Please enter new number of workshops in work from 0 to " << station.workshop_amount << ": ";
            cin >> value;

            if (IsFailed()) {
                continue;
            }
            else if (value < 0 || value > station.workshop_amount) {
                cout << "Error! Value must be between 0 and " << station.workshop_amount << "." << endl;
            }
            else {
                station.Inwork = value;
                cout << "Successfully updated workshops in work to: " << value << endl;
                return;
            }
        }
    }

    int main()
    {
        Pipe pipe;
        Station station;
        int choice;
        while (1) {
            cout << "MAIN MENU:" << endl << "1.Add pipe" << endl << "2.Add station" << endl << "3.View objects " << endl << "4.Edit pipe" << endl << "5.Edit CS" << endl << "6.Save to file" << endl << "7.Load from file" << endl << "0.Exit" << endl;
            cin >> choice;
            if (cin.good() && choice <= 7 && choice >= 0) {
                switch (choice) {
                case 0:
                    return 0;
                case 1:
                    add_pipe(pipe);
                    break;
                case 2:
                    add_station(station);
                    break;
                case 3:
                    output_pipe(pipe);
                    output_station(station);
                    break;
                case 4:
                    edit_pipe(pipe);
                    break;
                case 5:
                    edit_station(station);
                    break;
                case 6:
                    save_pipe(pipe);
                    save_station(station);
                    break;
                case 7:
                    loadF_pipe(pipe);
                    loadF_station(station);
                    break;
                }
            }
            else {
                if (!IsFailed()) {
                    cout << "Error! Input number from 0 to 7" << endl;
                }
            }
        }
    }