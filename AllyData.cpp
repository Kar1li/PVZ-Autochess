#include "structDec.h"


/*
struct Plt
{
    std::string name[3];---plant symbol
    int cost;---the cost associated with using this plant
    int atk[3];---the attack power of the plant in different levels.
    int hp[3];---It shows how much damage the plant can withstand in each of its stages before it gets destroyed.
    int mhp[3];--- It specifies the upper limit of health point that the plant can have in each of its stages.
    int id;---It is used to uniquely identify each type of plant within the game.
    int level;--- It indicates the current level of the plant.
    bool operator==(const Plt& other) const 
    {
        return id == other.id && level == other.level;
    }---It allows for straightforward comparison between two Plt objects, checking if they have the same id and level.
};
*/

plt Air = 
{ 
    {" ", " ", " "}, 
    0, 
    {0, 0, 0}, 
    {0, 0, 0}, 
    {0, 0, 0}, 
    -1, 
    0
};

plt sht = 
{ 
    {">", "\033[1;32m>\033[0m", "\033[1;31m>\033[0m" }, 
    10, 
    {1, 1, 2}, 
    {10, 12, 15}, 
    {10, 12, 15}, 
    0, 
    0
};

plt sfw = 
{ 
    {"*", "\033[1;32m*\033[0m", "\033[1;31m*\033[0m"}, 
    10, 
    {3, 10, 32}, 
    {10, 12, 14}, 
    {10, 12, 14}, 
    1, 
    0
};

plt boom = 
{ 
    {"!", "\033[1;32m!\033[0m", "\033[1;31m!\033[0m"}, 
    5, 
    {20, 25, 30}, 
    {10, 12, 14}, 
    {10, 12, 14}, 
    2, 
    0
};

plt wln = 
{ 
    {"]", "\033[1;32m]\033[0m", "\033[1;31m]\033[0m"},
    15, 
    {0, 0, 0}, 
    {20, 100, 400}, 
    {20, 100, 400}, 
    3, 
    0
};

plt sporeshroom = 
{
    {"=", "\033[1;32m=\033[0m", "\033[1;31m=\033[0m"}, 
    20, 
    {2, 4, 4}, 
    {10, 14, 16},
    {10, 14, 16},
    4, 
    0
};

plt Plants[5] = {sht, sfw, boom, wln, sporeshroom};

