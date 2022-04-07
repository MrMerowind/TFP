/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"

tfp::Map::Map()
    :Width(0), Height(0), Terrain(nullptr), MapName("NotLoaded"), GameHandle(nullptr), PreviewTerrainName("Unknown"), PreviewStart({0, 0}), PreviewEnd({0, 0}),
    Preview(false), PreviewSingle(false), ObjectPreview(false), ObjectPreviewPosition({0.0f, 0.0f}), ObjectPreviewName("Unknown") {}

tfp::Map::~Map()
{
    Unload();
}

bool tfp::Map::LoadMap(std::string MapName_)
{
    if(GameHandle->GetGameType() != "game" && GameHandle->GetGameType() != "mapeditor")
    {
        Debug.Command("Map only available in game and map editor");
        return false;
    }

    if(MapName_ == "") return false;
    std::string MapFileName = "Maps/" + MapName_ + ".map";

	rapidxml::xml_document<> GameMapXmlDocument;
	rapidxml::xml_node<> * RootNode;
	std::ifstream GameMapXmlFile (MapFileName.c_str());
	if(!GameMapXmlFile.good())
    {
        Debug.Warning("Can not load map: " + MapName_);
        return false;
    }
	std::vector<char> Buffer((std::istreambuf_iterator<char>(GameMapXmlFile)), std::istreambuf_iterator<char>());
	Buffer.push_back('\0');
	try
	{
	    GameMapXmlDocument.parse<0>(&Buffer[0]);
	}
	catch(std::exception &e)
	{
	    std::string ExceptionString = e.what();
	    Debug.Warning("Map file is corrupted: " + ExceptionString);
        return false;
	}

    RootNode = GameMapXmlDocument.first_node("gamemap");
    int NewWidth = tfp::StringToInt(RootNode->first_node("map")->first_attribute("width")->value());
    int NewHeight = tfp::StringToInt(RootNode->first_node("map")->first_attribute("height")->value());

    if(NewWidth < 1 || NewHeight < 1)
    {
        Debug.Command("Map borders must be wider than 0");
        return false;
    }

    std::string **NewTerrain;
    NewTerrain = new std::string*[NewHeight];
    for(int i = 0; i < NewHeight; i++)
    {
        NewTerrain[i] = new std::string[NewWidth];
    }
    for(int i = 0; i < NewHeight; i++)
    {
        for(int j = 0; j < NewWidth; j++)
        {
            NewTerrain[i][j] = "Unknown";
        }
    }

    rapidxml::xml_node<> *TerrainNode;
    TerrainNode = RootNode->first_node("map")->first_node("terrain");
    for(int i = 0; i < NewHeight; i++)
    {
        for(int j = 0; j < NewWidth; j++)
        {
            if(TerrainNode == nullptr) break;
            NewTerrain[i][j] = TerrainNode->value();
            TerrainNode = TerrainNode->next_sibling();
        }
    }
    rapidxml::xml_node<> *ObjectNode;
    ObjectNode = RootNode->first_node("objects")->first_node("object");


    Unload();

    while(ObjectNode != nullptr)
    {
        tfp::Animation NewAnimation;
        NewAnimation.Type = tfp::Animation::ObjectAnimation;
        NewAnimation.Position.x = tfp::StringToFloat(ObjectNode->first_attribute("position_x")->value());
        NewAnimation.Position.y = tfp::StringToFloat(ObjectNode->first_attribute("position_y")->value());
        NewAnimation.PositionZ = tfp::StringToInt(ObjectNode->first_attribute("position_z")->value());
        NewAnimation.Size.x = tfp::StringToFloat(ObjectNode->first_attribute("size_x")->value());
        NewAnimation.Size.y = tfp::StringToFloat(ObjectNode->first_attribute("size_y")->value());
        NewAnimation.Name = ObjectNode->value();

        ObjectList.PushBack(NewAnimation);
        ObjectNode = ObjectNode->next_sibling();
    }

    ObjectList.Sort();

    Terrain = NewTerrain;
    GameHandle->TerrainChanged = true;
    Width = NewWidth;
    Height = NewHeight;
    NewTerrain = nullptr;
    while(!TerrainChangeStack.empty()) TerrainChangeStack.pop();
    while(!TerrainChangeStackRedo.empty()) TerrainChangeStackRedo.pop();
    MapName = MapName_;
    Debug.Info("Map loaded: " + MapName);
    if(GameHandle != nullptr)
    {
        GameHandle->GameCamera.SetBorders(0, 0, GetPixelWidth().x, GetPixelWidth().y);
        GameHandle->GameCamera.SetGameHandle(GameHandle);
    }
    else Debug.Warning("Game handle not set");
    return true;
}

