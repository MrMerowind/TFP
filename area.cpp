/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"


tfp::AreaListClass::AreaListClass()
    :InputAreaActive(false) {}

tfp::AreaListClass::~AreaListClass() {}

tfp::AreaListClass::Node::Node(tfp::FocusArea *Handle)
    :FocusAreaHandle(Handle), DragableAreaHandle(nullptr), ClickableAreaHandle(nullptr), InputAreaHandle(nullptr), Type(Focus) {}

tfp::AreaListClass::Node::Node(tfp::DragableArea *Handle)
    :FocusAreaHandle(nullptr), DragableAreaHandle(Handle), ClickableAreaHandle(nullptr), InputAreaHandle(nullptr), Type(Dragable) {}

tfp::AreaListClass::Node::Node(tfp::ClickableArea *Handle)
    :FocusAreaHandle(nullptr), DragableAreaHandle(nullptr), ClickableAreaHandle(Handle), InputAreaHandle(nullptr), Type(Clickable) {}

tfp::AreaListClass::Node::Node(tfp::InputArea *Handle)
    :FocusAreaHandle(nullptr), DragableAreaHandle(nullptr), ClickableAreaHandle(nullptr), InputAreaHandle(Handle), Type(Input) {}

tfp::AreaListClass::Node::~Node()
{
    FocusAreaHandle = nullptr;
    DragableAreaHandle = nullptr;
    ClickableAreaHandle = nullptr;
    InputAreaHandle = nullptr;
}

tfp::FocusArea::FocusArea()
    :Position({0.0f, 0.0f}), Size({0.0f, 0.0f}), Active(false), Disabled(true), GameHandle(nullptr)
{
    AreaList.Register(this);
}

tfp::FocusArea::FocusArea(tfp::Game *Handle, sf::Vector2f Position, sf::Vector2f Size, bool RelativeSize)
    :Position(Position), Size(Size), Active(false), Disabled(true), RelativeSize(RelativeSize), GameHandle(Handle)
{
    AreaList.Register(this);
}

tfp::FocusArea::~FocusArea() {}

tfp::InputArea::InputArea()
    :Position({0.0f, 0.0f}), Size({0.0f, 0.0f}), Active(false), Disabled(true), GameHandle(nullptr), InputText(""), InputTextMaxLength(500)
{
    AreaList.Register(this);
}

tfp::InputArea::InputArea(tfp::Game *Handle, sf::Vector2f Position, sf::Vector2f Size, bool RelativeSize)
    :Position(Position), Size(Size), Active(false), Disabled(true), RelativeSize(RelativeSize), InputType(tfp::TextTypeString), GameHandle(Handle), KeyConfigActionName(""), InputTextMaxLength(500)
{
    AreaList.Register(this);
}

tfp::InputArea::~InputArea() {}

tfp::DragableArea::DragableArea()
    :Position({0.0f, 0.0f}), Size({0.0f, 0.0f}), Active(false), Disabled(false), RelativeSize(true),  ButtonJustPressed(false), GameHandle(nullptr)
{
    AreaList.Register(this);
}

tfp::DragableArea::DragableArea(tfp::Game *Handle, sf::Vector2f Position, sf::Vector2f Size, bool RelativeSize)
    :Position(Position), Size(Size), RelativeSize(RelativeSize), GameHandle(Handle)
{
    AreaList.Register(this);
}

tfp::DragableArea::~DragableArea() {}

tfp::ClickableArea::ClickableArea()
    :Position({0.0f, 0.0f}), Size({0.0f, 0.0f}), ButtonDown(false), Disabled(false), RelativeSize(true), ButtonActivated(false), Blocked(false),
    GameHandle(nullptr)
{
    AreaList.Register(this);
}

tfp::ClickableArea::ClickableArea(tfp::Game *Handle, sf::Vector2f Position, sf::Vector2f Size, bool RelativeSize)
    :Position(Position), Size(Size), ButtonDown(false), Disabled(false), RelativeSize(RelativeSize), ButtonActivated(false), Blocked(false), GameHandle(Handle)
{
    AreaList.Register(this);
}

tfp::ClickableArea::~ClickableArea()
{
    GameHandle = nullptr;
    Disabled = true;
}

void tfp::AreaListClass::SendEvent(sf::Event &Event)
{
    EventList.push(Event);
}

