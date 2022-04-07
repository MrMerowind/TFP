/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"

tfp::WindowGlobalDataClass::WindowGlobalDataClass()
    :BorderWidth(250), BorderHeight(250)
{
    WindowBorderTextureTop.loadFromFile("Graphics\\Interface\\WindowBorders.png", sf::Rect<int>(0, 0, 250, 250));
    WindowBorderTextureDown.loadFromFile("Graphics\\Interface\\WindowBorders.png", sf::Rect<int>(250, 250, 250, 250));
    WindowBorderTextureLeft.loadFromFile("Graphics\\Interface\\WindowBorders.png", sf::Rect<int>(0, 250, 250, 250));
    WindowBorderTextureRight.loadFromFile("Graphics\\Interface\\WindowBorders.png", sf::Rect<int>(250, 0, 250, 250));

    WindowCornerTextureLeftDown.loadFromFile("Graphics\\Interface\\WindowCorners.png", sf::Rect<int>(0, 250, 250, 250));
    WindowCornerTextureLeftTop.loadFromFile("Graphics\\Interface\\WindowCorners.png", sf::Rect<int>(0 , 0, 250, 250));
    WindowCornerTextureRightDown.loadFromFile("Graphics\\Interface\\WindowCorners.png", sf::Rect<int>(250, 250, 250, 250));
    WindowCornerTextureRightTop.loadFromFile("Graphics\\Interface\\WindowCorners.png", sf::Rect<int>(250 , 0, 250, 250));

    WindowInsideTexture.loadFromFile("Graphics\\Interface\\WindowInside.png");
}

tfp::WindowGlobalDataClass::~WindowGlobalDataClass() {}

tfp::Window::Window()
    :Visible(false), GameHandle(nullptr) {}


tfp::Window::Window(tfp::Game *GameHandle, sf::Rect<int> BoxInside, std::string WindowName)
    :InsideSize({BoxInside.width, BoxInside.height}), Position({(float) BoxInside.left, (float) BoxInside.top}), PositionPrevious({0.0f, 0.0f}), WindowMoved(false), Name(WindowName), GameHandle(GameHandle)
{
    WindowDragableArea.Reset(GameHandle, sf::Vector2f(Position.x, Position.y - WindowGlobalData.GetBorderWidth()), sf::Vector2f(InsideSize.x, WindowGlobalData.GetBorderHeight()), true);
    WindowFocusArea.Reset(GameHandle, Position, {(float) InsideSize.x, (float) InsideSize.y}, true);
    WindowGlobalData.RegisterWindow(this);
}

tfp::Window::~Window() {}

const int &tfp::WindowGlobalDataClass::GetBorderWidth() const
{
    return BorderWidth;
}

const int &tfp::WindowGlobalDataClass::GetBorderHeight() const
{
    return BorderHeight;
}

const sf::Texture &tfp::WindowGlobalDataClass::GetTexture(int Number) const
{
    if(Number == 7) return WindowCornerTextureLeftTop;
    else if(Number == 9) return WindowCornerTextureRightTop;
    else if(Number == 3) return WindowCornerTextureRightDown;
    else if(Number == 1) return WindowCornerTextureLeftDown;
    else if(Number == 8) return WindowBorderTextureTop;
    else if(Number == 4) return WindowBorderTextureLeft;
    else if(Number == 6) return WindowBorderTextureRight;
    else if(Number == 2) return WindowBorderTextureDown;
    else if(Number == 5) return WindowInsideTexture;
    else
    {
        Debug.Error("WindowGlobalData.GetTexture()  -  Wrong number");
        return WindowBorderTextureDown;
    }

}

std::string tfp::Window::GetWindowName()
{
    return Name;
}

tfp::DragableArea &tfp::Window::GetWindowDragableArea()
{
    return WindowDragableArea;
}

