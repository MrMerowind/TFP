#ifndef BACKGROUNDIMAGE_HPP_INCLUDED
#define BACKGROUNDIMAGE_HPP_INCLUDED

namespace tfp
{

    class BackgroundImageClass
    {
        struct Background
        {
            sf::Texture Texture;
            std::string Name;
            int Width;
            int Height;
            bool Loaded;
        };
        private:
            std::vector<tfp::BackgroundImageClass::Background> List;
            bool Loaded;
        public:
            BackgroundImageClass();
            ~BackgroundImageClass();
            void LoadAll(tfp::Game *GameHandle);
            void UnloadAll();
            std::vector<tfp::BackgroundImageClass::Background> &GetBackgroundList();
            /// tfp::BackgroundImageClass::Background &FindBackgroundWithName(std::string BackgroundName); ///< \deprecated Nie uzywac tego bo sie zcrashuje jak sie nie wczyta zadne tlo
            bool IsLoaded();
            void Draw(std::string BackgroundName, tfp::Game *GameHandle);
    };

}



#endif // BACKGROUNDIMAGE_HPP_INCLUDED