void tfp::AreaListClass::CheckActive()
{
    InputAreaActive = false;
    /// A przyciski?
    // if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)) return;
    bool Disable = false;
    int Skip = -1;
    /// Jesli jest jakies dragable aktywne to wylaczamy reszte
    for(unsigned i = 0; i < List.size(); i++)
    {
        if(List[i].Type == tfp::AreaListClass::Node::Dragable && List[i].DragableAreaHandle->GetGameHandle() != nullptr && !List[i].DragableAreaHandle->IsDisabled() && List[i].DragableAreaHandle->GetGameHandle()->GameScreen.IsFocused()
           && List[i].DragableAreaHandle->IsActive())
        {

            List[i].DragableAreaHandle->CheckActiveSystem();
            if(List[i].DragableAreaHandle->IsActive())
            {
                Disable = true;
                List[i].DragableAreaHandle->GetGameHandle()->GameScreen.GetRenderWindowHandle().setMouseCursorGrabbed(true);
                Skip = (int) i;
                break;
            }
        }
    }

    for(int i = 0; i < GameManager.GamesOpen(); i++)
    {
        GameManager.GetGame(i).GameScreen.GetRenderWindowHandle().setMouseCursorGrabbed(false);
    }

    for(int i = 0; i < (int) List.size(); i++)
    {
        if(i == Skip) continue;
        if(List[i].Type == tfp::AreaListClass::Node::Dragable)
        {
            if(List[i].DragableAreaHandle->GetGameHandle() == nullptr) continue;
            if(List[i].DragableAreaHandle->IsDisabled()) continue;
            if(List[i].DragableAreaHandle->GetGameHandle()->GameScreen.IsFocused())
            {
                if(Disable)
                {
                    List[i].DragableAreaHandle->SetActive(false);
                }
                else
                {
                    List[i].DragableAreaHandle->CheckActiveSystem();
                    if(List[i].DragableAreaHandle->IsActive()) Disable = true;
                }
            }
            else
            {
                List[i].DragableAreaHandle->SetActive(false);
            }
        }
        else if(List[i].Type == tfp::AreaListClass::Node::Focus)
        {
            if(List[i].FocusAreaHandle->GetGameHandle() == nullptr) continue;
            if(List[i].FocusAreaHandle->IsDisabled()) continue;
            if(List[i].FocusAreaHandle->GetGameHandle()->GameScreen.IsFocused())
            {
                if(Disable)
                {
                    List[i].FocusAreaHandle->SetActive(false);
                }
                else
                {
                    List[i].FocusAreaHandle->CheckActiveSystem();
                    if(List[i].FocusAreaHandle->IsActive()) Disable = true;
                }
            }
            else
            {
                List[i].FocusAreaHandle->SetActive(false);
            }
        }
        else if(List[i].Type == tfp::AreaListClass::Node::Input)
        {
            if(List[i].InputAreaHandle->GetGameHandle() == nullptr) continue;
            if(List[i].InputAreaHandle->IsDisabled()) continue;
            if(List[i].InputAreaHandle->GetGameHandle()->GameScreen.IsFocused())
            {
                if(Disable)
                {
                    List[i].InputAreaHandle->SetActive(false);
                }
                else
                {
                    List[i].InputAreaHandle->CheckActiveSystem();
                    if(List[i].InputAreaHandle->IsActive())
                    {
                        Disable = true;
                        InputAreaActive = true;
                        while(!EventList.empty())
                        {
                            List[i].InputAreaHandle->SendEvent(EventList.front());
                            EventList.pop();
                        }
                    }
                }
            }
            else
            {
                List[i].InputAreaHandle->SetActive(false);
            }
        }
        else if(List[i].Type == tfp::AreaListClass::Node::Clickable)
        {
            if(List[i].ClickableAreaHandle->GetGameHandle() == nullptr) continue;
            if(List[i].ClickableAreaHandle->IsDisabled()) continue;
            if(List[i].ClickableAreaHandle->GetGameHandle()->GameScreen.IsFocused())
            {
                if(Disable)
                {
                    List[i].ClickableAreaHandle->SetActive(false);
                }
                else
                {
                    List[i].ClickableAreaHandle->CheckActiveSystem();
                    if(List[i].ClickableAreaHandle->IsButtonDown() || List[i].ClickableAreaHandle->IsButtonPressed()) Disable = true;
                }
            }
            else
            {
                List[i].ClickableAreaHandle->SetActive(false);
            }
        }


    }
    while(!EventList.empty())
        EventList.pop();
}

