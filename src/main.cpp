#include "task.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <memory>
#include <cstdio>   // popen, pclose

// Function to run Python and capture output
std::string runCommand(const std::string& command) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) return "0";
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    if (!result.empty() && result.back() == '\n') {
        result.pop_back(); // remove trailing newline
    }
    return result;
}

int main() {
    // Load existing tasks
    std::vector<Task> tasks = loadTasks("data/tasks.json");

    // Take input for a new task
    Task newTask;
    std::cout << "Enter Task Name: ";
    std::getline(std::cin, newTask.name); // No cin.ignore()

    std::cout << "Days until deadline: ";
    std::cin >> newTask.deadlineDays;

    std::cout << "Estimated duration (hours): ";
    std::cin >> newTask.durationHours;

    std::cout << "Priority (1-5): ";
    std::cin >> newTask.priority;

    std::cout << "Free time available today (hours): ";
    std::cin >> newTask.freeTimeHours;

    // Build Python command for ML prediction
    std::string cmd = "python3 scripts/predict_urgency.py " +
                      std::to_string(newTask.deadlineDays) + " " +
                      std::to_string(newTask.durationHours) + " " +
                      std::to_string(newTask.priority) + " " +
                      std::to_string(newTask.freeTimeHours);

    std::string prediction = runCommand(cmd);
    newTask.urgency = std::stoi(prediction);

    // Show prediction
    if (newTask.urgency == 1) {
        std::cout << "🚨 Urgent Task! Notifications will be sent.\n";
        runCommand("python3 scripts/send_email.py");
        runCommand("python3 scripts/send_sms.py");
    } else {
        std::cout << "Task is not urgent.\n";
    }

    // Save task
    tasks.push_back(newTask);
    saveTasks(tasks, "data/tasks.json");
    std::cout << "✅ Task saved to data/tasks.json\n";

    // Display all tasks
    std::cout << "\n📋 Current Tasks:\n";
    for (const auto &t : tasks) {
        std::cout << "- " << t.name 
                  << " | Deadline: " << t.deadlineDays << " days"
                  << " | Urgency: " << (t.urgency ? "Urgent" : "Not Urgent") 
                  << "\n";
    }

    return 0;
}
