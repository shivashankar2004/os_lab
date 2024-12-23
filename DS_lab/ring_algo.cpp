#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class RingAlgorithm {
public:
    int n;                         // Number of processes
    vector<bool> isActive;         // To keep track of active processes
    int coordinator;               // Coordinator process ID

    RingAlgorithm(int numProcesses) : n(numProcesses) {
        isActive.resize(n, true);
        coordinator = n;           // Highest process is the initial coordinator
    }

    // Function to bring a process down
    void down(int process) {
        if (!isActive[process - 1]) {
            cout << "Process " << process << " is already down." << endl;
        } else {
            isActive[process - 1] = false;
            cout << "Process " << process << " is now down." << endl;
        }
    }

    // Function to bring a process up
    void up(int process) {
        if (isActive[process - 1]) {
            cout << "Process " << process << " is already up." << endl;
        } else {
            isActive[process - 1] = true;
            cout << "Process " << process << " is now up." << endl;
        }
    }

    // Function to initiate an election
    void startElection(int initiator) {
        if (!isActive[initiator - 1]) {
            cout << "Process " << initiator << " is down and cannot start an election." << endl;
            return;
        }

        cout << "Process " << initiator << " starts an election." << endl;
        vector<int> electionRing;

        // Circulate the election message
        int current = initiator - 1;
        do {
            if (isActive[current]) {
                electionRing.push_back(current + 1);
                cout << "Process " << (current + 1) << " participates in the election." << endl;
            }
            current = (current + 1) % n; // Move to the next process in the ring
        } while (current != initiator - 1);

        // Find the process with the maximum ID (new coordinator)
        int newCoordinator = *max_element(electionRing.begin(), electionRing.end());
        coordinator = newCoordinator;

        cout << "Process " << newCoordinator << " is elected as the new coordinator." << endl;
    }

    // Function to send a message
    void sendMessage(int sender) {
        if (!isActive[sender - 1]) {
            cout << "Process " << sender << " is down and cannot send messages." << endl;
            return;
        }

        if (isActive[coordinator - 1]) {
            cout << "Message sent successfully. Coordinator (Process " << coordinator << ") is active." << endl;
        } else {
            cout << "Coordinator (Process " << coordinator << ") is down. Starting an election." << endl;
            startElection(sender);
        }
    }

    // Display the status of processes
    void displayStatus() {
        cout << "Current process status:" << endl;
        for (int i = 0; i < n; i++) {
            cout << "Process " << (i + 1) << " is " << (isActive[i] ? "up" : "down") << endl;
        }
        cout << "Current coordinator is Process " << coordinator << "." << endl;
    }
};

int main() {
    int n = 5; // Number of processes
    RingAlgorithm ring(n);

    int choice;
    do {
        cout << "\n--- Ring Election Algorithm ---" << endl;
        cout << "1. Bring a process down" << endl;
        cout << "2. Bring a process up" << endl;
        cout << "3. Start an election" << endl;
        cout << "4. Send a message" << endl;
        cout << "5. Display process status" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int process;
                cout << "Enter process to bring down: ";
                cin >> process;
                ring.down(process);
            } break;

            case 2: {
                int process;
                cout << "Enter process to bring up: ";
                cin >> process;
                ring.up(process);
            } break;

            case 3: {
                int initiator;
                cout << "Enter process to initiate the election: ";
                cin >> initiator;
                ring.startElection(initiator);
            } break;

            case 4: {
                int sender;
                cout << "Enter process to send a message: ";
                cin >> sender;
                ring.sendMessage(sender);
            } break;

            case 5:
                ring.displayStatus();
                break;

            case 6:
                cout << "Exiting..." << endl;
                break;

            default:
                cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
//      g++ ring_algo.cpp -o rin
//      ./rin