std::vector<tfp::AreaListClass::Node> &tfp::AreaListClass::GetList()
{
    return List;
}

int tfp::AreaListClass::GetRegisteredAreaCount()
{
    return List.size();
}

void tfp::AreaListClass::UnregisterGame(tfp::Game *GameHandle)
{
    if(GameHandle == nullptr) return;
    for(unsigned i = 0; i < List.size(); i++)
    {
        if(List[i].Type == tfp::AreaListClass::Node::Clickable)
        {
            if(List[i].ClickableAreaHandle->GetGameHandle() == GameHandle)
            {
                List.erase(List.begin() + i);
                i--;
                continue;
            }
        }
        else if(List[i].Type == tfp::AreaListClass::Node::Focus)
        {
            if(List[i].FocusAreaHandle->GetGameHandle() == GameHandle)
            {
                List.erase(List.begin() + i);
                i--;
                continue;
            }
        }
        else if(List[i].Type == tfp::AreaListClass::Node::Input)
        {
            if(List[i].InputAreaHandle->GetGameHandle() == GameHandle)
            {
                List.erase(List.begin() + i);
                i--;
                continue;
            }
        }
        else if(List[i].Type == tfp::AreaListClass::Node::Dragable)
        {
            if(List[i].DragableAreaHandle->GetGameHandle() == GameHandle)
            {
                List.erase(List.begin() + i);
                i--;
                continue;
            }
        }
    }
}

bool &tfp::AreaListClass::IsInputAreaActive()
{
    return InputAreaActive;
}

void tfp::AreaListClass::Register(tfp::FocusArea *Handle)
{
    List.push_back(Handle);
}

void tfp::AreaListClass::Register(tfp::DragableArea *Handle)
{
    List.push_back(Handle);
}

void tfp::AreaListClass::Register(tfp::ClickableArea *Handle)
{
    List.push_back(Handle);
}

void tfp::AreaListClass::Register(tfp::InputArea *Handle)
{
    List.push_back(Handle);
}


void tfp::AreaListClass::Unregister(tfp::FocusArea *Handle)
{
    for(unsigned i = 0; i < List.size(); i++)
    {
        if(List[i].Type == tfp::AreaListClass::Node::Focus && List[i].FocusAreaHandle == Handle)
        {
            List.erase(List.begin() + i);
            return;
        }
    }
}

void tfp::AreaListClass::Unregister(tfp::DragableArea *Handle)
{
    for(unsigned i = 0; i < List.size(); i++)
    {
        if(List[i].Type == tfp::AreaListClass::Node::Dragable && List[i].DragableAreaHandle == Handle)
        {
            List.erase(List.begin() + i);
            return;
        }
    }
}

void tfp::AreaListClass::Unregister(tfp::ClickableArea *Handle)
{
    for(unsigned i = 0; i < List.size(); i++)
    {
        if(List[i].Type == tfp::AreaListClass::Node::Clickable && List[i].ClickableAreaHandle == Handle)
        {
            List.erase(List.begin() + i);
            return;
        }
    }
}

void tfp::AreaListClass::Unregister(tfp::InputArea *Handle)
{
    for(unsigned i = 0; i < List.size(); i++)
    {
        if(List[i].Type == tfp::AreaListClass::Node::Input && List[i].InputAreaHandle == Handle)
        {
            List.erase(List.begin() + i);
            return;
        }
    }
}

void tfp::FocusArea::SetGameHandle(tfp::Game *Handle)
{
    GameHandle = Handle;
}

void tfp::FocusArea::Reset(tfp::Game *Handle,sf::Vector2f _Position, sf::Vector2f _Size, bool RelativeSize_)
{
    Position = _Position;
    Size = _Size;
    RelativeSize = RelativeSize_;
    GameHandle = Handle;
}

