/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"

tfp::TerrainPositionSwapSave::TerrainPositionSwapSave(sf::Vector2i Position_, std::string Before_, std::string After_)
{
    Position = Position_;
    Before = Before_;
    After = After_;
    Pause = false;
}

tfp::TerrainPositionSwapSave::TerrainPositionSwapSave()
{
    Position = sf::Vector2i(0, 0);
    Before = "Pause";
    After = "Pause";
    Pause = true;
}
