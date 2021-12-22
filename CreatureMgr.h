#ifndef CREMGR_H
#define CREMGR_H

#include "Unit.h"
#include "Creature.h"

#pragma warning (disable: 4834) // lambda

class CreatureManager
{
public:
    CreatureManager()
    {
        // empty
    }

    static CreatureManager& GetInstance()
    {
        static CreatureManager lInst;
        return lInst;
    }

    // dont implement
    CreatureManager(CreatureManager const&);
    void operator=(CreatureManager const&);

    void AddUnit(Creature* pUnit)
    {
        mUnits.push_back(pUnit);
    }

    void RemoveUnit(Creature* pUnit)
    {
        auto lIter = std::find(mUnits.begin(), mUnits.end(), pUnit);
        if (lIter == mUnits.end())
            return;

        mUnits.erase(lIter);
    }

    Creature* GetRandomCreature()
    {
        if (mUnits.empty())
            return nullptr;

        UnitVector lUnits = mUnits;
        std::remove_if(lUnits.begin(), lUnits.end(), [](Creature* lCre) -> bool
        {
            return lCre->IsDead();
        });

        if (lUnits.empty())
            return nullptr;

        return mUnits[Helpers::randInt(0, static_cast<int32_t>(lUnits.size()) - 1)];
    }

private:
    typedef std::vector<Creature*> UnitVector;
    UnitVector mUnits;
};

static CreatureManager* sCreatureMgr = &CreatureManager::GetInstance();

#endif