void tfp::Window::Reset(tfp::Game *GameHandle_, sf::Rect<int> BoxInside, std::string WindowName)
{
    GameHandle = GameHandle_;
    Name = WindowName;
    Position = sf::Vector2f((float) BoxInside.left, (float) BoxInside.top);
    InsideSize = sf::Vector2i(BoxInside.width, BoxInside.height);
    WindowDragableArea.Reset(GameHandle, sf::Vector2f(Position.x, Position.y - WindowGlobalData.GetBorderWidth()), sf::Vector2f(InsideSize.x, WindowGlobalData.GetBorderHeight()), true);
    WindowFocusArea.Reset(GameHandle, Position, {(float) InsideSize.x, (float) InsideSize.y}, true);
    WindowGlobalData.RegisterWindow(this);
}

void tfp::Window::Resize(int Width, int Height)
{
    if(InsideSize.x == Width && InsideSize.y == Height) return;

    InsideSize.x = Width;
    InsideSize.y = Height;

    WindowDragableArea.Reset(GameHandle, sf::Vector2f(Position.x, Position.y - WindowGlobalData.GetBorderWidth()), sf::Vector2f(InsideSize.x, WindowGlobalData.GetBorderHeight()), true);
    WindowFocusArea.Reset(GameHandle, Position, {(float) InsideSize.x, (float) InsideSize.y}, true);

}

std::vector<tfp::Window*> &tfp::WindowGlobalDataClass::GetWindowList()
{
    return WindowList;
}

void tfp::Window::Show(bool State)
{
    Visible = State;
}

tfp::Game *tfp::Window::GetGameHandle()
{
    return GameHandle;
}

void tfp::Window::Draw(sf::Sprite &Object)
{
    Object.move(Position.x * GameHandle->GameScreen.GetViewScale(), Position.y * GameHandle->GameScreen.GetViewScale());
    GameHandle->GameScreen.Draw(Object);
}

void tfp::Window::Draw(sf::Text &Object)
{
    Object.move(Position.x * GameHandle->GameScreen.GetViewScale(), Position.y * GameHandle->GameScreen.GetViewScale());
    GameHandle->GameScreen.Draw(Object);
}

void tfp::Window::WindowEvents()
{
    if(PositionPrevious != Position)
    {
        WindowMoved = true;
        PositionPrevious = Position;
    }
    else
    {
        WindowMoved = false;
    }
    if(!IsVisible())
    {
        WindowDragableArea.SetActive(false);
    }
    AreaList.CheckActive();
    if(WindowDragableArea.IsActive() /*&& IsMouseInsideWindow()*/)
    {
        /// TEST
        Position -= GameHandle->GameMouse.GetLeftMouseButtonDeltaDragScaled();
        /// Position -= GameHandle->GameMouse.GetLeftMouseButtonDeltaDrag();
        WindowDragableArea.SetPosition(sf::Vector2f(Position.x, Position.y - WindowGlobalData.GetBorderHeight()));
    }
    if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(Position.x < 0) Position.x = 0;
        if(Position.y - WindowGlobalData.GetBorderHeight() < 0) Position.y = WindowGlobalData.GetBorderHeight();
        if(Position.x + InsideSize.x > GameHandle->GameScreen.GetOriginalViewSize().x) Position.x = GameHandle->GameScreen.GetOriginalViewSize().x - InsideSize.x;
        if(Position.y + InsideSize.y  > GameHandle->GameScreen.GetOriginalViewSize().y) Position.y = GameHandle->GameScreen.GetOriginalViewSize().y - InsideSize.y;
        WindowDragableArea.SetPosition(sf::Vector2f(Position.x, Position.y - WindowGlobalData.GetBorderHeight()));
    }
}

