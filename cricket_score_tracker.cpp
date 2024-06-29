#include <iostream>
#include <cstdlib>
#include <iomanip>

#define MAX_PLAYERS 100

using namespace std;

typedef enum player_type {
    PLAYER_1,
    PLAYER_2,
    PLAYER_3,
    PLAYER_4,
    PLAYER_5,
    PLAYER_6,
    PLAYER_7,
    PLAYER_8,
    PLAYER_9,
    PLAYER_10,
    PLAYER_11
} player_type;

struct Player {
    int id;
    player_type type;
    int runs;
};

Player players[MAX_PLAYERS];
int num_players = 0;
int total_runs = 0;
int runs_by_player[MAX_PLAYERS] = {0};

void clear_screen() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

void add_player() {
    int type, runs;
    if (num_players >= MAX_PLAYERS) {
        cout << "Maximum number of players reached." << endl;
        return;
    }
    
    cout << "Select player type (1-11): ";
    cin >> type;
    if (type < 1 || type > 11) {
        cout << "Invalid player type. Please select a number between 1 and 11." << endl;
        return;
    }

    cout << "Enter runs scored by Player " << type << ": ";
    cin >> runs;
    if (runs < 0) {
        cout << "Runs cannot be negative. Please enter a valid number." << endl;
        return;
    }

    players[num_players].id = num_players + 1;
    players[num_players].type = static_cast<player_type>(type - 1);
    players[num_players].runs = runs;
    total_runs += runs;
    runs_by_player[type - 1] += runs;
    num_players++;

    cout << "Player " << type << " added successfully with " << runs << " runs." << endl;
}

void list_scores() {
    clear_screen();
    cout << left << setw(5) << "ID" << setw(12) << "Player Type" << setw(5) << "Runs" << endl;
    cout << "=============================" << endl;
    for (int i = 0; i < num_players; i++) {
        cout << setw(5) << players[i].id
            << setw(12) << ("Player " + to_string(players[i].type + 1))
            << setw(5) << players[i].runs << endl;
    }
}

void get_statistics() {
    clear_screen();
    cout << "Total players: " << num_players << endl;
    cout << "Total runs: " << total_runs << endl;
    for (int i = 0; i < 11; i++) {
        cout << "Total runs by Player " << i + 1 << ": " << runs_by_player[i] 
             << " (" << (total_runs > 0 ? static_cast<float>(runs_by_player[i]) / total_runs * 100 : 0) << "%)" << endl;
    }
}

void exit_program() {
    cout << "Exiting the program." << endl;
    exit(0);
}

void display_menu() {
    cout << "1. Add Player" << endl;
    cout << "2. List Scores" << endl;
    cout << "3. Get Statistics" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    int choice;

    do {
        clear_screen();
        display_menu();
        cin >> choice;

        switch (choice) {
            case 1:
                add_player();
                break;
            case 2:
                list_scores();
                break;
            case 3:
                get_statistics();
                break;
            case 4:
                exit_program();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();

    } while (choice != 4);

    return 0;
}
