#include <iostream>
#include <vector>
using namespace std;

vector<bool> state(5, true); 
int coordinator = 5; 


void up(int up) {
    if (state[up - 1]) {
        cout << "Process " << up << " is already up." << endl;
    } else {
        state[up - 1] = true;
        cout << "Process " << up << " held election." << endl;

        for (int i = up; i < 5; i++) {
            cout << "Election message sent from process " << up << " to process " << (i + 1) << endl;
        }

        for (int i = up + 1; i <= 5; i++) {
            if (state[i - 1]) {
                cout << "Alive message sent from process " << i << " to process " << up << endl;
                break;
            }
        }
    }
}


void down(int down) {
    if (!state[down - 1]) {
        cout << "Process " << down << " is already down." << endl;
    } else {
        state[down - 1] = false;
        cout << "Process " << down << " is now down." << endl;
    }
}

void displayStatus() {
    cout << "Current process status:" << endl;
    for (int i = 0; i < coordinator; i++) {
        cout << "Process " << (i + 1) << " is " << (state[i] ? "up" : "down") << endl;
    }
    cout << "Current coordinator is Process " << coordinator << "." << endl;
}

void mess(int mess) {
    if (state[mess - 1]) {
        if (state[4]) { 
            cout << "OK" << endl;
        } else {
            cout << "Process " << mess << " is holding an election." << endl;

            for (int i = mess; i < 5; i++) {
                cout << "Election message sent from process " << mess << " to process " << (i + 1) << endl;
            }

            for (int i = 5; i >= mess; i--) {
                if (state[i - 1]) {
                    cout << "Coordinator message sent from process " << i << " to all." << endl;
                    break;
                }
            }
        }
    } else {
        cout << "Process " << mess << " is down." << endl;
    }
}


int main() {
    int choice;
    cout << "5 active processes are:" << endl;
    cout << "Processes up = P1 P2 P3 P4 P5" << endl;
    cout << "Process 5 is coordinator." << endl;

    do {
        cout << "..........." << endl;
        cout << "1. Bring a process up" << endl;
        cout << "2. Bring a process down" << endl;
        cout << "3. Send a message" << endl;
        cout << "4. Exit" << endl;
        cout << "5.Display status"<<endl;
        cout << "Enter your choice: "<<endl;
        //cout<<"current co-ordinator :"<<coordinator<<endl;
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Enter process number to bring up: ";
                int up_process;
                cin >> up_process;
                if (up_process == 5) {
                    cout << "Process 5 is the coordinator." << endl;
                    state[4] = true;
                } else {
                    up(up_process);
                }
            } break;

            case 2: {
                cout << "Enter process number to bring down: ";
                int down_process;
                cin >> down_process;
                down(down_process);
            } break;

            case 3: {
                cout << "Which process will send the message: ";
                int mess_process;
                cin >> mess_process;
                mess(mess_process);
            } break;

            case 4:
                cout << "Exiting..." << endl;
                break;
            case 5:{
                cout<<"current process status"<<endl;
                displayStatus();
            }break;

            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}

//      g++ bully_algo.cpp -o bul
//      ./bul