#pragma once
#include <string>
#include "Level.h"
#include <fstream>
#include <iostream>
#include "RoomFactory.h"

class FileUtils
{
public:
    static Level FileToLevel(std::string filename);
};