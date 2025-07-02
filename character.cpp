#include "character.h"
#include <iostream>

nlohmann::json levelData;

void Character::levelUp() {
    if (level >= 10) return;
    ++level;
    auto stats = levelData[getClassKey()]["levels"][std::to_string(level)];
    maxHp += stats["hp_bonus"].get<float>();
    baseDamage += stats["dmg_bonus"].get<float>();
    currentHp = maxHp;
    std::cout << getClassKey() << " leveled up to " << level << "!\n";
}

void Character::takeDamage(float amount) {
    currentHp -= amount;
    if (currentHp < 0) currentHp = 0;
}

void Character::heal(float amount) {
    currentHp += amount;
    if (currentHp > maxHp) currentHp = maxHp;
}
