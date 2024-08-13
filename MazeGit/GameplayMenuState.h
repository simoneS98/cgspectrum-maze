#pragma once
#include "GameState.h"
#include "StateMachineExampleGame.h"
#include "Options.h"
class GameplayMenuState :
    public GameState
{
public:
    GameplayMenuState(StateMachineExampleGame* pOwner);
    // Inherited via GameState
    virtual void Enter() override;
    virtual void Draw() override;
    virtual bool Update(bool processInput = true) override;
private:
    StateMachineExampleGame* m_pOwner;

    Options m_levels;
};

