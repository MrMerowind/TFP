/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"

tfp::Button::Button(sf::Vector2f Position, sf::Vector2f Size, std::string Text)
    :Position(Position), Size(Size), Name(Text), GameHandle(nullptr) {}

tfp::Button::~Button() {}

tfp::LoadingBar::LoadingBar(sf::Vector2f Position, sf::Vector2f Size, tfp::LoadingBar::Mode DisplayMode)
    :Position(Position), Size(Size), RenderText(""), Value(0), MaxValue(1), BarColor(sf::Color::Red), UnderBarColor({220, 215, 184, 255}),
    GameHandle(nullptr), BarMode(DisplayMode) {}

tfp::LoadingBar::~LoadingBar() {}

tfp::InputBar::InputBar(sf::Vector2f Position, sf::Vector2f Size)
    :Position(Position), Size(Size), RenderText(""), MaximumCharacters(20), UnderBarColor({220, 215, 184, 255}), GameHandle(nullptr), PlaceHolder("") {}

tfp::InputBar::~InputBar() {}

void tfp::Button::Display()
{
    if(GameHandle == nullptr) return;
    sf::VertexArray Lines(sf::Quads, 4);
    if(!Area.IsButtonDown())
    {
        Lines[0].color = sf::Color(220, 215, 184, 255);
        Lines[1].color = sf::Color(220, 215, 184, 255);
        Lines[2].color = sf::Color(220, 215, 184, 255);
        Lines[3].color = sf::Color(220, 215, 184, 255);
    }
    else
    {
        Lines[2].color = sf::Color(112, 141, 129, 255);
        Lines[3].color = sf::Color(112, 141, 129, 255);
        Lines[0].color = sf::Color(112, 141, 129, 255);
        Lines[1].color = sf::Color(112, 141, 129, 255);
    }
    Lines[0].position = sf::Vector2f((Position.x) * GameHandle->GameScreen.GetViewScale(), (Position.y) * GameHandle->GameScreen.GetViewScale());
    Lines[1].position = sf::Vector2f((Position.x + Size.x) * GameHandle->GameScreen.GetViewScale(), (Position.y) * GameHandle->GameScreen.GetViewScale());
    Lines[3].position = sf::Vector2f((Position.x) * GameHandle->GameScreen.GetViewScale(), (Position.y + Size.y) * GameHandle->GameScreen.GetViewScale());
    Lines[2].position = sf::Vector2f((Position.x + Size.x) * GameHandle->GameScreen.GetViewScale(), (Position.y + Size.y) * GameHandle->GameScreen.GetViewScale());

    GameHandle->GameScreen.Draw(Lines);

    Lines.setPrimitiveType(sf::Quads);
    if(!Area.IsButtonDown())
    {
        Lines[0].color = sf::Color(0, 0, 0, 0);
        Lines[1].color = sf::Color(0, 0, 0, 0);
        Lines[2].color = sf::Color(0, 0, 0, 50);
        Lines[3].color = sf::Color(0, 0, 0, 50);
    }
    else
    {
        Lines[0].color = sf::Color(0, 0, 0, 50);
        Lines[1].color = sf::Color(0, 0, 0, 50);
        Lines[2].color = sf::Color(0, 0, 0, 0);
        Lines[3].color = sf::Color(0, 0, 0, 0);
    }


    GameHandle->GameScreen.Draw(Lines);

    sf::VertexArray BorderLines(sf::LineStrip, 5);

    BorderLines[0].position = sf::Vector2f((Position.x) * GameHandle->GameScreen.GetViewScale(), (Position.y) * GameHandle->GameScreen.GetViewScale());
    BorderLines[4].position = sf::Vector2f((Position.x) * GameHandle->GameScreen.GetViewScale(), (Position.y) * GameHandle->GameScreen.GetViewScale());
    BorderLines[1].position = sf::Vector2f((Position.x + Size.x) * GameHandle->GameScreen.GetViewScale(), (Position.y) * GameHandle->GameScreen.GetViewScale());
    BorderLines[3].position = sf::Vector2f((Position.x) * GameHandle->GameScreen.GetViewScale(), (Position.y + Size.y) * GameHandle->GameScreen.GetViewScale());
    BorderLines[2].position = sf::Vector2f((Position.x + Size.x) * GameHandle->GameScreen.GetViewScale(), (Position.y + Size.y) * GameHandle->GameScreen.GetViewScale());

    BorderLines[0].color = sf::Color(20, 12, 9, 255);
    BorderLines[1].color = sf::Color(20, 12, 9, 255);
    BorderLines[2].color = sf::Color(20, 12, 9, 255);
    BorderLines[3].color = sf::Color(20, 12, 9, 255);
    BorderLines[4].color = sf::Color(20, 12, 9, 255);

    GameHandle->GameScreen.Draw(BorderLines);

    /// Trzeba ustawic ten tekst na srodku,czcionka a potem tfp::ClickableArea
    sf::Text TextTmp = Text.CreateTranslated(Name, FontList.FindFontWithName("Button"), Position + sf::Vector2f(Size.x / 2.0f, 2.0f), GameHandle->GameScreen.GetViewScale(), tfp::AlignCenter, Size.y * 0.7f);
    GameHandle->GameScreen.Draw(TextTmp);

    /// Odpalanie komendy
    if(Area.IsButtonPressed())
    {
        GameHandle->GameCommandBlock.RunCommand(Command);
        Area.SetActive(false);
    }
}

