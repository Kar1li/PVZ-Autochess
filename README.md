
Welcome to PVZ AUTO CHESS!

Having a same background of classic game Plant Vs. Zombie, our duty in this game is to defend our home against the zombies coming from the right hand side.
Game will over when one zombie gets into the leftest line and eats our brain!!!
It is an endless mode and the goal is to survive for the longest time you can!

Innovatively, the use of plants is combined with auto chess , where three same plants in the preparation state will be upgraded to become more powerful.
Moreover, try to make full use of different terrains to defend the zombies!

	ALMANAC:
	Plants:
		Shooter     	(>)
		Sunflower   	(*)
		Wallnut     	(])
		Boom        	(!)
		Sporeshroom 	(=)
	 Zombies:
	 	Normal Zombie	🧟
		Vampire		🧛
		Ghost		👻
		Monster		👹
	Terrains:
		Poison		☠
	 	Med		💊
	  	Highplace	🗻
	   	Water		🌊

BEGIN:
At the beginning of the game, "Start a new game or load? " was on the screen
We need to type in 
"load" 
and then 
the name of file 
to read a saved game
Or
any other word such as
"start"
to start a new game

START A NEW GAME OF 5*9:
Let's do it from the very beginning and start a new game
"Set up the board with two integers representing vertical and horizontal sizes respectively:"
We are asked to put in the x and y for the board.For example, let's put

	5 9

Although you can choose any size you want, it is still recommended that the horizontal size should not exceed 10 lest the display would be messy.

BUY AND DEPLOY/UNDEPLOY:
Buy:
Now we are in shop to buy plants to put them in preparation

	Shop:
	*   !   >    !    =
	15  5  10    5    20
	
	Cost: 50
	
	Preparation:(now empty)


If you want to buy a plant, we need to type in
"b"
and then it will ask you for the index of which plant you want to buy "Input the index in shop:  "
Please note that the index begins from 0! Let's put
"0"

	b 0
 _________________________
	
	Shop:
	*   !   >     !    =
	15  5   10    5    20
	
	Cost: 35
	
	Preparation:
	*

You bought one sunflower successfully!
and you can defend the zombies by deploying these plants you bought in shop!

Deploy:
For example, if you want to deploy the sunflower (index in preparation is 0) we bought just now in block (1,4)
the origin look of (1,4) is :

	"14      "

You can deploy the sunflower by typing

	dp

it will ask you for more imformation 

	"Deploy:    "
then we put in 

	140
(no space is required if both vertical and horizontal sizes <= 10 or you will have to put spaces between the three numbers)
which means deploy on (1, 4) with the plant with index "0" in preparation

then the (1, 4) will be like:

	"14  *   "

and the Preparation will be empty again (We only bought one plant just now)
Excellent! You planted it successfully!

Undeploy:
Similarly, you can undeploy the plant you do not like by typing

	ud

it will ask you for more imformation 

	"Undeploy:    "
then we put in

	14
(space required)
which means undeploy the plant on (1, 4)
then the look of (1,4) is :

	"14      "
Well done! You undeployed it successfully!

	
 TERRAINS:
 
	At the beginning of game, the board will generate 4 types of terrains in every block with 30% chance each
	1. Poison(☠)      : Plants and zombie on it will get damage
	2. Med   (💊)     : Plants and zombie on it will get heal (with boundary)
	3. Highplace(🗻)  : It will block zombies and make them change the line (go up or down randomly)
	4. Water  (🌊)    : It will give zombies "Frozen" effect to disrupt their moving
	
	
UPGRADING:
	
	If we put three same plants in our Preparation, the three will upgrade into a more powerful one! 
	Each type of plant will have 3 levels
	
	1.Shooter (">")
	Level 1: Attack one zombie on the line
	Level 2: Attack each one zombie on each of three lines (up and down)
	Level 3: Attack all zombie on each of three lines (up and down)
	
	2.Sunflower (*)
	Level 1: Generate some costs
	Level 2: Generate more costs
	Level 2: Generate much more costs and purify the poison terrain of this block into air
	
	3.Wallnut (])
	Level 1: Have high hp
	Level 2: Have higher hp
	Level 3: Have much higher hp that make it comes to an indestructible defensive line.
	
	4.Boom (!)
	Level 1: Give great damage to the zombie step on it
	Level 2: Give great damage to the zombies in boom-centered cross
	Level 3: Give great damage to ALL zombies on the board and destory all highplace terrains
	
	5.Sporeshroom (=)
	Level 1：Attack one zombie(near) on the line and give it "Frozen" affect
	Level 2：Attack one zombie(far)  on the line and give it "Frozen" affect
	Level 3：Attack All zombies on the line and give them "Frozen" affect

 Saving and loading:

