#include "structDec.h"


/* actionSht23: Executes an action for a shooting plant in level 2 and 3.
 Inputs:
    - int x: length of the game board
    - int y: width of the game board
    - int a, b: Coordinates of the shooting plant on the game board.
    - grid** brd: a pointer to the game board, a 2D array of grid structures holding game entities
    - sts* sta: a pointer to the game state, holding various statistics and state-related variables
*/
void actionSht23(int x, int y, int a, int b, grid ** brd, sts * sta) 
{
    int lv = brd[a][b].plant.level;

    // Choose an adjacent row to also attack
    int adjacentRows[] = {a - 1, a + 1, a};
    for (int i = 0; i < 3; ++i) 
    {
        int adjRow = adjacentRows[i];
        if (adjRow >= 0 && adjRow < x) 
        { 
            for (int i = b; i < y; ++i) 
            {
                if (brd[adjRow][i].terrain.id == 7 && lv <= 1)
                {
                    break;
                }

                if (brd[adjRow][i].zombie.id != -1) 
                {
                    brd[adjRow][i].zombie.hp -= brd[a][b].plant.atk[lv];
                    sta->statistic["Normal Damage: "] += brd[a][b].plant.atk[lv];
                    if (lv <= 1) break; // Stop after hitting the first zombie
                }
            }
        }
    }
}

/*actionSht: Executes a shooting action for a level 1 shooter plant
 Inputs:
    - int x: length of the game board
    - int y: width of the game board
    - int a, b: Coordinates of the shooting plant on the game board.
    - grid** brd: a pointer to the game board, a 2D array of grid structures holding game entities
    - sts* sta: a pointer to the game state, holding various statistics and state-related variables
*/
void actionSht(int x, int y, int a, int b, grid ** brd, sts * sta)
{    

    int lv = brd[a][b].plant.level;

    // if (checkBuff(brd, a, b, 'm', 'p') && brd[a][b].plant.hp[lv] < sht.hp[lv])
    // {
    //     brd[a][b].plant.hp[lv] += med.atk;
    // }

    if (brd[a][b].plant.level == 0) 
    {
        for (int i = b-1; ++i < y;)
        {
            if (brd[a][i].terrain.id == 7)
            {
                break;
            }
            if (brd[a][i].zombie.id != -1)
            {
                brd[a][i].zombie.hp -= brd[a][b].plant.atk[lv]; // deal one damage to the nearest zombie on the row
                sta->statistic["Normal Damage: "] += brd[a][b].plant.atk[lv];
                break;
            }
        }
    }
    if (brd[a][b].plant.level >= 1)
    actionSht23(x, y, a, b, brd, sta);// attack increase
}


/* actionSflw: Executes an action for a sunflower, related to cost generation.
 Inputs:
    - int a, b: Coordinates of the sunflower on the game board.
    - grid** brd: Pointer to the game board.
    - sts* sta: Pointer to the game state.
*/
void actionSflw(int a, int b, grid ** brd, sts *sta)
{
    int lv = brd[a][b].plant.level;
    sta->cost += sfw.atk[lv];// generate some costs
    sta->statistic["Costs Generated: "] += sfw.atk[lv];
    if (lv == 2 && brd[a][b].terrain.id == 1)
    {
        brd[a][b].terrain = aIr;
    }

} 

/* actionBoom: Executes an explosive action of a explosive plant, the explosion area increases with the increase of the level.
 Inputs:
    - int x: length of the area where the explosion occurs.
    - int y: width of the area where the explosion occurs.
    - int a, b: Coordinates of the explosive plant on the game board.
    - grid** brd: Pointer to the game board.
    - sts* sta: Pointer to the game state.
*/
void actionBoom(int x, int y, int a, int b, grid ** brd, sts * sta)
{
    int lv = brd[a][b].plant.level;
    if (brd[a][b].plant.level == 0) 
    {
        if (brd[a][b].zombie.hp > 0) // plant position boom
        {
            brd[a][b].zombie.hp -= brd[a][b].plant.atk[lv];
            sta->statistic["Explosion Damage: "] += brd[a][b].plant.atk[lv];
            brd[a][b].plant = Air;
        }
    }

    if (brd[a][b].plant.level == 1) 
    {
        // Assuming each Boom affects zombies in adjacent cells (up, down, left, right)
        const int dx[] = {-1, 1, 0, 0}; // Change in x (row) for adjacent cells
        const int dy[] = {0, 0, -1, 1}; // Change in y (column) for adjacent cells

        for (int i = 0; i < 4; ++i) 
        { // Check all four directions
            int adjX = a + dx[i], adjY = b + dy[i]; // Adjacent cell coordinates
            if (adjX >= 0 && adjX < x && adjY >= 0 && adjY < y) 
            { // Check boundaries
                if (brd[adjX][adjY].zombie.hp > 0) 
                { // If there's a zombie
                    brd[adjX][adjY].zombie.hp -= brd[a][b].plant.atk[lv]; // Kill the zombie
                    sta->statistic["Explosion Damage: "] += brd[a][b].plant.atk[lv];
                }
                
            }
        }
        brd[a][b].plant = Air; // Remove the Cherry Boom after activation
    }

    if (brd[a][b].plant.level == 2) 
    {
        for (int i = -1; ++i < x; )
        {
            for (int j = 0; j < y; ++j) 
            { // Iterate through the entire board
                if (brd[i][j].zombie.hp > 0) 
                { // If there's a zombie in the cell
                    brd[i][j].zombie.hp -= brd[a][b].plant.atk[lv]; // Set zombie's hp to 0, effectively removing it
                    sta->statistic["Explosion Damage: "] += brd[a][b].plant.atk[lv];
                }
                if (brd[i][j].terrain.id == 7)
                {
                    brd[i][j].terrain = aIr;
                }
            }
        }
        
        // Remove the Jalapeno plant after activation
        brd[a][b].plant = Air;
    }

}

/* actionSporeshroom: Executes an action for a sporeshroom, the scope of the attack increases with the level.
 Inputs:
    - int x: length of the area where the explosion occurs.
    - int y: width of the area where the explosion occurs.
    - int a, b: Coordinates of the sporeshroom on the game board.
    - grid** brd: Pointer to the game board.
    - sts* sta: Pointer to the game state.
*/
void actionSporeShroom(int y, int a, int b, grid ** brd) 
{
    int lv = brd[a][b].plant.level;
    int range;

    if (lv == 0) range = std::min(b + 3, y);
    else range = y;

    for (int i = b; i < range; ++i) // Assume that the attack range is the first two cells
    {
        if (brd[a][i].zombie.id != -1)
        {
            //brd[a][i].zombie.hp -= brd[a][b].plant.atk[lv];
            brd[a][i].zombie.frost = 1;
            if (lv < 2) break; 
        }
    }
}

