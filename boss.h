#ifndef BOSS_H
#define BOSS_H
#pragma once
#include "character.h"
#include <string>
#include <nlohmann/json.hpp>

class Boss : public Character {
private:
    std::string name;
    int xpReward;

public:
    Boss(std::string name, float hp, float dmg);
    int rollDamage(int bossNumber) const;
    static std::vector<Boss> loadBossesFromJson(const std::string& filename);
    void attackTeam(Character* assassin, Character* tank, Character* support);
    std::string getClassKey() const override { return "boss"; }
    void attack(Character* target) override {}
    void applySpecialAbilities() override {}
    std::string getName() const { return name; }
    void displayStatus() const;
};
#endif //BOSS_H
