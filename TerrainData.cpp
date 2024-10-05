#include "structDec.h"

trn aIr = {" ", -1, 99, 0, 0};//defalut terrian of board


trn poison = {"\U00002620",1,99,5,0};//give plant and zombie on it damage
trn med={"\U0001F48A",2,99, 5,0};//give plant and zombie on it healing


trn highplace={"\U0001F5FB",7,99,0,5};  //Block zombie to other line
trn water={"\U0001F30A",8,99,0,0};  //zombie will get frozen in water

trn T[5] = {aIr, poison, med, highplace, water};
trn Terrains[9] = {aIr, poison, med, aIr, aIr, aIr, aIr, highplace, water};//store the data of terrains

