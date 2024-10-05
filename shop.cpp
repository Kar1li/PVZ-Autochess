#include "structDec.h"

plt plts_in_shop[scale];
std::unordered_map<plt, int> count_preparation;
std::vector<plt> preparation;
bool sold[scale];

//return a upgraded plant
void level_up(plt *plant) {   
    if (plant) 
    {
        plant->level++;
    }
}

//check upgrade and update new plants from shop to preparation

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
void initialize_shop()
{
     int plts_in_shop_id[scale];
    for (int i = 0; i < scale; ++i)
    {
        sold[i] = 0;
        plts_in_shop_id[i] = rand() % (sizeof(Plants) / sizeof(plt));
        plts_in_shop[i] = Plants[plts_in_shop_id[i]];
    }
}

//refresh shop
void refresh_shop(sts *sta)
{
    if (sta->cost < 2)
    {
        std::cout << "Your gold is not enough \n";
        return;
    }
    sta->cost -= 2;//spend 2 to refresh
    initialize_shop();//call initialize_shop to refresh

    sta->statistic["Times of Refreshing: "]++;
}

//buy plants from shop
int buy(sts *sta)
{
    int num;
    std::cout << "Input the index in shop:  ";
    std::cin >> num;
    if (num < 0 || num >= scale || sold[num])
    {
        std::cout << "Invalid input \n";
        return 1;
    }
    if (sta->cost < plts_in_shop[num].cost)
    {
        std::cout << "Your gold is not enough \n";
        return 1;
    }
    sta->cost -= plts_in_shop[num].cost;
    sold[num] = 1;
    update(plts_in_shop[num]);//update bought plant in preparation

    std::string message = plts_in_shop[num].name[0] + " bought: ";

    sta->statistic[message]++;

    return 0;
}