void tfp::FocusArea::CheckActiveSystem()
{
    if(GameHandle == nullptr)
    {
        Debug.Warning("FocusArea  -  Screen handle is not set");
        return;
    }
    if(!GameHandle->GameScreen.IsFocused())
    {
        Active = false;
        return;
    }
    if(RelativeSize)
    {
        if(GameHandle->GameMouse.GetMousePositionScaled().x >= Position.x && GameHandle->GameMouse.GetMousePositionScaled().x <= Position.x + Size.x
        && GameHandle->GameMouse.GetMousePositionScaled().y >= Position.y && GameHandle->GameMouse.GetMousePositionScaled().y <= Position.y + Size.y
        && GameHandle->GameMouse.GetMouse().isButtonPressed(sf::Mouse::Left))
            Active = true;
        else if(GameHandle->GameMouse.GetMouse().isButtonPressed(sf::Mouse::Left)) Active = false;
    }
    else
    {
        if(GameHandle->GameMouse.GetMousePosition().x >= Position.x && GameHandle->GameMouse.GetMousePosition().x <= Position.x + Size.x
        && GameHandle->GameMouse.GetMousePosition().y >= Position.y && GameHandle->GameMouse.GetMousePosition().y <= Position.y + Size.y
        && GameHandle->GameMouse.GetMouse().isButtonPressed(sf::Mouse::Left))
            Active = true;
        else if(GameHandle->GameMouse.GetMouse().isButtonPressed(sf::Mouse::Left)) Active = false;
    }
    if(Disabled)
    {
        Active = false;
    }
}

sf::Vector2f &tfp::FocusArea::GetPosition()
{
    return Position;
}

sf::Vector2f &tfp::FocusArea::GetSize()
{
    return Size;
}

void tfp::FocusArea::SetPosition(sf::Vector2f NewPosition)
{
    Position = NewPosition;
}

const bool &tfp::FocusArea::IsDisabled() const
{
    return Disabled;
}

const bool tfp::FocusArea::IsActive() const
{
    if(Disabled) return false;
    else return Active;
}

void tfp::FocusArea::SetActive(bool State)
{
    Active = State;
}

void tfp::FocusArea::SetDisabled(bool State)
{
    Disabled = State;
}

void tfp::FocusArea::Move(sf::Vector2f Distance)
{
    Position += Distance;
}


/// InputArea

void tfp::InputArea::SetGameHandle(tfp::Game *Handle)
{
    GameHandle = Handle;
}

void tfp::InputArea::SetPosition(sf::Vector2f Position_)
{
    Position = Position_;
}

void tfp::InputArea::SetPosition(float PositionX, float PositionY)
{
    Position.x = PositionX;
    Position.y = PositionY;
}

void tfp::InputArea::SetSize(sf::Vector2f Size_, bool Relative)
{
    Size = Size_;
    RelativeSize = Relative;
}

sf::Vector2f &tfp::InputArea::GetPosition()
{
    return Position;
}

sf::Vector2f &tfp::InputArea::GetSize()
{
    return Size;
}

const bool &tfp::InputArea::IsDisabled() const
{
    return Disabled;
}

std::string &tfp::InputArea::GetText()
{
    if(InputType == tfp::TextTypeKey) InputText = KeyConfig.GetActionInString(KeyConfigActionName);
    return InputText;
}

void tfp::InputArea::SendEvent(sf::Event &Event)
{
    if(InputType == tfp::TextTypeKey)
    {
        if(Event.type == sf::Event::KeyPressed)
        {
            InputText = "";
            if(Event.key.system) InputText += "System + ";
            if(Event.key.control) InputText += "Ctrl + ";
            if(Event.key.alt) InputText += "Alt + ";
            if(Event.key.shift) InputText += "Shift + ";
            InputText += tfp::SfmlEventToString(Event);
            if(KeyConfigActionName != "")
            {
                KeyConfig.SetAction(KeyConfigActionName, Event);
                KeyConfig.SaveUserConfig();
            }
        }
    }
    else
    {
        if(Event.type == sf::Event::TextEntered && Event.text.unicode < 128)
        {
            char Character = Event.text.unicode;

            if(Character == 96 || Character == 126) /** Nic **/;
            else if(Character == 127) InputText = "";
            else if(Character == 8) // Backspace
            {
                if(InputText.size() > 0) InputText.resize(InputText.size() - 1);
            }
            else if(Character == 13)
            {
                Active = false;
            }
            else if(Character > 31 && Character < 128 && InputText.size() < 140 /*74*/)
            {
                if(InputTextMaxLength != 0 && (int) InputText.size() >= InputTextMaxLength) return;
                if(InputType == tfp::TextTypeString)
                {
                    InputText += Character;
                }
                else if(InputType == tfp::TextTypeInt)
                {
                    if(Character >= '0' && Character <= '9') InputText += Character;
                }
                else if(InputType == tfp::TextTypeFloat)
                {
                    if(Character >= '0' && Character <= '9') InputText += Character;
                    bool ComaInText = false;
                    for(unsigned i = 0; i < InputText.size(); i++)
                        if(InputText[i] == '.') ComaInText = true;
                    if(!ComaInText && (Character == '.' || Character == ',')) InputText += '.';
                }
            }
        }
    }

}

