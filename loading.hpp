/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef LOADING_HPP_INCLUDED
#define LOADING_HPP_INCLUDED

namespace tfp
{
    class LoadingScreenClass
    {
    private:
        std::string LoadingText;
        float Percentage;
    public:
        /// Konstruktor
        LoadingScreenClass();
        /// Destruktor
        ~LoadingScreenClass();
        /// Draws and displays immediately on screen
        void DisplayOnScreen(std::string Info, tfp::Game *Handle, float Percentage = -1.0f);
        /// Only draws loading screen and waits to be displayed
        void Draw(std::string Info, tfp::Game *Handle, float Percentage = -1.0f);
    };
}

#endif // LOADING_HPP_INCLUDED
