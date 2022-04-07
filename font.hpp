/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef FONT_HPP_INCLUDED
#define FONT_HPP_INCLUDED

namespace tfp
{
    struct Font
    {
        std::string Name;
        std::string FontPath;
        sf::Font FontData;
        sf::Color FontColor;
        sf::Color FontOutlineColor;
        float OutlineThickness;
        int CharacterSize;
        std::string Style;
        Font();
        ~Font();
    };

    class FontListClass
    {
        bool LoadedAll;
        std::vector<Font> FontArray;
    public:
        /// Konstruktor
        FontListClass();
        /// Destruktor
        ~FontListClass();
        /// Zwraca czcionke o podanej nazwie
        const tfp::Font &FindFontWithName(std::string FontName);
        /// Wczytuje czcionke
        const bool LoadFont(std::string FontName);
        /// Wczytuje informacje o czcionce
        const bool LoadFontData(std::string FontName);
        /// Wczytuje wszystkie informacje o czcionkach
        void LoadAllFonts(tfp::Game *GameHandle);
        /// Czysci liste czcionek
        void UnloadAll();
        /// Zwraca czy wszystkie czcionki sa zaladowane
        bool IsAllLoaded();
    };

}

#endif // FONT_HPP_INCLUDED
