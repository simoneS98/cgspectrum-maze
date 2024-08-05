#pragma once
#include "GameState.h"
#include "Player.h"
#include "Level.h"
#include "StateMachineExampleGame.h";
#include "Event.h"
#include "EventManager.h"
#include "ExitGameEvent.h"
#include "StartGameEvent.h"

class MenuOption
{
public:
    MenuOption(std::string title, Event* pEvent)
        : m_Title(title)
        , m_pEvent(pEvent)
    {
    }

    //void Select() { m_isSelected = true; };
    void Select() {
        if(m_pEvent != nullptr)
            EventManager::GetInstance()->Add(m_pEvent);
    };
    //void Deselect() { m_isSelected = false; };

    //bool IsSelected() { return m_isSelected == true; }

    friend std::ostream& operator<<(std::ostream& os, const MenuOption& menuOption);
private:
    std::string m_Title;
    //bool m_isSelected;
    Event* m_pEvent;
};


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

    std::vector<MenuOption> m_MenuOptions;
    short int m_SelectedIndex = 0;
    
    bool m_beatGame;

    bool Load();
    
    void DisplayOptions();
    Input GetUserInput();

};


