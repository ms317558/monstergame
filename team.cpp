#include "team.h"
#include <iostream>
#include <fstream>

Team::Team(const std::string& name) : name(name) {
    assassin = std::make_unique<Assassin>();
    tank = std::make_unique<Tank>();
    support = std::make_unique<Support>();
}

std::vector<Character*> Team::getMembers() const {
    return { assassin.get(), tank.get(), support.get() };
}

std::vector<Character*> Team::getLivingMembers() const {
    std::vector<Character*> living;
    for (auto* m : getMembers())
        if (m->isAlive())
            living.push_back(m);
    return living;
}

bool Team::isAlive() const {
    for (auto* member : getMembers()) {
        if (member->isAlive()) return true;
    }
    return false;
}

void Team::restoreAll() {
    for (auto* m : getMembers())
        m->heal(m->getMaxHP());
}

void Team::printStatus() const {
    std::cout << "Team \"" << name << "\" status:\n\n";
    std::cout << std::fixed << std::setprecision(1)
              << "- Assassin: HP " << assassin->getHP() << "/"<< assassin->getMaxHP() << ", Level " << assassin->getLevel() << "\n"
              << "- Tank:     HP " << tank->getHP() << "/"<< tank->getMaxHP() << ", Level " << tank->getLevel() << "\n"
              << "- Support:  HP " << support->getHP() << "/"<< support->getMaxHP() << ", Level " << support->getLevel() << "\n";
}

void Team::levelUpAll() {
    for (auto* member : getMembers()) {
        if (member->getLevel() < 10)
            member->levelUp();
            member->applySpecialAbilities();
    }
}

void Team::save(const std::string& path) const {
    nlohmann::json data;
    data["name"] = name;
    data["currentBossIndex"] = currentBossIndex;

    auto saveChar = [](Character* c) {
        return nlohmann::json{{"level", c->getLevel()}, {"hp", c->getHP()}};
    };

    data["assassin"] = saveChar(assassin.get());
    data["tank"] = saveChar(tank.get());
    data["support"] = saveChar(support.get());

    std::ofstream file(path);
    file << data.dump(2);
}

void Team::load(const std::string& path) {
    std::ifstream file(path);
    nlohmann::json data;
    file >> data;

    name = data["name"];
    currentBossIndex = data["currentBossIndex"];

    assassin = std::make_unique<Assassin>();
    tank = std::make_unique<Tank>();
    support = std::make_unique<Support>();

    for (int lvl = 1; lvl < data["assassin"]["level"].get<int>(); ++lvl) assassin->levelUp();
    for (int lvl = 1; lvl < data["tank"]["level"].get<int>(); ++lvl) tank->levelUp();
    for (int lvl = 1; lvl < data["support"]["level"].get<int>(); ++lvl) support->levelUp();

    assassin->takeDamage(assassin->getHP() - data["assassin"]["hp"].get<float>());
    tank->takeDamage(tank->getHP() - data["tank"]["hp"].get<float>());
    support->takeDamage(support->getHP() - data["support"]["hp"].get<float>());
}
