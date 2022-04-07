/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef GENERATOR_HPP_INCLUDED
#define GENERATOR_HPP_INCLUDED

namespace tfp
{
    class GeneratorClass
    {
    public:
        GeneratorClass(); ///< Constructor
        ~GeneratorClass(); ///< Destructor
        int RandomInt(int Min, int Max); ///< Generates random int in a given range
        float RandomFloat(float Min, float Max); ///< Generates random float in a given range
        float RandomFloat(); ///< Generates random float in range [0,1]
        bool RandomBool(int Chance, int OutOf); ///< Generates random bool with a given chance
    };
}

#endif // GENERATOR_HPP_INCLUDED
