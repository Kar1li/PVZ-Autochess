#include "structDec.h"

int actionZ(grid ** brd, int a, int b, int x, sts * sta)
{
    if (brd[a][b].zombie.frost || brd[a][b].terrain.id == 8) brd[a][b].zombie.frozen++;//Zombie will be influenced by the terrain.
    if (brd[a][b].zombie.frozen >= 3) // 3 frost pause an enemy for a round
    {
        brd[a][b].zombie.frozen = 0;
        sta->statistic["Frozen Time: "]++;
        return 0;
    }
    else if (brd[a][b].terrain.id==7) // a block terrain is encountered
    {
        int o=rand()%2;    //choose to move either up or down row
        int oi=o*2-1;
        if (!(a+oi<x && a+oi>=0))   {oi = -oi;}    //if out of range

        if (brd[a+oi][b].zombie.id == -1)
        {
            brd[a+oi][b].zombie = brd[a][b].zombie; // move 
        }

        else
        {   // fuse with another zombie if they overlap

            brd[a+oi][b].zombie.atk += brd[a][b].zombie.atk;
            brd[a+oi][b].zombie.hp += brd[a][b].zombie.hp;
            brd[a+oi][b].zombie.jmp += brd[a][b].zombie.jmp;
            brd[a+oi][b].zombie.boom += brd[a][b].zombie.boom;
            sta->statistic["Times of Fusion: "]++;
        }

        brd[a][b].zombie=aiR;
    }

    else if (brd[a][b].zombie.jmp >= 1 && brd[a][b].plant.id != -1)    // can jump and a plant is in front
    {
        brd[a][b].zombie.jmp--;    // jumped
        sta->statistic["Times of Jump: "]++;
        if (b - 1 >= 0)    // check range
        {
            if (brd[a][b-1].zombie.id == -1)    // no zombie ahead
            {
                brd[a][b-1].zombie = brd[a][b].zombie; // move one grid forward
            }
            else
            {   // fuse with another zombie if they overlap
                brd[a][b-1].zombie.atk += brd[a][b].zombie.atk;
                brd[a][b-1].zombie.hp += brd[a][b].zombie.hp;
                brd[a][b-1].zombie.jmp += brd[a][b].zombie.jmp;
                brd[a][b-1].zombie.boom += brd[a][b].zombie.boom;   
                sta->statistic["Times of Fusion: "]++;
            }
            brd[a][b].zombie = aiR;
        }
    }
    else{
        if (brd[a][b].plant.id != -1)    // a plant is in front
        {
            if (brd[a][b].zombie.boom >= 1)    //have a boom
            {
                brd[a][b].plant=Air;
                brd[a][b].zombie.hp -= 20; //damage of a boom
                brd[a][b].zombie.boom--;
                sta->statistic["Times of Detonation: "]++;
            }   //joker explode
            else  
            {    
                brd[a][b].plant.hp[brd[a][b].plant.level] -= brd[a][b].zombie.atk;
                sta->statistic["Damage Taken: "] += brd[a][b].zombie.atk;
            } // attack a plant
        }
        else
        {
            if (b - 1 >= 0)
            {
                if (brd[a][b-1].zombie.id == -1)    //no zom ahead
                {
                    brd[a][b-1].zombie = brd[a][b].zombie; // move one grid forward
                }
                else
                {   // fuse with another zombie if they overlap

                    brd[a][b-1].zombie.atk += brd[a][b].zombie.atk;
                    brd[a][b-1].zombie.hp += brd[a][b].zombie.hp;
                    brd[a][b-1].zombie.jmp += brd[a][b].zombie.jmp;
                    brd[a][b-1].zombie.boom += brd[a][b].zombie.boom;
                    sta->statistic["Times of Fusion: "]++;
                }
                brd[a][b].zombie = aiR;
            }
            else return 1;
        }
    }
    return 0;
}

