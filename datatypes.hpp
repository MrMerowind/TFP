/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef DATATYPES_HPP_INCLUDED
#define DATATYPES_HPP_INCLUDED

namespace tfp
{
    struct TerrainPositionSwapSave
    {
        sf::Vector2i Position;
        std::string Before;
        std::string After;
        bool Pause;
        /// Konstruktor zapisu terenu
        TerrainPositionSwapSave(sf::Vector2i Position, std::string Before, std::string After);
        /// Konstruktor pauzy zapisu
        TerrainPositionSwapSave();
    };

    enum Alignment
    {
        AlignLeft,
        AlignCenter,
        AlignRight
    };

    enum Direction
    {
        DirTop,
        DirDown,
        DirLeft,
        DirRight
    };

    enum TextType
    {
        TextTypeString,
        TextTypeInt,
        TextTypeFloat,
        TextTypeKey
    };
}

#endif // DATATYPES_HPP_INCLUDED
