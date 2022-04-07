/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef INTERFACEFFECTS_HPP_INCLUDED
#define INTERFACEFFECTS_HPP_INCLUDED

namespace tfp
{
    namespace specialeffects
    {
        class Rain
        {
        private:
            struct Drop
            {
                sf::Vector2f Position;
                float Length;
                float LifeSpan;
                int RandomTilt;
                float AliveFor;
            };
            std::vector<tfp::specialeffects::Rain::Drop> DropList;
            std::vector<sf::Vertex> VertexList;
            sf::Vertex RainDropVertexUp;
            sf::Vertex RainDropVertexDown;
            tfp::Game *GameHandle;
            int Density;
            float TimeBuffer;
            float CreationSpeed;
            float FallSpeed;
            void Create();
        public:
            /// Constructor
            Rain();
            /// Destructor
            ~Rain();
            /// Sets game handle
            void SetGameHandle(tfp::Game *Handle);
            /// Render rain
            void Display();
            /// Sets rain density (how much rain drops spawns in a given time)
            void SetDensity(int Value);
            /// Sets time betwen creating new rain drops
            void SetCreationSpeed(float TimeBetweenCreation);
            /// Sets speed of falling rain
            void SetFallSpeed(float Speed);
        };

        class Snow
        {
        private:
            struct Drop
            {
                sf::Vector2f Position;
                float Length;
                float LifeSpan;
                int RandomTilt;
                float AliveFor;
            };
            std::vector<tfp::specialeffects::Snow::Drop> DropList;
            std::vector<sf::Vertex> VertexList;
            sf::Vertex SnowDropVertex;
            tfp::Game *GameHandle;
            int Density;
            float TimeBuffer;
            float CreationSpeed;
            float FallSpeed;
            void Create();
        public:
            /// Constructor
            Snow();
            /// Destructor
            ~Snow();
            /// Sets game handle
            void SetGameHandle(tfp::Game *Handle);
            /// Render rain
            void Display();
            /// Sets rain density (how much rain drops spawns in a given time)
            void SetDensity(int Value);
            /// Sets time betwen creating new rain drops
            void SetCreationSpeed(float TimeBetweenCreation);
            /// Sets speed of falling rain
            void SetFallSpeed(float Speed);
        };

        class Night
        {
        private:
            tfp::Game *GameHandle;
            int Darkness;
            int DarknessOpacity;
            bool Lighter;
        public:
            /// Constructor
            Night();
            /// Destructor
            ~Night();
            /// Sets game handle
            void SetGameHandle(tfp::Game *Handle);
            /// Render night effect
            void Display();
            /// Sets how dark is night
            void SetDarkness(int Value);
            /// Sets temporary darkness that is rendered if lightning is enabled
            void SetDarknessOpacity(int Value);
            /// Turns on/off lighter (area on the middle that is not affected by night)
            void SetLighter(bool State);
            /// Returns if lighter is on
            bool IsLighterOn();
        };

        class Storm
        {
        private:
            tfp::Game *GameHandle;
            sf::Vector2i LightningTimeSpan;
            float TimeBuffer;
            float LightningTime;
            float LightningDuration;
            float NextLightning;
        public:
            /// Constructor
            Storm();
            /// Destructor
            ~Storm();
            /// Sets game handle
            void SetGameHandle(tfp::Game *Handle);
            /// Render night effect
            void Display();
            /// Sets time required to wait for next lightning
            void SetLightningTimeSpan(int Min, int Max);
        };

    }
}

#endif // INTERFACEFFECTS_HPP_INCLUDED
