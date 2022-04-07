/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"

tfp::ItemStats::ItemStats()
    :FullName("Unknown"), ItemName("Unknown"), Type("Unknown"), MaximumQuantity(1), RequiredLevel(0),
    MinimumDamage(0), MaximumDamage(0), Strength(0), Vitality(0), Evasion(0), Intelligence(0), AttackSpeed(1.0f), MovementSpeed(1.0f), LifeSteal(0.0f),
    IceResistance(0), DarknessResistance(0), FireResistance(0), WaterResistance(0), LightResistance(0), EarthResistance(0),
    IceElement(0), DarknessElement(0), FireElement(0), WaterElement(0), LightElement(0), EarthElement(0),
    HealthRegen(0), ManaRegen(0),
    SpellName("Unknown"),
    TexturePath("Graphics/Item/Unknown.png") {}

tfp::ItemStats::~ItemStats() {}

tfp::ItemListClass::ItemListClass()
:Loaded(false)
{

}

tfp::ItemListClass::~ItemListClass()
{
    UnloadAll();
}

tfp::Item::Item()
    :Name("Unknown"), Rarity("Common"), Improvement(0), Quantity(0), Position({0.0f, 0.0f}) {}

tfp::Item::Item(std::string ItemName, int ItemQuantity, sf::Vector2f ItemPosition)
    :Name(ItemName), Quantity(ItemQuantity), Position(ItemPosition)
{

}

tfp::Item::~Item() {}

const bool tfp::ItemListClass::LoadTexture(std::string ItemName)
{
    for(unsigned i = 0; i < ItemArray.size(); i++)
    {
        if(ItemArray[i].ItemName == ItemName)
        {
            ItemArray[i].Texture.loadFromFile(ItemArray[i].TexturePath);
            return true;
        }
    }
    return false;
}

