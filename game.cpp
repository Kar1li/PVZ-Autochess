#include "structDec.h"



// It asks player to choose a coordinate and the id of the plant to deploy it
void deploy(int x, int y,/*int x, int y, plt p, */grid**board)
{
    int r = x, c = y;
    int dx, dy, z;

    if (x <=10 && y <=10) // for small size boards
    {
        int k;
        std::cin >> k;
        z = k % 10; //id of ally unit
        k /= 10;    //reduce k to coordinate
        dx = k / 10; dy = k % 10;   //get coordinate
    }
    else
    {
        printf("Deploy: "); //for large size boards
        scanf("%d%d%d",&dx,&dy,&z);
    }

    if (dx >= r || dy >= c)
    {
        std::cout << "out of board\n"; //as the cout suggests
        return;
    }
    if (preparation.empty() || z > preparation.size() - 1 || z < 0)
    {
        printf("no such plant\n");  //as the cout suggests
        return;
    }
    if (board[dx][dy].terrain.id == 8)
    {
        printf("cannot deploy on water\n"); //as the cout suggests
        return;
    }
    plt p;

   
    // check for validation
    if (board[dx][dy].plant.id == -1)
        {
            // update the board and status bar if valid
            p = preparation[z]; //get unit
            preparation.erase(preparation.begin() + z); //take away unit
            board[dx][dy].plant = p;    //deploy unit
            count_preparation[p]--;
        }
    else
    {
        printf("Occupied! Try elsewhere or use the spade!\n");  //as the message suggests
    }
}
void undeploy(int x, int y, grid**board)
{
    int r = x, c = y;   //get sizes
    int dx, dy; //get current location
    std::cout << "Undeploy: ";
    std::cin >> dx >> dy;
    if (dx >= r || dy >= c)
    {
        std::cout << "out of board\n";
        return;
    }
    if (board[dx][dy].plant.id == -1)   //Air
    {
        std::cout << "no plant here\n";
        return;
    }
    update(board[dx][dy].plant);    //put back to the desk
    board[dx][dy].plant = Air;  //replace with air
}

void genZom(grid ** brd, int x, int y, sts sta)
{
    int t = sta.time;   //rounds survived
    for (int i = -1; ++ i < x; )
    {
        int prob = rand() % (20+t); //denominator of the probability
        if (prob <= t)  //numerator
        {
            int _ = rand() % 4; //one random enemy unit
            brd[i][y-1].zombie = Zombies[_];
        }
    }
}

grid** makeBoard(int x, int y)  //take in sizes
{
    grid air = {Air, aiR, aIr};
    grid ** brd = new grid*[x]; //pointer of x pointers which represent the vertical indexes
    for (int i=-1;++i<x;)
    {
        brd[i]=new grid[y]; //each stores y grid 

    }
    for (int j = -1; ++j <x*y;)
    {   
        int a = j/y, b = j%y;
        // initialization with the "air" corresponding the its type
        brd[a][b] = air;
    }

    return brd;
}


void genbuffTrn(grid** brd, int x, int y, sts * sta)
{
    for (int i=0;i<x;i++)
    {
        for (int j=0;j<y;j++)   //iterate the whole board
        {
            if (brd[i][j].terrain.id == -1 )    //if not air
            {
                int den = rand()%10;    //denominator of probability
                if (den<=2) //numerator
                {
                    trn tt = T[rand()%4+1]; //one random terrain
                    brd[i][j].terrain = tt; //generate to grid
                    std::string message = tt.name + " generated: "; //record statistics
                    sta->statistic[message]++;
                }
            }
        }
    }
}






