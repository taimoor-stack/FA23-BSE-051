#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <iomanip>
#include <map>

using namespace std;

// Patient class to store patient information
class Patient {
public:
    string name;
    int arrivalOrder;
    string condition;
    int priority;

    Patient(string n, int order, string cond, int pri)
        : name(n), arrivalOrder(order), condition(cond), priority(pri) {}

    // Overload the < operator for priority queue
    bool operator<(const Patient& other) const {
        // Higher priority comes first
        // If priorities are equal, earlier arrival comes first
        if (priority == other.priority) {
            return arrivalOrder > other.priority;
        }
        return priority > other.priority;
    }
};

// Function to assign priority based on condition
int assignPriority(const string& condition) {
    static const map<string, int> conditionPriority = {
        {"Heart Attack", 1},
        {"Stroke", 1},
        {"Severe Burn", 2},
        {"Broken Leg", 2},
        {"Fractured Arm", 2},
        {"Fever", 3},
        {"Food Poisoning", 3},
        {"Migraine", 3},
        {"Mild Cold", 4},
        {"Small Cut", 4}
    };

    auto it = conditionPriority.find(condition);
    if (it != conditionPriority.end()) {
        return it->second;
    }
    return 4; // Default priority for unknown conditions
}

// Function to display the current treatment order
void displayTreatmentOrder(priority_queue<Patient> pq) {
    cout << "\nCurrent Treatment Order:\n";
    cout << setw(15) << left << "Patient Name"
         << setw(20) << "Emergency Condition"
         << setw(10) << "Priority"
         << "Arrival Order\n";
    cout << string(60, '-') << endl;

    while (!pq.empty()) {
        Patient p = pq.top();
        cout << setw(15) << left << p.name
             << setw(20) << p.condition
             << setw(10) << p.priority
             << p.arrivalOrder << endl;
        pq.pop();
    }
    cout << endl;
}

int main() {
    priority_queue<Patient> treatmentQueue;
    int arrivalCounter = 1;
    int choice;

    // Predefined conditions for selection
    vector<string> conditions = {
        "Heart Attack", "Stroke", "Severe Burn", "Broken Leg",
        "Fractured Arm", "Fever", "Food Poisoning", "Migraine",
        "Mild Cold", "Small Cut", "Other"
    };

    cout << "Hospital Patient Treatment Priority System\n";
    cout << string(40, '=') << "\n\n";

    while (true) {
        cout << "Menu:\n";
        cout << "1. Add Patient\n";
        cout << "2. View Current Treatment Order\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name, condition;
            int conditionChoice;

            cout << "\nEnter patient name: ";
            cin.ignore(); // Clear input buffer
            getline(cin, name);

            cout << "Select emergency condition:\n";
            for (int i = 0; i < conditions.size(); i++) {
                cout << i+1 << ". " << conditions[i] << "\n";
            }
            cout << "Enter condition number: ";
            cin >> conditionChoice;

            if (conditionChoice < 1 || conditionChoice > conditions.size()) {
                conditionChoice = conditions.size(); // Default to "Other"
            }
            condition = conditions[conditionChoice - 1];

            int priority = assignPriority(condition);
            treatmentQueue.push(Patient(name, arrivalCounter++, condition, priority));

            cout << "\nPatient added successfully!\n";
            displayTreatmentOrder(treatmentQueue);

        } else if (choice == 2) {
            displayTreatmentOrder(treatmentQueue);
        } else if (choice == 3) {
            cout << "Exiting program...\n";
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
