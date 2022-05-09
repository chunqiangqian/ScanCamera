#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <string.h>
#include "scan.h"
#include <vector>


int main()
{
    std::vector<std::string> camCards;
    std::vector<std::string> camPaths;

    ScanCameras(camCards, camPaths);

    std::cout << "-------------------" << '\n';

    for (int i = 0; i < camCards.size(); i++)
    {
        std::cout << "camCard: " << camCards[i] << '\n';
        std::cout << "camPath: " << camPaths[i] << '\n';
    }
    

    
    

    return 0;
}