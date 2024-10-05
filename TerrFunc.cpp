#include "structDec.h"

// action of poison
// the function take in the coordinate of poison
// give damage to zombie and plant on it
void actionP(int a, int b , grid ** brd, sts * sta)
{
    int lv = brd[a][b].plant.level;
    if (brd[a][b].zombie.id != -1)
    {
        brd[a][b].zombie.hp -= poison.atk;//give damage to zombie through grid ** brd
        sta->statistic["Poison to Ally: "] += poison.atk;
    }
    if (brd[a][b].plant.id != -1)
    {
        brd[a][b].plant.hp[lv] -= poison.atk;//give damage to plant through grid ** brd
        sta->statistic["Poison to Enemy: "] += poison.atk;
        
    }  
}
// action of med
// the function take in the coordinate of med
// give healing to zombie and plant on it
void actionM(int a, int b , grid ** brd, sts * sta)
{
    int lv = brd[a][b].plant.level;
    if (brd[a][b].zombie.id != -1 && brd[a][b].zombie.hp < brd[a][b].zombie.mhp)//give damage to zombie through grid ** brd
    {                                                                              // use boundary to avoid huge zombie 
        brd[a][b].zombie.hp += med.atk;                                            // which will affect the balance
        sta->statistic["Med to Ally: "] += med.atk;                                // show the affect 
    }
    if (brd[a][b].plant.id != -1 && brd[a][b].plant.hp[lv] < brd[a][b].plant.mhp[lv])//give damage to zombie through grid ** brd
    {                                                                                  // use boundary to avoid huge zombie 
        brd[a][b].plant.hp[lv] += med.atk;                                             // which will affect the balance
        sta->statistic["Med to Enemy: "] += med.atk;                                   // show the affect 
    }  
}