bool tfp::Map::SaveMap(std::string MapName_)
{
    if(GameHandle->GetGameType() != "game" && GameHandle->GetGameType() != "mapeditor")
    {
        Debug.Command("Map only available in game and map editor");
        return false;
    }

    if(MapName_ == "") return false;
    std::string MapFileName = "Maps/" + MapName_ + ".map";
    /// Sprawdzenie czy mapa jest poprawnie stworzona
    if(Terrain == nullptr)
    {
        Debug.Command("Create map before saving");
        return false;
    }
    if(Width < 1 || Height < 1)
    {
        Debug.Command("Map borders must be wider than 0");
        return false;
    }

    MapName = MapName_;

    /// Otwieranie pliku
    std::fstream SaveFile;
    SaveFile.open(MapFileName.c_str(), std::ios::out);
    if(!SaveFile.good())
    {
        Debug.Command("Can not save to file: " + MapName_);
        return false;
    }
    /// Zapsywanie do pliku mapy
    SaveFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
    SaveFile << "<gamemap>" << std::endl;
	SaveFile << "\t<map width=\"" << Width << "\" height=\"" << Height << "\">" << std::endl;
	for(int j = 0; j < Height; j++)
    {
        for(int i = 0; i < Width; i++)
        {
            SaveFile << "\t\t<terrain>" << Terrain[j][i] << "</terrain>" << std::endl;

        }
    }
    SaveFile << "\t</map>" << std::endl;
    SaveFile << "\t<objects>" << std::endl;

    for(unsigned i = 0; i < ObjectList.Size(); i++)
    {
            SaveFile << "\t\t<object position_x=\"" << tfp::FloatToString(ObjectList[i].Position.x)
            << "\" position_y=\"" << tfp::FloatToString(ObjectList[i].Position.y) << "\" position_z=\""
            << tfp::IntToString(ObjectList[i].PositionZ) << "\" size_x=\"" << tfp::FloatToString(ObjectList[i].Size.x)
            << "\" size_y=\"" << tfp::FloatToString(ObjectList[i].Size.y) << "\" >" << ObjectList[i].Name << "</object>" << std::endl;
    }

    SaveFile << "\t</objects>" << std::endl;
    SaveFile << "\t<items>" << std::endl;

    SaveFile << "\t</items>" << std::endl;
    SaveFile << "</gamemap>" << std::endl;

    /// Zamykanie pliku
    SaveFile.close();

    /// Informacja o udanym zapisie
    Debug.Info("Map saved: " + MapName);
    return true;
}

void tfp::Map::SetMapName(std::string NewName)
{
    if(GameHandle->GetGameType() != "game" && GameHandle->GetGameType() != "mapeditor")
    {
        Debug.Command("Map only available in game and map editor");
        return;
    }

    if(NewName == "")
    {
        Debug.Command("Map name must contain at least one character");
    }
    MapName = NewName;
    Debug.Command("Map name set to: " + MapName);
}

std::string tfp::Map::GetMapName() const
{
    return MapName;
}