bool tfp::WindowGlobalDataClass::IsMouseInsideWindow(tfp::Window *Handle)
{
    if(!Handle->GetGameHandle()->GameScreen.IsFocused()) return false;
    for(unsigned i = 0; i < WindowList.size(); i++)
    {
        if(WindowList[i]->GetGameHandle()->GameScreen.IsFocused())
        {
            if(WindowList[i]->IsMouseInsideWindowSystem())
            {
                if(WindowList[i] == Handle) return true;
                else return false;
            }
            else if(WindowList[i] == Handle) return false;
        }
    }

    Debug.Warning("Window is not registered");
    return false;
}

bool tfp::WindowGlobalDataClass::IsMouseInsideAnyWindow(tfp::Game *Handle)
{
    if(Handle == nullptr) return false;
    if(!Handle->GameScreen.IsFocused()) return false;
    for(unsigned i = 0; i < WindowList.size(); i++)
    {
        if(WindowList[i]->GetGameHandle()->GameScreen.IsFocused() && WindowList[i]->IsMouseInsideWindowSystem())
        {
            return true;
        }
    }
    return false;
}

bool tfp::WindowGlobalDataClass::IsMouseInsideBorders(tfp::Window *Handle)
{
    /// Okno gry nie ma focusu
    if(!Handle->GetGameHandle()->GameScreen.IsFocused()) return false;
    for(unsigned i = 0; i < WindowList.size(); i++)
    {
        if(WindowList[i]->GetGameHandle()->GameScreen.IsFocused())
        {
            if(WindowList[i]->IsMouseInsideBordersSystem())
            {
                if(WindowList[i] == Handle) return true;
                else return false;
            }
            else if(WindowList[i] == Handle) return false;
        }
    }

    Debug.Warning("Window is not registered");
    return false;
}

void tfp::WindowGlobalDataClass::RegisterWindow(tfp::Window *Handle)
{
    WindowList.push_back(Handle);
}

void tfp::WindowGlobalDataClass::UnregisterWindows(tfp::Game *Handle)
{
    for(unsigned i = 0; i < WindowList.size(); i++)
    {
        if(WindowList[i]->GetGameHandle() == Handle)
        {
            WindowList.erase(WindowList.begin() + i);
            i--;
        }
    }
}

bool tfp::Window::IsMouseInsideWindow()
{

    return WindowGlobalData.IsMouseInsideWindow(this);
}

bool tfp::Window::IsMouseInsideBorders()
{
    return WindowGlobalData.IsMouseInsideBorders(this);
}

sf::Vector2f &tfp::Window::GetPosition()
{
    return Position;
}

bool tfp::Window::IsMouseInsideWindowSystem()
{
    if(!IsVisible()) return false;
    if(WindowDragableArea.IsActive()) return true;
    if(GetMousePosition().x < 0 || GetMousePosition().x > InsideSize.x) return false;
    if(GetMousePosition().y < - WindowGlobalData.GetBorderHeight() || GetMousePosition().y > InsideSize.y) return false;
    return true;
}

bool tfp::Window::IsMouseInsideBordersSystem()
{
    if(!IsVisible()) return false;
    if(GetMousePosition().x < 0 || GetMousePosition().x > InsideSize.x) return false;
    if(GetMousePosition().y < 0 || GetMousePosition().y > InsideSize.y) return false;
    return true;
}

sf::Vector2f tfp::Window::GetTitlePosition()
{
    sf::Vector2f Return;
    Return.x = Position.x + InsideSize.x / 2.0f;
    Return.y = Position.y - WindowGlobalData.GetBorderHeight() + 150;
    return Return;
}

bool tfp::Window::IsVisible()
{
    return Visible;
}

sf::Vector2f tfp::Window::GetMousePosition()
{
    return GameHandle->GameMouse.GetMousePositionScaled() - Position;
}

bool tfp::Window::HasMoved()
{
    return WindowMoved;
}

sf::Vector2i &tfp::Window::GetInsideSize()
{
    return InsideSize;
}

