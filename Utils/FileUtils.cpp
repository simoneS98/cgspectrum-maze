#include "FileUtils.h"
#include "FileUtils.h

void FileUtils::FileToLevel(std::string filename)
{
    //Level* level = new Level;
    Level level = Level{};

    ifstream levelFile;

    filename.insert(0, "../");

    levelFile.open(filename);

    if (!levelFile)
    {
        cout << "Opening file failed!" << endl;
    }
    else
    {
        if (levelFile.is_open())
        {
            string line;
            int c = 0; //TODO: use names
            while (getline(levelFile, line))
            {
                if (c == cParseWidthLine)
                {

                    level.width = stoi(line);
                }
                else if (c == cParseHeightLine)
                {
                    level.height = stoi(line);
                }
                else if (c == cParseLevelLine)
                {
                    // declaring character array (+1 for null terminator) 
                    char* mapAsCharArray = new char[level.width * level.height + 1];
                    // copying the contents of the 
                    // string to char array 
                    strcpy_s(mapAsCharArray, level.width * level.height + 1, line.c_str());
                    level.map = mapAsCharArray;
                }

                c++;
            }
            levelFile.close();
        }

        levelFile.close();
    }
    return level;
}
