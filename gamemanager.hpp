/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef GAMEMANAGER_HPP_INCLUDED
#define GAMEMANAGER_HPP_INCLUDED

namespace tfp
{
    class GameManagerClass
    {
    private:
        std::vector<tfp::Game*> GameList;
        int FramerateLimit;
        bool VerticalSync;
    public:
        /// Konstruktor
        GameManagerClass();
        /// Destruktor
        ~GameManagerClass();
        /// Zwraca czy jakies okno gry jest otwarte
        const bool IsAnyWindowOpen() const;
        /// Tworzenie nowej gry
        void CreateGame(std::string Option = "game", std::string Command = "");
        /// Zwraca ile gier jest otwartych
        const int GamesOpen() const;
        /// Zwraca gre o indexie
        tfp::Game &GetGame(unsigned Index) const;
        /// Renderuje okna wszystkich gier
        void RenderFrames();
        /// Ustawia limit klatek
        void SetFrameLimit(int Frames);
        /// Zwraca limit klatek
        const int GetFrameLimit() const;
        /// Zwraca czy vertical sync jest wlaczony
        bool GetVerticalSync();
        /// Wlacza lub wylacza vertical sync
        void SetVerticalSync(bool State);
        /// Usuwa wylaczone gry
        void DestroyClosedGames();
        /// Resetuje tytuly okien
        void ResetWindowTitles();
    };

}


#endif // GAMEMANAGER_HPP_INCLUDED