void tfp::Button::SetPosition(float PositionX, float PositionY)
{
    Position.x = PositionX;
    Position.y = PositionY;
    Area.SetPosition(Position);
}

void tfp::Button::Move(float PositionX, float PositionY)
{
    Position.x += PositionX;
    Position.y += PositionY;
    Area.SetPosition(Position);
}

void tfp::Button::SetSize(float Width, float Height)
{
    Size.x = Width;
    Size.y = Height;
    Area.SetSize(Size);
}

void tfp::Button::SetGameHandle(tfp::Game *Handle)
{
    GameHandle = Handle;
    Area.SetGameHandle(Handle);
}

void tfp::Button::SetCommand(std::string Command_)
{
    Command = Command_;
}

void tfp::Button::SetText(std::string Text_)
{
    Name = Text_;
}

void tfp::LoadingBar::Display()
{
    if(GameHandle == nullptr) return;
    sf::VertexArray Lines(sf::Quads, 4);

    Lines[0].color = UnderBarColor;
    Lines[1].color = UnderBarColor;
    Lines[2].color = UnderBarColor;
    Lines[3].color = UnderBarColor;

    Lines[0].position = sf::Vector2f((Position.x) * GameHandle->GameScreen.GetViewScale(), (Position.y) * GameHandle->GameScreen.GetViewScale());
    Lines[1].position = sf::Vector2f((Position.x + Size.x) * GameHandle->GameScreen.GetViewScale(), (Position.y) * GameHandle->GameScreen.GetViewScale());
    Lines[3].position = sf::Vector2f((Position.x) * GameHandle->GameScreen.GetViewScale(), (Position.y + Size.y) * GameHandle->GameScreen.GetViewScale());
    Lines[2].position = sf::Vector2f((Position.x + Size.x) * GameHandle->GameScreen.GetViewScale(), (Position.y + Size.y) * GameHandle->GameScreen.GetViewScale());

    GameHandle->GameScreen.Draw(Lines);

    if(MaxValue > 0)
    {
        Lines[0].color = BarColor;
        Lines[1].color = BarColor;
        Lines[2].color = BarColor;
        Lines[3].color = BarColor;

        Lines[1].position = sf::Vector2f((Position.x + Size.x * ((float) Value / (float) MaxValue)) * GameHandle->GameScreen.GetViewScale(), (Position.y) * GameHandle->GameScreen.GetViewScale());
        Lines[2].position = sf::Vector2f((Position.x + Size.x * ((float) Value / (float) MaxValue)) * GameHandle->GameScreen.GetViewScale(), (Position.y + Size.y) * GameHandle->GameScreen.GetViewScale());

        GameHandle->GameScreen.Draw(Lines);
    }

    if(BarMode == tfp::LoadingBar::None)
    {
        RenderText = "";
    }
    else if(BarMode == tfp::LoadingBar::PercentageMode)
    {
        RenderText = tfp::IntToString((Value * 100) / MaxValue) + '%';
    }
    else if(BarMode == tfp::LoadingBar::ValueMode)
    {
        RenderText = tfp::IntToString(Value);
    }
    else if(BarMode == tfp::LoadingBar::MaxValueMode)
    {
        RenderText = tfp::IntToString(Value) + '/' + tfp::IntToString(MaxValue);
    }
    else if(BarMode == tfp::LoadingBar::FullMode)
    {
        RenderText = tfp::IntToString(Value) + '/' + tfp::IntToString(MaxValue) + " (" + tfp::IntToString((Value * 100) / MaxValue) + "%)";
    }

    /// Trzeba ustawic ten tekst na srodku,czcionka a potem tfp::ClickableArea
    sf::Text TextTmp = Text.Create(RenderText, FontList.FindFontWithName("LoadingBar"), Position + sf::Vector2f(Size.x / 2.0f, 2.0f), GameHandle->GameScreen.GetViewScale(), tfp::AlignCenter, Size.y * 0.7f);
    GameHandle->GameScreen.Draw(TextTmp);

}

