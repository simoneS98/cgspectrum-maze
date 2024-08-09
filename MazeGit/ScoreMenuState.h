#pragma once
#include "GameState.h"
#include "StateMachineExampleGame.h"
#include <fstream>
#include <vector>
class ScoreMenuState :
    public GameState
{
public:
    ScoreMenuState(StateMachineExampleGame* pOwner);

    bool LoadScoresForLevel(std::string levelName);
    virtual void Enter() override;
    virtual void Exit() override;
    virtual bool Update(bool processInput = true) override;

    // Inherited via GameState
    virtual void Draw() override;

private:
    StateMachineExampleGame* m_pOwner;

    std::string ReadFile(const std::string& fileName)
    {
        std::ifstream ifs(fileName.c_str(), std::ios::in | std::ios::binary | std::ios::ate);

        std::ifstream::pos_type fileSize = ifs.tellg();
        ifs.seekg(0, std::ios::beg);

        std::vector<char> bytes(fileSize);
        ifs.read(bytes.data(), fileSize);

        return std::string(bytes.data(), fileSize);
    }
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
