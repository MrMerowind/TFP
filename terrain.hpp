/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED

namespace tfp
{
    struct Terrain
    {
        std::string Name;
        std::string TexturePath;
        sf::Vector2i TexturePosition;
        float MovingSpeed;
        bool Colider;
        sf::Texture Texture;
        sf::Image Image;
        sf::Vector2f TextureBufferPosition;
        Terrain();
        ~Terrain();
    };

    class TerrainListClass
    {
    private:
        std::vector<Terrain> TerrainArray;
        sf::Texture SelectedTerrainTexture;
        bool TerrainNamesLoaded;
        /// Wczytuje dane terenu
        const bool LoadTerrain(std::string TerrainName);
        sf::Image TerrainImageBuffer;
        sf::Texture TerrainTextureBuffer;
        bool GraphicDriverTerrainLoadingBoost;
    public:
        /// Konstruktor
        TerrainListClass();
        /// Destruktor
        ~TerrainListClass();
        /// Pobieranie predkosci na terenie
        const tfp::Terrain &FindTerrainWithName(std::string TerrainName);
        /// Zwalnianie pamieci podreczniej
        void UnloadAll();
        /// Wczytuje wszystkie nazwy terenow
        void LoadAllTerrains(tfp::Game *GameHandle);
        /// Zwraca liste wszystkich nazw terenow
        std::vector<Terrain> &GetTerrainArray();
        ///  Zwraca czy lista wszystkich nazw terenow jest zaladowana
        bool IsAllTerrainLoaded();
        /// Zwraca teksture wybranego terenu
        sf::Texture &GetSelectedTerrainTexture();
        /// Zwraca buffer ze wszystkimi teksturami
        sf::Texture &GetTextureBuffer();
        /// Is graphic boost enabled
        bool IsGraphicDriverTerrainLoadingBoostEnabled();
    };
}

#endif // TERRAIN_H_INCLUDED
