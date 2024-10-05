#include "structDec.h"

//save the game status
//input the name of file
//output a file saving the data
void save(grid ** brd, sts * sta, int x, int y, std::string name)
{
    std::ofstream ofs(name);//open a file stream to save the data

    if (ofs.is_open())//save the x and y
    {
        int size = x * y;

        ofs << x << ' ' << y << " " << sta->cost << " " << sta->time << '\n';//save the cost and time

        for (int i = -1; ++i < size; )//save the plant/zombie/terrian in every block
        {
            int a = i / y, b = i % y;
            grid g = brd[a][b];
            ofs << g.plant.id << ' ' << g.plant.level << ' ' << g.terrain.id << ' ' 
            << g.zombie.id << ' ' << g.zombie.atk << ' ' << g.zombie.hp << ' ' << g.zombie.jmp << ' ' << g.zombie.boom << '\n';
        }
        for (plt p: preparation)//save the plants in preparation state
        {
            ofs << p.id << ' ' << p.level << '\n';
        }
        ofs.close();//close the file
        std::cout <<
            " _____ ___ _     _____                         \n"
            "|  ___|_ _| |   | ____|                        \n"
            "| |_   | || |   |  _|                          \n"
            "|  _|  | || |___| |___                         \n"
            "|_|   |___|_____|_____|  ____                \n"
            "/ ___|  / \\ \\   / / ____|  _ \\                 \n"
            "\\___ \\ / _ \\ \\ / /|  _| | | | |                \n"
            " ___) / ___ \\ V / | |___| |_| |                \n"
            "|____/_/   \\_\\_/  |_____|____/  \n";

    }
    else
    {
        std::cout << "fail to open file" << std::endl;
    }
}

//load the game status
//input the name of file
//output a board using the data saved in the file
grid ** load(std::string name, int * x, int * y, sts *sta)
{
    std::ifstream ifs(name);//open a file stream to read the data
    grid ** brd;
    if (ifs.is_open())
    {
        ifs >> *x >> *y >> sta->cost >> sta->time;//read x, y, cost, time in the file
        brd = makeBoard(*x, *y);//make the board
        int size = (*x) * (*y);
        int pid, plv, tid, zid, zak, zhp, zjp, zbm;//initialize data 
        for (int i = -1; ++i < size; )//loop over every block
        {
            int a = i / (*y), b = i % (*y);
            ifs >> pid >> plv >> tid >> zid >> zak >> zhp >> zjp >> zbm;//read in all data for the block
            brd[a][b].plant = (pid < 0) ? Air: Plants[pid];//plant's data
            brd[a][b].plant.level = plv;
            brd[a][b].terrain = (tid < 0) ? aIr: Terrains[tid];//terrain's data
            brd[a][b].zombie = (zid < 0) ? aiR: Zombies[zid];//zombie's data
            brd[a][b].zombie.atk = zak;
            brd[a][b].zombie.hp = zhp;
            brd[a][b].zombie.jmp = zjp;
            brd[a][b].zombie.boom = zbm;
        }
        while (ifs >> pid >> plv) //read in the data of plants in preparation status
        {
            plt p = Plants[pid];
            p.level = plv;
            update(p);
        }
        ifs.close();//close the file stream
        std::cout <<
            " ______ _____ _      ______         \n"
            "|  ____|_   _| |    |  ____|        \n"
            "| |__    | | | |    | |__           \n"
            "|  __|   | | | |    |  __|          \n"
            "| |     _| |_| |____| |____         \n"
            "|_|    |_____|______| _____| ______ _____\n"
            "| |    / __ \\   /\\   |  __ \\|  ____|  __ \\ \n"
            "| |   | |  | | /  \\  | |  | | |__  | |  | |\n"
            "| |   | |  | |/ /\\ \\ | |  | |  __| | |  | |\n"
            "| |___| |__| / ____ \\| |__| | |____| |__| |\n"
            "|______\\____/_/    \\_\\_____/|______|_____/ \n";
    }
    else
    {
        std::cout << "fail to open file" << std::endl;
    }
    return brd;
}