When you play the game for a while but want to pause and return later, for example, you are here:

 	Shop:
	]       ]       =       !       ]
	15      15      20      5       15
	
	Cost: 28
	
	Preparation:
	
	
	
	00              01              02   ☠          03              04   💊         05              06              07              08
	
	10              11              12              13   💊         14              15              16              17   💊         18
	
	20              21   💊         22   🌊         23   ☠          24              25              26              27              28
	
	30              31   🗻         32              33              34              35              36              37              38
	
	40  *           41  *🗻         42   🌊         43   ☠          44              45              46   ☠          47   🗻         48
	
	50              51              52              53   ☠          54   🗻         55   ☠          56              57   ☠          58

 and want to save the game.

Use "s filename":

 	s juststarted

The next time you start the game, when asked whether to load, input "load filename"

	load juststarted

or you can also load previously saved games even when you are in the middle of a game.

Use "lo filename":

 	lo juststarted

Both commands retrieve exactily the same game status.
	

________________________________________________________________________________________________________________________________________________
A list of features that you have implemented and explain how each coding element 1 to 5 listed under the coding requirements aforementioned support our features:

1.Generation of random game sets or events:


		game.cpp
  
		void genbuffTrn(grid** brd, int x, int y, sts * sta){
		    for (int i=0;i<x;i++){
		        for (int j=0;j<y;j++)   //iterate the whole board{
		            if (brd[i][j].terrain.id == -1 )    //if not air{
		                int den = rand()%10;    //denominator of probability
		                if (den<=2) //numerator{
		                    trn tt = T[rand()%4+1]; //one random terrain
		                    brd[i][j].terrain = tt; //generate to grid
		                    std::string message = tt.name + " generated: "; //record statistics
		                    sta->statistic[message]++;}}}}}

Before the start of the game, a random terrain is generated with a 30% probability on every grid. Two for loops are used to iterate the whole board. For each grid that is iterated, its terrain is checked whether this is air. If it is, we first generate a random number ranging from 0 to 9. If the number generated falls in the range of 0 to 2, it is considered valid. A random number representing the ID of a terrain is then generated and used as the index to retrieve the corresponding terrain from their array to deploy it to the grid. 

		game.cpp
  
		void genZom(grid ** brd, int x, int y, sts sta){
		    int t = sta.time;   //rounds survived
		    for (int i = -1; ++ i < x; ){
		        int prob = rand() % (20+t); //denominator of the probability
		        if (prob <= t)  //numerator{
		            int _ = rand() % 4; //one random enemy unit
		            brd[i][y-1].zombie = Zombies[_];}}}

After every frame ends, enemies would be generated on the rightmost column. This is implemented in a similar way to terrain generation. The probability of a random enemy generated is time-varying. p(t) = t / ( 20 + t ) serves as the difficulty curve of the game.

		shop.cpp
  
		void initialize_shop(){
		     int plts_in_shop_id[scale];
		    for (int i = 0; i < scale; ++i){
		        sold[i] = 0;
		        plts_in_shop_id[i] = rand() % (sizeof(Plants) / sizeof(plt));
		        plts_in_shop[i] = Plants[plts_in_shop_id[i]];}}
 The combination of items in the shop is also randomly generated.


_________________________________________________________________________________________________________________________________________

	

2.Data structures for storing game status:

		structDec.h
  
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

Data of a unit are organised in structs. As part of the level-up system of allies, some members are arrays of three items with each storing the parameter of its corresponding level. For example, hp[0] is the hp of a level-0 ally. And the operator== is overloaded to check the identity of allies. If two plants have the same id and level, they are considered the same.

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

 The grid struct contains all three basic units of the game. It is a struct of structs and the "space" of the gameplay. The board is the group of grids. On them, plants are deployed, terrains are generated, enemies walk.
	
	struct Status{
	    int cost;//availible cost
	    int score;
	    int time;
	    std::map<std::string, int> statistic;
     	    //statistic game data
     };

	typedef struct Status sts;

The struct Status records the status as the name suggests. A map is nested to record statistics. Cost is for purchasing plants. Time is for recording rounds survived and to change the probability of zombies generated.

 ________________________________________________________________________________________________________________________________________________
