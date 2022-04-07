/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"

sf::Sprite &tfp::SpriteCreator::Create(const sf::Texture &Texture, int PositionX, int PositionY, float Scale, float Scale2, float WidthScale, float HeightScale)
{
    if(Scale2 == -1.0f) Scale2 = Scale;
    Object.setTexture(Texture, true);
    Object.setPosition(PositionX * Scale, PositionY * Scale2);
    Object.setScale(sf::Vector2f(Scale * WidthScale, Scale2 * HeightScale));
    return Object;
}

sf::Sprite &tfp::SpriteCreator::Create(const sf::Texture &Texture, sf::Rect<int> TextureRectangle, int PositionX, int PositionY, float Scale, float Scale2, float WidthScale, float HeightScale)
{
    if(Scale2 == -1.0f) Scale2 = Scale;
    Object.setTexture(Texture, false);
    Object.setTextureRect(TextureRectangle);
    Object.setPosition(PositionX * Scale, PositionY * Scale2);
    Object.setScale(sf::Vector2f(Scale * WidthScale, Scale2 * HeightScale));
    return Object;
}
