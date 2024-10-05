#include "structDec.h"

//print the shop
//take in the status sta
//print names/costs of plants and the cost we have
void print_shop(sts sta)
{
    std::cout << "Shop:\n";
    for (int i = 0; i < scale; ++i)
        std::cout << plts_in_shop[i].name[0] << '\t';//print the name of plants
    std::cout << std::endl;
    for (int i = 0; i < scale; ++i)
        std::cout << plts_in_shop[i].cost << '\t';//print the costs of plants
    std::cout << std::endl;
    printf("\n");
    std:: cout << "Cost: " << sta.cost << std::endl;//print the cost we have
    printf("\n");
}


//print the board to show the game
//take in the width and lenth of board, the board brd and the status sts
//print the plant/zombie.terrian of every block
void printBoard(grid** board, int x, int y, sts sta)
{
    int size = x*y;
    for (int i =-1;++i<size;)//loop over every block
    {
        int a = i/y, b = i%y;
        int lv = board[a][b].plant.level;
        std::cout << a << b << ' ' 
        << std::setw(2) << board[a][b].plant.name[lv] //the name of plant
        << std::setw(2) << board[a][b].terrain.name//the name of terrian
        << std::setw(7) << board[a][b].zombie.name//the name of zombie
        << "\t";
        if (b == y-1) 
        {
            printf("\n\n");
        }
    }
}

//from shop to game
//take in the width and lenth of board, the board brd and the status sts
//print the preparation 
void printAll(grid ** brd, int x, int y, sts sta)
{
    for ( int i = -1; ++i < 40; std::cout << std::endl); // clear screen
    print_shop(sta);//call the function to print shop
    std::cout << "Preparation:\n";
    for (plt p: preparation)//print the plants we bought and now in preparation 
    {
        int lv = p.level; //level of the plant
        std::cout << p.name[lv] << "\t"; // name of the plant
    }
    printf("\n\n\n");
    printBoard(brd, x, y, sta);
    printf("\n\n\n");
}

