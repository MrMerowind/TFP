/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"

tfp::Mouse::Mouse()
    :LeftMouseButtonDown(false), RightMouseButtonDown(false), LeftMouseButtonDragStart({0.0f, 0.0f}), RightMouseButtonDragStart({0.0f,0.0f}),
    LeftMouseButtonDragDelta({0.0f, 0.0f}), RightMouseButtonDragDelta({0.0f, 0.0f}) {}

tfp::Mouse::~Mouse()
{
}

const sf::Vector2f &tfp::Mouse::GetMousePosition()
{
    Position.x = MouseData.getPosition(GameHandle->GameScreen.GetRenderWindowHandle()).x * GameHandle->GameScreen.GetViewSize().x / GameHandle->GameScreen.GetWindowSize().x;
    Position.y = MouseData.getPosition(GameHandle->GameScreen.GetRenderWindowHandle()).y * GameHandle->GameScreen.GetViewSize().y / GameHandle->GameScreen.GetWindowSize().y;
    return Position;
}

const sf::Vector2f tfp::Mouse::GetMousePositionScaled()
{
    Position.x = MouseData.getPosition(GameHandle->GameScreen.GetRenderWindowHandle()).x * GameHandle->GameScreen.GetOriginalViewSize().x / GameHandle->GameScreen.GetWindowSize().x;
    Position.y = MouseData.getPosition(GameHandle->GameScreen.GetRenderWindowHandle()).y * GameHandle->GameScreen.GetOriginalViewSize().y / GameHandle->GameScreen.GetWindowSize().y;
    return Position;
}

const sf::Vector2f tfp::Mouse::GetMousePositionOnMap()
{
    sf::Vector2f Return = GameHandle->GameCamera.GetPosition() + GetMousePosition();
    return Return;
}

void tfp::Mouse::SetGameHandle(tfp::Game *Handle)
{
    GameHandle = Handle;
}

sf::Mouse &tfp::Mouse::GetMouse()
{
    return MouseData;
}

const sf::Vector2f tfp::Mouse::GetLeftMouseButtonDeltaDrag() const
{
    return LeftMouseButtonDragDelta;
}

const sf::Vector2f tfp::Mouse::GetRightMouseButtonDeltaDrag() const
{
    return RightMouseButtonDragDelta;
}

const sf::Vector2f tfp::Mouse::GetLeftMouseButtonDeltaDragScaled()
{
    sf::Vector2f Return = LeftMouseButtonDragDelta;
    Return /= GameHandle->GameScreen.GetViewScale();
    return Return;
}

const sf::Vector2f tfp::Mouse::GetRightMouseButtonDeltaDragScaled()
{
    sf::Vector2f Return = RightMouseButtonDragDelta;
    Return /= GameHandle->GameScreen.GetViewScale();
    return Return;
}

void tfp::Mouse::LoadData()
{
    /// LPM
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && LeftMouseButtonDown == false) // Klikniecie lewym
    {
        LeftMouseButtonDown = true;
        LeftMouseButtonDragStart = Position;
    }
    else if(!sf::Mouse::isButtonPressed(sf::Mouse::Left) && LeftMouseButtonDown == true)  // Puszczenie
    {
        LeftMouseButtonDown = false;
        LeftMouseButtonDragDelta = LeftMouseButtonDragStart - Position;
    }
    else if(LeftMouseButtonDown == true) // Trzymanie
    {
        sf::Vector2f Tmp = Position;
        LeftMouseButtonDragDelta = LeftMouseButtonDragStart - Tmp;
        LeftMouseButtonDragStart = Tmp;
    }
    else // Nie trzymanie
    {
        LeftMouseButtonDragDelta = sf::Vector2f(0.0f, 0.0f);
    }
    /// PPM
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && RightMouseButtonDown == false) // Klikniecie prawym
    {
        RightMouseButtonDown = true;
        RightMouseButtonDragStart = Position;
    }
    else if(!sf::Mouse::isButtonPressed(sf::Mouse::Right) && RightMouseButtonDown == true)  // Puszczenie
    {
        RightMouseButtonDown = false;
        RightMouseButtonDragDelta = RightMouseButtonDragStart - Position;
    }
    else if(RightMouseButtonDown == true) // Trzymanie
    {
        sf::Vector2f Tmp = Position;
        RightMouseButtonDragDelta = RightMouseButtonDragStart - Tmp;
        RightMouseButtonDragStart = Tmp;
    }
    else // Nie trzymanie
    {
        RightMouseButtonDragDelta = sf::Vector2f(0.0f, 0.0f);
    }

    if(!GameHandle->GameScreen.IsFocused())
    {
        LeftMouseButtonDragDelta = sf::Vector2f(0.0f, 0.0f);
        RightMouseButtonDragDelta = sf::Vector2f(0.0f, 0.0f);
    }

    return;
}
