#ifndef TEAM_H
#define TEAM_H

#include <string>
#include <memory>
#include <vector>
#include "assassin.h"
#include "tank.h"
#include "support.h"

class Team {
private:
    std::string name;
    std::unique_ptr<Assassin> assassin;
    std::unique_ptr<Tank> tank;
    std::unique_ptr<Support> support;
    int currentBossIndex = 0;

public:
    Team() = default;
    Team(const std::string& name);

    std::vector<Character*> getMembers() const;
    std::vector<Character*> getLivingMembers() const;

    bool isAlive() const;
    void restoreAll();
    void printStatus() const;
    void advanceBoss() { currentBossIndex++; }
    int getCurrentBossIndex() const { return currentBossIndex; }
    void levelUpAll();

    void save(const std::string& path) const;
    void load(const std::string& path);

    Assassin* getAssassin() const { return assassin.get(); }
    Tank* getTank() const { return tank.get(); }
    Support* getSupport() const { return support.get(); }
};

#endif // TEAM_H
