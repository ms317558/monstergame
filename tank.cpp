#include "tank.h"
#include <iostream>
#include <iomanip>

Tank::Tank() {
    maxHp = 150.0f;
    currentHp = maxHp;
    baseDamage = 2.0f;
}

void Tank::applySpecialAbilities() {
    if (level >= 3 && blockChance < 0.2f) {
        blockChance = 0.2f;
        std::cout << "Tank unlocked BLOCK! (20% chance to block attacks)\n";
    }
    if (level >= 6 && lifeSteal < 0.05f) {
        lifeSteal = 0.05f;
        std::cout << "Tank unlocked LIFESTEAL! (5% of damage dealt heals tank)\n";
    }
    if (level >= 9 && blockChance < 0.4f) {
        blockChance = 0.4f;
        std::cout << "Tank's BLOCK chance increased! (40%)\n";
    }
}

bool Tank::tryBlock() {
    bool blocked = (rand() % 100) < (blockChance * 100);
    if (blocked) {
        std::cout << "Tank BLOCKED the attack!\n";
    }
    return blocked;
}

void Tank::attack(Character* target) {
    float dmg = baseDamage * getTempDamageMultiplier();
    std::cout << std::fixed << std::setprecision(1)
              << "Tank attacks for " << dmg << "\n";
    target->takeDamage(dmg);
    if (lifeSteal > 0.0f) {
        float heal = dmg * lifeSteal;
        if (heal > 0)
            std::cout << "Tank heals for " << heal << " (LIFESTEAL)\n";
        this->heal(heal);
    }
    applySpecialAbilities();
    clearDamageMultiplier();
}
