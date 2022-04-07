/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef CLOCK_HPP_INCLUDED
#define CLOCK_HPP_INCLUDED

namespace tfp
{

    class ClockClass
    {
    private:
        float DeltaTime;
        sf::Clock ClockClock;
    public:
        /// Konstruktor
        ClockClass();
        /// Destruktor
        ~ClockClass();
        /// Restartuje zegar
        void Restart();
        /// Zwraca miniony czas w sekundach
        const float GetDeltaTime() const;

    };



}

#endif // CLOCK_HPP_INCLUDED
