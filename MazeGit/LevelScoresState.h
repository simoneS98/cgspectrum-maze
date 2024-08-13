#pragma once
#include "GameState.h"
#include "ScoreMenuState.h"
#include <map>
#include <any>
class LevelScoresState :
    public GameState
{
	class ScoreData
	{
	// everything is a string, it just needs to be printed
	// i read it directly from file without casts
	typedef std::map<std::string, std::any> Stats;
	private:
		// actually I'm not using map
		// it's easier to process values with predefined types
		// and also I need to specify key names to calculate score
		Stats m_data;
		int m_totalScore;
		
		std::string m_playerName;
		int m_stepsTaken;
		int m_enemiesKilled;
		int m_livesLeft;
		int m_money;
		
		std::string Print();
	public:
		void ParseSetVal(std::string str);
		void PrintData()
		{
		};
		const int CalculateTotalScore();

		friend std::ostream& operator<<(std::ostream& os, ScoreData& scoreData)
		{
			return os << scoreData.Print();
		}

		// Overloading < operator 
		// used for comparisons
		friend bool operator<( ScoreData& l,  ScoreData& r)
		{
			return l.CalculateTotalScore() > r.CalculateTotalScore();
		}
	};

private:
	StateMachineExampleGame* m_pOwner;
	const char* m_levelName;
	short int m_pageSize;
	short int m_currentPage;
	std::vector<ScoreData> m_scores;

	bool LoadScores();
	void ShowLegend();
	Input GetInput();
	//bool Sort(ScoreData i, ScoreData j) { return (i.CalculateTotalScore() < j.CalculateTotalScore()); }
public:
	LevelScoresState(StateMachineExampleGame* pOwner, const char* levelName);
	virtual void Enter() override;
	virtual bool Update(bool processInput = true) override;
	virtual void Draw() override;
	virtual void Exit() override;
};

