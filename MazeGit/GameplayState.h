#pragma once

#include "GameState.h"
#include "Player.h"
#include "Level.h"
#include "StateMachineExampleGame.h"
#include "Options.h"

class GameplayState :
    public GameState
{


public:
    GameplayState(StateMachineExampleGame* pOwner);
    
    virtual void Enter() override;
    virtual void Exit() override;
    virtual bool Update(bool processInput = true) override;

    // Inherited via GameState
    virtual void Draw() override;

private:
    StateMachineExampleGame* m_pOwner;

    Options m_levels;

    Player* m_pPlayer;
    Level m_level;

    bool m_beatGame;

    void ChooseLevel();
    bool Load();
    bool Resume();
    bool HandleCollision(int newPlayerPosX, int newPlayerPosY);
    const void ShowLegend();

};