void game() //process of the game
{
    char cmd[100];  //command
    int x, y;   //sizes
    sts sta = {50, 0 , 0};  //status
    grid ** board;
    printf("Start a new game or load? \n");
    scanf("%s", cmd);
    if ( ! strcmp(cmd, "load"))
        {
            std::string name;
            std::cin >> name;
            board = load(name, &x, &y, &sta);   //load from file input
        }
    else
    {
        printf("Set up the board with two integers representing vertical and horizontal sizes respectively: \n");
        scanf("%d%d", &x, &y);  //prompt for sizes
        board = makeBoard(x, y);
        genbuffTrn(board, x, y, &sta);  //generate terrains
    }


    printAll(board, x, y, sta); //print the UI

    for (scanf("%s",&cmd); cmd[0] != 'q'; scanf("%s",&cmd)) //stop when q is read
    {
        if (strcmp(cmd,"dp")==0) deploy(x, y, board);
        if (!strcmp(cmd, "ud")) undeploy(x, y, board);
        if (strcmp(cmd, "b") == 0)
        {
            buy(&sta);
        }
        if (strcmp(cmd, "re") == 0)
        {
            refresh_shop(&sta);
        }
        if (!strcmp(cmd, "gt"))
        {
            genbuffTrn(board, x, y, &sta);
        }
        if (!strcmp(cmd, "l"))  //level up an ally
        {
            int a, b;
            scanf("%d%d", &a, &b);
            board[a][b].plant.level++;
        }
        if (!strcmp(cmd, "dt")) //deploy terrain (debug feature)
        {
            int a, b, z;
            scanf("%d%d%d", &a, &b, &z);
            board[a][b].terrain = T[z];
        }
        if (!strcmp(cmd, "dz")) //debug feature
        {
            int a, b, z;
            scanf("%d%d%d", &a, &b, &z);
            board[a][b].zombie = Zombies[z];
        }
        if (!strcmp(cmd, "d"))  //debug feature
        {
            int a, b, z;
            scanf("%d%d%d", &a, &b, &z);
            board[a][b].plant = Plants[z];
        }
        if (strcmp(cmd,"pb")==0) printBoard(board, x, y, sta);

        if (strcmp(cmd,"gz")==0) genZom(board, x, y, sta);

        if (strcmp(cmd,"sw")==0)    //sw the data in any grid specified
        {
            int a, b;   //coordinate
            scanf("%d%d",&a,&b);
            {
                int lv = board[a][b].plant.level;   
                printf("Plant  ATK: %d, COST: %d, HP: %d ID: %d\n", 
                board[a][b].plant.atk[lv],board[a][b].plant.cost,board[a][b].plant.hp[lv],board[a][b].plant.id);
                printf("Zom  ATK: %d, HP: %d ID: %d\n", 
                board[a][b].zombie.atk,board[a][b].zombie.hp,board[a][b].zombie.id);
            }
        }
     
        if (strcmp(cmd, "sp") == 0)
        {
            print_shop(sta);
        }

        if (!strcmp(cmd, "st")) //show rounds survived at the moment
        {
            int t;
            scanf("%d", &t);
            sta.time = t;
        }

        if (strcmp(cmd,"sc")==0)    //set cost (debug feature)
        {
            int cst;
            scanf("%d",&cst);
            sta.cost = cst;
        }

        if (!strcmp(cmd, "ps"))
        {
            printStatistic(&sta);
        }

        if (strcmp(cmd,"n")==0) 
        {
            if (nextFrame(board, &sta, x, y))   //if an enemy reaches a leftmost grid
            {
                std::cout <<
                    "          _______  _______  __   __  _______  ___   _______                      \n"
                    "         |       ||       ||  |_|  ||  _    ||   | |       |                     \n"
                    "         |____   ||   _   ||       || |_|   ||   | |    ___|                     \n"
                    "          ____|  ||  | |  ||       ||       ||   | |   |___                      \n"
                    "         | ______||  |_|  ||       ||  _   | |   | |    ___|                     \n"
                    "         | |_____ |       || ||_|| || |_|   ||   | |   |___                      \n"
                    "         |_______||_______||_|   |_||_______||___| |_______|                     \n"
                    "                        _______  _______  _______                       \n"
                    "                       |   _   ||       ||       |                      \n"
                    "                       |  |_|  ||_     _||    ___|                      \n"
                    "                       |       |  |   |  |   |___                       \n"
                    "                       |       |  |   |  |    ___|                      \n"
                    "                       |   _   |  |   |  |   |___                       \n"
                    "                       |__| |__|  |___|  |_______|                       \n"
                    " __   __  _______  __   __  ______      _______  ______    _______  ___   __    _ \n"
                    "|  | |  ||       ||  | |  ||    _ |    |  _    ||    _ |  |   _   ||   | |  |  | |\n"
                    "|  |_|  ||   _   ||  | |  ||   | ||    | |_|   ||   | ||  |  |_|  ||   | |   |_| |\n"
                    "|       ||  | |  ||  |_|  ||   |_||_   |       ||   |_||_ |       ||   | |       |\n"
                    "|_     _||  |_|  ||       ||    __  |  |  _   | |    __  ||       ||   | |  _    |\n"
                    "  |   |  |       ||       ||   |  | |  | |_|   ||   |  | ||   _   ||   | | | |   |\n"
                    "  |___|  |_______||_______||___|  |_|  |_______||___|  |_||__| |__||___| |_|  |__|\n"
                    "                               __   __   __                             \n"
                    "                              |  | |  | |  |                            \n"
                    "                              |  | |  | |  |                            \n"
                    "                              |  | |  | |  |                            \n"
                    "                              |__| |__| |__|                            \n"
                    "                               __   __   __                             \n"
                    "                              |__| |__| |__|                            \n";
                std::cout << "Game Ends" << std::endl;
                printStatistic(&sta);
                writeStatistic(&sta);
                return;
            }
            genZom(board, x, y, sta);   //generate enemies
            printAll(board, x, y, sta);
        }

        if ( ! strcmp(cmd, "s"))    //save current status 
        {
            std::string name;
            std::cin >> name;
            save(board, &sta, x, y, name);  //name is the file name
        }

        if ( ! strcmp(cmd, "lo"))   //load from file input
        {
            preparation.clear();
            count_preparation.clear();  
            for (int i = -1; ++i < x; )     //free memories
            {
                delete[] (board[i]);
            }
            delete[] (board);
            std::string name;
            std::cin >> name;
            board = load(name, &x, &y, &sta);
        }

        printAll(board, x, y, sta);


    }

    for (int i = -1; ++i < x; )
    {
        delete[] (board[i]);
    }
    delete[] (board);
}

