/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef COMMANDBLOCK_HPP_INCLUDED
#define COMMANDBLOCK_HPP_INCLUDED

namespace tfp
{
    class CommandBlock
    {
    private:
        /// Wskaznik na gre
        tfp::Game *GameHandle;
        /// Lista komend dla menedzera gier
        std::queue<std::string> GameManagerCommandList;
    public:
        /// Konstruktor
        CommandBlock();
        /// Destruktor
        ~CommandBlock();
        /// Ustawia wskaznik na gre ktora obsluguje
        void SetGameHandle(tfp::Game *Handle);
        /// Wykonuje podana komende
        void RunCommand(std::string Command);
        /// Zwraca komende dla menedzera gier
        std::string GetGameManagerCommand();
        /// Zwraca czy lista komend dla menedzera jest pusta
        const bool IsGameManagerCommandListEmpty() const;
    };
}

#endif // COMMANDBLOCK_HPP_INCLUDED
