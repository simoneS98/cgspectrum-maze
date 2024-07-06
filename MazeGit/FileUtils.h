#pragma once
#include <string>
#include "Level.h"
#include <fstream>
#include <iostream>
#include "Constants.h"
#include "RoomFactory.h"

class FileUtils
{
public:
    static Level* FileToLevel(std::string filename);
};