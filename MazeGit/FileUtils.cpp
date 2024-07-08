#include "FileUtils.h"

Level* FileUtils::FileToLevel(std::string filename)
{
    int width = 0;
    int height = 0;
    Room** map = nullptr;

    std::ifstream levelFile;

    filename.insert(0, "../");

    levelFile.open(filename);

    if (!levelFile)
    {
        std::cout << "Opening file failed!" << std::endl;
    }
    else
    {
        if (levelFile.is_open())
        {
            std::string line;
            
            getline(levelFile, line);
            
            width = stoi(line);

            getline(levelFile, line);
              
            height = stoi(line);
               
            getline(levelFile, line);

            //TODO: fix file parsing
            int size = width * height + 1;

            // declaring character array (+1 for null terminator) 
            char* mapAsCharArray = new char[size];
            map = new Room*[size];
           
            // copying the contents of the 
            // string to char array
            strcpy_s(mapAsCharArray, size, line.c_str());

            for (int i = 0; i < size; i++)
            {
                    map[i] = RoomFactory::make(RoomType(mapAsCharArray[i]));
            }

            delete[] mapAsCharArray;
            mapAsCharArray = nullptr;

            levelFile.close();
        }

        levelFile.close();
    }

    if (map == nullptr)
        exit(1);

    Level* level = new Level(map, width, height);

    return level;
}

