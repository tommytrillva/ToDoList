#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct Task {
    std::string description;
    bool completed = false;

};

void saveTasks(const std::vector<Task>& tasks) {
    std::ofstream file("tasks.txt");
    for (const auto& t : tasks)
        file << t.description << "|" << t.completed << "\n";

}

void loadTasks(std::vector<Task>& tasks) {
    std::ifstream file("tasks.txt");
    std::string line;
    while (std::getline(file, line)) {
        size_t sep = line.find('|');
        if (sep != std::string::npos) {
            Task t;
            t.description = line.substr(0, sep);
            t.completed = (line.substr(sep + 1) == "1");
            tasks.push_back(t);

        }
    }
}

void displayTasks(const std::vector<Task>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks yet.\n";
        return;
    }
    for (size_t i = 0; i < tasks.size(); ++i)
        std::cout << i + 1 << ". [ "
        << (tasks[i].completed ? "x " : " ")
        << "] " << tasks[i].description << "\n";

}
int main() {
    std::vector<Task> tasks;
    loadTasks(tasks);

    int choice;
    do {
        std::cout << "\n=== To Do List ===\n";
        std::cout << "1. Add Task\n2. View Tasks\n3. Mark Done\n4. Save & Exit\n> ";
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            Task t;
            std::cout << "Enter task: ";
            std::getline(std::cin, t.description);
            tasks.push_back(t);

        }
        else if (choice == 2) {
            displayTasks(tasks);

        }
        else if (choice == 3) {
            displayTasks(tasks);
            std::cout << "Enter number to mark done: ";
            size_t n; std::cin >> n;
            if (n >= 1 && n <= tasks.size()) tasks[n - 1].completed = true;
        }
    } while (choice != 4);

    saveTasks(tasks);
    std::cout << "Tasks saved! Goodbye.\n";

    return 0;
}