void tfp::Map::Resize(int Width_, int Height_)
{
    if(GameHandle->GetGameType() != "game" && GameHandle->GetGameType() != "mapeditor")
    {
        Debug.Command("Map only available in game and map editor");
        return;
    }

    if(Width == Width_ && Height == Height_)
    {
        return;
    }

    if(Width_ < 1 || Height_ < 1)
    {
        Debug.Command("Map borders must be wider than 0");
        return;
    }
    if(Width_ > 1000 || Height_ > 1000)
    {
        Debug.Command("Maximum map borders are 1000 x 1000");
        return;
    }
    /// Tworzenie nowego terenu
    std::string **NewTerrain;
    NewTerrain = new std::string*[Height_];
    for(int i = 0; i < Height_; i++)
    {
        NewTerrain[i] = new std::string[Width_];
    }
    /// Zerowanie mapy
    for(int i = 0; i < Height_; i++)
    {
        for(int j = 0; j < Width_; j++)
        {
            NewTerrain[i][j] = "Grass";
        }
    }
    /// Przepisywanie starej mapy
    for(int i = 0; i < Height_ && i < Height; i++)
    {
        for(int j = 0; j < Width_ && j < Width; j++)
        {
            NewTerrain[i][j] = Terrain[i][j];
        }
    }
    /// Usuwanie starej mapy
    for(int i = 0; i < Height; i++)
    {
        delete Terrain[i];
    }
    delete Terrain;
    Terrain = nullptr;
    Terrain = NewTerrain;
    if(MapName == "NotLoaded") MapName = "Unnamed";
    NewTerrain = nullptr;
    Height = Height_;
    Width = Width_;
    Debug.Command("Map resized");
    if(GameHandle != nullptr)
    {
        GameHandle->GameCamera.SetBorders(0, 0, GetPixelWidth().x, GetPixelWidth().y);
        GameHandle->GameCamera.SetGameHandle(GameHandle);
    }
    else Debug.Warning("Game handle not set");
}

void tfp::Map::SetTerrain(std::string TerrainName_, int PositionX, int PositionY)
{
    if(Terrain == nullptr) return;
    if(PositionX >= 0 && PositionY >= 0 && PositionX < Width && PositionY < Height)
    {
        TerrainChangeStack.push(tfp::TerrainPositionSwapSave(sf::Vector2i(PositionX,PositionY), Terrain[PositionY][PositionX], TerrainName_));
        TerrainChangeStack.push(tfp::TerrainPositionSwapSave());
        while(!TerrainChangeStackRedo.empty()) TerrainChangeStackRedo.pop();
        Terrain[PositionY][PositionX] = TerrainName_;
    }
}

void tfp::Map::SetTerrainPreview(std::string TerrainName_, int PositionX, int PositionY)
{
    PreviewSingle = true;
    PreviewTerrainNameSingle = TerrainName_;
    PreviewSinglePosition.x = PositionX;
    PreviewSinglePosition.y = PositionY;
}

void tfp::Map::SetTerrainNoPause(std::string TerrainName_, int PositionX, int PositionY)
{
    if(Terrain == nullptr) return;
    if(PositionX >= 0 && PositionY >= 0 && PositionX < Width && PositionY < Height)
    {
        TerrainChangeStack.push(tfp::TerrainPositionSwapSave(sf::Vector2i(PositionX,PositionY), Terrain[PositionY][PositionX], TerrainName_));
        while(!TerrainChangeStackRedo.empty()) TerrainChangeStackRedo.pop();
        Terrain[PositionY][PositionX] = TerrainName_;
    }
}

void tfp::Map::SetTerrainPreview(bool State)
{
    PreviewSingle = State;
}

void tfp::Map::SetTerrainPause()
{
    TerrainChangeStack.push(tfp::TerrainPositionSwapSave());
}

void tfp::Map::UndoTerrainChanges()
{
    if(Terrain == nullptr) return;
    if(!TerrainChangeStack.empty())
    {
        while(!TerrainChangeStack.empty() && TerrainChangeStack.top().Pause == true) TerrainChangeStack.pop();
        while(!TerrainChangeStack.empty())
        {
            if(TerrainChangeStack.top().Pause) break;
            else
            {
                if(TerrainChangeStack.top().Position.x >= 0 && TerrainChangeStack.top().Position.y >= 0 && TerrainChangeStack.top().Position.x < Width && TerrainChangeStack.top().Position.y < Height)
                {
                    TerrainChangeStackRedo.push(TerrainChangeStack.top());
                    Terrain[TerrainChangeStack.top().Position.y][TerrainChangeStack.top().Position.x] = TerrainChangeStack.top().Before;
                }
                TerrainChangeStack.pop();
            }
        }
        TerrainChangeStackRedo.push(tfp::TerrainPositionSwapSave());
    }
}

