/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"

const sf::Text &tfp::TextCreator::Create(std::string TextString, const tfp::Font &TextFont, sf::Vector2f Position, float Scale, tfp::Alignment Align, int CharacterSize_)
{
    Position.x *= Scale;
    Position.y *= Scale;

    Object.setFont(TextFont.FontData);
    Object.setString(TextString);
    if(CharacterSize_ == -1) Object.setCharacterSize(tfp::RoundToInt(TextFont.CharacterSize * Scale));
    else Object.setCharacterSize(tfp::RoundToInt(CharacterSize_ * Scale));
    Object.setFillColor(TextFont.FontColor);
    Object.setOutlineColor(TextFont.FontOutlineColor);
    Object.setOutlineThickness(TextFont.OutlineThickness);
    if(TextFont.Style == "Underlined") Object.setStyle(sf::Text::Style::Underlined);
    else if(TextFont.Style == "Regular") Object.setStyle(sf::Text::Style::Regular);
    else if(TextFont.Style == "Italic") Object.setStyle(sf::Text::Style::Italic);
    else if(TextFont.Style == "StrikeThrough") Object.setStyle(sf::Text::Style::StrikeThrough);
    else Object.setStyle(sf::Text::Style::Regular);

    if(Align == tfp::AlignLeft) Object.setPosition(Position);
    else if(Align == tfp::AlignCenter) Object.setPosition(sf::Vector2f(Position.x - (Object.getGlobalBounds().width / 2.0f), Position.y));
    else if(Align == tfp::AlignRight) Object.setPosition(sf::Vector2f(Position.x - Object.getGlobalBounds().width, Position.y));

    Object.setPosition({tfp::RoundToFloat(Object.getPosition().x), tfp::RoundToFloat(Object.getPosition().y)});

    return Object;
}

const sf::Text &tfp::TextCreator::Create(std::wstring TextString, const tfp::Font &TextFont, sf::Vector2f Position, float Scale, tfp::Alignment Align, int CharacterSize_)
{
    Position.x *= Scale;
    Position.y *= Scale;

    Object.setFont(TextFont.FontData);
    sf::String SfmlString(TextString);
    Object.setString(SfmlString);
    if(CharacterSize_ == -1) Object.setCharacterSize(tfp::RoundToInt(TextFont.CharacterSize * Scale));
    else Object.setCharacterSize(tfp::RoundToInt(CharacterSize_ * Scale));
    Object.setFillColor(TextFont.FontColor);
    Object.setOutlineColor(TextFont.FontOutlineColor);
    Object.setOutlineThickness(TextFont.OutlineThickness);
    if(TextFont.Style == "Underlined") Object.setStyle(sf::Text::Style::Underlined);
    else if(TextFont.Style == "Regular") Object.setStyle(sf::Text::Style::Regular);
    else if(TextFont.Style == "Italic") Object.setStyle(sf::Text::Style::Italic);
    else if(TextFont.Style == "StrikeThrough") Object.setStyle(sf::Text::Style::StrikeThrough);
    else Object.setStyle(sf::Text::Style::Regular);

    if(Align == tfp::AlignLeft) Object.setPosition(Position);
    else if(Align == tfp::AlignCenter) Object.setPosition(sf::Vector2f(Position.x - (Object.getGlobalBounds().width / 2.0f), Position.y));
    else if(Align == tfp::AlignRight) Object.setPosition(sf::Vector2f(Position.x - Object.getGlobalBounds().width, Position.y));

    Object.setPosition({tfp::RoundToFloat(Object.getPosition().x), tfp::RoundToFloat(Object.getPosition().y)});

    return Object;
}

const sf::Text &tfp::TextCreator::CreateTranslated(std::string TextString, const tfp::Font &TextFont, sf::Vector2f Position, float Scale, tfp::Alignment Align, int CharacterSize_)
{
    Position.x *= Scale;
    Position.y *= Scale;

    Object.setFont(TextFont.FontData);
    sf::String SfmlString(Language.Translate(TextString));
    Object.setString(SfmlString);
    if(CharacterSize_ == -1) Object.setCharacterSize(tfp::RoundToInt(TextFont.CharacterSize * Scale));
    else Object.setCharacterSize(tfp::RoundToInt(CharacterSize_ * Scale));
    Object.setFillColor(TextFont.FontColor);
    Object.setOutlineColor(TextFont.FontOutlineColor);
    Object.setOutlineThickness(TextFont.OutlineThickness);
    if(TextFont.Style == "Underlined") Object.setStyle(sf::Text::Style::Underlined);
    else if(TextFont.Style == "Regular") Object.setStyle(sf::Text::Style::Regular);
    else if(TextFont.Style == "Italic") Object.setStyle(sf::Text::Style::Italic);
    else if(TextFont.Style == "StrikeThrough") Object.setStyle(sf::Text::Style::StrikeThrough);
    else Object.setStyle(sf::Text::Style::Regular);

    if(Align == tfp::AlignLeft) Object.setPosition(Position);
    else if(Align == tfp::AlignCenter) Object.setPosition(sf::Vector2f(Position.x - (Object.getGlobalBounds().width / 2.0f), Position.y));
    else if(Align == tfp::AlignRight) Object.setPosition(sf::Vector2f(Position.x - Object.getGlobalBounds().width, Position.y));

    Object.setPosition({tfp::RoundToFloat(Object.getPosition().x), tfp::RoundToFloat(Object.getPosition().y)});

    return Object;
}

