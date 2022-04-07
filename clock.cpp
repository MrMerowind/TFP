/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"

tfp::ClockClass::ClockClass()
{
    ClockClock.restart();
}

tfp::ClockClass::~ClockClass() {}

void tfp::ClockClass::Restart()
{
    DeltaTime = ClockClock.restart().asSeconds();
}

const float tfp::ClockClass::GetDeltaTime() const
{
    return DeltaTime;
}
