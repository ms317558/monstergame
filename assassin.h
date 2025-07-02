#ifndef ASSASSIN_H
#define ASSASSIN_H

#pragma once
#include "character.h"

class Assassin : public Character {
private:
    float critChance = 0.0f;
    bool doubleAttackUnlocked = false;

public:
    Assassin();
    void attack(Character* target) override;
    void applySpecialAbilities() override;
    std::string getClassKey() const override { return "Assassin"; }
};

#endif //ASSASSIN_H