void tfp::Map::RedoTerrainChanges()
{
    if(Terrain == nullptr) return;
    if(!TerrainChangeStackRedo.empty())
    {
        while(TerrainChangeStackRedo.top().Pause == true && !TerrainChangeStackRedo.empty()) TerrainChangeStackRedo.pop();
        while(!TerrainChangeStackRedo.empty())
        {
            if(TerrainChangeStackRedo.top().Pause) break;
            else
            {
                if(TerrainChangeStackRedo.top().Position.x >= 0 && TerrainChangeStackRedo.top().Position.y >= 0 && TerrainChangeStackRedo.top().Position.x < Width && TerrainChangeStackRedo.top().Position.y < Height)
                {
                    TerrainChangeStack.push(TerrainChangeStackRedo.top());
                    Terrain[TerrainChangeStackRedo.top().Position.y][TerrainChangeStackRedo.top().Position.x] = TerrainChangeStackRedo.top().After;
                }
                TerrainChangeStackRedo.pop();
            }
        }
        TerrainChangeStack.push(tfp::TerrainPositionSwapSave());
    }
}

void tfp::Map::SetTerrainRect(std::string TerrainName_, sf::Vector2i Start, sf::Vector2i End, bool OnlySameTerrain)
{
    if(Terrain == nullptr) return;
    PreviewTerrainNameBefore = GetTerrainRealName(Start.y, Start.x);
    OnlySame = OnlySameTerrain;

    int PosStX = tfp::Lesser(Start.x, End.x);
    int PosEnX = tfp::Greater(Start.x, End.x);
    int PosStY = tfp::Lesser(Start.y, End.y);
    int PosEnY = tfp::Greater(Start.y, End.y);

    for(int i = PosStX; i <= PosEnX; i++)
    {
        for(int j = PosStY; j <= PosEnY; j++)
        {
            if(i >= 0 && j >= 0 && i < Width && j < Height)
            {
                if(OnlySame && Terrain[j][i] == PreviewTerrainNameBefore)
                {
                    TerrainChangeStack.push(tfp::TerrainPositionSwapSave(sf::Vector2i(i,j), Terrain[j][i], TerrainName_));
                    Terrain[j][i] = TerrainName_;
                }
                else if(!OnlySame)
                {
                    TerrainChangeStack.push(tfp::TerrainPositionSwapSave(sf::Vector2i(i,j), Terrain[j][i], TerrainName_));
                    Terrain[j][i] = TerrainName_;
                }

            }
        }
    }
    TerrainChangeStack.push(tfp::TerrainPositionSwapSave());
    while(!TerrainChangeStackRedo.empty()) TerrainChangeStackRedo.pop();
}

void tfp::Map::SetTerrainRectPreview(std::string TerrainName_, sf::Vector2i Start, sf::Vector2i End, bool OnlySameTerrain)
{
    PreviewTerrainName = TerrainName_;
    PreviewTerrainNameBefore = GetTerrainRealName(Start.y, Start.x);
    OnlySame = OnlySameTerrain;
    PreviewStart.x = tfp::Lesser(Start.x, End.x);
    PreviewEnd.x = tfp::Greater(Start.x, End.x);
    PreviewStart.y = tfp::Lesser(Start.y, End.y);
    PreviewEnd.y = tfp::Greater(Start.y, End.y);
    Preview = true;
}

void tfp::Map::SetTerrainRectPreview(bool State)
{
    Preview = State;
}

void tfp::Map::Unload()
{
    if(Terrain == nullptr) return;

    if(GameHandle->GetGameType() != "game" && GameHandle->GetGameType() != "mapeditor")
    {
        Debug.Command("Map only available in game and map editor");
        return;
    }

    for(int i = 0; i < Height; i++)
    {
        delete [] Terrain[i];
    }

    delete [] Terrain;
    Terrain = nullptr;
    Width = 0;
    Height = 0;
    Debug.Info("Map unloaded: " + MapName);
    MapName = "NotLoaded";
    ObjectList.Clear();
}

const int &tfp::Map::GetWidth() const
{
    return Width;
}

const int &tfp::Map::GetHeight() const
{
    return Height;
}

const bool tfp::Map::IsLoaded() const
{
    if(Terrain == nullptr) return false;
    else return true;
}

void tfp::Map::SetGameHandle(tfp::Game *Handle)
{
    GameHandle = Handle;
}

