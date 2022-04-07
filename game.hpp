/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

namespace tfp
{

    class Game{
    private:
        std::string GameType;
        std::vector<sf::Vertex> MapVertexBuffer;
        sf::Vertex MapVertexPoint;
        sf::Vector2f PreviousCameraPosition;
        float NotActiveFor;
    public:
        bool TerrainChanged;
    private:
        /// Renderuje postacie
        void DrawCharacters();
        void DrawCharacters(tfp::SortedVector<tfp::Animation> &ObjectList, bool &CharactersDrawn, int Index);
        void DrawSpells();
        void MoveCameraOnControledPlayer();
    public:
        /// Konstruktor
        Game(std::string GameType);
        /// Destruktor
        ~Game();
        /// Nasza postac
        tfp::Player ControlledPlayer;
        /// Nasza animacja postaci
        tfp::CharacterAnimation ControlledPlayerAnimation;
        /// Myszka
        tfp::Mouse GameMouse;
        /// Czasy wykonywania funkcji
        tfp::FunctionTimeClass GameFunctionTimes;
        /// Ekran
        tfp::Screen GameScreen;
        /// Interfejs
        tfp::Interface GameInterface;
        /// Mapa
        tfp::Map GameMap;
        /// Kamera
        tfp::Camera GameCamera;
        /// Blok komend
        tfp::CommandBlock GameCommandBlock;
        /// Klient
        tfp::NetworkClient GameNetworkClient;
        /// Server
        tfp::NetworkServer GameNetworkServer;
        /// Renderowanie okna gry
        void RenderFrame();
        /// Renderuje okno gry do poki nie zostanie zamkniete
        void LoopFrames();
        /// Renderuje teren
        void DrawTerrain();
        /// Renderuje interface
        void DrawInterface();
        /// Sprawdza eventy okna
        void Events();
        /// Ustawia typ gry
        void SetGameType(std::string GameType);
        /// Zwraca typ gry
        const std::string &GetGameType() const;
        /// Renderuje obiekty i postacie
        void DrawObjects();
    };
}


#endif // GAME_HPP_INCLUDED
