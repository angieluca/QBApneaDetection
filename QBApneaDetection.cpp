#include <iostream> 
#include <vector> 
#include <unordered_map>
using namespace std;


int main() 
{ 
    /**
     * 0 = quiet breath; 1 = sigh; 2 = sniff; 3 = apnea; 4 = hypopnea
     * Should find Type I: 2, Type II: 1, Type III: 2
     * Type 1 Apnea = sigh 5 or less breath cycles before apnea; Type 2 Apnea = sigh immediately before apnea; Type 3 Apnea: spontaneous and in quiet breathing section
     * vector<int> breaths: vector representing a segment of diffrent breath types
     * unordered_map<int, int> apneaMap: stores <apnea index, apnea type>; default apnea type is type 3
     */

    std::vector<int> breaths= {0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3}; 
    unordered_map<int, int> apneaMap; 
    int type1 = 0, type2 = 0, type3 = 0; 
    
    //Traverse entire list to find apneas O(n)
    for (int i = 0; i < breaths.size(); i++){ if (breaths[i] == 3) apneaMap[i] = 3;} //add apnea index with default type 3

    //Traverse through found apneas to classify them
    for (auto apneaPair : apneaMap)
    {
        int apneaIndex = apneaPair.first; //Remember apneaPair.first = apnea index; apneaPair.second = apnea type
        
        //Check for type 2 apnea first (sigh immediately before apnea)
        if (breaths[apneaIndex - 1] == 1) //found sigh
        {
            type2++;
            apneaMap[apneaIndex] = 2; //change apnea type to type 2
            continue; //classify the next apnea
        }

        //If not type 2, then determine if type 1 or type 3
        for (int j = apneaIndex - 2; j >= 0 && j > apneaIndex - 6; j--)
        {  
            if (breaths[j] == 1) 
            { 
                type1++; 
                apneaMap[apneaIndex] = 1;
                continue; 
            } 
        } 
        //If not changed to type 2 nor type 1, then remains as default type 3
        type3 = apneaMap.size() - type1 - type2;
    }
  
    std::cout << "The number of Type 1: " << type1 << std::endl; 
    std::cout << "The number of Type 2: " << type2 << std::endl; 
    std::cout << "The number of Type 3: " << type3 << std::endl; 

    return 0; 

} 