tfp::Game* tfp::InputArea::GetGameHandle()
{
    return GameHandle;
}

void tfp::InputArea::SetTextMaxLength(int Length)
{
    InputTextMaxLength = Length;
}

void tfp::InputArea::Reset(tfp::Game *Handle,sf::Vector2f _Position, sf::Vector2f _Size, bool RelativeSize_)
{
    Position = _Position;
    Size = _Size;
    RelativeSize = RelativeSize_;
    GameHandle = Handle;
}

void tfp::InputArea::SetText(std::string Text)
{
    InputText = Text;
}

void tfp::InputArea::CheckActiveSystem()
{
    if(GameHandle == nullptr)
    {
        Debug.Warning("InputArea  -  Screen handle is not set");
        return;
    }
    if(!GameHandle->GameScreen.IsFocused())
    {
        Active = false;
        return;
    }
    if(RelativeSize)
    {
        if(GameHandle->GameMouse.GetMousePositionScaled().x >= Position.x && GameHandle->GameMouse.GetMousePositionScaled().x <= Position.x + Size.x
        && GameHandle->GameMouse.GetMousePositionScaled().y >= Position.y && GameHandle->GameMouse.GetMousePositionScaled().y <= Position.y + Size.y
        && GameHandle->GameMouse.GetMouse().isButtonPressed(sf::Mouse::Left))
            Active = true;
        else if(GameHandle->GameMouse.GetMouse().isButtonPressed(sf::Mouse::Left)) Active = false;
    }
    else
    {
        if(GameHandle->GameMouse.GetMousePosition().x >= Position.x && GameHandle->GameMouse.GetMousePosition().x <= Position.x + Size.x
        && GameHandle->GameMouse.GetMousePosition().y >= Position.y && GameHandle->GameMouse.GetMousePosition().y <= Position.y + Size.y
        && GameHandle->GameMouse.GetMouse().isButtonPressed(sf::Mouse::Left))
            Active = true;
        else if(GameHandle->GameMouse.GetMouse().isButtonPressed(sf::Mouse::Left)) Active = false;
    }
    if(Disabled)
    {
        Active = false;
    }

}

const bool tfp::InputArea::IsActive() const
{
    if(Disabled) return false;
    else return Active;
}

void tfp::InputArea::SetKeyConfigActionName(std::string Name)
{
    KeyConfigActionName = Name;
    InputText = KeyConfig.GetActionInString(KeyConfigActionName);
}

void tfp::InputArea::SetActive(bool State)
{
    Active = State;
}

void tfp::InputArea::SetDisabled(bool State)
{
    Disabled = State;
}

void tfp::InputArea::Move(sf::Vector2f Distance)
{
    Position += Distance;
}

void tfp::InputArea::SetInputType(tfp::TextType InputType_)
{
    InputType = InputType_;
}

/// Dragable

void tfp::DragableArea::SetGameHandle(tfp::Game *Handle)
{
    GameHandle = Handle;
}

void tfp::DragableArea::Reset(tfp::Game *Handle,sf::Vector2f _Position, sf::Vector2f _Size, bool RelativeSize_)
{
    Position = _Position;
    Size = _Size;
    RelativeSize = RelativeSize_;
    GameHandle = Handle;
}

sf::Vector2f &tfp::DragableArea::GetPosition()
{
    return Position;
}

const bool &tfp::DragableArea::IsDisabled() const
{
    return Disabled;
}

sf::Vector2f &tfp::DragableArea::GetSize()
{
    return Size;
}

