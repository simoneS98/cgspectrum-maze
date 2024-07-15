#pragma once
#include "Character.h"
#include "Key.h"

// forward class declaration, avoids recompile in case of changes
// can only be used with pointer types
// actually it's not working
//class Key;

constexpr char playerSprite = (char)Sprite::PLAYER;

class Player : public Character
{

public:
    // Constructors
    Player();
    ~Player();

    bool HasKey();
    bool HasKey(Color color);
    void PickupKey(Key* key);

    void UseKey();
    void DropKey();

    void AddMoney(int money) { this->money += money; }
    int GetMoney() { return money; }
    int GetLives() { return lives; }
    void DecrementLives() { lives--; }
    // Generic
    
    //TODO: pickup <T>

    virtual void Draw() override;

    virtual void Die() override;

private:
    Key* pCurrentKey;
    int money;
    int lives;

};