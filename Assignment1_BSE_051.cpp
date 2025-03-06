#include <iostream>
#include <string>
using namespace std;

// Task Node Structure
struct Task {
    int taskID;
    string description;
    int priority;
    Task* next;
};

class TaskManager {
private:
    Task* head; // Head of the linked list

public:
    TaskManager() { head = nullptr; }

    // Function to add a task based on priority order
    void addTask(int id, string desc, int pri) {
        Task* newTask = new Task{id, desc, pri, nullptr};
        if (!head || pri > head->priority) { // Insert at the beginning
            newTask->next = head;
            head = newTask;
        } else {
            Task* temp = head;
            while (temp->next && temp->next->priority >= pri) {
                temp = temp->next;
            }
            newTask->next = temp->next;
            temp->next = newTask;
        }
        cout << "Task added successfully!" << endl;
    }

    // Function to remove the highest priority task
    void removeHighestPriorityTask() {
        if (!head) {
            cout << "No tasks available!" << endl;
            return;
        }
        Task* temp = head;
        head = head->next;
        cout << "Removed task: " << temp->taskID << " - " << temp->description << endl;
        delete temp;
    }

    // Function to remove a task by ID
    void removeTaskByID(int id) {
        if (!head) {
            cout << "No tasks available!" << endl;
            return;
        }
        if (head->taskID == id) { // If the head needs to be removed
            Task* temp = head;
            head = head->next;
            delete temp;
            cout << "Task removed successfully!" << endl;
            return;
        }
        Task* temp = head;
        while (temp->next && temp->next->taskID != id) {
            temp = temp->next;
        }
        if (!temp->next) {
            cout << "Task ID not found!" << endl;
            return;
        }
        Task* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
        cout << "Task removed successfully!" << endl;
    }

    // Function to display all tasks
    void viewTasks() {
        if (!head) {
            cout << "No tasks available!" << endl;
            return;
        }
        Task* temp = head;
        cout << "\nTask List:\n";
        while (temp) {
            cout << "ID: " << temp->taskID << " | Description: " << temp->description << " | Priority: " << temp->priority << endl;
            temp = temp->next;
        }
    }
};

int main() {
    TaskManager taskManager;
    int choice, id, priority;
    string description;

    do {
        cout << "\nTask Management System";
        cout << "\n1. Add Task";
        cout << "\n2. View All Tasks";
        cout << "\n3. Remove Highest Priority Task";
        cout << "\n4. Remove Task by ID";
        cout << "\n5. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Task ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Description: ";
                getline(cin, description);
                cout << "Enter Priority (Higher value = Higher Priority): ";
                cin >> priority;
                taskManager.addTask(id, description, priority);
                break;
            case 2:
                taskManager.viewTasks();
                break;
            case 3:
                taskManager.removeHighestPriorityTask();
                break;
            case 4:
                cout << "Enter Task ID to remove: ";
                cin >> id;
                taskManager.removeTaskByID(id);
                break;
            case 5:
                cout << "Exiting Task Management System." << endl;
                break;
            default:
                cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