const bool tfp::ItemListClass::LoadItem(std::string ItemName)
{
    ItemArray.push_back(tfp::ItemStats());
    ItemArray[ItemArray.size() - 1].ItemName = ItemName;
    std::fstream ItemFile;
    std::string ItemFileName = "Item/" + ItemName + ".item";
    ItemFile.open(ItemFileName, std::ios::in);
    if(ItemFile.good())
    {
        std::string Line;
        while(!ItemFile.eof())
        {
            getline(ItemFile,Line);
            if(Line[0] == '#');
            else if(tfp::SplitString(Line,0) == "TexturePath")
            {
                ItemArray[ItemArray.size() - 1].TexturePath = tfp::SplitString(Line,1);
            }
            else if(tfp::SplitString(Line,0) == "Name")
            {
                ItemArray[ItemArray.size() - 1].FullName = tfp::SplitString(Line,1);
            }
            else if(tfp::SplitString(Line,0) == "Type")
            {
                ItemArray[ItemArray.size() - 1].Type = tfp::SplitString(Line,1);
            }
            else if(tfp::SplitString(Line,0) == "MaximumQuantity")
            {
                ItemArray[ItemArray.size() - 1].MaximumQuantity = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "RequiredLevel")
            {
                ItemArray[ItemArray.size() - 1].RequiredLevel = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "MinimumDamage")
            {
                ItemArray[ItemArray.size() - 1].MinimumDamage = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "MaximumDamage")
            {
                ItemArray[ItemArray.size() - 1].MaximumDamage = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "Strength")
            {
                ItemArray[ItemArray.size() - 1].Strength = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "Vitality")
            {
                ItemArray[ItemArray.size() - 1].Vitality = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "Evasion")
            {
                ItemArray[ItemArray.size() - 1].Evasion = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "Intelligence")
            {
                ItemArray[ItemArray.size() - 1].Intelligence = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "AttackSpeed")
            {
                ItemArray[ItemArray.size() - 1].AttackSpeed = tfp::StringToFloat(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "MovementSpeed")
            {
                ItemArray[ItemArray.size() - 1].MovementSpeed = tfp::StringToFloat(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "LifeSteal")
            {
                ItemArray[ItemArray.size() - 1].LifeSteal = tfp::StringToFloat(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "IceResistance")
            {
                ItemArray[ItemArray.size() - 1].IceResistance = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "DarknessResistance")
            {
                ItemArray[ItemArray.size() - 1].DarknessResistance = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "FireResistance")
            {
                ItemArray[ItemArray.size() - 1].FireResistance = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "WaterResistance")
            {
                ItemArray[ItemArray.size() - 1].WaterResistance = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "LightResistance")
            {
                ItemArray[ItemArray.size() - 1].LightResistance = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "EarthResistance")
            {
                ItemArray[ItemArray.size() - 1].EarthResistance = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "IceElement")
            {
                ItemArray[ItemArray.size() - 1].IceElement = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "DarknessElement")
            {
                ItemArray[ItemArray.size() - 1].DarknessElement = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "FireElement")
            {
                ItemArray[ItemArray.size() - 1].FireElement = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "WaterElement")
            {
                ItemArray[ItemArray.size() - 1].WaterElement = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "LightElement")
            {
                ItemArray[ItemArray.size() - 1].LightElement = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "EarthElement")
            {
                ItemArray[ItemArray.size() - 1].EarthElement = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "HealthRegen")
            {
                ItemArray[ItemArray.size() - 1].HealthRegen = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "ManaRegen")
            {
                ItemArray[ItemArray.size() - 1].ManaRegen = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "SpellName")
            {
                ItemArray[ItemArray.size() - 1].SpellName = tfp::SplitString(Line,1);
            }
            else if(tfp::SplitString(Line,0) == "InventorySizeWidth")
            {
                ItemArray[ItemArray.size() - 1].InventorySize.x = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "InventorySizeHeight")
            {
                ItemArray[ItemArray.size() - 1].InventorySize.y = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else
            {
                Debug.Warning("Unknow line in: " + ItemFileName + "  -  " + Line);
            }
        }
        ItemFile.close();
    }
    else
    {
        LoadTexture(ItemName);
        Debug.Warning("ItemList: Item not existing: " + ItemName);
        return false;
    }
    LoadTexture(ItemName);
    Debug.Info("ItemList loaded: " + ItemName);
    return true;
}

const sf::Texture &tfp::ItemListClass::GetTexture(std::string ItemName)
{
    for(unsigned i = 0; i < ItemArray.size(); i++)
    {
        if(ItemArray[i].ItemName == ItemName) return ItemArray[i].Texture;
    }
    LoadItem(ItemName);
    return ItemArray[ItemArray.size() - 1].Texture;
}

void tfp::ItemListClass::LoadAllItems(tfp::Game *GameHandle)
{
    UnloadAll();

    tfp::ListFilesInDirectory(".\\Item", ".\\Cache\\ItemList.txt");

    std::string Line;
    std::queue<std::string> ToLoadList;
    std::fstream ConfigFile;
    ConfigFile.open("Cache/ItemList.txt", std::ios::in);
    if(ConfigFile.good())
    {
        while(!ConfigFile.eof())
        {
            getline(ConfigFile,Line);
            Line = tfp::PathToFileTitle(Line);
            if(Line == "") continue;
            ToLoadList.push(Line);
        }
        ConfigFile.close();
    }
    else
    {
        Debug.Warning("Can not load Cache/ItemList.txt");
        return;
    }

    /// Ladowanie terenu
    int ToLoadQuantity = ToLoadList.size();
    for(int i = 0; i < ToLoadQuantity; i++)
    {
        LoadingScreen.DisplayOnScreen("Loading items...", GameHandle, std::floor(((i + 1.0f) / (float) ToLoadQuantity) * 100.0f));
        LoadItem(ToLoadList.front());
        ToLoadList.pop();
    }
    Loaded = true;
}

bool tfp::ItemListClass::IsLoaded()
{
    return Loaded;
}

const tfp::ItemStats &tfp::ItemListClass::FindItemWithName(std::string ItemName)
{
    for(unsigned i = 0; i < ItemArray.size(); i++)
    {
        if(ItemArray[i].ItemName == ItemName) return ItemArray[i];
    }
    LoadItem(ItemName);
    return ItemArray[ItemArray.size() - 1];
}

void tfp::ItemListClass::UnloadAll()
{
    if(ItemArray.size() <= 0) return;
    ItemArray.clear();
    Debug.Info("ItemList unloaded");
    Loaded = false;
}
