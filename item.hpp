/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef ITEM_HPP_INCLUDED
#define ITEM_HPP_INCLUDED

namespace tfp
{
    struct Item
    {
        std::string Name;
        std::string Rarity;
        int Improvement;
        int Quantity;
        sf::Vector2f Position;
        Item();
        Item(std::string ItemName, int ItemQuantity = 1, sf::Vector2f ItemPosition = sf::Vector2f(0.0f, 0.0f));
        ~Item();
    };

    struct ItemStats
    {
        /// Main
        std::string FullName;
        std::string ItemName;
        std::string Type;
        int MaximumQuantity;
        int RequiredLevel;
        /// Weapon Armor
        int MinimumDamage;
        int MaximumDamage;
        int Strength;
        int Vitality;
        int Evasion;
        int Intelligence;
        float AttackSpeed;
        float MovementSpeed;
        float LifeSteal;
        /// Resistance
        int IceResistance;
        int DarknessResistance;
        int FireResistance;
        int WaterResistance;
        int LightResistance;
        int EarthResistance;
        /// Elements
        int IceElement;
        int DarknessElement;
        int FireElement;
        int WaterElement;
        int LightElement;
        int EarthElement;
        /// Potion
        int HealthRegen;
        int ManaRegen;
        /// SpellBook
        std::string SpellName;
        /// Inventory size if its a bag
        sf::Vector2i InventorySize;
        /// Different
        std::string TexturePath;
        sf::Texture Texture;
        ItemStats();
        ~ItemStats();
    };

    class ItemListClass
    {
    private:
        std::vector<ItemStats> ItemArray;
        const bool LoadItem(std::string ItemName);
        const bool LoadTexture(std::string ItemName);
        bool Loaded;
    public:
        /// Konstruktor
        ItemListClass();
        /// Destruktor
        ~ItemListClass();
        /// Pobieranie tekstury terenu
        const sf::Texture &GetTexture(std::string ItemName);
        /// Pobieranie predkosci na terenie
        const tfp::ItemStats &FindItemWithName(std::string ItemName);
        /// Zwalnianie pamieci podreczniej
        void UnloadAll();
        /// Wczytywanie wszystkich itemow
        void LoadAllItems(tfp::Game *GameHandle);
        /// Zwraca czy lista itemow jest zaladowana
        bool IsLoaded();
    };
}


#endif // ITEM_HPP_INCLUDED
