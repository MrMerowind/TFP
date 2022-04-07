/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef TEXT_HPP_INCLUDED
#define TEXT_HPP_INCLUDED

namespace tfp
{

    class TextCreator
    {
    private:
        sf::Text Object;
    public:
        /// Tworzy tekst i zwraca do wyrenderowania
        const sf::Text &Create(std::string TextString, const tfp::Font &TextFont, sf::Vector2f Position, float Scale = 1.0f, tfp::Alignment Align = tfp::AlignLeft, int CharacterSize_ = -1);
        /// Tworzy tekst i zwraca do wyrenderowania
        const sf::Text &Create(std::wstring TextString, const tfp::Font &TextFont, sf::Vector2f Position, float Scale = 1.0f, tfp::Alignment Align = tfp::AlignLeft, int CharacterSize_ = -1);
        /// Tworzy tekst z lista autorow i zwraca do wyrenderowania
            /// Juz inaczej jest to zrobione
        // const sf::Text &CreateAuthors(sf::Vector2f Position, float Scale = 1.0f, tfp::Alignment Align = tfp::AlignLeft, int CharacterSize_ = -1);
        /// Tworzy i zwraca przetlumaczony tekst do wyrenderowania
        const sf::Text &CreateTranslated(std::string TextString, const tfp::Font &TextFont, sf::Vector2f Position, float Scale = 1.0f, tfp::Alignment Align = tfp::AlignLeft, int CharacterSize_ = -1);
    };

}

#endif // TEXT_HPP_INCLUDED
