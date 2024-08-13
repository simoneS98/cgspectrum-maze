#pragma once
#include "GameState.h"
#include "StateMachineExampleGame.h"
#include <fstream>
#include <vector>
#include <filesystem>
#include "MainMenuState.h"

class ScoreMenuState :
    public GameState
{
public:
    ScoreMenuState(StateMachineExampleGame* pOwner);
    virtual void Enter() override;
    virtual void Exit() override;
    virtual bool Update(bool processInput = true) override;

    // Inherited via GameState
    virtual void Draw() override;
    //void Quit();

private:
    StateMachineExampleGame* m_pOwner;
    Options m_savedGames;
};

class Score
{
public:
    Score(std::string playerName, int stepsTaken, int enemiesKilled, int livesLeft, int money)
        : m_playerName(playerName)
        , m_stepsTaken(stepsTaken)
        , m_enemiesKilled(enemiesKilled)
        , m_livesLeft(livesLeft)
        , m_money(money)
    {
    }
private:
    // TODO: create variable 'totalScore' for sorting
    std::string m_playerName;
    int m_stepsTaken;
    int m_enemiesKilled;
    int m_livesLeft;
    int m_money;

};
