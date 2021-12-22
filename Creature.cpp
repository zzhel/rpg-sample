#include "Creature.h"
#include "CreatureMgr.h"

Creature::Creature(eCreTypes eType) : mType(eType)
{
    switch (mType)
    {
    case eCreTypes::Zombie:
    {
        Unit::Init(4, 4, 12);
        mDeathRewards = { 5, static_cast<uint8_t>(Helpers::randInt(2, 8)) };
        mName = "Zombie";
        break;
    }
    case eCreTypes::Skeleton:
    {
        Unit::Init(6, 7, 6);
        mDeathRewards = { 3, static_cast<uint8_t>(Helpers::randInt(3, 7)) };
        mName = "Skeleton";
        break;
    }
    case eCreTypes::Vampire:
    {
        Unit::Init(16, 16, 16);
        mDeathRewards = { 12, static_cast<uint8_t>(Helpers::randInt(25, 60)) };
        mName = "Vampire";
        break;
    }
    default:
        mDeathRewards = { 0, 0 };
    }

    sCreatureMgr->AddUnit(this);
}

Creature::~Creature()
{
    sCreatureMgr->RemoveUnit(this);
}

void Creature::KillByPlayer(Player* const lPlayer)
{
    lPlayer->GrantXP(mDeathRewards.mXP);
    lPlayer->ModGold(mDeathRewards.mGold);
    printf_s("Received %u gold from %s\'s loot. Gold: %d\r\n", mDeathRewards.mGold, GetName().c_str(), lPlayer->GetGold());
}