void tfp::LoadingBar::SetPosition(float PositionX, float PositionY)
{
    Position.x = PositionX;
    Position.y = PositionY;
}

void tfp::LoadingBar::Move(float PositionX, float PositionY)
{
    Position.x += PositionX;
    Position.y += PositionY;
}

void tfp::LoadingBar::SetSize(float Width, float Height)
{
    Size.x = Width;
    Size.y = Height;
}

void tfp::LoadingBar::SetGameHandle(tfp::Game *Handle)
{
    GameHandle = Handle;
}

void tfp::LoadingBar::SetValue(int Value_)
{
    Value = Value_;
}

void tfp::LoadingBar::SetMode(tfp::LoadingBar::Mode BarMode_)
{
    BarMode = BarMode_;
}

void tfp::LoadingBar::SetMaxValue(int MaxValue_)
{
    MaxValue = MaxValue_;
}

void tfp::LoadingBar::SetColor(sf::Color BarColor_)
{
    BarColor = BarColor_;
}

void tfp::LoadingBar::SetUnderColor(sf::Color UnderBarColor_)
{
    UnderBarColor = UnderBarColor_;
}

/// Input bar functions

void tfp::InputBar::Display()
{
    if(GameHandle == nullptr) return;
    sf::VertexArray Lines(sf::Quads, 4);

    Lines[0].color = UnderBarColor;
    Lines[1].color = UnderBarColor;
    Lines[2].color = UnderBarColor;
    Lines[3].color = UnderBarColor;

    Lines[0].position = sf::Vector2f((Position.x) * GameHandle->GameScreen.GetViewScale(), (Position.y) * GameHandle->GameScreen.GetViewScale());
    Lines[1].position = sf::Vector2f((Position.x + Size.x) * GameHandle->GameScreen.GetViewScale(), (Position.y) * GameHandle->GameScreen.GetViewScale());
    Lines[3].position = sf::Vector2f((Position.x) * GameHandle->GameScreen.GetViewScale(), (Position.y + Size.y) * GameHandle->GameScreen.GetViewScale());
    Lines[2].position = sf::Vector2f((Position.x + Size.x) * GameHandle->GameScreen.GetViewScale(), (Position.y + Size.y) * GameHandle->GameScreen.GetViewScale());

    GameHandle->GameScreen.Draw(Lines);

    if(Area.IsDisabled())
    {
        Lines[0].color = {127, 127, 127, 100};
        Lines[1].color = {127, 127, 127, 100};
        Lines[2].color = {127, 127, 127, 100};
        Lines[3].color = {127, 127, 127, 100};
        Lines.setPrimitiveType(sf::Quads);
        GameHandle->GameScreen.Draw(Lines);
    }
    else if(Area.IsActive())
    {
        Lines[0].color = {112, 141, 129, 255};
        Lines[1].color = {112, 141, 129, 255};
        Lines[2].color = {112, 141, 129, 255};
        Lines[3].color = {112, 141, 129, 255};
        Lines.setPrimitiveType(sf::Quads);
        GameHandle->GameScreen.Draw(Lines);
    }

    sf::VertexArray BorderLines(sf::LineStrip, 5);
    BorderLines[0].position = sf::Vector2f((Position.x) * GameHandle->GameScreen.GetViewScale(), (Position.y) * GameHandle->GameScreen.GetViewScale());
    BorderLines[1].position = sf::Vector2f((Position.x + Size.x) * GameHandle->GameScreen.GetViewScale(), (Position.y) * GameHandle->GameScreen.GetViewScale());
    BorderLines[3].position = sf::Vector2f((Position.x) * GameHandle->GameScreen.GetViewScale(), (Position.y + Size.y) * GameHandle->GameScreen.GetViewScale());
    BorderLines[2].position = sf::Vector2f((Position.x + Size.x) * GameHandle->GameScreen.GetViewScale(), (Position.y + Size.y) * GameHandle->GameScreen.GetViewScale());
    BorderLines[4].position = sf::Vector2f((Position.x) * GameHandle->GameScreen.GetViewScale(), (Position.y) * GameHandle->GameScreen.GetViewScale());

    BorderLines[0].color = {20, 12, 9, 255};
    BorderLines[1].color = {20, 12, 9, 255};
    BorderLines[2].color = {20, 12, 9, 255};
    BorderLines[3].color = {20, 12, 9, 255};
    BorderLines[4].color = {20, 12, 9, 255};
    GameHandle->GameScreen.Draw(BorderLines);

    RenderText = Area.GetText();
    if(RenderText == "")
    {
        // RenderText = PlaceHolder;
        sf::Text TextTmp;
        if(TranslatedPlaceHolder == L"")
            TextTmp = Text.CreateTranslated(PlaceHolder, FontList.FindFontWithName("InputBarPlaceHolder"), Position + sf::Vector2f(Size.x / 2.0f, 2.0f), GameHandle->GameScreen.GetViewScale(), tfp::AlignCenter, Size.y * 0.7f);
        else
        {
            TextTmp = Text.Create(TranslatedPlaceHolder, FontList.FindFontWithName("InputBarPlaceHolder"), Position + sf::Vector2f(Size.x / 2.0f, 2.0f), GameHandle->GameScreen.GetViewScale(), tfp::AlignCenter, Size.y * 0.7f);
        }

        GameHandle->GameScreen.Draw(TextTmp);
    }
    else
    {
        if((int) RenderText.size() >= MaximumCharacters)
            RenderText = RenderText.substr(RenderText.size() - MaximumCharacters/* - 1*/, MaximumCharacters);
        /// Trzeba ustawic ten tekst na srodku,czcionka a potem tfp::ClickableArea
        sf::Text TextTmp = Text.Create(RenderText, FontList.FindFontWithName("InputBar"), Position + sf::Vector2f(Size.x / 2.0f, 2.0f), GameHandle->GameScreen.GetViewScale(), tfp::AlignCenter, Size.y * 0.7f);
        GameHandle->GameScreen.Draw(TextTmp);
    }





}

