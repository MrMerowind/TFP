/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef SPRITE_HPP_INCLUDED
#define SPRITE_HPP_INCLUDED

namespace tfp
{

    class SpriteCreator
    {
    private:
        sf::Sprite Object;
    public:
        /// Tworzy sprite i zwraca go do wyrenderowania
        sf::Sprite &Create(const sf::Texture &Texture, int PositionX, int PositionY, float Scale = 1.0f, float Scale2 = -1.0f, float WidthScale = 1.0f, float HeightScale = 1.0f);
        /// Tworzy sprite i zwraca go do wyrenderowania
        sf::Sprite &Create(const sf::Texture &Texture, sf::Rect<int> TextureRectangle, int PositionX, int PositionY, float Scale = 1.0f, float Scale2 = -1.0f, float WidthScale = 1.0f, float HeightScale = 1.0f);
    };

}

#endif // SPRITE_HPP_INCLUDED