void tfp::Window::Display()
{
    if(GameHandle == nullptr)
    {
        Debug.Warning("Window game handle is not set");
        return;
    }
    WindowEvents();
    if(!IsVisible())
    {
       WindowFocusArea.SetDisabled(true);
       WindowDragableArea.SetDisabled(true);
       return;
    }
    else
    {
        WindowFocusArea.SetDisabled(false);
        WindowDragableArea.SetDisabled(false);
    }

    WindowFocusArea.SetPosition(Position);

    GameHandle->GameScreen.Draw(Sprite.Create(WindowGlobalData.GetTexture(7),
                                              Position.x - WindowGlobalData.GetBorderWidth(),
                                              Position.y - WindowGlobalData.GetBorderHeight(),
                                              GameHandle->GameScreen.GetViewScale()));
    GameHandle->GameScreen.Draw(Sprite.Create(WindowGlobalData.GetTexture(1),
                                              Position.x - WindowGlobalData.GetBorderWidth(),
                                              Position.y + InsideSize.y,
                                              GameHandle->GameScreen.GetViewScale()));
    GameHandle->GameScreen.Draw(Sprite.Create(WindowGlobalData.GetTexture(9),
                                              Position.x + InsideSize.x,
                                              Position.y - WindowGlobalData.GetBorderHeight(),
                                              GameHandle->GameScreen.GetViewScale()));
    GameHandle->GameScreen.Draw(Sprite.Create(WindowGlobalData.GetTexture(3),
                                              Position.x + InsideSize.x,
                                              Position.y + InsideSize.y,
                                              GameHandle->GameScreen.GetViewScale()));
    GameHandle->GameScreen.Draw(Sprite.Create(WindowGlobalData.GetTexture(8),
                                              Position.x,
                                              Position.y - WindowGlobalData.GetBorderHeight(),
                                              GameHandle->GameScreen.GetViewScale(),
                                              GameHandle->GameScreen.GetViewScale(),
                                              InsideSize.x / (float) WindowGlobalData.GetBorderWidth()));
    GameHandle->GameScreen.Draw(Sprite.Create(WindowGlobalData.GetTexture(4),
                                              Position.x - WindowGlobalData.GetBorderWidth(),
                                              Position.y,
                                              GameHandle->GameScreen.GetViewScale(),
                                              GameHandle->GameScreen.GetViewScale(),
                                              1.0f,
                                              InsideSize.y / (float) WindowGlobalData.GetBorderHeight()));
    GameHandle->GameScreen.Draw(Sprite.Create(WindowGlobalData.GetTexture(6),
                                              Position.x + InsideSize.x,
                                              Position.y,
                                              GameHandle->GameScreen.GetViewScale(),
                                              GameHandle->GameScreen.GetViewScale(),
                                              1.0f,
                                              InsideSize.y / (float) WindowGlobalData.GetBorderHeight()));
    GameHandle->GameScreen.Draw(Sprite.Create(WindowGlobalData.GetTexture(2),
                                              Position.x,
                                              Position.y + InsideSize.y,
                                              GameHandle->GameScreen.GetViewScale(),
                                              GameHandle->GameScreen.GetViewScale(),
                                              InsideSize.x / (float) WindowGlobalData.GetBorderWidth()));

    GameHandle->GameScreen.Draw(Text.CreateTranslated(Name,
                                                      FontList.FindFontWithName("WindowTitle"),
                                                      GetTitlePosition(),
                                                      GameHandle->GameScreen.GetViewScale(), tfp::AlignCenter));


    GameHandle->GameScreen.Draw(Sprite.Create(WindowGlobalData.GetTexture(5),
                                              Position.x,
                                              Position.y,
                                              GameHandle->GameScreen.GetViewScale(),
                                              GameHandle->GameScreen.GetViewScale(),
                                              InsideSize.x / (float) WindowGlobalData.GetBorderWidth(),
                                              InsideSize.y / (float) WindowGlobalData.GetBorderHeight()));
}
