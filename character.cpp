/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"

tfp::CharacterStats::CharacterStats()
    :MinimumDamage(0), MaximumDamage(0), Strenght(0), Vitality(0), Dexterity(0), Intelligence(0), AttackSpeed(1.0f), MovementSpeed(1.0f), LifeSteal(0.0f),
    IceElement(0), DarknessElement(0), FireElement(0), WaterElement(0), LightElement(0), EarthElement(0), IceResistance(0), DarknessResistance(0), FireResistance(0),
    WaterResistance(0), LightResistance(0), EarthResistance(0) {}

tfp::Player::Player()
    :ID(-1), Name("Unknown"), SkinName("Unknown"), Position({0.0f, 0.0f}), Destination({0.0f, 0.f}),
    Experience(0), Level(0), InventorySize({4, 2})
{
    InventoryItemList.resize(8);
}

tfp::Player::~Player() {}

void tfp::Player::SetID(int ID_)
{
    ID = ID_;
}

int tfp::Player::GetID()
{
    return ID;
}

void tfp::Player::SetName(std::string Name_)
{
    Name = Name_;
}

std::string tfp::Player::GetName()
{
    return Name;
}

void tfp::Player::SetSkinName(std::string SkinName_)
{
    SkinName = SkinName_;
}

std::string tfp::Player::GetSkinName()
{
    return SkinName;
}

void tfp::Player::SetPosition(sf::Vector2f Position_)
{
    Position = Position_;
}

sf::Vector2f tfp::Player::GetPosition()
{
    return Position;
}

void tfp::Player::SetDestination(sf::Vector2f Destination_)
{
    Destination = Destination_;
}

sf::Vector2f tfp::Player::GetDestination()
{
    return Destination;
}

void tfp::Player::SetLevel(int Level_)
{
    Level = Level_;
}

int tfp::Player::GetLevel()
{
    return Level;
}

void tfp::Player::SetExperience(int Experience_)
{
    Experience = Experience_;
}

int tfp::Player::GetExperience()
{
    return Experience;
}

void tfp::Player::SetInventorySize(int Width, int Height)
{
    InventorySize.x = Width;
    InventorySize.y = Height;
    if(InventorySize.x > 10) InventorySize.x = 10;
    if(InventorySize.y > 10) InventorySize.y = 10;
    if(InventorySize.x < 1) InventorySize.x = 1;
    if(InventorySize.y < 1) InventorySize.y = 1;
    InventoryItemList.resize(InventorySize.x * InventorySize.y);
}

void tfp::Player::SetInventorySize(sf::Vector2i Size)
{
    InventorySize = Size;
}

sf::Vector2i tfp::Player::GetInventorySize()
{
    return InventorySize;
}

void tfp::Player::SetInventoryItem(std::string Name, int Quantity, unsigned ListPosition, std::string Rarity, int Improvement)
{
    if(ListPosition < InventoryItemList.size())
    {
        InventoryItemList[ListPosition].Name = Name;
        InventoryItemList[ListPosition].Quantity = Quantity;
        InventoryItemList[ListPosition].Rarity = Rarity;
        InventoryItemList[ListPosition].Improvement = Improvement;
    }
}
