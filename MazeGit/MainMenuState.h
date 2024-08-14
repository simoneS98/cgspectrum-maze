#pragma once
#include "GameState.h"
#include "Player.h"
#include "Level.h"
#include "StateMachineExampleGame.h"
#include "Event.h"
#include "EventManager.h"
#include "ExitGameEvent.h"
#include "StartGameEvent.h"
#include "ResumeGameEvent.h"
#include "ShowLeaderboardEvent.h"
#include "Options.h"

class MainMenuState :
    public GameState
{

public:
    MainMenuState(StateMachineExampleGame* pOwner);

    virtual void Enter() override;
    virtual void Exit() override;
    virtual bool Update(bool processInput = true) override;

    // Inherited via GameState
    virtual void Draw() override;

private:
    StateMachineExampleGame* m_pOwner;

    Options m_options;

    bool m_beatGame;

    bool Load();

};


