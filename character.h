#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <nlohmann/json.hpp>

class Character {
protected:
    float maxHp = 0.0f;
    float currentHp = 0.0f;
    float baseDamage = 0.0f;
    int level = 1;

public:
    virtual ~Character() = default;

    virtual void attack(Character* target) = 0;
    virtual void applySpecialAbilities() = 0;
    virtual std::string getClassKey() const = 0;

    virtual void levelUp();
    float getHP() const { return currentHp; }
    float getMaxHP() const { return maxHp; }
    int getLevel() const { return level; }
    bool isAlive() const { return currentHp > 0; }

    virtual void takeDamage(float amount);
    virtual void heal(float amount);

    void setDamageMultiplier(float mult) { tempDamageMultiplier = mult; }
    float getTempDamageMultiplier() const { return tempDamageMultiplier; }
    void clearDamageMultiplier() { tempDamageMultiplier = 1.0f; }

protected:
    float tempDamageMultiplier = 1.0f;
};

extern nlohmann::json levelData;

#endif // CHARACTER_H
