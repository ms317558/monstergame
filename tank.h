#ifndef TANK_H
#define TANK_H

#include "character.h"

class Tank : public Character {
private:
    float blockChance = 0.0f;
    float lifeSteal = 0.0f;

public:
    Tank();
    void attack(Character* target) override;
    void applySpecialAbilities() override;
    bool tryBlock();
    std::string getClassKey() const override { return "Tank"; }
};

#endif //TANK_H
