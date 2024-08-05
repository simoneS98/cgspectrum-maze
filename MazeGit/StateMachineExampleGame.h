#pragma once
#include "GameStateMachine.h"
class Game;
class GameStates;

class StateMachineExampleGame :
    public GameStateMachine
{
public:
    enum class SceneName
    {
        NONE,
        MAIN_MENU,
        GAMEPLAY
    };

private:
    Game* m_pOwner;
    GameState* m_pCurrentState;
    GameState* m_pNextState;

public:
    StateMachineExampleGame(Game* pOwner);

    // Inherited via GameStateMachine
    virtual bool Init() override;

    virtual bool UpdateCurrentState(bool processInput = true) override;

    virtual bool DrawCurrentState() override;

    virtual void ChangeState(GameState* pNextState) override;

    virtual bool Cleanup() override;

    void LoadScene(SceneName scene);

};

