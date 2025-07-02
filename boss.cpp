#include "boss.h"
#include "tank.h"
#include <iostream>
#include <fstream>

Boss::Boss(std::string name, float hp, float dmg)
    : name(std::move(name)) {
    maxHp = hp;
    currentHp = maxHp;
    baseDamage = dmg;
}
std::vector<Boss> Boss::loadBossesFromJson(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) throw std::runtime_error("Cannot open boss file: " + filename);

    nlohmann::json data;
    file >> data;

    std::vector<Boss> bosses;
    for (const auto& bossData : data["bosses"]) {
        std::string name = bossData["name"];
        float hp = bossData["hp"];
        float dmg = bossData["damage"];
        bosses.emplace_back(name, hp, dmg);
    }
    return bosses;
}
void Boss::displayStatus() const
{
    std::cout << name << "- HP " << currentHp << '/' << maxHp << '\n';
}
int Boss::rollDamage(int bossNumber) const
{
    double spread      = 0.85 + (std::rand() % 31) / 100.0;
    double difficulty  = 1.0 + bossNumber * 0.05;
    return static_cast<int>(baseDamage * spread * difficulty);
}
void Boss::attackTeam(Character* assassin, Character* tank, Character* support) {
    int bossNo      = xpReward / 10 - 5;
    int totalDamage = rollDamage(bossNo);
    std::cout << name << " attacks team!\n";

    int dmgTank = static_cast<int>(totalDamage * 0.6);
    int dmgAssassin = static_cast<int>(totalDamage * 0.3);
    int dmgSupport = totalDamage - dmgTank - dmgAssassin;

    if (tank->isAlive()) {
        Tank* tankPtr = static_cast<Tank*>(tank);
        if (tankPtr->tryBlock()) {
        } else {
            tank->takeDamage(dmgTank);
            std::cout << "Tank takes " << dmgTank << " damage.\n";
        }
    }
    if (assassin->isAlive()) {
        assassin->takeDamage(dmgAssassin);
        std::cout << "Assassin takes " << dmgAssassin << " damage.\n";
    }
    if (support->isAlive()) {
        support->takeDamage(dmgSupport);
        std::cout << "Support takes " << dmgSupport << " damage.\n";
    }
}