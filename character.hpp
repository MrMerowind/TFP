/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

namespace tfp
{
    class CharacterStats{
    public:
        /// Podstawowe
        int MinimumDamage;
        int MaximumDamage;
        int Strenght;
        int Vitality;
        int Dexterity;
        int Intelligence;
        float AttackSpeed;
        float MovementSpeed;
        float LifeSteal;
        /// Elementy
        int IceElement;
        int DarknessElement;
        int FireElement;
        int WaterElement;
        int LightElement;
        int EarthElement;
        /// Resy
        int IceResistance;
        int DarknessResistance;
        int FireResistance;
        int WaterResistance;
        int LightResistance;
        int EarthResistance;
    public:
        CharacterStats();
    };

    class Player : public CharacterStats
    {
    private:
        int ID;
        std::string Name;
        std::string SkinName;
        sf::Vector2f Position;
        sf::Vector2f Destination;
        int Experience;
        int Level;
        sf::Vector2i InventorySize;
    public:
        std::vector<tfp::Item> InventoryItemList;
        // Statystyki dziedziczone z CharacterStats
    public:
        /// Konstruktor
        Player();
        /// Destruktor
        ~Player();
        /// Ustawia id gracza
        void SetID(int ID);
        /// Zwraca id gracza
        int GetID();
        /// Ustawia nazwe gracza
        void SetName(std::string Name);
        /// Zwraca nazwe gracza
        std::string GetName();
        /// Ustawia nazwe skina
        void SetSkinName(std::string SkinName);
        /// Zwraca nazwe skina
        std::string GetSkinName();
        /// Ustawia pozycje gracza
        void SetPosition(sf::Vector2f Position);
        /// Zwraca pozycje gracza
        sf::Vector2f GetPosition();
        /// Ustawia pozycje docelowa gracza
        void SetDestination(sf::Vector2f Destination);
        /// Zwraca pozycje docelowa gracza
        sf::Vector2f GetDestination();
        /// Ustawia posiom
        void SetLevel(int Level);
        /// Zwraca poziom
        int GetLevel();
        /// Ustawia doswiadczenie
        void SetExperience(int Experience);
        /// Zwraca doswiadczenie
        int GetExperience();
        /// Ustawia rozmiar ekwipunku
        void SetInventorySize(int Width, int Height);
        /// Ustawia rozmiar ekwipunku
        void SetInventorySize(sf::Vector2i Size);
        /// Zwraca rozmiar ekwipunku
        sf::Vector2i GetInventorySize();
        /// Ustawia przedmiot w ekwipunku w wybranym miejscu
        void SetInventoryItem(std::string Name, int Quantity, unsigned ListPosition, std::string Rarity = "Common", int Improvement = 0);

    };

    /// class Mob : Public CharacterStats

    /// class Npc : Public CharacterStats
}

#endif // PLAYER_HPP_INCLUDED