void tfp::InputBar::SetPosition(float PositionX, float PositionY)
{
    Position.x = PositionX;
    Position.y = PositionY;
    Area.SetPosition(Position);
}

void tfp::InputBar::SetPlaceHolder(std::string Text)
{
    PlaceHolder = Text;
}

void tfp::InputBar::SetTranslatedPlaceHolder(std::wstring Text)
{
    TranslatedPlaceHolder = Text;
}

void tfp::InputBar::Move(float PositionX, float PositionY)
{
    Position.x += PositionX;
    Position.y += PositionY;
    Area.SetPosition(Position);
}

void tfp::InputBar::SetInputType(tfp::TextType InputType)
{
    Area.SetInputType(InputType);
}

void tfp::InputBar::SetSize(float Width, float Height, bool Relative)
{
    Size.x = Width;
    Size.y = Height;
    Area.SetSize(Size, Relative);
}

void tfp::InputBar::SetGameHandle(tfp::Game *Handle)
{
    GameHandle = Handle;
    Area.SetGameHandle(Handle);
}

void tfp::InputBar::SetMaxCharacters(int MaxCharacters)
{
    MaximumCharacters = MaxCharacters;
}

void tfp::InputBar::SetUnderColor(sf::Color UnderBarColor_)
{
    UnderBarColor = UnderBarColor_;
}