std::string tfp::Map::GetTerrainName(int HorizontalPosition, int VerticalPosition)
{
    if(HorizontalPosition < 0 || HorizontalPosition >= Height || VerticalPosition < 0 || VerticalPosition > Width)
    {
        return "";
    }
    else
    {
        if(OnlySame && Preview && HorizontalPosition >= PreviewStart.y && HorizontalPosition <= PreviewEnd.y
           && VerticalPosition >= PreviewStart.x && VerticalPosition <= PreviewEnd.x && Terrain[HorizontalPosition][VerticalPosition] == PreviewTerrainNameBefore)
            return PreviewTerrainName;
        else if(!OnlySame && Preview && HorizontalPosition >= PreviewStart.y && HorizontalPosition <= PreviewEnd.y
           && VerticalPosition >= PreviewStart.x && VerticalPosition <= PreviewEnd.x)
            return PreviewTerrainName;
        else if(PreviewSingle && PreviewSinglePosition.x == VerticalPosition && PreviewSinglePosition.y == HorizontalPosition)
            return PreviewTerrainNameSingle;
        else return Terrain[HorizontalPosition][VerticalPosition];
    }
}

/// Odwrotnie sa tu indeksy
std::string tfp::Map::GetTerrainRealName(int HorizontalPosition, int VerticalPosition)
{
    if(VerticalPosition < 0 || VerticalPosition >= Height || HorizontalPosition < 0 || HorizontalPosition >= Width)
    {
        return "";
    }
    else
    {
        return Terrain[HorizontalPosition][VerticalPosition];
    }
}

const sf::Vector2i tfp::Map::GetPixelWidth()
{
    return sf::Vector2i(Width * 200, Height * 200);
}

tfp::SortedVector<tfp::Animation> &tfp::Map::GetObjectList()
{
    return ObjectList;
}

void tfp::Map::AddObject(std::string Name, float PositionX, float PositionY)
{
    sf::Vector2i Grid = GameHandle->GameInterface.GetGridSize();
    sf::Vector2f GridShift = GameHandle->GameInterface.GetGridShift();

    if(Grid.x != 0)
    {
        PositionX -= (float) ((int) PositionX % Grid.x) - GridShift.x;
    }

    if(Grid.y != 0)
    {
        PositionY -= (float) ((int) PositionY % Grid.y) - GridShift.y;
    }

    tfp::Animation NewAnimation = {Name, tfp::Animation::ObjectAnimation, PositionX, PositionY};
    NewAnimation.PositionZ = GameHandle->GameInterface.TerrainWindowTileZIndex;

    if(PositionX < - NewAnimation.Size.x) return;
    if(PositionY < - NewAnimation.Size.y) return;
    if(PositionX > Width * 200.0f) return;
    if(PositionY > Height * 200.0f) return;

    ObjectList.Push(NewAnimation);
}

void tfp::Map::RemoveObject(float PositonX, float PositionY)
{
    for(int i = ObjectList.Size() - 1; i >= 0; i--)
    {
        if(PositonX >= ObjectList[i].Position.x && PositonX <= ObjectList[i].Position.x + ObjectList[i].Size.x &&
           PositionY >= ObjectList[i].Position.y && PositionY <= ObjectList[i].Position.y + ObjectList[i].Size.y)
        {
            ObjectList.Delete(i);
            return;
        }
    }
}

void tfp::Map::SetObjectPreview(bool State)
{
    ObjectPreview = State;
}

void tfp::Map::SetObjectPreview(std::string Name, int PositionX, int PositionY)
{
    ObjectPreview = true;
    ObjectPreviewName = Name;
    ObjectPreviewPosition.x = PositionX;
    ObjectPreviewPosition.y = PositionY;

    sf::Vector2i Grid = GameHandle->GameInterface.GetGridSize();
    sf::Vector2f GridShift = GameHandle->GameInterface.GetGridShift();
    if(Grid.x != 0)
    {
        ObjectPreviewPosition.x -= (int) ObjectPreviewPosition.x % Grid.x - (int) GridShift.x;
    }

    if(Grid.y != 0)
    {
        ObjectPreviewPosition.y -= (int) ObjectPreviewPosition.y % Grid.y - (int) GridShift.y;
    }
}
