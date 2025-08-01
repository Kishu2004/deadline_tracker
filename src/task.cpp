#include "task.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>

using json = nlohmann::json;

void saveTasks(const std::vector<Task> &tasks, const std::string &filename) {
    json j;
    for (auto &t : tasks) {
        j.push_back({
            {"name", t.name},
            {"deadlineDays", t.deadlineDays},
            {"durationHours", t.durationHours},
            {"priority", t.priority},
            {"freeTimeHours", t.freeTimeHours},
            {"urgency", t.urgency}
        });
    }
    std::ofstream file(filename);
    file << j.dump(4);
}

std::vector<Task> loadTasks(const std::string &filename) {
    std::ifstream file(filename);
    std::vector<Task> tasks;
    if (!file.is_open()) return tasks;

    json j;
    file >> j;
    for (auto &item : j) {
        Task t;
        t.name = item["name"];
        t.deadlineDays = item["deadlineDays"];
        t.durationHours = item["durationHours"];
        t.priority = item["priority"];
        t.freeTimeHours = item["freeTimeHours"];
        t.urgency = item["urgency"];
        tasks.push_back(t);
    }
    return tasks;
}
