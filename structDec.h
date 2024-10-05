#ifndef SD
#define SD

#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <time.h>
#include <unordered_map>
#include <vector>

//structure plant
struct Plt
{
    std::string name[3];
    //an array contains a plant's name of three level, level 1 change to green, level 2 change to red
    int cost;
    //price of a level 0 plant in shop
    int atk[3];
    //an array contains a plant's attack of three levels 
    int hp[3];
    //hp
    int mhp[3];
    //maxmium hp, avoid terrain med over heal a plant
    int id;
    //plant's id
    int level;
    //plant's level
    bool operator==(const Plt& other) const 
    {
        return id == other.id && level == other.level;
        //judge two plants equal or not by their id and level
    }
};
typedef struct Plt plt;
namespace std{
    template<>
    struct hash<Plt>{
        size_t operator()(const Plt &plt) const{
            size_t h1 = hash<int>()(plt.id);
            size_t h2 = hash<int>()(plt.level);
            return h1 ^ (h2 << 1); 
        }
    };
}//make structure plt hashable to use plt in map count_preparation 

struct Zom
 {
    std::string name;
    int atk;//attack
    int hp;
    int mhp;//maximum hp
    int id;
    int jmp;
    //times jump over the plant
    int boom;
    //explode after encountering a plant
    int frost;
    int frozen;
    //freeze zombie by plant or terrain
};
typedef struct Zom zom;

struct Trn
{
    std::string name;
    int id;
    int time;
    int atk;//add attack/heal to unit on this terrain
    int buff;//add buff to unit
};
typedef struct Trn trn;

struct Grid
{
    plt plant;
    zom zombie;
    trn terrain;
    //save the plant, zombie, terrain on this grid
};
typedef struct Grid grid;




struct Status
{
    int cost;//availible cost
    int score;
    int time;
    std::map<std::string, int> statistic;
    //statistic game data
};
typedef struct Status sts;

// action of a shooter
void actionSht(int x, int y, int a, int b, grid ** brd, sts * sta);
void actionSht23(int x, int y, int a, int b, grid ** brd, sts * sta);

// action of a sunflower
void actionSflw(int a, int b, grid ** brd, sts *sta);

//action of a sporeshroom
void actionSporeShroom(int y, int a, int b, grid ** brd);

// action of a boom the plant
void actionBoom(int x, int y, int a, int b, grid ** brd, sts * sta);

// action of a boom the terrain
void actionB(int a, int b, grid ** brd);

//action of trn poison
void actionP(int a, int b , grid ** brd, sts * sta);

// action of med
void actionM(int a, int b , grid ** brd, sts * sta);

// action of a zombie
int actionZ(grid ** brd, int a, int b, int x, sts * sta);

// take in a vertical size x, and a horizontal size y to generate a 2D game board
// !! two "*" (the "board" is a point of pointers of "grid"s) !!
grid** makeBoard(int x, int y);

// present the user interface
void printBoard(grid** board, int x, int y, sts sta);

//print plants in shop
void print_shop(sts sta);

// It asks player to choose a coordinate and the id of the plant to deploy it
//input the position of grid and index of preparation to deploy a plant on a grid
void deploy(int x, int y, grid**board);

// randomly generate zombies on the rightmost column
void genZom(grid ** brd, int x, int y, sts sta);

//generate terrain randomly
void genbuffTrn(grid** brd, int x, int y, sts * sta);

// remove units with hp no greater than 0 (by replacing with "air")
void clear(int a, int b, grid ** brd);

// trigger action of all units and go to next frame
int nextFrame(grid ** brd, sts * sta, int x, int y);

// used for debug mode
void debug();

//update and count plants in preparation
void update(plt newplant);

//buy plants in shop
int buy(sts *sta);

//initialize shop
void initialize_shop();

//spend cost to refresh shop
void refresh_shop(sts *sta);

//make plant.level++
void level_up(plt *plant);

//undeploy plant from certain grid to preparation
void undeploy(int x, int y, grid **board);

//overall print function
void printAll(grid ** brd, int x, int y, sts sta);

//print statistic of player
void printStatistic(sts * sta);

//output and save statistic game data in a file
void writeStatistic(sts * sta);

//save game data
void save(grid ** brd, sts * sta, int x, int y, std::string name);

//load
grid ** load(std::string name, int * x, int * y, sts *sta);

//game
void game();

//Global variables

//an undered_map to count amount of plants
extern std::unordered_map<plt, int> count_preparation;

//plants in preparation
extern std::vector<plt> preparation;

//all plants, level = 0 defaut
extern plt Air;
extern plt sht;
extern plt sfw;
extern plt boom;
extern plt wln;
extern plt sporeshroom;
extern plt Plants[5];

//all terrains
extern trn aIr;
extern trn poison;
extern trn med;
extern trn highplace;
extern trn water;
extern trn T[5];
extern trn Terrains[9];

//all zombies
extern zom aiR;
extern zom Z;
extern zom X;
extern zom J;
extern zom K;
extern zom Zombies[4];

//shop scale
const int scale = 5;

//plants in shop currently
extern plt plts_in_shop[scale];

//to avoid repeat purchase
extern bool sold[scale];

// grid air = {Air, aiR, aIr};


#endif
