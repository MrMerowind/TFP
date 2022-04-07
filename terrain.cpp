/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"

tfp::Terrain::Terrain()
    :Name("Unknown"), TexturePath("Graphics/Terrain/Unknown.png"), TexturePosition({0, 0}), MovingSpeed(1.0f), Colider(true) {}

tfp::Terrain::~Terrain() {}

tfp::TerrainListClass::TerrainListClass()
    :TerrainNamesLoaded(false), GraphicDriverTerrainLoadingBoost(false)
{
    SelectedTerrainTexture.loadFromFile("Graphics\\Interface\\SelectedTerrain.png");
}

tfp::TerrainListClass::~TerrainListClass()
{
    UnloadAll();
}

const bool tfp::TerrainListClass::LoadTerrain(std::string TerrainName)
{
    TerrainName = tfp::SplitString(TerrainName, 0, '#');

    tfp::Terrain TerrainPrefab;
    sf::Vector2i TerrainPositionStart = sf::Vector2i(0,0);
    sf::Vector2i TerrainPositionEnd = sf::Vector2i(-1,-1);;
    std::fstream TerrainFile;
    std::string TerrainFileName = "Terrain/" + TerrainName + ".terrain";
    TerrainFile.open(TerrainFileName, std::ios::in);
    if(TerrainFile.good())
    {
        std::string Line;
        while(!TerrainFile.eof())
        {
            getline(TerrainFile,Line);
            if(Line == "");
            else if(Line[0] == '#');
            else if(tfp::SplitString(Line,0) == "TexturePath")
            {
                TerrainPrefab.TexturePath = tfp::SplitString(Line,1);
            }
            else if(tfp::SplitString(Line,0) == "MovingSpeed")
            {
                TerrainPrefab.MovingSpeed = tfp::StringToFloat(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "Colider")
            {
                TerrainPrefab.Colider = tfp::StringToBool(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "TexturePositionHorizontal")
            {
                TerrainPositionStart.x = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "TexturePositionVertical")
            {
                TerrainPositionStart.y = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "TexturePositionHorizontalEnd")
            {
                TerrainPositionEnd.x = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "TexturePositionVerticalEnd")
            {
                TerrainPositionEnd.y = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else
            {
                Debug.Warning("Unknow line in: " + TerrainFileName + "  -  " + Line);
            }
        }
        TerrainFile.close();
    }
    else
    {
        TerrainPrefab.Name = TerrainName + "#0";
        TerrainArray.push_back(TerrainPrefab);
        TerrainArray[TerrainArray.size() - 1].Texture.loadFromFile(TerrainArray[TerrainArray.size() - 1].TexturePath, sf::Rect<int>(TerrainArray[TerrainArray.size() - 1].TexturePosition.x * 200, TerrainArray[TerrainArray.size() - 1].TexturePosition.y * 200, 200, 200));
        TerrainArray[TerrainArray.size() - 1].Texture.setSmooth(true);
        Debug.Warning("Terrain not existing: " + TerrainName);
        return false;
    }

    if(TerrainPositionEnd.x < 0) TerrainPositionEnd.x = TerrainPositionStart.x;
    if(TerrainPositionEnd.y < 0) TerrainPositionEnd.y = TerrainPositionStart.y;
    tfp::SwapIfGreater(TerrainPositionStart.x, TerrainPositionEnd.x);
    tfp::SwapIfGreater(TerrainPositionStart.y, TerrainPositionEnd.y);

    /// Ladowanie wczytanych terenow
    sf::Image ImageBuffer;
    ImageBuffer.loadFromFile(TerrainPrefab.TexturePath);
    bool ImageBufferLoaded = true;
    if(ImageBuffer.getSize().x <= 0) ImageBufferLoaded = false;
    if(ImageBuffer.getSize().y <= 0) ImageBufferLoaded = false;

    int Iterator = 0;
    for(int i = TerrainPositionStart.x; i <= TerrainPositionEnd.x; i++)
    {
        for(int j = TerrainPositionStart.y; j <= TerrainPositionEnd.y; j++)
        {
            TerrainPrefab.TexturePosition.x = j;
            TerrainPrefab.TexturePosition.y = i;
            TerrainPrefab.Name = TerrainName + "#" + tfp::IntToString(Iterator);
            TerrainArray.push_back(TerrainPrefab);
            /// Wczytywanie z bufora
            if(ImageBufferLoaded)
            {
                TerrainArray[TerrainArray.size() - 1].Texture.loadFromImage(ImageBuffer, sf::Rect<int>(TerrainArray[TerrainArray.size() - 1].TexturePosition.x * 200, TerrainArray[TerrainArray.size() - 1].TexturePosition.y * 200, 200, 200));
                TerrainArray[TerrainArray.size() - 1].Image.create(200, 200, sf::Color(0,0,0,0));
                TerrainArray[TerrainArray.size() - 1].Image.copy(ImageBuffer, 0, 0, sf::Rect<int>(TerrainArray[TerrainArray.size() - 1].TexturePosition.x * 200, TerrainArray[TerrainArray.size() - 1].TexturePosition.y * 200, 200, 200));
            }

            Iterator++;
        }
    }
    Debug.Info("Terrain loaded: " + TerrainName);
    return true;
}

const tfp::Terrain &tfp::TerrainListClass::FindTerrainWithName(std::string TerrainName)
{
    for(unsigned i = 0; i < TerrainArray.size(); i++)
    {
        if(TerrainArray[i].Name == TerrainName) return TerrainArray[i];
    }
    TerrainName = tfp::SplitString(TerrainName, 0, '#') + "#0";
    for(unsigned i = 0; i < TerrainArray.size(); i++)
    {
        if(TerrainArray[i].Name == TerrainName) return TerrainArray[i];
    }


    for(unsigned i = 0; i < TerrainArray.size(); i++)
    {
        if(TerrainArray[i].Name == "Unknown#0") return TerrainArray[i];
    }

    Debug.Error("Missing terrain for exchange with unknown terrains");

    return TerrainArray[0];

}

void tfp::TerrainListClass::UnloadAll()
{
    if(TerrainArray.size() <= 0) return;
    TerrainArray.clear();
    Debug.Info("TerrainList unloaded");
}

sf::Texture &tfp::TerrainListClass::GetTextureBuffer()
{
    return TerrainTextureBuffer;
}

void tfp::TerrainListClass::LoadAllTerrains(tfp::Game *GameHandle)
{
    UnloadAll();

    tfp::ListFilesInDirectory(".\\Terrain", ".\\Cache\\TerrainList.txt");


    std::string Line;
    std::queue<std::string> ToLoadList;
    std::fstream ConfigFile;
    ConfigFile.open("Cache/TerrainList.txt", std::ios::in);
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
        Debug.Warning("Can not load Cache/TerrainList.txt");
        return;
    }
    TerrainNamesLoaded = true;

    /// Ladowanie terenu
    int ToLoadQuantity = ToLoadList.size();
    for(int i = 0; i < ToLoadQuantity; i++)
    {
        LoadingScreen.DisplayOnScreen("Loading terrains...", GameHandle, std::floor(((i + 1.0f) / (float) ToLoadQuantity) * 100.0f));
        LoadTerrain(ToLoadList.front());
        ToLoadList.pop();
    }


    /// Ladowanie buffera do szybkiego wyswietlania mapy

    const unsigned int maxSize = sf::Texture::getMaximumSize();

    int MaxTerrainEntitiesInLine = maxSize / 200;
    int MaxTerrainEntities = MaxTerrainEntitiesInLine * MaxTerrainEntitiesInLine;

    if(MaxTerrainEntities >= (int) TerrainArray.size())
    {
        GraphicDriverTerrainLoadingBoost = true;
        Debug.Info("GraphicDriver: Terrain rendering boost: Enabled (Entities supported: " + tfp::IntToString(TerrainArray.size()) + "/" + tfp::IntToString(MaxTerrainEntities) + ")");
    }
    else
    {
        GraphicDriverTerrainLoadingBoost = false;
        Debug.Warning("Graphic driver not supporting fast rendering with this many entities (Entities supported: " + tfp::IntToString(TerrainArray.size()) + "/" + tfp::IntToString(MaxTerrainEntities) + ")");
        Debug.Info("GraphicDriver: Terrain rendering boost: Disabled");
    }


    if(GraphicDriverTerrainLoadingBoost)
    {
        int BufferWidth = MaxTerrainEntitiesInLine * 200;
        int BufferHeight = TerrainArray.size() / MaxTerrainEntitiesInLine * 200 + 200;
        if(BufferHeight > BufferWidth) BufferHeight = BufferWidth;

        TerrainImageBuffer.create(BufferWidth, BufferHeight, sf::Color(0,0,0,0));
        for(unsigned i = 0; i < TerrainArray.size(); i++)
        {
            TerrainImageBuffer.copy(TerrainArray[i].Image, (i % MaxTerrainEntitiesInLine) * 200, (i / MaxTerrainEntitiesInLine) * 200, sf::Rect<int>(0, 0, 200, 200));
            TerrainArray[i].TextureBufferPosition = {(i % MaxTerrainEntitiesInLine) * 200.0f, (i / MaxTerrainEntitiesInLine) * 200.0f};
        }
        TerrainTextureBuffer.loadFromImage(TerrainImageBuffer, sf::Rect<int>(0, 0, 200 * BufferWidth, 200 * BufferHeight));
        #if GRAPHICBOOST == 0
        TerrainTextureBuffer.setSmooth(false);
        TerrainTextureBuffer.setRepeated(false);
        GraphicDriverTerrainLoadingBoost = false;
        #endif // TEST
    }
}

bool tfp::TerrainListClass::IsGraphicDriverTerrainLoadingBoostEnabled()
{
    return GraphicDriverTerrainLoadingBoost;
}

sf::Texture &tfp::TerrainListClass::GetSelectedTerrainTexture()
{
    return SelectedTerrainTexture;
}

std::vector<tfp::Terrain> &tfp::TerrainListClass::GetTerrainArray()
{
    return TerrainArray;
}

bool tfp::TerrainListClass::IsAllTerrainLoaded()
{
    return TerrainNamesLoaded;
}

