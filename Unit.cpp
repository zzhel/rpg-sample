#include "Unit.h"
#include "CreatureMgr.h"

void Unit::ModHealth(int16_t pMod)
{
    int16_t lHealth = GetHealth() + pMod;
    if (lHealth <= 0)
        lHealth = 0;
    else if (lHealth > MAXHP)
        lHealth = MAXHP;

    SetHealth(lHealth);
}

uint16_t Unit::TakeDamageFrom(uint16_t pDamage)
{
    if (pDamage <= GetDefense())
        pDamage = 1;
    else
        pDamage -= GetDefense();

    ModHealth(-pDamage);
    return pDamage;
}
