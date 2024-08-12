#include "LevelScoresState.h"
#include <conio.h>

LevelScoresState::LevelScoresState(StateMachineExampleGame* pOwner,const char* levelName)
    : m_pOwner(pOwner)
    , m_levelName(levelName)
    , m_currentPage(0)
    , m_pageSize(3)
{
}

void LevelScoresState::Enter()
{
    bool loadSuccessful = LoadScores();

    if (!loadSuccessful)
        m_pOwner->Quit();
    
    // this shouldn't happen
    if(m_scores.empty())
        m_pOwner->Quit("No scores found for the selectd level");

    // sort scores from top-ranking to lowest
    std::sort(m_scores.begin(), m_scores.end());

}

bool LevelScoresState::Update(bool processInput)
{
    Input userInput = AskForInput();
    return false;
}

void LevelScoresState::Draw()
{
    for (int i = 0; i < m_scores.size(); i++)// auto& const score : m_scores)
    {
        std::cout << "Rank " << (i + 1) << ": " << std::endl << std::endl;
        std::cout << m_scores[i];
    }
    /*
    * for (auto const& dir_entry : std::filesystem::directory_iterator{sandbox})
    {
        if (dir_entry.is_directory())
        {
            std::string levelName = dir_entry.path().filename().string();
            m_savedGames.Add(
                Option(
                    levelName,
                    new LoadLevelScoresEvent(levelName.c_str())
                )
            );
        }

    }
    */
}

void LevelScoresState::Exit()
{
}

bool LevelScoresState::LoadScores()
{
    if (m_levelName == nullptr)
    {
        system("cls");
        std::cout << "[Scores] Level name not set!" << std::endl;

        return false;
    }

    std::string fileName = "../levels/" + std::string(m_levelName) + "/leaderboard.txt";

    std::ifstream file;
    file.open(fileName);

    // TODO: also here, use static string
    std::string separator = ";";

    if (!file)
    {
        std::cout << "Opening file failed!" << std::endl;
        return false;
    }
    else
    {
        std::string line;
        ScoreData scoreData = ScoreData();

        while (std::getline(file, line))
        {
            scoreData.ParseSetVal(line);

            if (line == separator)
            {
                m_scores.push_back(scoreData);
                scoreData = ScoreData();
            }
        }

        // a yield-like return would be awesome
        file.close();
    }

    return true;
}

Input LevelScoresState::AskForInput()
{
    int intInput = _getch();
    Input input = Input::NONE;

    //check if an arrow key was pressed
    if (intInput == (int)Input::ARROW_IN)
    {
        //read actual arrow value
        int arrowInput = _getch();

        switch (arrowInput)
        {
        case (int)Input::ARROW_DOWN:
        case (int)Input::ARROW_RIGHT:
            input = Input::ARROW_DOWN;
            break;
        case (int)Input::ARROW_UP:
        case (int)Input::ARROW_LEFT:
            input = Input::ARROW_UP;
            break;
        case (int)Input::LIST_END:
            input = Input::LIST_END;
        default:
            break;
        }
    }
    else if (intInput == (int)Input::ENTER)
    {
        input = Input::ENTER;
    }

    return input;
}

std::string LevelScoresState::ScoreData::Print()
{
    std::string res;
    res += "\tPlayer: " + m_playerName + "\n"
    + "\tSteps taken to reach the exit: " + std::to_string(m_stepsTaken) + "\n"
    + "\tLives left: " + std::to_string(m_livesLeft)  + "\n"
    + "\tMoney collected: " + std::to_string(m_money) + "\n"
    + "\tTotal score: " + std::to_string(CalculateTotalScore()) + "\n";

    return res;
}

void LevelScoresState::ScoreData::ParseSetVal(std::string str)
{
    size_t separatorPos = str.find('=');
    std::string key = str.substr(0, separatorPos);
    std::string value = str.substr(separatorPos + 1, str.size());

    //std::cout << "KEY: " << key << " VALUE: " << value << std::endl;
    //m_data[key] = value;
    //m_data.insert(Stats::value_type(key, value));

    // TODO: use public static const somewhere! to check key name
    if (key == "enemies_killed")
        m_enemiesKilled = stoi(value);
    else if (key == "money")
        m_money = stoi(value);
    else if (key == "money")
        m_money = stoi(value);
    else if (key == "lives_left")
        m_livesLeft = stoi(value);
    else if (key == "name")
        m_playerName = value;
    else if (key == "steps")
        m_stepsTaken = stoi(value);

    return;
}

const int LevelScoresState::ScoreData::CalculateTotalScore()
{
    return m_money + m_enemiesKilled - (m_stepsTaken * 0.9);
}
