#pragma once
#include "Character.h"

class Player : Character{

public:
    int numKeys;
    // Constructors
    Player();

    // Getters
    int GetXPos();
    int GetYPos();
    //bool HasKey { numKeys > 0 };
    int GetNumKeys();
    int GetMaxHp();
    int GetCurrentHp();

    // Setters
    void SetPos(int x, int y);
    void SetXPos(int x);
    void SetYPos(int y);
    
    // Generic
    void TakeDamage(int amount);
    //TODO: pickup <T>
    void PickupKey();
    bool UseKey();

private:

    //Member variables

    void Die();
};