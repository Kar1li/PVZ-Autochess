#include "structDec.h"

/*struct Zom
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
*/
zom aiR = {" ", 0, 0, 0, -1,0, 0, 0, 0};
zom Z = {"\U0001F9DF", 1, 10, 10, 0,0, 0, 0, 0};
zom X = {"\U0001F9DB", 2, 15, 15, 1,0, 0, 0, 0};
zom J = {"\U0001F47B", 2, 10, 10, 2,1, 0, 0, 0};
zom K = {"\U0001F479", 0, 3, 3, 3,0, 1, 0, 0};
zom Zombies[4] = {Z, X, J, K};
//aiR is to occupy the position.
// Z is Basic Zombie
// X is Conehead Zombie
//J is Pole Vaulting Zombie
// K is Jake-in-the-box zombie. It will boom when meeting a plant

