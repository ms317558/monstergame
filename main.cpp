#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>
#include <limits>
#include <thread>
#include <chrono>
#include "team.h"
#include "boss.h"
#include "fight.h"

static std::string gCurrentSavePath = "";

void loadLevelData();

std::string chooseSaveFile();

void manualSave(Team& team);

extern nlohmann::json levelData;

void loadLevelData() {
    std::ifstream file("leveling.json");
    if (!file) {
        std::cerr << "Could not open leveling.json!\n";
        exit(1);
    }
    file >> levelData;
}

std::string chooseSaveFile() {
    std::vector<std::filesystem::directory_entry> saves;
    const std::string saveDir = "saves";

    if (!std::filesystem::exists(saveDir)) {
        std::filesystem::create_directory(saveDir);
    }
    for (const auto& file : std::filesystem::directory_iterator(saveDir)) {
        if (file.path().extension() == ".json")
            saves.push_back(file);
    }
    if (saves.empty()) {
        std::cout << "No saved games found.\n";
        return "";
    }
    std::cout << "\n=== Available saves ===\n";
    for (size_t i = 0; i < saves.size(); ++i) {
        std::cout << i + 1 << ". " << saves[i].path().filename().string() << "\n";
    }
    std::cout << "Choose save number: ";
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice < 1 || choice > static_cast<int>(saves.size())) {
        std::cout << "Invalid choice.\n";
        return "";
    }
    return saves[choice - 1].path().string();
}
void manualSave(Team& team) {
    std::string filename;
    std::cout << "Enter filename for save (e.g., mysave.json): ";
    std::cin >> filename;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string path = "saves/" + filename;
    team.save(path);
    gCurrentSavePath = path;
    std::cout << "Game manually saved to: " << path << "\n";
}
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    loadLevelData();
    std::vector<Boss> bosses = Boss::loadBossesFromJson("bosses.json");
    Team team;
    std::cout << "=== MonsterRPG ===\n1. New Game\n2. Load Game\n3. Exit\nChoice: ";
    int menuChoice;
    std::cin >> menuChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (menuChoice == 1) {
        std::string teamName;
        std::cout << "Enter team name: ";
        std::getline(std::cin, teamName);
        team = Team(teamName);
    } else if (menuChoice == 2) {
        std::string path = chooseSaveFile();
        if (path.empty()) return 0;
        team.load(path);
        gCurrentSavePath = path;
    } else {
        std::cout << "Exiting...\n";
        return 0;
    }

    team.printStatus();

    std::cout << "\nList of bosses:\n";
    for (size_t i = 0; i < bosses.size(); ++i) {
        std::cout << (i + 1) << ". " << bosses[i].getName() << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    while (team.getCurrentBossIndex() < static_cast<int>(bosses.size())) {
        int bossIndex = team.getCurrentBossIndex();
        std::cout << "\nBoss #" << (bossIndex + 1) << ": " << bosses[bossIndex].getName() << "\n";

        int fightChoice;
        while (true) {
            std::cout << "1. Fight\n2. Manual Save\n3. Exit\nChoice: ";
            if (std::cin >> fightChoice && fightChoice >= 1 && fightChoice <= 3) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
            std::cout << "Invalid choice. Please enter 1, 2, or 3.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (fightChoice == 3) {
            return 0;
        }

        if (fightChoice == 2) {
            manualSave(team);
            continue;
        }

        std::cout << "Starting the battle...\n";
        bool won = fightBoss(team, bosses[bossIndex]);
        if (!won) {
            std::cout << "You were defeated... regrouping!\n";
            team.restoreAll();
        }
    }

    if (team.getCurrentBossIndex() >= static_cast<int>(bosses.size())) {
        std::cout << "\nCongratulations! You have defeated all bosses!\n";

        if (!gCurrentSavePath.empty() && std::filesystem::exists(gCurrentSavePath)) {
            std::filesystem::remove(gCurrentSavePath);
            std::cout << "Your save file (" << gCurrentSavePath << ") has been deleted.\n";
        }
    }

    return 0;
}
