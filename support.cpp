#include "support.h"
#include <iostream>
#include <iomanip>

Support::Support() {
    maxHp = 90.0f;
    currentHp = maxHp;
    baseDamage = 3.0f;
}

void Support::applySpecialAbilities() {
    if (level >= 3 && healAmount < 1.0f) {
        healAmount = 1.0f;
        std::cout << "Support unlocked HEAL! (Heals for 1 HP per round)\n";
    }
    if (level >= 6 && buffMultiplier < 1.25f) {
        buffMultiplier = 1.25f;
        std::cout << "Support BUFF increased! (+25% attack multiplier for team)\n";
    }
    if (level >= 9 && buffMultiplier < 1.5f) {
        buffMultiplier = 1.5f;
        std::cout << "Support BUFF increased! (+50% attack multiplier for team)\n";
    }
}

void Support::attack(Character* target) {
    std::cout << std::fixed << std::setprecision(1)
              << "Support attacks for " << baseDamage << "\n";
    target->takeDamage(baseDamage);
    applySpecialAbilities();
}

void Support::healAllies(std::vector<Character*>& allies) {
    if (healAmount > 0.0f) {
        for (auto* member : allies) {
            if (member->isAlive()) {
                member->heal(healAmount);
                std::cout << "Support heals ally for " << healAmount << "\n";
            }
        }
    }
}

float Support::getBuffMultiplier() const {
    return buffMultiplier;
}
