#include "Unit.h"
#include "CreatureMgr.h"

int main()
{
    printf_s("Spawning creatures! \r\n");
    // spawn creatures
    for (auto lIter : { 
        eCreTypes::Skeleton, 
        eCreTypes::Skeleton, 
        eCreTypes::Skeleton, 
        eCreTypes::Skeleton, 
        eCreTypes::Skeleton, 
        eCreTypes::Skeleton, 
        eCreTypes::Skeleton, 
        eCreTypes::Skeleton, 
        eCreTypes::Skeleton, 
        eCreTypes::Skeleton, 
        eCreTypes::Skeleton, 
        eCreTypes::Zombie, 
        eCreTypes::Zombie, 
        eCreTypes::Zombie, 
        eCreTypes::Vampire,
        eCreTypes::Vampire })
    {
        Creature* lCre = new Creature(lIter);
        //lCre->PrintStats();
    }

    Player* const lPlayer = new Player();

    printf_s("\r\nInitialized player: \r\n");
    lPlayer->PrintStats();

    lPlayer->GrantXP(20);
    lPlayer->GrantXP(200);
    lPlayer->BeginGame();
}
