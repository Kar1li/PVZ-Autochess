#include "structDec.h"

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
void writeStatistic(sts * sta)
{
    std::ofstream ofs("statistics.txt", std::ios_base::app);
    if (ofs.is_open())
    {
        int l = sta->statistic.size();
        std::map<std::string, int>::iterator itr = sta->statistic.begin();
        std::map<std::string, int>::iterator end = sta->statistic.end();
        for (; itr != end; itr++ )
        {
            ofs << (*itr).first << (*itr).second << std::endl;
        }
        ofs.close();
    }
    else
    {
        std::cerr << "Error opening the file.\n";// Here we use fileIO
    }
}

