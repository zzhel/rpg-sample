#ifndef UNIT_H
#define UNIT_H
#include <iostream>
#include <chrono>
#include <memory>
#include <set>
#include <string>
#include <algorithm>
#include <vector>
#include <math.h>

namespace Helpers
{
    static int32_t randInt(int32_t pMin, int32_t pMax)
    {
        srand(static_cast<uint32_t>(std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::steady_clock::now()).time_since_epoch().count()));
        return rand() % (pMax - pMin + 1) + pMin;
    }

    static bool rollChance(int32_t pChance)
    {
        return randInt(0, 99) < pChance;
    }

    static bool HandleInput(std::set<std::string> pOptions, std::string& pInput)
    {
        std::string lRet = "";

        while (true)
        {
            std::getline(std::cin, lRet);

            std::string lTemp = lRet;
            std::transform(lTemp.begin(), lTemp.end(), lTemp.begin(), [](char c)
            {
                return std::tolower(c); 
            });

            // found
            if (pOptions.find(lTemp.c_str()) == pOptions.end())
            {
                printf_s("Invalid value \"%s\", please try again.\r\n", lRet.c_str());
                continue;
            }
            else
            {
                pInput.append(lTemp);
                break;
            }
        }

        return true;
    };
};

#define MINHP 12
#define MAXHP 16

#define MIN_AP_AND_DEF 8
#define MAX_AP_AND_DEF 12

#define MIN_STUMBLE_GOLD 20
#define MAX_STUMBLE_GOLD 40

class Creature;
class Player;

class Unit
{
public:
    Unit()
    {
        mHealth = 0;
        mAttack = 0;
        mDefense = 0;

        mPlayer = false;
    };

    void Init(int16_t pHealth, uint16_t pAttack, uint16_t pDefense)
    {
        mHealth = pHealth;
        mAttack = pAttack;
        mDefense = pDefense;
    }

    int16_t GetHealth() const { return mHealth; }
    virtual uint16_t GetAttack() const { return mAttack; }
    virtual uint16_t GetDefense() const { return mDefense; }

    void SetHealth(int16_t pHealth) { mHealth = pHealth; }
    virtual void ModHealth(int16_t pMod);
    virtual std::string GetName() const { return "unk"; };

    uint16_t TakeDamageFrom(uint16_t);

    bool IsDead() const { return mHealth <= 0; }

    void SetIsPlayer() { mPlayer = true; }
    bool IsPlayer() const { return mPlayer; }

    Creature* ToCreature() { if (!mPlayer) return reinterpret_cast<Creature*>(this); else return nullptr; }
    Player* ToPlayer() { if (mPlayer) return reinterpret_cast<Player*>(this); else return nullptr; }

    virtual void PrintStats(bool pName = true)
    {
        if (pName)
            printf_s("\r\nName: \"%s\"", GetName().c_str());

        printf_s("\r\nHealth: %d\r\nAttack: %d Defense: %d\r\n", mHealth, GetAttack(), GetDefense());
    }

private:
    int16_t mHealth;
    uint16_t mAttack;
    uint16_t mDefense;
    bool mPlayer;
};

enum class eCreTypes : uint8_t
{
    None = 0,
    Zombie,
    Skeleton,
    Vampire
};

#endif
