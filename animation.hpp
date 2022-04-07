/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef ANIMATION_HPP_INCLUDED
#define ANIMATION_HPP_INCLUDED

namespace tfp
{
    class Gif
    {
    public:
        std::string GifName;
        std::string Folder;
        std::string GifPath;
        std::vector<sf::Texture> GifTexture;
        std::vector<sf::Texture> GifColliderTexture;
        std::vector<sf::Image> GifColliderImage;
        std::vector<sf::Image> GifImage;
        bool Collider;
        float SecondsPerFrame;
        int FrameWidth;
        int FrameHeight;
        int Frames;

        Gif();
        Gif(std::string GifName, std::string Folder);
        ~Gif();
        void Load(std::string GifName, std::string Folder);

    };

    class GifListClass
    {
    private:
        std::vector<tfp::Gif> List;
        std::string Folder;
        bool Loaded;
    public:
        /// Konstruktor
        GifListClass(std::string Folder = "ObjectAnimation");
        /// Destruktor
        ~GifListClass();
        /// Zwraca gif o podanej nazwie
        tfp::Gif &FindGifWithName(std::string GifName);
        /// Wczytuje wszystkie nazwy gifow
        void LoadGifFiles(tfp::Game *GameHandle);
        /// Czysci liste gifow
        void UnloadAll();
        /// Zwraca czy sa zaladowane
        bool IsLoaded();
        /// Zwraca liste gifow
        std::vector<tfp::Gif> &GetList();
    };

    class Animation
    {
    public:
        enum AnimationType{
            ObjectAnimation,
            SpellAnimation,
            CharacterAnimation,
            MobAnimation,
            SpecialObjectAnimation
        };
        bool operator<(tfp::Animation &Right);
        bool operator<=(tfp::Animation &Right);
        bool operator>(tfp::Animation &Right);
        bool operator>=(tfp::Animation &Right);
        bool operator==(tfp::Animation &Right);
        bool operator!=(tfp::Animation &Right);
    public:
        std::string Name;
        float TimeRunning;
        sf::Vector2f Position;
        sf::Vector2f Size;
        int PositionZ;
        AnimationType Type;

    public:
        /// Konstruktor
        Animation();
        /// Konstruktor kopiujacy
        Animation(tfp::Animation &Right);
        /// Konstruktor uruchamiajacy funkcje wczytania animacji do GifList
        Animation(std::string AnimationName, AnimationType Type, float PositionX = 0, float PositionY = 0);
        /// Destruktor
        ~Animation();
        /// Wczytuje animacje o nazwie z GifList
        void LoadAnimation(std::string AnimationName, AnimationType Type);
        /// Zwraca teksture animacji. Jako parametry podane sa miniony czas w sekundach, predkosc animacji, ktora klatke wyswietlic (-1 oznacza wyliczona)
        sf::Texture &GetTexture(float DeltaTime, float AnimationSpeed = 1.0f, int Frame = -1);
        /// Zwraca obraz kolidera do sprawdzania kolizji
        sf::Image &GetColiderImage(float DeltaTime, float AnimationSpeed = 1.0f, int Frame = -1);
        /// Restartuje animacje
        void Restart();
    };


}

#endif // ANIMATION_HPP_INCLUDED