3.Dynamic memory management:

		game.cpp
  
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

 At the very beginning of a game, the player is asked to cumtomise their own board. Any sizes are allowed, since the dynamic array is adopted.
 The board is a pointer of x pointers that represent the vertical axis indexes of all grids and that store y horizontal grids severally. They are initialised with "air"s.

 		shop.cpp

		void update(plt newplant)   
		{  
		    if (count_preparation.count(newplant))  
		        count_preparation[newplant]++;  
		    else   
		    {  
		        count_preparation[newplant] = 1;
		        preparation.push_back(newplant);
		        return;  
		    }
		    //update the amount of newplant in count_preparation
		    if (count_preparation[newplant] == 3 && newplant.level < 2) //if has three same plant and not level max  
		    {  
		        count_preparation[newplant] = 0; 
		        for(auto it = preparation.begin(); it != preparation.end();)  
		        {  
		            if (it->id == newplant.id && it->level == newplant.level)   
		            {  
		                it = preparation.erase(it);
		            }   
		            else   
		            {  
		                ++it;  
		            }  
		        }  //delete this plant in preparation
		        level_up(&newplant); //upgrade this plant
		        update(newplant); //update the upgraded plant in preparation and count_preparation
		    }   
		    else   
		    {  
		        preparation.push_back(newplant); //push newplant in preparation if no need to upgrade it
		    }  
		}  
		
		//initialize the shop randomly  

 STL contains map and vector cooperate to implement the shop and level system. After a plant is bought, its count is incremented by 1. If its number reaches 3, the level-up mechanism is triggered. All of its kinds are removed and one of higher level is created. The recursive call is to deal with the case that the number of some plant reaches 3 as a result of a previous leveling-up.

 		Stat.cpp

		void printStatistic(sts * sta)
		{
		    std::cout << "Rounds survived: " << sta->time << std::endl; //There aren't different game levels.We use rounds survived to show your progress.
		    int l = sta->statistic.size();
		    std::map<std::string, int>::iterator itr = sta->statistic.begin();
		    std::map<std::string, int>::iterator end = sta->statistic.end();
		    for (; itr != end; itr++ )
		    {
		        std::cout << (*itr).first << (*itr).second << std::endl;
		    }
		}
		// we use maps and iterators here. (STL)
____________________________________________________________________
		AllyFunction.cpp
  
 	sta->statistic["Normal Damage: "] += brd[a][b].plant.atk[lv];

 Map is used to record statistics. We record some interesting data during gameplay and iterate through the map to print them out.
 A sample output is as follows.

	 > bought: 9
	Damage Taken: 4
	Med to Ally: 25
	Normal Damage: 84
	Poison to Ally: 40
	Poison to Enemy: 15
	Times of Fusion: 4
	Times of Refreshing: 7
	☠ generated: 2
	🌊 generated: 4
	💊 generated: 2
	🗻 generated: 2
____________________________________________________________________________________________________________________________________________________________
4. File input/output:

			fileIO.cpp
  
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


 Record the size, data in every grid and struct status to save the game. The function iterates through the whole board to write the data in every grid as well as the size and the status.

		fileIO.cpp
  
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

Loading is to retrieve the data inversely in a similar way to the save function.
________________________________________________________________________________________________________________________________________________

5. Program codes in multiple files:

		AllyData.cpp/ AllyFunction.cpp
		Enemy......
		Terrain......

Parameters and behaviour of units 

	shop.cpp
 	mech.cpp
  	game.cpp

Mechanism of game systems

	print.cpp
 	stat.cpp
  	fileIO.cpp

User interface system

	main.cpp

 Main

__________________________________________________________________________________________________________________________________________
A list of non-standard C/C++ libraries that are used in our work and integrated to our code repo. Please also indicate what features in our game are supported by these libraries.

All of these codes are written by ourselves

1.# "structDec.h" (Dynamic memory management)
Share the definition of struct of plants/zombies/terrains among files

2.# "shop.cpp" (Dynamic memory management)
Share the function of shop among files

3.# "AllyData.cpp" (Data structures for storing game status)
Share the data of plants among files

4.# "EnemyData.cpp"(Data structures for storing game status)
Share the data of zombies among files

5.# "TerrainData.cpp"(Data structures for storing game status)
Share the data of terrains among files

6.# "EnemyFunc.cpp"(Data structures for storing game status)
Share the function of zombies among files

7.# "AllyFunction.cpp"(Data structures for storing game status)
Share the function of plants among files

8.# "TerrFunc.cpp"(Data structures for storing game status)
Share the function of terrains among files

9.# "Stat.cpp" (Data structures for storing game status)
Show/write status in other files

10.# "mech.cpp" (Data structures for storing game status)
Share the function of clear and nextframe among files
__________________________________________________________________________________________________________________________________________
Compilation and execution instructions

In the directory including the makefile, use

	make test

 to make or start the game.


