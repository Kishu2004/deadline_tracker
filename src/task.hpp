#pragma once
#include <string>

struct Task {
    std::string name;
    int deadlineDays;
    int durationHours;
    int priority;
    double freeTimeHours;
    int urgency; // 0 = non-urgent, 1 = urgent
};

// Functions to save and load tasks
void saveTasks(const std::vector<Task> &tasks, const std::string &filename);
std::vector<Task> loadTasks(const std::string &filename);
