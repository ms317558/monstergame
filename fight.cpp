#include "fight.h"
#include <iostream>
#include <chrono>
#include "team.h"
#include "boss.h"
#include "support.h"

bool fightBoss(Team& team, Boss& boss) {
    team.restoreAll();

    while (team.isAlive() && boss.isAlive()) {
        std::cout << "\n--- Player Team Turn ---\n\n";

        Support* support = team.getSupport();
        float buffMultiplier = support->getBuffMultiplier();
        std::vector<Character*> members = team.getLivingMembers();

        for (Character* member : members) {
            if (!member->isAlive()) continue;

            member->setDamageMultiplier(buffMultiplier);
            member->attack(&boss);
            member->clearDamageMultiplier();

            if (!boss.isAlive()) break;
        }

        if (!boss.isAlive()) {
            std::cout << "\n--------------------------\n--------------------------\n------Boss defeated!------\n--------------------------\n--------------------------\n\n";
            team.levelUpAll();
            team.advanceBoss();
            return true;
        }

        std::cout << "\n--- Boss Turn ---\n\n";
        boss.attackTeam(team.getAssassin(), team.getTank(), team.getSupport());

        std::vector<Character*> livingMembers = team.getLivingMembers();
        support->healAllies(livingMembers);

        std::cout << "\nCurrent Status:\n\n";
        team.printStatus();
        std::cout << "\nBoss HP: " << boss.getHP() << "/" << boss.getMaxHP() << "\n";

        std::cout << "\nPress ENTER to continue...";
        std::cin.get();

    }

    return false;
}
