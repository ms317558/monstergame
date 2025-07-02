#ifndef SUPPORT_H
#define SUPPORT_H

#include "character.h"
#include <vector>

class Support : public Character {
private:
    float healAmount = 0.0f;
    float buffMultiplier = 1.0f;

public:
    Support();
    void attack(Character* target) override;
    void applySpecialAbilities() override;
    void healAllies(std::vector<Character*>& allies);
    float getBuffMultiplier() const;
    std::string getClassKey() const override { return "Support"; }
};

#endif //SUPPORT_H
