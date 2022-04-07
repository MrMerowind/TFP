/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"

int main()
{
    #ifdef TFP_DEBUG
    std::fetestexcept(FE_ALL_EXCEPT);
    std::feclearexcept(FE_ALL_EXCEPT);
    #endif // TFP_DEBUG

    GameManager.CreateGame("menu");

    while(GameManager.IsAnyWindowOpen())
    {
        Clock.Restart();
        GameManager.RenderFrames();
        GameManager.DestroyClosedGames();
    }

    #ifdef TFP_DEBUG
    if(std::fetestexcept(FE_DIVBYZERO)) Debug.Error("Pole error occurred in an earlier floating-point operation");
    if(std::fetestexcept(FE_INEXACT)) Debug.Warning("Inexact result: rounding was necessary to store the result of an earlier floating-point operation");
    if(std::fetestexcept(FE_INVALID)) Debug.Warning("Domain error occurred in an earlier floating-point operation");
    if(std::fetestexcept(FE_OVERFLOW)) Debug.Error("The result of the earlier floating-point operation was too large to be representable");
    if(std::fetestexcept(FE_UNDERFLOW)) Debug.Error("The result of the earlier floating-point operation was subnormal with a loss of precision");
    #endif // TFP_DEBUG

    return 0;
}
