/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"

tfp::Font::Font()
    :Name("Unknown"), FontColor({0, 0, 0, 255}), FontOutlineColor({0, 0, 0, 255}), OutlineThickness(0.0f), CharacterSize(12), Style("") {}

tfp::Font::~Font() {}

tfp::FontListClass::FontListClass()
    :LoadedAll(false) {}

tfp::FontListClass::~FontListClass() {}

const tfp::Font &tfp::FontListClass::FindFontWithName(std::string FontName)
{
    for(unsigned i = 0; i < FontArray.size(); i++)
    {
        if(FontArray[i].Name == FontName) return FontArray[i];
    }
    LoadFont(FontName);
    return FontArray[FontArray.size() - 1];
}

bool tfp::FontListClass::IsAllLoaded()
{
    return LoadedAll;
}

void tfp::FontListClass::LoadAllFonts(tfp::Game *GameHandle)
{
    UnloadAll();

    tfp::ListFilesInDirectory(".\\Text", ".\\Cache\\FontList.txt");

    std::string Line;
    std::queue<std::string> ToLoadList;
    std::fstream ConfigFile;
    ConfigFile.open("Cache/FontList.txt", std::ios::in);
    if(ConfigFile.good())
    {
        while(!ConfigFile.eof())
        {
            getline(ConfigFile,Line);
            Line = tfp::PathToFileTitle(Line);
            if(Line == "") continue;
            ToLoadList.push(Line);
            // LoadTerrain(Line);
        }
        ConfigFile.close();
    }
    else
    {
        Debug.Warning("Can not load Cache/FontList.txt");
        return;
    }
    LoadedAll = true;

    /// Ladowanie czcionek
    int ToLoadQuantity = ToLoadList.size();
    for(int i = 0; i < ToLoadQuantity; i++)
    {
        LoadingScreen.DisplayOnScreen("Loading fonts...", GameHandle, std::floor(((i + 1.0f) / (float) ToLoadQuantity) * 100.0f));
        LoadFont(ToLoadList.front());
        ToLoadList.pop();
    }
}

const bool tfp::FontListClass::LoadFont(std::string FontName)
{
    for(unsigned i = 0; i < FontArray.size(); i++)
    {
        if(FontArray[i].Name == FontName) return false;
    }

    FontArray.push_back(tfp::Font());
    FontArray[FontArray.size() - 1].Name = FontName;
    std::fstream FontFile;
    std::string FontFileName = "Text/" + FontName + ".font";
    FontFile.open(FontFileName, std::ios::in);
    if(FontFile.good())
    {
        std::string Line;
        while(!FontFile.eof())
        {
            getline(FontFile,Line);
            if(Line[0] == '#');
            else if(Line == "");
            else if(tfp::SplitString(Line,0) == "FontPath")
            {
                FontArray[FontArray.size() - 1].FontPath = tfp::SplitString(Line,1);
            }
            else if(tfp::SplitString(Line,0) == "CharacterSize")
            {
                FontArray[FontArray.size() - 1].CharacterSize = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "OutlineThickness")
            {
                FontArray[FontArray.size() - 1].OutlineThickness = tfp::StringToFloat(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "Color")
            {
                FontArray[FontArray.size() - 1].FontColor.r = tfp::StringToInt(tfp::SplitString(tfp::SplitString(Line,1), 0, ','));
                FontArray[FontArray.size() - 1].FontColor.g = tfp::StringToInt(tfp::SplitString(tfp::SplitString(Line,1), 1, ','));
                FontArray[FontArray.size() - 1].FontColor.b = tfp::StringToInt(tfp::SplitString(tfp::SplitString(Line,1), 2, ','));
                FontArray[FontArray.size() - 1].FontColor.a = tfp::StringToInt(tfp::SplitString(tfp::SplitString(Line,1), 3, ','));
            }
            else if(tfp::SplitString(Line,0) == "OutlineColor")
            {
                FontArray[FontArray.size() - 1].FontOutlineColor.r = tfp::StringToInt(tfp::SplitString(tfp::SplitString(Line,1), 0, ','));
                FontArray[FontArray.size() - 1].FontOutlineColor.g = tfp::StringToInt(tfp::SplitString(tfp::SplitString(Line,1), 1, ','));
                FontArray[FontArray.size() - 1].FontOutlineColor.b = tfp::StringToInt(tfp::SplitString(tfp::SplitString(Line,1), 2, ','));
                FontArray[FontArray.size() - 1].FontOutlineColor.a = tfp::StringToInt(tfp::SplitString(tfp::SplitString(Line,1), 3, ','));
            }
            else if(tfp::SplitString(Line,0) == "Style")
            {
                FontArray[FontArray.size() - 1].Style = tfp::SplitString(Line,1);
            }
            else
            {
                Debug.Warning("Unknow line in: " + FontFileName + "  -  " + Line);
            }
        }
        FontFile.close();
    }
    else
    {
        LoadFontData(FontName);
        Debug.Warning("Font not existing: " + FontName);
        return false;
    }
    LoadFontData(FontName);
    Debug.Info("Font loaded: " + FontName);
    return true;
}

const bool tfp::FontListClass::LoadFontData(std::string FontName)
{
    for(unsigned i = 0; i < FontArray.size(); i++)
    {
        if(FontArray[i].Name == FontName)
        {
            FontArray[i].FontData.loadFromFile(FontArray[i].FontPath);
            #ifndef FONT_SMOOTHING
            ((sf::Texture&)FontArray[i].FontData.getTexture(FontArray[i].CharacterSize)).setSmooth(false);
            #endif // FONT_SMOOTHING
            return true;
        }
    }
    return false;
}

void tfp::FontListClass::UnloadAll()
{
    if(FontArray.size() <= 1) return;
    FontArray.clear();
    Debug.Info("FontList unloaded");
}