void tfp::DragableArea::CheckActiveSystem()
{
    if(GameHandle == nullptr)
    {
        Debug.Warning("DragableArea  -  Screen handle is not set");
        return;
    }
    if(!GameHandle->GameScreen.IsFocused())
    {
        Active = false;
        return;
    }
    if(RelativeSize)
    {
        if(GameHandle->GameMouse.GetMousePositionScaled().x >= Position.x && GameHandle->GameMouse.GetMousePositionScaled().x <= Position.x + Size.x
        && GameHandle->GameMouse.GetMousePositionScaled().y >= Position.y && GameHandle->GameMouse.GetMousePositionScaled().y <= Position.y + Size.y
        && GameHandle->GameMouse.GetMouse().isButtonPressed(sf::Mouse::Left) && !ButtonJustPressed)
        {
            Active = true;
            ButtonJustPressed = true;
        }
        else if(!GameHandle->GameMouse.GetMouse().isButtonPressed(sf::Mouse::Left))
        {
            Active = false;
            ButtonJustPressed = false;
        }
        else if(GameHandle->GameMouse.GetMouse().isButtonPressed(sf::Mouse::Left)) ButtonJustPressed = true;
    }
    else
    {
        if(GameHandle->GameMouse.GetMousePosition().x >= Position.x && GameHandle->GameMouse.GetMousePosition().x <= Position.x + Size.x
        && GameHandle->GameMouse.GetMousePosition().y >= Position.y && GameHandle->GameMouse.GetMousePosition().y <= Position.y + Size.y
        && GameHandle->GameMouse.GetMouse().isButtonPressed(sf::Mouse::Left) && !ButtonJustPressed)
        {
            Active = true;
            ButtonJustPressed = true;
        }
        else if(!GameHandle->GameMouse.GetMouse().isButtonPressed(sf::Mouse::Left))
        {
            Active = false;
            ButtonJustPressed = false;
        }
        else if(GameHandle->GameMouse.GetMouse().isButtonPressed(sf::Mouse::Left)) ButtonJustPressed = true;
    }
    if(Disabled)
    {
        Active = false;
    }
}

bool tfp::DragableArea::IsMouseInBorders()
{
    if(GameHandle == nullptr)
    {
        Debug.Warning("DragableArea  -  Screen handle is not set");
        return false;
    }
    if(!GameHandle->GameScreen.IsFocused())
    {
        return false;
    }
    if(RelativeSize)
    {
        if(GameHandle->GameMouse.GetMousePositionScaled().x >= Position.x && GameHandle->GameMouse.GetMousePositionScaled().x <= Position.x + Size.x
        && GameHandle->GameMouse.GetMousePositionScaled().y >= Position.y && GameHandle->GameMouse.GetMousePositionScaled().y <= Position.y + Size.y)
        {
            return true;
        }
        else return false;
    }
    else
    {
        if(GameHandle->GameMouse.GetMousePosition().x >= Position.x && GameHandle->GameMouse.GetMousePosition().x <= Position.x + Size.x
        && GameHandle->GameMouse.GetMousePosition().y >= Position.y && GameHandle->GameMouse.GetMousePosition().y <= Position.y + Size.y)
        {
            return true;
        }
        else return false;
    }
}

const bool tfp::DragableArea::IsActive() const
{
    if(Disabled) return false;
    else return Active;
}

void tfp::DragableArea::SetActive(bool State)
{
    Active = State;
}

void tfp::DragableArea::SetDisabled(bool State)
{
    Disabled = State;
}

void tfp::DragableArea::Move(sf::Vector2f Distance)
{
    Position += Distance;
}

void tfp::DragableArea::SetPosition(sf::Vector2f Position_)
{
    Position = Position_;
}

tfp::Game* tfp::FocusArea::GetGameHandle()
{
    return GameHandle;
}

tfp::Game* tfp::DragableArea::GetGameHandle()
{
    return GameHandle;
}

void tfp::ClickableArea::Reset(tfp::Game *Handle, sf::Vector2f Position_, sf::Vector2f Size_, bool RelativeSize_)
{
    Position = Position_;
    Size = Size_;
    ButtonDown = false;
    Disabled = false;
    RelativeSize = RelativeSize_;
    ButtonActivated = false;
    GameHandle = Handle;
}

void tfp::ClickableArea::SetGameHandle(tfp::Game *Handle)
{
    GameHandle = Handle;
}

sf::Vector2f &tfp::ClickableArea::GetPosition()
{
    return Position;
}

const bool &tfp::ClickableArea::IsDisabled() const
{
    return Disabled;
}

sf::Vector2f &tfp::ClickableArea::GetSize()
{
    return Size;
}

