#pragma once
#include "GameStateMachine.h"
#include <string>

class Game;
class GameStates;
class Player;

class StateMachineExampleGame :
    public GameStateMachine
{
public:
    enum class SceneName
    {
        NONE,
        MAIN_MENU,
        SCORE_MENU,
        SCORE_LEVEL_DETAIL,
        GAMEPLAY
    };

private:
    StateMachineExampleGame();
    static StateMachineExampleGame* instance;
    Game* m_pOwner;
    GameState* m_pCurrentState;
    GameState* m_pNextState;

    void LoadScene(SceneName scene);
    void LoadScene(SceneName scene, const char* levelName);

public:
    
    static StateMachineExampleGame* GetInstance() { 
        if (instance == nullptr)
            instance = new StateMachineExampleGame();
        return instance; 
    }
    // Inherited via GameStateMachine
    virtual bool Init(Game* pOwner) override;

    virtual bool UpdateCurrentState(bool processInput = true) override;

    virtual bool DrawCurrentState() override;

    virtual void ChangeState(GameState* pNextState) override;

    virtual bool Cleanup() override;

    bool LoadGame(Player*& pPlayer);

    void ChangeRoom(std::string roomName, std::string levelName);

    void StartNewGame();

    void PauseGame();

    void EndGame();

    void ShowScores(const char* levelName = nullptr);

    void Quit(std::string message = "");
};

