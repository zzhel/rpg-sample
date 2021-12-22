#ifndef CREATURE_H
#define CREATURE_H

#include "Player.h"

class Unit;

class Creature : public Unit
{
public:
    Creature() = delete;

    explicit Creature(eCreTypes eType);
    ~Creature();

    eCreTypes GetType() const { return mType; }
    std::string GetName() const override { return mName; }

    void KillByPlayer(Player* const lPlayer);

    void ModHealth(int8_t pMod)
    {
        int8_t lHealth = GetHealth() + pMod;
        if (lHealth > MAXHP)
            lHealth = MAXHP;

        SetHealth(lHealth);
    }

    std::string GetName() { return mName; };

private:
    struct DeathRewards
    {
        /*DeathRewards(uint8_t XP, uint8_t Gold)
        {
        mXP = XP;
        mGold = Gold;
        };*/

        uint8_t mXP;
        uint8_t mGold;
    } mDeathRewards;

    eCreTypes mType;
    std::string mName;
};

#endif
