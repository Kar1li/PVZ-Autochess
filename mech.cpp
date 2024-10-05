#include "structDec.h"

//take in the brd data
//clear plants and zombies with 0/negative hp into air
void clear(int a, int b, grid ** brd)
{
    int lv = brd[a][b].plant.level; 
    if (brd[a][b].plant.hp[lv]<=0) brd[a][b].plant = Air;//turn dead plant into air
    if (brd[a][b].zombie.hp<=0) brd[a][b].zombie = aiR;//turn dead zombie into air
}


//make the game into next frame(execute the functions of all plants/zombies/terrians)
//take in the status sta of this status

int nextFrame(grid ** brd, sts * sta, int x, int y)
{
    int size = x*y;

    sta->time++;//time plus by 1
    
    for (int i = -1; ++i < size; )
    {
        

        int a = i/y, b = i%y; // (a, b) is the coordinate of the current grid


        clear(a, b, brd); //call the clear function to clear the dead plant/zombie

        if (brd[a][b].terrain.id == 1) actionP(a, b, brd, sta); //execute the function of poison
        if (brd[a][b].terrain.id == 2) actionM(a, b, brd, sta); //execute the function of med


        if (brd[a][b].plant.id == 0) actionSht(x, y, a, b, brd, sta); //execute the function of shooter
        if (brd[a][b].plant.id == 1) actionSflw(a, b, brd, sta); //execute the function of sunflower
        if (brd[a][b].plant.id == 2) actionBoom(x, y, a, b, brd, sta);//execute the function of boom
        if (brd[a][b].plant.id == 4) actionSporeShroom(y, a, b, brd);//execute the function of sporeshroom


        clear(a, b, brd);//call the clear function to clear the dead plant/zombie

        if (brd[a][b].zombie.id != -1)
        {
            if (actionZ(brd, a, b, x, sta)) return 1; //execute the function of zombie
        }
        


        
    }
    return 0;
}

