/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef DEBUG_HPP_INCLUDED
#define DEBUG_HPP_INCLUDED

namespace tfp
{
    class DebugClass{
    private:
        bool ShowError;
        bool ShowInfo;
        bool ShowWarning;
        bool ShowCommand;
        bool LogError;
        bool LogInfo;
        bool LogWarning;
        bool LogCommand;
        bool DontRepeat;
        std::string LogPath;
        std::fstream DebugLogFile;
        std::string LastError;
        int NextDebugMessageID;
        int DebugMessageHistoryLimit;
        struct DebugMessageHistory
        {
            int Number;
            std::string Information;
            DebugMessageHistory(std::string Information, int Number);
        };
        std::vector<DebugMessageHistory> DebugMessageHistoryList;
    public:
        /// Wiadomosc o bledzie
        void Error(std::string Message);
        /// Informacja do testow
        void Info(std::string Message);
        /// Wiadomosc o ostrzezeniu
        void Warning(std::string Message);
        /// Wiadomosc o uzytej komendzie
        void Command(std::string Message);
        /// Zapisuje wiadomosc do logu
        void Log(std::string Text);
        /// Dodaje wiadomosc do historii
        void AddToHistory(std::string Text);
        /// Zwraca wiadomisc o numerze
        std::string GetDebugMessage(int Number);
        /// Zwraca czy dany numer wiadomosci jest dostepny
        const bool IsDebugMessageAvailiable(int Number);
        /// Zwraca najnizszsy numer wiadomosci
        int WhatIsTheLowestDebugMessageNumber();
        /// Konstruktor
        DebugClass();
        /// Destruktor
        ~DebugClass();

    };

}

/// Prosze uzywac tylko obiekt Debug w #include "globalobjects.hpp"


#endif // DEBUG_HPP_INCLUDED
