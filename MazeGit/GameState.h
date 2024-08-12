#pragma once
class GameState
{
private:
	//std::vector<MenuOption> m_menuOptions;
public:
	virtual ~GameState() = default;

	virtual void Enter() {};
	virtual bool Update(bool processInput = true) { return false; }
	virtual void Draw() = 0;
	virtual void Exit() {};
	/*
	virtual void DisplayOptions()
	{
		for (int i = 0; i < m_MenuOptions.size(); i++)
		{
			if (m_SelectedIndex == i)
				std::cout << "-> ";
			std::cout << m_menuOptions[i] << std::endl;
		}
	}
	*/
};