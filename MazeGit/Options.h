#pragma once
#include <vector>
#include <string>
#include "EventManager.h"

class Options
{
public:

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
            if (m_pEvent != nullptr)
                EventManager::GetInstance()->Add(m_pEvent);
        };
        //void Deselect() { m_isSelected = false; };

        //bool IsSelected() { return m_isSelected == true; }

        // overloads
        friend std::ostream& operator<<(std::ostream& os, const MenuOption& menuOption) { return os << menuOption.m_Title; }
    private:
        std::string m_Title;
        //bool m_isSelected;
        Event* m_pEvent;
    };

    Options();
    Options(std::vector<MenuOption> options);
    void Update();
    void Draw();
    void Add(MenuOption menuOption) { m_options.push_back(menuOption); }
private:
    std::vector<MenuOption> m_options;
    short int m_selectedIndex;

    Input GetUserInput();
};

