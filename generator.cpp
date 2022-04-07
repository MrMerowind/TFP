/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"

tfp::GeneratorClass::GeneratorClass()
{
    srand(time(nullptr));
}

tfp::GeneratorClass::~GeneratorClass()
{

}

int tfp::GeneratorClass::RandomInt(int Min, int Max)
{
    if(Min > Max) std::swap(Min, Max);
    return (rand()%(Max - Min + 1) + Min);
}

float tfp::GeneratorClass::RandomFloat(float Min, float Max)
{
    float Return = Max - Min;
    Return *= RandomFloat();
    Return += Min;
    return Return;
}

float tfp::GeneratorClass::RandomFloat()
{
    if(RandomBool(1, 10000) && RandomBool(1, 10000) && RandomBool(1, 10000) && RandomBool(1, 10000) && RandomBool(1, 10000) && RandomBool(1, 1000))
    {
        return 1.0f;
    }

    float Return = 0.0f;
    int Random = 0;

    for(int i = 0; i < 5; i++)
    {
        Random = RandomInt(0, 9999);
        Return += Random;
        Return /= 10000;
    }

    Random = RandomInt(0, 999);
    Return += Random;
    Return /= 1000;

    return Random;
}

bool tfp::GeneratorClass::RandomBool(int Chance, int OutOf)
{
    int Random = RandomInt(0, OutOf - 1);
    if(Random < Chance) return true;
    else return false;
}
