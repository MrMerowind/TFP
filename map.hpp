/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

/// Klasa mapy
namespace tfp
{
    class Map{
    private:
        /// Szerokosc
        int Width;
        /// Wysokosc
        int Height;
        /// Dwuwymiarowa tablica zawierajaca nazwy terenow [Wysokosc][Szerokosc]
        std::string **Terrain; /// Textury do odczytania w TerrainList
        tfp::SortedVector<tfp::Animation> ObjectList;
        /// Nazwa mapy
        std::string MapName;
        tfp::Game *GameHandle;
        /// Podglad zmienianego terenu
        std::string PreviewTerrainName;
        std::string PreviewTerrainNameBefore;
        sf::Vector2i PreviewStart;
        sf::Vector2i PreviewEnd;
        bool Preview;
        bool OnlySame;
        /// Podglad pojedynczego terenu
        std::string PreviewTerrainNameSingle;
        sf::Vector2i PreviewSinglePosition;
        bool PreviewSingle;
        /// Podglad obiektu
    public:
        bool ObjectPreview;
        sf::Vector2f ObjectPreviewPosition;
        std::string ObjectPreviewName;
    private:
        /// Stos zmian w mapie
        std::stack<tfp::TerrainPositionSwapSave> TerrainChangeStack;
        std::stack<tfp::TerrainPositionSwapSave> TerrainChangeStackRedo;
    public:
        /// Itemy na mapie
        std::vector <tfp::Item> ItemsOnGround;
    public:
        /// Konstruktor
        Map();
        /// Destruktor
        ~Map();
        /// Wczytywanie mapy z Maps/<MapName>.map
        bool LoadMap(std::string MapName);
        /// Zapisywanie mapy do Maps/<MapName>.map
        bool SaveMap(std::string MapName);
        /// Czyszczenie mapy
        void Unload();
        /// Zwraca szerokosc mapy
        const int &GetWidth() const;
        /// Zwraca wysokosc mapy
        const int &GetHeight() const;
        /// Zwraca rozmiar mapy w pixelach
        const sf::Vector2i GetPixelWidth();
        /// Zmienia rozmiar mapy
        void Resize(int Width, int Height);
        /// Zwraca czy mapa jest zaladowana
        const bool IsLoaded() const;
        /// Ustawia uchwyt gry
        void SetGameHandle(tfp::Game *Handle);
        /// Ustawianie terenu w danym miejscu
        void SetTerrain(std::string TerrainName, int PositionX, int PositionY);
        /// Ustawianie podgladu terenu w danym miejscu
        void SetTerrainPreview(std::string TerrainName, int PositionX, int PositionY);
        /// Ustawianie terenu w danym miejscu bez pauzy zapisu historii (do cofania)
        void SetTerrainNoPause(std::string TerrainName, int PositionX, int PositionY);
        /// Ustawia pauze w danym miejscu historii
        void SetTerrainPause();
        /// Ustawia prostokat terenu w danym miejscu
        void SetTerrainRect(std::string TerrainName, sf::Vector2i Start, sf::Vector2i End, bool OnlySameTerrain = false);
        /// Cofa ostatnie zmiany
        void UndoTerrainChanges();
        /// Cofa cofniecie ostatnich zmian
        void RedoTerrainChanges();
        /// Ustawia podglad prostokata terenu w danym miejscu
        void SetTerrainRectPreview(std::string TerrainName, sf::Vector2i Start, sf::Vector2i End, bool OnlySameTerrain = false);
        /// Wlacza lub wylacza podglad
        void SetTerrainRectPreview(bool State);
        /// Wlacza lub wylacza podglad
        void SetTerrainPreview(bool State);
        /// Ustawia nazwe mapy
        void SetMapName(std::string NewName);
        /// Zwraca nazwe mapy
        std::string GetMapName() const;
        /// Zwraca nazwe terenu na danej pozycji
        std::string GetTerrainName(int HorizontalPosition, int VerticalPosition);
        /// Zwraca nazwe terenu na danej pozycji bez podgladu
        std::string GetTerrainRealName(int HorizontalPosition, int VerticalPosition);
        /// Zwraca liste obiektow
        tfp::SortedVector<tfp::Animation> &GetObjectList();
        /// Wstawia obiekt na mape
        void AddObject(std::string Name, float PositionX, float PositionY);
        /// Usuwa obiekt na mapie
        void RemoveObject(float PositonX, float PositionY);
        /// Wlacza lub wylacza podglad stawianai obiektow
        void SetObjectPreview(bool State);
        /// Ustawia podglad obiektu
        void SetObjectPreview(std::string Name, int PositionX, int PositionY);
    };

}
#endif // MAP_HPP_INCLUDED
