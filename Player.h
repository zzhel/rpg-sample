#ifndef PLAYER_H
#define PLAYER_H

#include "Unit.h"

class Creature;

#define LEVELUP_STAT_MIN 2
#define LEVELUP_STAT_MAX 5

class Player : public Unit
{
public:
    Player()
    {
        Unit::Init(Helpers::randInt(MINHP, MAXHP), Helpers::randInt(MIN_AP_AND_DEF, MAX_AP_AND_DEF), Helpers::randInt(MIN_AP_AND_DEF, MAX_AP_AND_DEF));

        mXP = 0;
        mGold = 0;
        mLevel = 1;
        mState = ePlayerState::None;

        mHealthMod = 0;
        mAttackMod = 0;
        mDefenseMod = 0;

        SetIsPlayer();
    };

    enum class ePlayerState : uint8_t
    {
        None = 0,
        Nap,
        Goldseek
    };

    void ModGold(int16_t pGold)
    {
        mGold += pGold;
        if (mGold < 0)
            mGold = 0;
    }

    void LevelUp()
    {
        if (mLevel == 0xFF)
            return;

        mLevel++;
        mHealthMod += Helpers::randInt(LEVELUP_STAT_MIN, LEVELUP_STAT_MAX);
        mAttackMod += Helpers::randInt(LEVELUP_STAT_MIN, LEVELUP_STAT_MAX);
        mDefenseMod += Helpers::randInt(LEVELUP_STAT_MIN, LEVELUP_STAT_MAX);

        SetHealth(GetMaxHealth());

        printf_s("\r\n");
        printf_s("Gained 1 level! New stats:\r\n");
        PrintStats(false);
        printf_s("\r\n");
    }

    std::string GetStateStr()
    {
        switch (mState)
        {
            case ePlayerState::Goldseek: return "goldseeking";
            case ePlayerState::Nap: return "napping";
        }

        return "Unk";
    }

    std::string GetName() const override { return "Player"; }

    /*void PrintStats(bool pName = true) override
    {
        Unit::PrintStats(pName);
        printf_s("---\r\nGold: %d Experience: %d Level: %d\r\n", mGold, mXP, mLevel);
    }*/

    void ModHealth(int16_t pMod) override;
    void GrantXP(uint8_t pXP);

    bool NextRound();

    void BeginGame();

    uint8_t GetXP() const { return mXP; }
    uint16_t GetGold() const { return mGold; }

    uint16_t GetMaxHealth() const { return 16 + mHealthMod; }
    uint16_t GetAttack() const override { return Unit::GetAttack() + mAttackMod; }
    uint16_t GetDefense() const override { return Unit::GetDefense() + mDefenseMod; }

private:
    uint8_t mXP;
    uint8_t mLevel;
    uint16_t mGold;
    ePlayerState mState;

    uint16_t mHealthMod;
    uint16_t mAttackMod;
    uint16_t mDefenseMod;
};

class Fight
{
public:
    Fight(Player* pPlayer, Creature* pCre)
    {
        mPlayer = pPlayer;
        mCre = pCre;
        mPlayerTurn = false;
        mRound = 0;
    }

    bool NextFightRound();
    bool Strike(Unit* pAttacker, Unit* pVictim);
    void Begin();

private:
    Player* mPlayer;
    Creature* mCre;
    bool mPlayerTurn;
    uint8_t mRound;
};


#endif
