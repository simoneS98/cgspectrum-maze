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
    Player(Room *pRoom);
    ~Player();

    bool HasKey();
    bool HasKey(Color color);

    void DropKey();

    void AddMoney(int money) { this->money += money; }
    int GetMoney() { return money; }
    int GetLives() { return lives; }
    void DecrementLives() { lives--; }

    #ifdef GODMODE
    void TakeDamage(int amount) override
    {
        return Character::TakeDamage(0);
    }
    #endif

    void BlockKeyDrop() { canDropKey = false; }
    void RestoreKeyDrop() { canDropKey = true; }
    // Generic
    
    //TODO: pickup <T>

    void DisplayInfo();

    virtual void Draw() override;

    virtual void Die() override;

    virtual Point Update() override;

    virtual bool CollideWith(GameEntity* collidedEntity) override;

    virtual bool TryUseKeyOn(GameEntity* lockedEntity) override;

    virtual void PickupMoney(GameEntity* lockedEntity) override;

private:
    int money;
    int lives;
    bool canDropKey;
    Point GetInput();

    void UseKey();

};