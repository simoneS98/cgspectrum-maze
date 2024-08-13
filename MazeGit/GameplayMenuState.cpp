#include "GameplayMenuState.h"
#include <filesystem>
#include "Options.h"
#include "LevelChosenEvent.h"
#include "InputSystem.h"

using Option = Options::MenuOption;

GameplayMenuState::GameplayMenuState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{
}

void GameplayMenuState::Enter()
{
    // todo: use function to get list of levels
    const std::filesystem::path levelsPath{ "../levels" };
    for (auto const& dir_entry : std::filesystem::directory_iterator{ levelsPath })
    {
        if (dir_entry.is_directory())
        {
            std::string levelName = dir_entry.path().filename().string();
            m_levels.Add(
                Option(
                    levelName,
                    new LevelChosenEvent(levelName)
                )
            );
        }
    }

    Draw();
}

void GameplayMenuState::Draw()
{
    system("cls");
    std::cout << "Choose one of the following levels: " << std::endl << std::endl;
    m_levels.Draw();
}

bool GameplayMenuState::Update(bool processInput)
{
    m_levels.Update();
    return false;
}
