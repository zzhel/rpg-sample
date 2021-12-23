#include "Player.h"
#include "Creature.h"
#include "CreatureMgr.h"

void Player::GrantXP(uint8_t pXP)
{
    uint8_t lNewXp = mXP + pXP;
    uint8_t lNextLvlXp = GetAttack() + GetDefense();

    printf_s("Gained %u XP.\r\n", pXP);

    while (lNewXp >= lNextLvlXp)
    {
        lNewXp -= lNextLvlXp;
        LevelUp();
        lNextLvlXp = GetAttack() + GetDefense();
    }

    mXP += lNewXp;
    printf_s("Experience: %d Level: %d\r\n", mXP, mLevel);
}

void Player::ModHealth(int16_t pMod)
{
    int16_t lHealth = GetHealth() + pMod;
    if (lHealth <= 0)
        lHealth = 0;
    else if (lHealth > GetMaxHealth())
        lHealth = GetMaxHealth();

    SetHealth(lHealth);
}

bool Player::NextRound()
{
    std::string lInput;
    printf_s("Do you wish to take a nap or go goldseeking? Possible answers: \"nap\", \"goldseek\"\r\n");
    Helpers::HandleInput({ "nap", "goldseek" }, lInput);

    if (lInput.compare("nap") == 0)
    {
        mState = ePlayerState::Nap;
        if (Helpers::rollChance(50))
        {
            ModHealth(static_cast<uint16_t>(std::round(GetMaxHealth() * 0.2f)));
            printf_s("You took a refreshing nap, health restored by 20%%. Health: %d\r\n", GetHealth());
        }
        else
        {
            // fight
            if (Creature* lCre = sCreatureMgr->GetRandomCreature())
            {
                Fight* lFight = new Fight(this, lCre);
                lFight->Begin();
                delete lFight;
            }
        }
    }
    else
    {
        mState = ePlayerState::Goldseek;
        if (Helpers::rollChance(60))
        {
            // fight
            if (Creature* lCre = sCreatureMgr->GetRandomCreature())
            {
                Fight* lFight = new Fight(this, lCre);
                lFight->Begin();
                delete lFight;
            }
            else
            {
                printf_s("No creature found. Exiting game.\r\n");
                return false;
            }
        }
        else if (Helpers::rollChance(10))
        {
            // stumbled upon gold
            uint8_t lGold = Helpers::randInt(MIN_STUMBLE_GOLD, MAX_STUMBLE_GOLD);
            ModGold(lGold);
            printf_s("Found %d gold! Total Gold: %d\r\n", lGold, mGold);
        }
        else
            printf_s("No gold found! Gold: %d\r\n", mGold);
    }

    return !IsDead();
}

void Player::BeginGame()
{
    while (NextRound());

    printf_s("Game finished.\r\n");
    system("PAUSE");
}

bool Fight::NextFightRound()
{
    printf_s("Round %d!\r\n", ++mRound);

    if (mPlayerTurn)
    {
        printf_s("Possible options: \"run\", \"attack\"\r\n");

        std::string lInput;
        Helpers::HandleInput({ "run", "attack" }, lInput);

        if (lInput.compare("run") == 0)
        {
            if (Helpers::rollChance(50))
            {
                // ran away
                printf_s("You ran away from the fight, returning to previous state.\r\n");
                return false;
            }
            else
            {
                printf_s("You failed to flee the fight, it\'s the monster\'s turn!.\r\n");
                mPlayerTurn = false;
            }

        }
    }
    
    Unit* lAttacker = mPlayer;
    Unit* lVictim = mCre;

    if (!mPlayerTurn)
        std::swap(lAttacker, lVictim);

    if (Strike(lAttacker, lVictim))
    {
        printf_s("[%s] died in battle from [%s]!\r\n", lVictim->GetName().c_str(), lAttacker->GetName().c_str());

        if (!lVictim->IsPlayer())
            lVictim->ToCreature()->KillByPlayer(lAttacker->ToPlayer());

        return false;
    }

    mPlayerTurn = !mPlayerTurn;
    return true;
}

bool Fight::Strike(Unit* pAttacker, Unit* pVictim)
{
    uint16_t lDmg = pVictim->TakeDamageFrom(pAttacker->GetAttack());
    printf_s("[%s] dealt %d damage to [%s]! Health: %d\r\n", pAttacker->GetName().c_str(), lDmg, pVictim->GetName().c_str(), pVictim->GetHealth());
    return pVictim->IsDead();
}

void Fight::Begin()
{
    printf("\r\nYou have stumbled upon a %s!", mCre->GetName().c_str());
    printf("Stats brief:\r\n");
    mCre->PrintStats(false);
    printf("Let the fight commence!\r\n");
    mPlayerTurn = true;
    while (NextFightRound());
}