void tfp::ClickableArea::CheckActiveSystem()
{
    if(GameHandle == nullptr)
    {
        Debug.Warning("ClickableArea  -  Screen handle is not set");
        return;
    }
    if(!GameHandle->GameScreen.IsFocused())
    {
        ButtonDown = false;
        ButtonActivated = false;
        return;
    }
    if(RelativeSize)
    {
        /// Klikniecie w przycisk
        if(GameHandle->GameMouse.GetMousePositionScaled().x >= Position.x && GameHandle->GameMouse.GetMousePositionScaled().x <= Position.x + Size.x
        && GameHandle->GameMouse.GetMousePositionScaled().y >= Position.y && GameHandle->GameMouse.GetMousePositionScaled().y <= Position.y + Size.y
        && GameHandle->GameMouse.GetMouse().isButtonPressed(sf::Mouse::Left) && !ButtonDown && !Blocked)
        {
            ButtonDown = true;
            // ButtonActivated = false;
        }
        /// LeftButtonUp in rect
        else if(GameHandle->GameMouse.GetMousePositionScaled().x >= Position.x && GameHandle->GameMouse.GetMousePositionScaled().x <= Position.x + Size.x
        && GameHandle->GameMouse.GetMousePositionScaled().y >= Position.y && GameHandle->GameMouse.GetMousePositionScaled().y <= Position.y + Size.y
        && !GameHandle->GameMouse.GetMouse().isButtonPressed(sf::Mouse::Left) && ButtonDown)
        {
            ButtonDown = false;
            ButtonActivated = true;
            Blocked = false;
        }
        /// LeftButtonUp outside rect
        else if(!GameHandle->GameMouse.GetMouse().isButtonPressed(sf::Mouse::Left))
        {
            ButtonDown = false;
            // ButtonActivated = false;
            Blocked = false;
        }
        else if(GameHandle->GameMouse.GetMouse().isButtonPressed(sf::Mouse::Left) & !ButtonDown)
        {
            Blocked = true;
        }
    }
    else
    {
        /// Klikniecie w przycisk
        if(GameHandle->GameMouse.GetMousePosition().x >= Position.x && GameHandle->GameMouse.GetMousePosition().x <= Position.x + Size.x
        && GameHandle->GameMouse.GetMousePosition().y >= Position.y && GameHandle->GameMouse.GetMousePosition().y <= Position.y + Size.y
        && GameHandle->GameMouse.GetMouse().isButtonPressed(sf::Mouse::Left) && !ButtonDown && !Blocked)
        {
            ButtonDown = true;
            // ButtonActivated = false;
        }
        /// LeftButtonUp in rect
        else if(GameHandle->GameMouse.GetMousePosition().x >= Position.x && GameHandle->GameMouse.GetMousePosition().x <= Position.x + Size.x
        && GameHandle->GameMouse.GetMousePosition().y >= Position.y && GameHandle->GameMouse.GetMousePosition().y <= Position.y + Size.y
        && !GameHandle->GameMouse.GetMouse().isButtonPressed(sf::Mouse::Left) && ButtonDown)
        {
            ButtonDown = false;
            ButtonActivated = true;
            Blocked = false;
        }
        /// LeftButtonUp outside rect
        else if(!GameHandle->GameMouse.GetMouse().isButtonPressed(sf::Mouse::Left))
        {
            ButtonDown = false;
            // ButtonActivated = false;
            Blocked = false;
        }
        else if(GameHandle->GameMouse.GetMouse().isButtonPressed(sf::Mouse::Left) & !ButtonDown)
        {
            Blocked = true;
        }
    }
    if(Disabled)
    {
        ButtonDown = false;
        // ButtonActivated = false;
    }
}

void tfp::ClickableArea::SetDisabled(bool State)
{
    Disabled = State;
}

void tfp::ClickableArea::Move(sf::Vector2f Distance)
{
    Position += Distance;
}

void tfp::ClickableArea::SetPosition(sf::Vector2f Position_)
{
    Position = Position_;
}

tfp::Game* tfp::ClickableArea::GetGameHandle()
{
    return GameHandle;
}

bool tfp::ClickableArea::IsButtonDown()
{
    if(!Disabled) return ButtonDown;
    else return false;
}

void tfp::ClickableArea::SetSize(sf::Vector2f Size_)
{
    Size = Size_;
}

bool tfp::ClickableArea::IsButtonPressed()
{
    if(!Disabled) return ButtonActivated;
    else return false;
}

void tfp::ClickableArea::SetActive(bool State)
{
    ButtonDown = false;
    ButtonActivated = State;
}
