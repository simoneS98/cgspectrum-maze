#pragma once

struct Cursor {
    int x = 0;
    int y = 0;
};

struct Level {
    int width = 0;
    int height = 0;
    char* map = nullptr;
};


//TODO: create interactableObject with method interact()