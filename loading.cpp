/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"


tfp::LoadingScreenClass::LoadingScreenClass()
    :LoadingText("Initializing loading...") {}

tfp::LoadingScreenClass::~LoadingScreenClass() {}

void tfp::LoadingScreenClass::DisplayOnScreen(std::string Info, tfp::Game *Handle, float Percentage_)
{
    LoadingText = Info;
    Handle->GameScreen.GetRenderWindowHandle().clear(sf::Color(20, 12, 9));
    Percentage = Percentage_;

    std::string PercentageText;
    if(Percentage >= 0) PercentageText = tfp::FloatToString(Percentage) + "%";
    else PercentageText = "";

    sf::Text TextTmp = Text.CreateTranslated(LoadingText, FontList.FindFontWithName("LoadingScreen"), sf::Vector2f(0.0f, Handle->GameScreen.GetOriginalViewSize().y * 0.8f), Handle->GameScreen.GetViewScale());
    sf::Text TextTmp2 = Text.Create(" " + PercentageText, FontList.FindFontWithName("LoadingScreen"), sf::Vector2f(0.0f, Handle->GameScreen.GetOriginalViewSize().y * 0.8f), Handle->GameScreen.GetViewScale());
    TextTmp.setPosition(sf::Vector2f(((Handle->GameScreen.GetOriginalViewSize().x - TextTmp.getLocalBounds().width - TextTmp2.getLocalBounds().width) / 2.0f) * Handle->GameScreen.GetViewScale(), TextTmp.getPosition().y));
    TextTmp2.setPosition(sf::Vector2f(((Handle->GameScreen.GetOriginalViewSize().x + TextTmp.getLocalBounds().width - TextTmp2.getLocalBounds().width) / 2.0f) * Handle->GameScreen.GetViewScale(), TextTmp.getPosition().y));
    Handle->GameScreen.Draw(TextTmp);
    Handle->GameScreen.Draw(TextTmp2);
    Handle->GameScreen.GetRenderWindowHandle().display();

}


void tfp::LoadingScreenClass::Draw(std::string Info, tfp::Game *Handle, float Percentage_)
{
    LoadingText = Info;
    Handle->GameScreen.GetRenderWindowHandle().clear(sf::Color(20, 12, 9));
    Percentage = Percentage_;

    std::string PercentageText;
    if(Percentage >= 0) PercentageText = tfp::FloatToString(Percentage) + "%";
    else PercentageText = "";

    sf::Text TextTmp = Text.CreateTranslated(LoadingText, FontList.FindFontWithName("LoadingScreen"), sf::Vector2f(0.0f, Handle->GameScreen.GetOriginalViewSize().y * 0.8f), Handle->GameScreen.GetViewScale());
    sf::Text TextTmp2 = Text.Create(" " + PercentageText, FontList.FindFontWithName("LoadingScreen"), sf::Vector2f(0.0f, Handle->GameScreen.GetOriginalViewSize().y * 0.8f), Handle->GameScreen.GetViewScale());
    TextTmp.setPosition(sf::Vector2f(((Handle->GameScreen.GetOriginalViewSize().x - TextTmp.getLocalBounds().width - TextTmp2.getLocalBounds().width) / 2.0f) * Handle->GameScreen.GetViewScale(), TextTmp.getPosition().y));
    TextTmp2.setPosition(sf::Vector2f(((Handle->GameScreen.GetOriginalViewSize().x + TextTmp.getLocalBounds().width - TextTmp2.getLocalBounds().width) / 2.0f) * Handle->GameScreen.GetViewScale(), TextTmp.getPosition().y));
    Handle->GameScreen.Draw(TextTmp);
    Handle->GameScreen.Draw(TextTmp2);

}
