#include "assassin.h"
#include <iostream>
#include <iomanip>

Assassin::Assassin() {
    maxHp = 75.0f;
    currentHp = maxHp;
    baseDamage = 5.0f;
    critChance = 0.0f;
    doubleAttackUnlocked = false;
}

void Assassin::applySpecialAbilities() {
    if (level >= 3 && critChance < 0.4f) {
        critChance = 0.4f;
        std::cout << "Assassin unlocked CRITICAL HITS! (40% chance for 150% damage)\n";
    }
    if (level >= 6 && !doubleAttackUnlocked) {
        doubleAttackUnlocked = true;
        std::cout << "Assassin unlocked DOUBLE ATTACK! (30% chance to attack twice)\n";
    }
    if (level >= 9 && critChance < 0.6f) {
        critChance = 0.6f;
        std::cout << "Assassin's CRIT CHANCE increased! (60%)\n";
    }
}

void Assassin::attack(Character* target) {
    float dmg = baseDamage * getTempDamageMultiplier();

    bool didCrit = false;
    if ((rand() % 100) < (critChance * 100)) {
        dmg *= 1.5f;
        didCrit = true;
        std::cout << "Assassin critical hit! ";
    }
    std::cout << std::fixed << std::setprecision(1)
              << "Assassin attacks for " << dmg << (didCrit ? " (CRIT)\n" : "\n");
    target->takeDamage(dmg);

    if (doubleAttackUnlocked) {
        int doubleAttackRoll = rand() % 100;
        if (doubleAttackRoll < 30) {
            std::cout << "Assassin performs a SECOND ATTACK!\n";
            float secondDmg = baseDamage * getTempDamageMultiplier();
            bool secondCrit = false;
            if ((rand() % 100) < (critChance * 100)) {
                secondDmg *= 1.5f;
                secondCrit = true;
                std::cout << "Assassin critical hit! ";
            }
            std::cout << "Assassin attacks for " << secondDmg << (secondCrit ? " (CRIT)\n" : "\n");
            target->takeDamage(secondDmg);
        }
    }
    applySpecialAbilities();
    clearDamageMultiplier();
}
