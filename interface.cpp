/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"

tfp::Interface::Interface()
    :CommandLineVisible(false), CommandLineInput(""), LastDebugMessage(0), Fps(false), LastTimeFpsCount(tfp::Seconds()),
    GameHandle(nullptr), PlaceTerrainTerrainID(0), PlaceTerrainLeftButtonDown(false), GridSize({200.0f, 200.0f}), GridShift({0.0f, 0.0f}),
    GridEnabled(false), ShowGridEnabled(true), TerrainNamesIndexPrevious(999), SetTile("terrain"), DraggedItemId(-1), IndexZHelpVisible(false),
    TerrainWindowTileSetIndex(0), TerrainWindowTileIndex(0), TerrainWindowTileZIndex(0), LanguageNamesIndex(0)
{
    CommandLineFocusArea.SetDisabled(true);

    for(int i = 0; i < CommandLineOutputLines; i++)
    {
        CommandLineOutput[i] = "";
    }
    InterfaceCommandLineTexture.loadFromFile("Graphics/Interface/CommandLine.png");
    InventoryGridTexture.loadFromFile("Graphics/Interface/Inventory.png");
}

tfp::Interface::~Interface()
{
    GameHandle = nullptr;
}

void tfp::Interface::ShowFps(bool State)
{
    Fps = State;
}


const bool tfp::Interface::IsFpsVisible() const
{
    return Fps;
}

void tfp::Interface::DisplayFps()
{
    if(LastTimeFpsCount != tfp::Seconds())
    {
        LastTimeFpsCount = tfp::Seconds();
        FpsCounter = "FPS: " + tfp::FloatToString(floor(1.0f / Clock.GetDeltaTime()));
    }
    if(Fps)
    {
        GameHandle->GameScreen.Draw(Text.Create(FpsCounter, FontList.FindFontWithName("Fps"), sf::Vector2f(GameHandle->GameScreen.GetOriginalViewSize().x - 400.0f, 5.0f), GameHandle->GameScreen.GetViewScale()));
    }
}

void tfp::Interface::SetTileZIndex(unsigned Value)
{
    TerrainWindowTileZIndex = Value;
    if(TerrainWindowTileZIndex > 6) TerrainWindowTileZIndex = 6;

    TerrainSelectInputSetZIndex.Area.SetText(tfp::IntToString(TerrainWindowTileZIndex));
}

bool tfp::Interface::IsGridVisible() const
{
    return ShowGridEnabled;
}

std::string tfp::Interface::GetTileBuildMode()
{
    return SetTile;
}

void tfp::Interface::SetTileBuildMode(std::string Mode)
{
    SetTile = Mode;
    if(SetTile == "")
    {
        SetTile = "terrain";
        Debug.Command("settilemode [terrain/object/mob/special/npc]");
    }
}

void tfp::Interface::SetGrid(int Width, int Height)
{
    if(Width == 0 && SetTile == "object")
    {
        int TileObjectID = TerrainWindowTileIndex + TerrainWindowTileSetIndex * 100;
        if(TileObjectID < (int) ObjectGifList.GetList().size())
        {
            Width = ObjectGifList.GetList()[TileObjectID].FrameWidth;
        }

    }

    if(Height == 0 && SetTile == "object")
    {
        int TileObjectID = TerrainWindowTileIndex + TerrainWindowTileSetIndex * 100;
        if(TileObjectID < (int) ObjectGifList.GetList().size())
        {
            Height = ObjectGifList.GetList()[TileObjectID].FrameHeight;
        }
    }

    if(Width > 1 && Height > 1)
    {
        GridEnabled = true;
        ShowGridEnabled = true;
        GridSize.x = Width;
        GridSize.y = Height;
    }
    else
    {
        Debug.Command("Grid size must be greater then 1");
    }
}

void tfp::Interface::ShowGrid(bool State)
{
    ShowGridEnabled = State;
}

void tfp::Interface::EnableGrid(bool State)
{
    GridEnabled = State;
}

void tfp::Interface::LoadDebugMessages()
{
    if(!Debug.IsDebugMessageAvailiable(LastDebugMessage))
    {
        LastDebugMessage = Debug.WhatIsTheLowestDebugMessageNumber() - 1;
    }
    while(Debug.IsDebugMessageAvailiable(LastDebugMessage + 1))
    {
        SendCommandLineOutputLine(Debug.GetDebugMessage(++LastDebugMessage));
    }
}

const bool tfp::Interface::IsCommandLineActive()
{
    return CommandLineFocusArea.IsActive();
}

void tfp::Interface::SetTileIndex(int Value)
{

    int TileCount = 0;

    if(SetTile == "terrain") TileCount = TerrainList.GetTerrainArray().size();
    else if(SetTile == "object") TileCount = ObjectGifList.GetList().size();


    if(Value < 0 ) Value = 0;
    if(TileCount == 0)
    {
        Value = 0;
    }
    else if(TileCount % 100 != 0)
    {
        if(Value > (int) TileCount / 100) Value = (int) TileCount / 100;
    }
    else
    {
        if(Value > (int) TileCount / 100 - 1) Value = (int) TileCount / 100 - 1;
    }


    TerrainWindowTileIndex = tfp::NotBelowZero(Value);

}

void tfp::Interface::AddTileSetIndex(int Value)
{
    Value += (int) TerrainWindowTileSetIndex;
    if(Value < 0 ) Value = 0;

    int TileCount = 0;

    if(SetTile == "terrain") TileCount = TerrainList.GetTerrainArray().size();
    else if(SetTile == "object") TileCount = ObjectGifList.GetList().size();

    if(TileCount == 0)
    {
        Value = 0;
    }
    else if(TileCount % 100 != 0)
    {
        if(Value > (int) TileCount / 100) Value = (int) TileCount / 100;
    }
    else
    {
        if(Value > (int) TileCount / 100 - 1) Value = (int) TileCount / 100 - 1;
    }

    TerrainWindowTileSetIndex = tfp::NotBelowZero(Value);
}

sf::Vector2f tfp::Interface::GetGridShift()
{
    return GridShift;
}

void tfp::Interface::SetLanguageNamesIndexAdd(int Value)
{
    Value += (int) LanguageNamesIndex;
    if(Value < 0 ) Value = 0;
    if(Language.LanguageNameList.size() == 0)
    {
        Value = 0;
    }
    else if(Language.LanguageNameList.size() % 6 != 0)
    {
        if(Value > (int) Language.LanguageNameList.size() / 6) Value = (int) Language.LanguageNameList.size() / 6;
    }
    else
    {
        if(Value > (int) Language.LanguageNameList.size() / 6 - 1) Value = (int) Language.LanguageNameList.size() / 6 - 1;
    }

    LanguageNamesIndex = tfp::NotBelowZero(Value);
    // Debug.Info("Language index set to: " + tfp::IntToString(LanguageNamesIndex));
}

void tfp::Interface::SetGridShift(float Horizontal, float Vertical)
{
    GridShift.x = Horizontal;
    GridShift.y = Vertical;
}

inline void tfp::Interface::LoadAssetsIfNotLoaded()
{
    if(!FontList.IsAllLoaded()) FontList.LoadAllFonts(GameHandle);
    if(!TerrainList.IsAllTerrainLoaded()) TerrainList.LoadAllTerrains(GameHandle);
    if(!ObjectGifList.IsLoaded()) ObjectGifList.LoadGifFiles(GameHandle);
    if(!SpellGifList.IsLoaded()) SpellGifList.LoadGifFiles(GameHandle);
    if(!CharacterGifList.IsLoaded()) CharacterGifList.LoadGifFiles(GameHandle);
    if(!MobGifList.IsLoaded()) MobGifList.LoadGifFiles(GameHandle);
    if(!SpecialObjectGifList.IsLoaded()) SpecialObjectGifList.LoadGifFiles(GameHandle);
    if(!ItemList.IsLoaded()) ItemList.LoadAllItems(GameHandle);
    if(!BackgroundImage.IsLoaded()) BackgroundImage.LoadAll(GameHandle);
}

inline void tfp::Interface::DrawGrid()
{
    if(GridEnabled && ShowGridEnabled)
    {
        sf::VertexArray Lines(sf::Lines, 2);
        Lines[0].color = sf::Color::Black;
        Lines[1].color = sf::Color::Black;

        /// Vertical lines
        float VerticalPosition = 0.0f - (float) ((int) GameHandle->GameCamera.GetPosition().x % (int) GridSize.x) + GridShift.x;
        while(VerticalPosition <= GameHandle->GameScreen.GetViewSize().x)
        {
            Lines[0].position = sf::Vector2f(VerticalPosition, 0);
            Lines[1].position = sf::Vector2f(VerticalPosition, GameHandle->GameScreen.GetViewSize().y);
            GameHandle->GameScreen.Draw(Lines);
            VerticalPosition += GridSize.x;
        }

        /// Horizontal lines
        float HorizontalPosition = 0.0f - (float) ((int) GameHandle->GameCamera.GetPosition().y % (int) GridSize.y) + GridShift.y;
        while(HorizontalPosition <= GameHandle->GameScreen.GetViewSize().y)
        {
            Lines[0].position = sf::Vector2f(0, HorizontalPosition);
            Lines[1].position = sf::Vector2f(GameHandle->GameScreen.GetViewSize().x, HorizontalPosition);
            GameHandle->GameScreen.Draw(Lines);
            HorizontalPosition += GridSize.y;
        }


    }
}

inline void tfp::Interface::DrawBackground(std::string &GameType)
{
    if(GameType == "menu") BackgroundImage.Draw("MenuBackground", GameHandle);
    // else if(GameType == "mapeditor") BackgroundImage.Draw("MapEditorBackground", GameHandle);
    else if(GameType == "server") BackgroundImage.Draw("ServerBackground", GameHandle);
}

inline void tfp::Interface::DrawSpecialEffects()
{
    RainEffect.Display();
    SnowEffect.Display();
    StormEffect.Display();
    NightEffect.Display();
}

inline void tfp::Interface::CloseNotSuitableWindows(std::string &GameType)
{
    if(GameType == "mapeditor")
    {
        CharacterInfoWindow.Show(false);
        InventoryWindow.Show(false);
    }
    else if(GameType == "game")
    {
        TerrainSelectWindow.Show(false);
    }
}

inline void tfp::Interface::DrawUserInterface()
{
    HealthBar.Display();
    ManaBar.Display();
}

inline void tfp::Interface::DrawWindows()
{
    /// Interface
    TerrainSelectWindow.Display();

    if(TerrainSelectWindow.IsVisible())
    {
        TerrainSelectButtonNext.SetPosition(TerrainSelectWindow.GetPosition().x + 1000.0f, TerrainSelectWindow.GetPosition().y + 2000.0f);
        TerrainSelectButtonPrevious.SetPosition(TerrainSelectWindow.GetPosition().x, TerrainSelectWindow.GetPosition().y + 2000.0f);

        TerrainSelectButtonSetMapSize.SetPosition(TerrainSelectWindow.GetPosition().x + 1000.0f, TerrainSelectWindow.GetPosition().y + 2250.0f);
        TerrainSelectButtonSpecial.SetPosition(TerrainSelectWindow.GetPosition().x + 1500.0f, TerrainSelectWindow.GetPosition().y + 2125.0f);
        TerrainSelectButtonMobs.SetPosition(TerrainSelectWindow.GetPosition().x + 1000.0f, TerrainSelectWindow.GetPosition().y + 2125.0f);
        TerrainSelectButtonObjects.SetPosition(TerrainSelectWindow.GetPosition().x + 500.0f, TerrainSelectWindow.GetPosition().y + 2125.0f);
        TerrainSelectButtonTerrain.SetPosition(TerrainSelectWindow.GetPosition().x, TerrainSelectWindow.GetPosition().y + 2125.0f);

        TerrainSelectInputSetGridSizeX.SetPosition(TerrainSelectWindow.GetPosition().x + 0.0f, TerrainSelectWindow.GetPosition().y + 2375.0f);
        TerrainSelectInputSetGridSizeY.SetPosition(TerrainSelectWindow.GetPosition().x + 500.0f, TerrainSelectWindow.GetPosition().y + 2375.0f);
        TerrainSelectButtonSetGridSize.SetPosition(TerrainSelectWindow.GetPosition().x + 1000.0f, TerrainSelectWindow.GetPosition().y + 2375.0f);
        TerrainSelectInputSetMapSizeX.SetPosition(TerrainSelectWindow.GetPosition().x + 0.0f, TerrainSelectWindow.GetPosition().y + 2250.0f);
        TerrainSelectInputSetMapSizeY.SetPosition(TerrainSelectWindow.GetPosition().x + 500.0f, TerrainSelectWindow.GetPosition().y + 2250.0f);

        TerrainSelectInputSetZIndex.SetPosition(TerrainSelectWindow.GetPosition().x + 0.0f, TerrainSelectWindow.GetPosition().y + 2500.0f);

        TerrainSelectButtonSetZIndex.SetPosition(TerrainSelectWindow.GetPosition().x + 500.0f, TerrainSelectWindow.GetPosition().y + 2500.0f);

        TerrainSelectButtonSetZIndexHelp.SetPosition(TerrainSelectWindow.GetPosition().x + 1500.0f, TerrainSelectWindow.GetPosition().y + 2500.0f);

        TerrainSelectButtonDisableGrid.SetPosition(TerrainSelectWindow.GetPosition().x + 1000.0f, TerrainSelectWindow.GetPosition().y + 2625.0f);
        TerrainSelectButtonHideGrid.SetPosition(TerrainSelectWindow.GetPosition().x + 0.0f, TerrainSelectWindow.GetPosition().y + 2625.0f);
        TerrainSelectButtonLockCamera.SetPosition(TerrainSelectWindow.GetPosition().x + 0.0f, TerrainSelectWindow.GetPosition().y + 2750.0f);
        TerrainSelectButtonUnlockCamera.SetPosition(TerrainSelectWindow.GetPosition().x + 1000.0f, TerrainSelectWindow.GetPosition().y + 2750.0f);
        TerrainSelectButtonLoadMap.SetPosition(TerrainSelectWindow.GetPosition().x + 0.0f, TerrainSelectWindow.GetPosition().y + 2875.0f);
        TerrainSelectButtonSaveMap.SetPosition(TerrainSelectWindow.GetPosition().x + 1000.0f, TerrainSelectWindow.GetPosition().y + 2875.0f);


        TerrainSelectButtonSetGridSize.SetCommand("setgridsize " + TerrainSelectInputSetGridSizeX.Area.GetText() + " " + TerrainSelectInputSetGridSizeY.Area.GetText());
        TerrainSelectButtonSetMapSize.SetCommand("setmapsize " + TerrainSelectInputSetMapSizeX.Area.GetText() + " " + TerrainSelectInputSetMapSizeY.Area.GetText());
        TerrainSelectButtonSetZIndex.SetCommand("setzindex " + TerrainSelectInputSetZIndex.Area.GetText());
        if(IsGridVisible()) TerrainSelectButtonHideGrid.SetText("Hide grid");
        else TerrainSelectButtonHideGrid.SetText("Show grid");
        if(GridEnabled) TerrainSelectButtonDisableGrid.SetText("Disable grid");
        else TerrainSelectButtonDisableGrid.SetText("Enable grid");

        TerrainSelectButtonNext.Area.SetDisabled(false);
        TerrainSelectButtonPrevious.Area.SetDisabled(false);
        TerrainSelectButtonSetMapSize.Area.SetDisabled(false);
        TerrainSelectButtonSpecial.Area.SetDisabled(false);
        TerrainSelectButtonObjects.Area.SetDisabled(false);
        TerrainSelectButtonTerrain.Area.SetDisabled(false);
        TerrainSelectInputSetGridSizeX.Area.SetDisabled(false);
        TerrainSelectInputSetGridSizeY.Area.SetDisabled(false);
        TerrainSelectButtonSetGridSize.Area.SetDisabled(false);
        TerrainSelectInputSetMapSizeX.Area.SetDisabled(false);
        TerrainSelectInputSetMapSizeY.Area.SetDisabled(false);
        TerrainSelectButtonDisableGrid.Area.SetDisabled(false);
        TerrainSelectButtonLockCamera.Area.SetDisabled(false);
        TerrainSelectButtonUnlockCamera.Area.SetDisabled(false);
        TerrainSelectButtonLoadMap.Area.SetDisabled(false);
        TerrainSelectButtonSaveMap.Area.SetDisabled(false);
        TerrainSelectButtonHideGrid.Area.SetDisabled(false);
        TerrainSelectButtonMobs.Area.SetDisabled(false);
        TerrainSelectInputSetZIndex.Area.SetDisabled(false);
        TerrainSelectButtonSetZIndex.Area.SetDisabled(false);
        TerrainSelectButtonSetZIndexHelp.Area.SetDisabled(false);
        TerrainSelectButtonNext.Display();
        TerrainSelectButtonPrevious.Display();
        TerrainSelectButtonSpecial.Display();
        TerrainSelectButtonObjects.Display();
        TerrainSelectButtonMobs.Display();
        TerrainSelectButtonTerrain.Display();
        TerrainSelectButtonSetGridSize.Display();
        TerrainSelectInputSetGridSizeX.Display();
        TerrainSelectInputSetGridSizeY.Display();
        TerrainSelectButtonSetMapSize.Display();
        TerrainSelectInputSetMapSizeX.Display();
        TerrainSelectInputSetMapSizeY.Display();
        TerrainSelectButtonDisableGrid.Display();
        TerrainSelectButtonHideGrid.Display();
        TerrainSelectButtonLockCamera.Display();
        TerrainSelectButtonUnlockCamera.Display();
        TerrainSelectButtonLoadMap.Display();
        TerrainSelectButtonSaveMap.Display();
        TerrainSelectInputSetZIndex.Display();
        TerrainSelectButtonSetZIndex.Display();
        TerrainSelectButtonSetZIndexHelp.Display();

        DrawTerrainWindowContent();

    }
    else
    {
        TerrainSelectButtonNext.Area.SetDisabled(true);
        TerrainSelectButtonPrevious.Area.SetDisabled(true);
        TerrainSelectButtonSetMapSize.Area.SetDisabled(true);
        TerrainSelectButtonSpecial.Area.SetDisabled(true);
        TerrainSelectButtonMobs.Area.SetDisabled(true);
        TerrainSelectButtonObjects.Area.SetDisabled(true);
        TerrainSelectButtonTerrain.Area.SetDisabled(true);
        TerrainSelectInputSetGridSizeX.Area.SetDisabled(true);
        TerrainSelectInputSetGridSizeY.Area.SetDisabled(true);
        TerrainSelectButtonSetGridSize.Area.SetDisabled(true);
        TerrainSelectInputSetMapSizeX.Area.SetDisabled(true);
        TerrainSelectInputSetMapSizeY.Area.SetDisabled(true);
        TerrainSelectButtonDisableGrid.Area.SetDisabled(true);
        TerrainSelectButtonHideGrid.Area.SetDisabled(true);
        TerrainSelectButtonLockCamera.Area.SetDisabled(true);
        TerrainSelectButtonUnlockCamera.Area.SetDisabled(true);
        TerrainSelectButtonLoadMap.Area.SetDisabled(true);
        TerrainSelectButtonSaveMap.Area.SetDisabled(true);
        TerrainSelectInputSetZIndex.Area.SetDisabled(true);
        TerrainSelectButtonSetZIndex.Area.SetDisabled(true);
        TerrainSelectButtonSetZIndexHelp.Area.SetDisabled(true);
    }

    InventoryWindow.Resize(GameHandle->ControlledPlayer.GetInventorySize().x * 200, GameHandle->ControlledPlayer.GetInventorySize().y * 200);
    InventoryWindow.Display();
    if(InventoryWindow.IsVisible())
    {
        for(unsigned i = 0; i < GameHandle->ControlledPlayer.InventoryItemList.size(); i++)
        {
            InventoryDragableArray[i].SetDisabled(false);
            if(!InventoryDragableArray[i].IsActive())
            {
                if(DraggedItemId == (int) i)
                {
                    /// Przedmiot puszczony
                    int SwapItemId = -1;
                    for(unsigned j = 0; j < GameHandle->ControlledPlayer.InventoryItemList.size(); j++)
                    {
                        if((int) j != DraggedItemId && InventoryDragableArray[j].IsMouseInBorders()) SwapItemId = j;
                    }

                    if(SwapItemId != -1) /// Zamiana w ekwipunku
                    {


                        /// Zamiana
                        if(GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Name == GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Name &&
                           GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Rarity == GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Rarity &&
                           GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Improvement == GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Improvement)
                        {
                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                            {
                                if(GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Quantity + GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Quantity / 2 <= ItemList.FindItemWithName(GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Name).MaximumQuantity)
                                {
                                    /// Ilosc sie miesci
                                    int MoveQuantity = GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Quantity / 2;
                                    GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Quantity += MoveQuantity;
                                    GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Quantity -= MoveQuantity;
                                    if(GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Quantity <= 0)
                                        GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Name = "Unknown";
                                }
                                else
                                {
                                    /// Ilosc sie nie miesci
                                    GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Quantity -= ItemList.FindItemWithName(GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Name).MaximumQuantity - GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Quantity;
                                    GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Quantity = ItemList.FindItemWithName(GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Name).MaximumQuantity;
                                }
                            }
                            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                            {
                                if(GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Quantity + 1 <= ItemList.FindItemWithName(GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Name).MaximumQuantity)
                                {
                                    /// Ilosc sie miesci
                                    GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Quantity += 1;
                                    GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Quantity -= 1;
                                    if(GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Quantity <= 0)
                                        GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Name = "Unknown";
                                }
                                else
                                {
                                    /// Ilosc sie nie miesci
                                    /// To nic sie nie dzieje
                                }
                            }
                            else
                            {
                                if(GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Quantity + GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Quantity <= ItemList.FindItemWithName(GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Name).MaximumQuantity)
                                {
                                    /// Ilosc sie miesci
                                    GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Quantity += GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Quantity;
                                    GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Quantity = 0;
                                    GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Name = "Unknown";
                                }
                                else
                                {
                                    /// Ilosc sie nie miesci
                                    GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Quantity -= ItemList.FindItemWithName(GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Name).MaximumQuantity - GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Quantity;
                                    GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Quantity = ItemList.FindItemWithName(GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Name).MaximumQuantity;
                                }
                            }
                        }
                        else if(GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Name == "Unknown" && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Quantity > 1)
                        {
                            /// Na puste miejsce z shiftem
                            GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Quantity = GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Quantity / 2;
                            GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Quantity -= GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Quantity;
                            GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Name = GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Name;
                            GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Rarity = GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Rarity;
                            GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Improvement = GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Improvement;

                        }
                        else if(GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Name == "Unknown" && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Quantity > 1)
                        {
                            /// Na puste miejsce z controlem
                            GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Quantity = 1;
                            GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Quantity -= 1;
                            GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Name = GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Name;
                            GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Rarity = GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Rarity;
                            GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Improvement = GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Improvement;
                        }
                        else
                        {
                            std::string TmpName = GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Name;
                            int TmpQuantity = GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Quantity;
                            std::string TmpRarity = GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Rarity;
                            int TmpImprovement = GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Improvement;
                            GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Name = GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Name;
                            GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Quantity = GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Quantity;
                            GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Rarity = GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Rarity;
                            GameHandle->ControlledPlayer.InventoryItemList[SwapItemId].Improvement = GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Improvement;
                            GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Name = TmpName;
                            GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Quantity = TmpQuantity;
                            GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Rarity = TmpRarity;
                            GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Improvement = TmpImprovement;
                        }

                    }
                    else if(InventoryWindow.IsMouseInsideBorders() || CharacterInfoWindow.IsMouseInsideBorders())
                    {

                    }
                    else /// Upuszczamy przedmiot na mape
                    {
                        GameHandle->GameNetworkClient.SendCommandToServer("dropitem " + tfp::IntToString(DraggedItemId) + " " + tfp::FloatToString(GameHandle->GameMouse.GetMousePositionOnMap().x) + " " + tfp::FloatToString(GameHandle->GameMouse.GetMousePositionOnMap().y));
                    }

                    DraggedItemId = -1;
                }
                InventoryDragableArray[i].SetPosition({InventoryWindow.GetPosition().x + (i % GameHandle->ControlledPlayer.GetInventorySize().x) * 200 * GameHandle->GameScreen.GetViewScale(), InventoryWindow.GetPosition().y + (i / GameHandle->ControlledPlayer.GetInventorySize().x) * 200 * GameHandle->GameScreen.GetViewScale()});
            }
            else
            {
                DraggedItemId = i;
                InventoryDragableArray[i].Move({- GameHandle->GameMouse.GetLeftMouseButtonDeltaDragScaled().x, - GameHandle->GameMouse.GetLeftMouseButtonDeltaDragScaled().y});
            }
        }

        InventoryWindow.Draw(Sprite.Create(InventoryGridTexture, {0, 0, InventoryWindow.GetInsideSize().x, InventoryWindow.GetInsideSize().y}, 0, 0, GameHandle->GameScreen.GetViewScale()));
        for(int i = 0; i < GameHandle->ControlledPlayer.GetInventorySize().y; i++)
        {
            for(int j = 0; j < GameHandle->ControlledPlayer.GetInventorySize().x; j++)
            {
                unsigned Index = i * GameHandle->ControlledPlayer.GetInventorySize().x + j;
                if((int) Index == DraggedItemId) continue;
                if(Index < GameHandle->ControlledPlayer.InventoryItemList.size())
                {
                    if(GameHandle->ControlledPlayer.InventoryItemList[Index].Name != "Unknown")
                    {
                        GameHandle->GameScreen.Draw(Sprite.Create(ItemList.FindItemWithName(GameHandle->ControlledPlayer.InventoryItemList[Index].Name).Texture, InventoryDragableArray[Index].GetPosition().x, InventoryDragableArray[Index].GetPosition().y, GameHandle->GameScreen.GetViewScale()));
                        if(GameHandle->ControlledPlayer.InventoryItemList[Index].Quantity != 1)
                            GameHandle->GameScreen.Draw(Text.Create(tfp::IntToString(GameHandle->ControlledPlayer.InventoryItemList[Index].Quantity), FontList.FindFontWithName("ItemQuantityLabel"),{InventoryDragableArray[Index].GetPosition().x + 10 * GameHandle->GameScreen.GetViewScale(), InventoryDragableArray[Index].GetPosition().y + 190 * GameHandle->GameScreen.GetViewScale() - FontList.FindFontWithName("ItemQuantityLabel").CharacterSize}, GameHandle->GameScreen.GetViewScale()));
                    }
                }
            }
        }

        /// Przesuwany item
        if(DraggedItemId != -1)
        {
            if(DraggedItemId < (int) GameHandle->ControlledPlayer.InventoryItemList.size())
            {
                if(GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Name != "Unknown")
                {
                    GameHandle->GameScreen.Draw(Sprite.Create(ItemList.FindItemWithName(GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Name).Texture, InventoryDragableArray[DraggedItemId].GetPosition().x, InventoryDragableArray[DraggedItemId].GetPosition().y, GameHandle->GameScreen.GetViewScale()));
                    if(GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Quantity != 1)
                        GameHandle->GameScreen.Draw(Text.Create(tfp::IntToString(GameHandle->ControlledPlayer.InventoryItemList[DraggedItemId].Quantity), FontList.FindFontWithName("ItemQuantityLabel"),{InventoryDragableArray[DraggedItemId].GetPosition().x + 10 * GameHandle->GameScreen.GetViewScale(), InventoryDragableArray[DraggedItemId].GetPosition().y + 190 * GameHandle->GameScreen.GetViewScale() - FontList.FindFontWithName("ItemQuantityLabel").CharacterSize}, GameHandle->GameScreen.GetViewScale()));
                }
            }
        }
        else
        {
            /// Staty itemku
            for(unsigned i = 0; i < GameHandle->ControlledPlayer.InventoryItemList.size(); i++)
            {
                if(InventoryDragableArray[i].IsMouseInBorders() && GameHandle->ControlledPlayer.InventoryItemList[i].Name != "Unknown")
                {
                    float PositionY = GameHandle->GameScreen.GetViewSize().y / 4;
                    float PositionX = 0;
                    float Scale = GameHandle->GameScreen.GetViewScale();
                    if(GameHandle->GameMouse.GetMousePositionScaled().x < GameHandle->GameScreen.GetViewSize().x / 2)
                    {
                        PositionX = GameHandle->GameScreen.GetViewSize().x - 1200.0f * Scale;
                    }

                    sf::VertexArray Background(sf::Quads, 4);
                    Background[0].position = sf::Vector2f(PositionX, PositionY);
                    Background[1].position = sf::Vector2f(PositionX + 1200.0f * Scale, PositionY);
                    Background[2].position = sf::Vector2f(PositionX + 1200.0f * Scale, PositionY + 1000 * Scale);
                    Background[3].position = sf::Vector2f(PositionX, PositionY + 1000 * Scale);

                    Background[0].color = sf::Color(0 , 0, 0, 230);
                    Background[1].color = sf::Color(0 , 0, 0, 230);
                    Background[2].color = sf::Color(0 , 0, 0, 230);
                    Background[3].color = sf::Color(0 , 0, 0, 230);

                    GameHandle->GameScreen.Draw(Background);

                    std::string ItemName = GameHandle->ControlledPlayer.InventoryItemList[i].Name;
                    std::string InformationText;
                    std::wstring TextToDraw;

                    tfp::ItemStats ItemStatsTmp = ItemList.FindItemWithName(ItemName);
                    tfp::Item ItemTmp = GameHandle->ControlledPlayer.InventoryItemList[i];

                    float PowerMultiplier = 0.0f;

                    if(ItemTmp.Rarity == "Broken") PowerMultiplier = 0.5f;
                    else if(ItemTmp.Rarity == "Common") PowerMultiplier = 1.0f;
                    else if(ItemTmp.Rarity == "Rare") PowerMultiplier = 1.1f;
                    else if(ItemTmp.Rarity == "Epic") PowerMultiplier = 1.25f;
                    else if(ItemTmp.Rarity == "Legendary") PowerMultiplier = 1.5f;

                    if(ItemTmp.Improvement == 0) PowerMultiplier *= 1.0f;
                    else if(ItemTmp.Improvement == 1) PowerMultiplier *= 1.1f;
                    else if(ItemTmp.Improvement == 2) PowerMultiplier *= 1.2f;
                    else if(ItemTmp.Improvement == 3) PowerMultiplier *= 1.3f;
                    else if(ItemTmp.Improvement == 4) PowerMultiplier *= 1.4f;
                    else if(ItemTmp.Improvement == 5) PowerMultiplier *= 1.5f;

                    if(ItemStatsTmp.Type == "Material" || ItemStatsTmp.Type == "Potion" || ItemStatsTmp.Type == "Scroll" ||
                       ItemStatsTmp.Type == "Bag")
                    {
                        TextToDraw = Language.Translate(ItemStatsTmp.FullName);
                    }
                    else
                    {
                        TextToDraw = Language.Translate(ItemStatsTmp.FullName) + L" + " + tfp::IntToWString(ItemTmp.Improvement);
                    }
                    PositionY += 25 * Scale;
                    if(ItemStatsTmp.Type == "Material") GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformationNameMaterial"), {PositionX + 600.0f * Scale, PositionY + 10.0f * Scale},GameHandle->GameScreen.GetViewScale(), tfp::AlignCenter, 65));
                    else if(ItemStatsTmp.Type == "Potion") GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformationNamePotion"), {PositionX + 600.0f * Scale, PositionY + 10.0f * Scale},GameHandle->GameScreen.GetViewScale(), tfp::AlignCenter, 65));
                    else if(ItemStatsTmp.Type == "Scroll") GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformationNameScroll"), {PositionX + 600.0f * Scale, PositionY + 10.0f * Scale},GameHandle->GameScreen.GetViewScale(), tfp::AlignCenter, 65));
                    else if(ItemTmp.Rarity == "Broken") GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformationNameBroken"), {PositionX + 600.0f * Scale, PositionY + 10.0f * Scale},GameHandle->GameScreen.GetViewScale(), tfp::AlignCenter, 65));
                    else if(ItemTmp.Rarity == "Common") GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformationNameCommon"), {PositionX + 600.0f * Scale, PositionY + 10.0f * Scale},GameHandle->GameScreen.GetViewScale(), tfp::AlignCenter, 65));
                    else if(ItemTmp.Rarity == "Rare") GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformationNameRare"), {PositionX + 600.0f * Scale, PositionY + 10.0f * Scale},GameHandle->GameScreen.GetViewScale(), tfp::AlignCenter, 65));
                    else if(ItemTmp.Rarity == "Epic") GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformationNameEpic"), {PositionX + 600.0f * Scale, PositionY + 10.0f * Scale},GameHandle->GameScreen.GetViewScale(), tfp::AlignCenter, 65));
                    else if(ItemTmp.Rarity == "Legendary") GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformationNameLegendary"), {PositionX + 600.0f * Scale, PositionY + 10.0f * Scale},GameHandle->GameScreen.GetViewScale(), tfp::AlignCenter, 65));
                    else
                    {
                        Debug.Warning("Unknown rarity: " + ItemTmp.Rarity + " in:" + ItemName);
                    }


                    PositionY += 90.0f * Scale;
                    InformationText = ItemStatsTmp.Type;
                    GameHandle->GameScreen.Draw(Text.CreateTranslated(InformationText, FontList.FindFontWithName("ItemInformation"), {PositionX + 600.0f * Scale, PositionY},GameHandle->GameScreen.GetViewScale(), tfp::AlignCenter, 50));

                    PositionY += 65.0f * Scale;
                    TextToDraw = Language.Translate("Required level") + L":   " + tfp::IntToWString(ItemStatsTmp.RequiredLevel);
                    GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformation"), {PositionX + 600.0f * Scale, PositionY},GameHandle->GameScreen.GetViewScale(), tfp::AlignCenter, 50));

                    if(ItemStatsTmp.Type == "Material" || ItemStatsTmp.Type == "Potion" || ItemStatsTmp.Type == "Scroll" ||
                       ItemStatsTmp.Type == "Bag")
                    {

                    }
                    else
                    {
                        PositionY += 65.0f * Scale;
                        TextToDraw = Language.Translate("Rarity") + L":   " + Language.Translate(ItemTmp.Rarity);
                        GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformation"), {PositionX + 600.0f * Scale, PositionY},GameHandle->GameScreen.GetViewScale(), tfp::AlignCenter, 50));
                    }

                    PositionY += 65.0f * Scale;
                    TextToDraw = Language.Translate("Quantity") + L":   " + tfp::IntToWString(ItemTmp.Quantity) + L" / " + tfp::IntToWString(ItemStatsTmp.MaximumQuantity);
                    GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformation"), {PositionX + 600.0f * Scale, PositionY},GameHandle->GameScreen.GetViewScale(), tfp::AlignCenter, 50));


                    if(ItemStatsTmp.MaximumDamage > 0)
                    {
                        PositionY += 75.0f * Scale;
                        TextToDraw =  tfp::IntToWString(std::floor(ItemStatsTmp.MinimumDamage * PowerMultiplier)) + L" - " + tfp::IntToWString(std::floor(ItemStatsTmp.MaximumDamage * PowerMultiplier)) + L"   " + Language.Translate("Damage");
                        GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformation"), {PositionX + 50.0f * Scale, PositionY},GameHandle->GameScreen.GetViewScale(), tfp::AlignLeft, 60));
                    }

                    if(ItemStatsTmp.Type == "Weapon")
                    {
                        PositionY += 75.0f * Scale;
                        TextToDraw = tfp::FloatToWString(ItemStatsTmp.AttackSpeed * PowerMultiplier) + L"   " + Language.Translate("Attack speed");
                        GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformation"), {PositionX + 50.0f * Scale, PositionY},GameHandle->GameScreen.GetViewScale(), tfp::AlignLeft, 60));
                    }

                    if(ItemStatsTmp.Strength > 0)
                    {
                        PositionY += 75.0f * Scale;
                        TextToDraw = L"+ " + tfp::IntToWString(std::floor(ItemStatsTmp.Strength * PowerMultiplier)) + L"   " + Language.Translate("Strength");
                        GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformation"), {PositionX + 50.0f * Scale, PositionY},GameHandle->GameScreen.GetViewScale(), tfp::AlignLeft, 60));
                    }

                    if(ItemStatsTmp.Vitality > 0)
                    {
                        PositionY += 75.0f * Scale;
                        TextToDraw = L"+ " + tfp::IntToWString(std::floor(ItemStatsTmp.Vitality * PowerMultiplier)) + L"   " + Language.Translate("Vitality");
                        GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformation"), {PositionX + 50.0f * Scale, PositionY},GameHandle->GameScreen.GetViewScale(), tfp::AlignLeft, 60));
                    }

                    if(ItemStatsTmp.Evasion > 0)
                    {
                        PositionY += 75.0f * Scale;
                        TextToDraw = L"+ " + tfp::IntToWString(std::floor(ItemStatsTmp.Evasion * PowerMultiplier)) + L" %   " + Language.Translate("Evasion");
                        GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformation"), {PositionX + 50.0f * Scale, PositionY},GameHandle->GameScreen.GetViewScale(), tfp::AlignLeft, 60));
                    }

                    if(ItemStatsTmp.Intelligence > 0)
                    {
                        PositionY += 75.0f * Scale;
                        TextToDraw = L"+ " + tfp::IntToWString(std::floor(ItemStatsTmp.Intelligence * PowerMultiplier)) + L"   " + Language.Translate("Intelligence");
                        GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformation"), {PositionX + 50.0f * Scale, PositionY},GameHandle->GameScreen.GetViewScale(), tfp::AlignLeft, 60));
                    }

                    if(ItemStatsTmp.Type == "Boots")
                    {
                        PositionY += 75.0f * Scale;
                        TextToDraw = L"+ " + tfp::FloatToWString(ItemStatsTmp.MovementSpeed * PowerMultiplier) + L"   " + Language.Translate("Movement speed");
                        GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformation"), {PositionX + 50.0f * Scale, PositionY},GameHandle->GameScreen.GetViewScale(), tfp::AlignLeft, 60));
                    }

                    if(ItemStatsTmp.LifeSteal > 0)
                    {
                        PositionY += 75.0f * Scale;
                        TextToDraw =  tfp::IntToWString(std::floor(ItemStatsTmp.LifeSteal * PowerMultiplier)) + L" %   " + Language.Translate("Lifesteal");
                        GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformation"), {PositionX + 50.0f * Scale, PositionY},GameHandle->GameScreen.GetViewScale(), tfp::AlignLeft, 60));
                    }

                    if(ItemStatsTmp.IceResistance > 0)
                    {
                        PositionY += 75.0f * Scale;
                        TextToDraw = L"+ " + tfp::IntToWString(std::floor(ItemStatsTmp.IceResistance * PowerMultiplier)) + L" %   " + Language.Translate("Ice resistance");
                        GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformation"), {PositionX + 50.0f * Scale, PositionY},GameHandle->GameScreen.GetViewScale(), tfp::AlignLeft, 60));
                    }

                    if(ItemStatsTmp.DarknessResistance > 0)
                    {
                        PositionY += 75.0f * Scale;
                        TextToDraw = L"+ " + tfp::IntToWString(std::floor(ItemStatsTmp.DarknessResistance * PowerMultiplier)) + L" %   " + Language.Translate("Darkness resistance");
                        GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformation"), {PositionX + 50.0f * Scale, PositionY},GameHandle->GameScreen.GetViewScale(), tfp::AlignLeft, 60));
                    }

                    if(ItemStatsTmp.FireResistance > 0)
                    {
                        PositionY += 75.0f * Scale;
                        TextToDraw = L"+ " + tfp::IntToWString(std::floor(ItemStatsTmp.FireResistance * PowerMultiplier)) + L" %   " + Language.Translate("Fire resistance");
                        GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformation"), {PositionX + 50.0f * Scale, PositionY},GameHandle->GameScreen.GetViewScale(), tfp::AlignLeft, 60));
                    }

                    if(ItemStatsTmp.WaterResistance > 0)
                    {
                        PositionY += 75.0f * Scale;
                        TextToDraw = L"+ " + tfp::IntToWString(std::floor(ItemStatsTmp.WaterResistance * PowerMultiplier)) + L" %   " + Language.Translate("Water resistance");
                        GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformation"), {PositionX + 50.0f * Scale, PositionY},GameHandle->GameScreen.GetViewScale(), tfp::AlignLeft, 60));
                    }

                    if(ItemStatsTmp.LightResistance > 0)
                    {
                        PositionY += 75.0f * Scale;
                        TextToDraw = L"+ " + tfp::IntToWString(std::floor(ItemStatsTmp.LightResistance * PowerMultiplier)) + L" %   " + Language.Translate("Light resistance");
                        GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformation"), {PositionX + 50.0f * Scale, PositionY},GameHandle->GameScreen.GetViewScale(), tfp::AlignLeft, 60));
                    }

                    if(ItemStatsTmp.EarthResistance > 0)
                    {
                        PositionY += 75.0f * Scale;
                        TextToDraw = L"+ " + tfp::IntToWString(std::floor(ItemStatsTmp.EarthResistance * PowerMultiplier)) + L" %   " + Language.Translate("Earth resistance");
                        GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformation"), {PositionX + 50.0f * Scale, PositionY},GameHandle->GameScreen.GetViewScale(), tfp::AlignLeft, 60));
                    }

                    if(ItemStatsTmp.IceElement > 0)
                    {
                        PositionY += 75.0f * Scale;
                        TextToDraw = L"+ " + tfp::IntToWString(std::floor(ItemStatsTmp.IceElement * PowerMultiplier)) + L" %   " + Language.Translate("Ice element");
                        GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformation"), {PositionX + 50.0f * Scale, PositionY},GameHandle->GameScreen.GetViewScale(), tfp::AlignLeft, 60));
                    }

                    if(ItemStatsTmp.DarknessElement > 0)
                    {
                        PositionY += 75.0f * Scale;
                        TextToDraw = L"+ " + tfp::IntToWString(std::floor(ItemStatsTmp.DarknessElement * PowerMultiplier)) + L" %   " + Language.Translate("Darkness element");
                        GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformation"), {PositionX + 50.0f * Scale, PositionY},GameHandle->GameScreen.GetViewScale(), tfp::AlignLeft, 60));
                    }

                    if(ItemStatsTmp.FireElement > 0)
                    {
                        PositionY += 75.0f * Scale;
                        TextToDraw = L"+ " + tfp::IntToWString(std::floor(ItemStatsTmp.FireElement * PowerMultiplier)) + L" %   " + Language.Translate("Fire element");
                        GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformation"), {PositionX + 50.0f * Scale, PositionY},GameHandle->GameScreen.GetViewScale(), tfp::AlignLeft, 60));
                    }

                    if(ItemStatsTmp.WaterElement > 0)
                    {
                        PositionY += 75.0f * Scale;
                        TextToDraw = L"+ " + tfp::IntToWString(std::floor(ItemStatsTmp.WaterElement * PowerMultiplier)) + L" %   " + Language.Translate("Water element");
                        GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformation"), {PositionX + 50.0f * Scale, PositionY},GameHandle->GameScreen.GetViewScale(), tfp::AlignLeft, 60));
                    }

                    if(ItemStatsTmp.LightElement > 0)
                    {
                        PositionY += 75.0f * Scale;
                        TextToDraw = L"+ " + tfp::IntToWString(std::floor(ItemStatsTmp.LightElement * PowerMultiplier)) + L" %   " + Language.Translate("Light element");
                        GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformation"), {PositionX + 50.0f * Scale, PositionY},GameHandle->GameScreen.GetViewScale(), tfp::AlignLeft, 60));
                    }

                    if(ItemStatsTmp.EarthElement > 0)
                    {
                        PositionY += 75.0f * Scale;
                        TextToDraw = L"+ " + tfp::IntToWString(std::floor(ItemStatsTmp.EarthElement * PowerMultiplier)) + L" %   " + Language.Translate("Earth element");
                        GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformation"), {PositionX + 50.0f * Scale, PositionY},GameHandle->GameScreen.GetViewScale(), tfp::AlignLeft, 60));
                    }

                    if(ItemStatsTmp.HealthRegen > 0)
                    {
                        PositionY += 75.0f * Scale;
                        TextToDraw = L"+ " + tfp::IntToWString(std::floor(ItemStatsTmp.HealthRegen * PowerMultiplier)) + L"   " + Language.Translate("Health regeneration");
                        GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformation"), {PositionX + 50.0f * Scale, PositionY},GameHandle->GameScreen.GetViewScale(), tfp::AlignLeft, 60));
                    }

                    if(ItemStatsTmp.ManaRegen > 0)
                    {
                        PositionY += 75.0f * Scale;
                        TextToDraw = L"+ " + tfp::IntToWString(std::floor(ItemStatsTmp.ManaRegen * PowerMultiplier)) + L"   " + Language.Translate("Mana regeneration");
                        GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformation"), {PositionX + 50.0f * Scale, PositionY},GameHandle->GameScreen.GetViewScale(), tfp::AlignLeft, 60));
                    }

                    if(ItemStatsTmp.InventorySize.y > 0)
                    {
                        PositionY += 75.0f * Scale;
                        TextToDraw = tfp::IntToWString(ItemStatsTmp.InventorySize.x * ItemStatsTmp.InventorySize.y) + L"   " + Language.Translate("Inventory space");
                        GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ItemInformation"), {PositionX + 50.0f * Scale, PositionY},GameHandle->GameScreen.GetViewScale(), tfp::AlignLeft, 60));
                    }

                    break;
                }
            }
        }

    }
    else
    {
        for(int i = 0; i < 100; i++)
        {
            InventoryDragableArray[i].SetDisabled(true);
        }
    }


    OptionsWindow.Display();
    if(OptionsWindow.IsVisible())
    {
        /// Ustawianie pozycji
        OptionsMenu.SetPosition(OptionsWindow.GetPosition().x, OptionsWindow.GetPosition().y + 0.0f);
        OptionsMapEditor.SetPosition(OptionsWindow.GetPosition().x, OptionsWindow.GetPosition().y + 125.0f);
        OptionsControls.SetPosition(OptionsWindow.GetPosition().x, OptionsWindow.GetPosition().y + 250.0f);
        OptionsVideoOptions.SetPosition(OptionsWindow.GetPosition().x, OptionsWindow.GetPosition().y + 375.0f);
        OptionsLanguage.SetPosition(OptionsWindow.GetPosition().x, OptionsWindow.GetPosition().y + 500.0f);
        OptionsAuthors.SetPosition(OptionsWindow.GetPosition().x, OptionsWindow.GetPosition().y + 625.0f);
        OptionsExit.SetPosition(OptionsWindow.GetPosition().x, OptionsWindow.GetPosition().y + 750.0f);
        OptionsExitAll.SetPosition(OptionsWindow.GetPosition().x, OptionsWindow.GetPosition().y + 875.0f);
        OptionsClose.SetPosition(OptionsWindow.GetPosition().x, OptionsWindow.GetPosition().y + 1000.0f);

        /// Wlaczanie
        OptionsMenu.Area.SetDisabled(false);
        OptionsMapEditor.Area.SetDisabled(false);
        OptionsVideoOptions.Area.SetDisabled(false);
        OptionsControls.Area.SetDisabled(false);
        OptionsLanguage.Area.SetDisabled(false);
        OptionsAuthors.Area.SetDisabled(false);
        OptionsExit.Area.SetDisabled(false);
        OptionsExitAll.Area.SetDisabled(false);
        OptionsClose.Area.SetDisabled(false);

        /// Wyswietlanie
        OptionsMenu.Display();
        OptionsMapEditor.Display();
        OptionsControls.Display();
        OptionsVideoOptions.Display();
        OptionsLanguage.Display();
        OptionsAuthors.Display();
        OptionsExit.Display();
        OptionsExitAll.Display();
        OptionsClose.Display();

    }
    else
    {
        /// Wylaczanie
        OptionsMenu.Area.SetDisabled(true);
        OptionsMapEditor.Area.SetDisabled(true);
        OptionsControls.Area.SetDisabled(true);
        OptionsVideoOptions.Area.SetDisabled(true);
        OptionsLanguage.Area.SetDisabled(true);
        OptionsAuthors.Area.SetDisabled(true);
        OptionsExit.Area.SetDisabled(true);
        OptionsExitAll.Area.SetDisabled(true);
        OptionsClose.Area.SetDisabled(true);
    }

    LanguageWindow.Display();
    if(LanguageWindow.IsVisible())
    {
        for(int i = 0; i < 6; i++)
        {
            int LanguageIndex = i + LanguageNamesIndex * 6;
            if((int) Language.LanguageNameList.size() > LanguageIndex)
            {
                LanguageButtonSelect[i].SetText(Language.LanguageNameList[LanguageIndex]);
                LanguageButtonSelect[i].SetCommand("setlanguage " + Language.LanguageNameList[LanguageIndex]);
            }
            else
            {
                LanguageButtonSelect[i].SetText("");
                LanguageButtonSelect[i].SetCommand("");
            }

        }

        for(int i = 0; i < 6; i++)
            LanguageButtonSelect[i].SetPosition(LanguageWindow.GetPosition().x, LanguageWindow.GetPosition().y + 125.0f * i);

        LanguageButtonSelect[6].SetPosition(LanguageWindow.GetPosition().x, LanguageWindow.GetPosition().y + 125.0f * 6);
        LanguageButtonSelect[7].SetPosition(LanguageWindow.GetPosition().x + 500.0f, LanguageWindow.GetPosition().y + 125.0f * 6);
        LanguageButtonSelect[8].SetPosition(LanguageWindow.GetPosition().x, LanguageWindow.GetPosition().y + 125.0f * 7);

        for(int i = 0; i < 9; i++)
            LanguageButtonSelect[i].Area.SetDisabled(false);
        for(int i = 0; i < 9; i++)
            LanguageButtonSelect[i].Display();
    }
    else
    {
        for(int i = 0; i < 9; i++)
        {
            LanguageButtonSelect[i].Area.SetDisabled(true);
        }
    }

    ControlsWindow.Display();
    if(ControlsWindow.IsVisible())
    {
        ScreenshotInputBar.Area.SetDisabled(false);
        ShowConsoleInputBar.Area.SetDisabled(true);
        ShowOptionsInputBar.Area.SetDisabled(true);
        ShowTerrainSelectInputBar.Area.SetDisabled(false);
        UndoTerrainChangesInputBar.Area.SetDisabled(false);
        RedoTerrainChangesInputBar.Area.SetDisabled(false);
        ShowInventoryInputBar.Area.SetDisabled(false);
        ShowCharacterInfoInputBar.Area.SetDisabled(false);
        OpenChatInputBar.Area.SetDisabled(false);
        CloseControlsButton.Area.SetDisabled(false);
        ResetControlsButton.Area.SetDisabled(false);

        sf::VertexArray Lines(sf::Quads, 4);

        Lines[0].color = sf::Color(112, 141, 129, 255);
        Lines[1].color = sf::Color(112, 141, 129, 255);
        Lines[2].color = sf::Color(148, 174, 137, 255);
        Lines[3].color = sf::Color(148, 174, 137, 255);

        Lines[0].position = ControlsWindow.GetPosition();
        Lines[1].position = sf::Vector2f(ControlsWindow.GetPosition().x + (float) ControlsWindow.GetInsideSize().x, ControlsWindow.GetPosition().y);
        Lines[3].position = sf::Vector2f(ControlsWindow.GetPosition().x, ControlsWindow.GetPosition().y + (float) ControlsWindow.GetInsideSize().y);
        Lines[2].position = sf::Vector2f(ControlsWindow.GetPosition().x + (float) ControlsWindow.GetInsideSize().x, ControlsWindow.GetPosition().y + (float) ControlsWindow.GetInsideSize().y);


        for(int i = 0; i < 4; i++)
        {
            Lines[i].position.x *= GameHandle->GameScreen.GetViewScale();
            Lines[i].position.y *= GameHandle->GameScreen.GetViewScale();
        }

        GameHandle->GameScreen.Draw(Lines);


        ShowOptionsInputBar.SetPosition(ControlsWindow.GetPosition().x + 1087.5f, ControlsWindow.GetPosition().y + 15.0f);
        GameHandle->GameScreen.Draw(Text.CreateTranslated("Options", FontList.FindFontWithName("ControlLabel"), {ControlsWindow.GetPosition().x + 1050.0f, ControlsWindow.GetPosition().y + 15.0f}, GameHandle->GameScreen.GetViewScale(), tfp::AlignRight));
        ShowConsoleInputBar.SetPosition(ControlsWindow.GetPosition().x + 1087.5f, ControlsWindow.GetPosition().y + 115.0f);
        GameHandle->GameScreen.Draw(Text.CreateTranslated("Console", FontList.FindFontWithName("ControlLabel"), {ControlsWindow.GetPosition().x + 1050.0f, ControlsWindow.GetPosition().y + 115.0f}, GameHandle->GameScreen.GetViewScale(), tfp::AlignRight));
        ShowTerrainSelectInputBar.SetPosition(ControlsWindow.GetPosition().x + 1087.5f, ControlsWindow.GetPosition().y + 215.0f);
        GameHandle->GameScreen.Draw(Text.CreateTranslated("Terrain select", FontList.FindFontWithName("ControlLabel"), {ControlsWindow.GetPosition().x + 1050.0f, ControlsWindow.GetPosition().y + 215.0f}, GameHandle->GameScreen.GetViewScale(), tfp::AlignRight));
        UndoTerrainChangesInputBar.SetPosition(ControlsWindow.GetPosition().x + 1087.5f, ControlsWindow.GetPosition().y + 315.0f);
        GameHandle->GameScreen.Draw(Text.CreateTranslated("Undo changes", FontList.FindFontWithName("ControlLabel"), {ControlsWindow.GetPosition().x + 1050.0f, ControlsWindow.GetPosition().y + 315.0f}, GameHandle->GameScreen.GetViewScale(), tfp::AlignRight));
        RedoTerrainChangesInputBar.SetPosition(ControlsWindow.GetPosition().x + 1087.5f, ControlsWindow.GetPosition().y + 415.0f);
        GameHandle->GameScreen.Draw(Text.CreateTranslated("Redo changes", FontList.FindFontWithName("ControlLabel"), {ControlsWindow.GetPosition().x + 1050.0f, ControlsWindow.GetPosition().y + 415.0f}, GameHandle->GameScreen.GetViewScale(), tfp::AlignRight));
        ShowInventoryInputBar.SetPosition(ControlsWindow.GetPosition().x + 1087.5f, ControlsWindow.GetPosition().y + 515.0f);
        GameHandle->GameScreen.Draw(Text.CreateTranslated("Inventory", FontList.FindFontWithName("ControlLabel"), {ControlsWindow.GetPosition().x + 1050.0f, ControlsWindow.GetPosition().y + 515.0f}, GameHandle->GameScreen.GetViewScale(), tfp::AlignRight));
        ShowCharacterInfoInputBar.SetPosition(ControlsWindow.GetPosition().x + 1087.5f, ControlsWindow.GetPosition().y + 615.0f);
        GameHandle->GameScreen.Draw(Text.CreateTranslated("Character information", FontList.FindFontWithName("ControlLabel"), {ControlsWindow.GetPosition().x + 1050.0f, ControlsWindow.GetPosition().y + 615.0f}, GameHandle->GameScreen.GetViewScale(), tfp::AlignRight));
        ScreenshotInputBar.SetPosition(ControlsWindow.GetPosition().x + 1087.5f, ControlsWindow.GetPosition().y + 715.0f);
        GameHandle->GameScreen.Draw(Text.CreateTranslated("Screenshot", FontList.FindFontWithName("ControlLabel"), {ControlsWindow.GetPosition().x + 1050.0f, ControlsWindow.GetPosition().y + 715.0f}, GameHandle->GameScreen.GetViewScale(), tfp::AlignRight));
        OpenChatInputBar.SetPosition(ControlsWindow.GetPosition().x + 1087.5f, ControlsWindow.GetPosition().y + 815.0f);
        GameHandle->GameScreen.Draw(Text.CreateTranslated("Chat", FontList.FindFontWithName("ControlLabel"), {ControlsWindow.GetPosition().x + 1050.0f, ControlsWindow.GetPosition().y + 815.0f}, GameHandle->GameScreen.GetViewScale(), tfp::AlignRight));

        CloseControlsButton.SetPosition(ControlsWindow.GetPosition().x + 0.0f, ControlsWindow.GetPosition().y + 2375.0f);
        ResetControlsButton.SetPosition(ControlsWindow.GetPosition().x + 3950.0f, ControlsWindow.GetPosition().y + 2175.0f);




        ScreenshotInputBar.Display();
        ShowConsoleInputBar.Display();
        ShowOptionsInputBar.Display();
        ShowTerrainSelectInputBar.Display();
        UndoTerrainChangesInputBar.Display();
        RedoTerrainChangesInputBar.Display();
        ShowInventoryInputBar.Display();
        ShowCharacterInfoInputBar.Display();
        OpenChatInputBar.Display();
        CloseControlsButton.Display();
        ResetControlsButton.Display();

    }
    else
    {
        ScreenshotInputBar.Area.SetDisabled(true);
        ShowConsoleInputBar.Area.SetDisabled(true);
        ShowOptionsInputBar.Area.SetDisabled(true);
        ShowTerrainSelectInputBar.Area.SetDisabled(true);
        UndoTerrainChangesInputBar.Area.SetDisabled(true);
        RedoTerrainChangesInputBar.Area.SetDisabled(true);
        ShowInventoryInputBar.Area.SetDisabled(true);
        ShowCharacterInfoInputBar.Area.SetDisabled(true);
        OpenChatInputBar.Area.SetDisabled(true);
        CloseControlsButton.Area.SetDisabled(true);
        ResetControlsButton.Area.SetDisabled(true);
    }

    VideoOptionsWindow.Display();
    if(VideoOptionsWindow.IsVisible())
    {
        sf::VertexArray Lines(sf::Quads, 4);

        Lines[0].color = sf::Color(112, 141, 129, 255);
        Lines[1].color = sf::Color(112, 141, 129, 255);
        Lines[2].color = sf::Color(148, 174, 137, 255);
        Lines[3].color = sf::Color(148, 174, 137, 255);

        Lines[0].position = VideoOptionsWindow.GetPosition();
        Lines[1].position = sf::Vector2f(VideoOptionsWindow.GetPosition().x + (float) VideoOptionsWindow.GetInsideSize().x, VideoOptionsWindow.GetPosition().y);
        Lines[3].position = sf::Vector2f(VideoOptionsWindow.GetPosition().x, VideoOptionsWindow.GetPosition().y + (float) VideoOptionsWindow.GetInsideSize().y);
        Lines[2].position = sf::Vector2f(VideoOptionsWindow.GetPosition().x + (float) VideoOptionsWindow.GetInsideSize().x, VideoOptionsWindow.GetPosition().y + (float) VideoOptionsWindow.GetInsideSize().y);


        for(int i = 0; i < 4; i++)
        {
            Lines[i].position.x *= GameHandle->GameScreen.GetViewScale();
            Lines[i].position.y *= GameHandle->GameScreen.GetViewScale();
        }

        GameHandle->GameScreen.Draw(Lines);


        GameHandle->GameScreen.Draw(Text.CreateTranslated("Menu", FontList.FindFontWithName("VideoOptionsLabel"), {VideoOptionsWindow.GetPosition().x + 25.0f, VideoOptionsWindow.GetPosition().y + 25.0f}, GameHandle->GameScreen.GetViewScale()));
        for(int i = 0; i < 12; i++)
        {
            MenuWindowSizeButton[i].Area.SetDisabled(false);
            MenuWindowSizeButton[i].SetPosition(VideoOptionsWindow.GetPosition().x + 25.0f + 425.0f * i, VideoOptionsWindow.GetPosition().y + 175.0f);
            MenuWindowSizeButton[i].Display();
        }
        if(GameHandle->GameScreen.GetFullScreen("menu"))
        {
            MenuWindowSizeButton[12].SetText("Fullscreen: on");
            MenuWindowSizeButton[12].SetCommand("setmenufullscreen false");
        }
        else
        {
            MenuWindowSizeButton[12].SetText("Fullscreen: off");
            MenuWindowSizeButton[12].SetCommand("setmenufullscreen true");
        }

        MenuWindowSizeButton[12].Area.SetDisabled(false);
        MenuWindowSizeButton[12].SetPosition(VideoOptionsWindow.GetPosition().x + 25.0f, VideoOptionsWindow.GetPosition().y + 325.0f);
        MenuWindowSizeButton[12].Display();

        GameHandle->GameScreen.Draw(Text.CreateTranslated("Game", FontList.FindFontWithName("VideoOptionsLabel"), {VideoOptionsWindow.GetPosition().x + 25.0f, VideoOptionsWindow.GetPosition().y + 475.0f}, GameHandle->GameScreen.GetViewScale()));
        for(int i = 0; i < 12; i++)
        {
            GameWindowSizeButton[i].Area.SetDisabled(false);
            GameWindowSizeButton[i].SetPosition(VideoOptionsWindow.GetPosition().x + 25.0f + 425.0f * i, VideoOptionsWindow.GetPosition().y + 625.0f);
            GameWindowSizeButton[i].Display();
        }
        if(GameHandle->GameScreen.GetFullScreen("game"))
        {
            GameWindowSizeButton[12].SetText("Fullscreen: on");
            GameWindowSizeButton[12].SetCommand("setgamefullscreen false");
        }
        else
        {
            GameWindowSizeButton[12].SetText("Fullscreen: off");
            GameWindowSizeButton[12].SetCommand("setgamefullscreen true");
        }

        GameWindowSizeButton[12].Area.SetDisabled(false);
        GameWindowSizeButton[12].SetPosition(VideoOptionsWindow.GetPosition().x + 25.0f, VideoOptionsWindow.GetPosition().y + 775.0f);
        GameWindowSizeButton[12].Display();

        GameHandle->GameScreen.Draw(Text.CreateTranslated("Map editor", FontList.FindFontWithName("VideoOptionsLabel"), {VideoOptionsWindow.GetPosition().x + 25.0f, VideoOptionsWindow.GetPosition().y + 925.0f}, GameHandle->GameScreen.GetViewScale()));
        for(int i = 0; i < 12; i++)
        {
            MapEditorWindowSizeButton[i].Area.SetDisabled(false);
            MapEditorWindowSizeButton[i].SetPosition(VideoOptionsWindow.GetPosition().x + 25.0f + 425.0f * i, VideoOptionsWindow.GetPosition().y + 1075.0f);
            MapEditorWindowSizeButton[i].Display();
        }
        if(GameHandle->GameScreen.GetFullScreen("mapeditor"))
        {
            MapEditorWindowSizeButton[12].SetText("Fullscreen: on");
            MapEditorWindowSizeButton[12].SetCommand("setmapeditorfullscreen false");
        }
        else
        {
            MapEditorWindowSizeButton[12].SetText("Fullscreen: off");
            MapEditorWindowSizeButton[12].SetCommand("setmapeditorfullscreen true");
        }

        MapEditorWindowSizeButton[12].Area.SetDisabled(false);
        MapEditorWindowSizeButton[12].SetPosition(VideoOptionsWindow.GetPosition().x + 25.0f, VideoOptionsWindow.GetPosition().y + 1225.0f);
        MapEditorWindowSizeButton[12].Display();

        GameHandle->GameScreen.Draw(Text.CreateTranslated("Server", FontList.FindFontWithName("VideoOptionsLabel"), {VideoOptionsWindow.GetPosition().x + 25.0f, VideoOptionsWindow.GetPosition().y + 1375.0f}, GameHandle->GameScreen.GetViewScale()));
        for(int i = 0; i < 12; i++)
        {
            ServerWindowSizeButton[i].Area.SetDisabled(false);
            ServerWindowSizeButton[i].SetPosition(VideoOptionsWindow.GetPosition().x + 25.0f + 425.0f * i, VideoOptionsWindow.GetPosition().y + 1525.0f);
            ServerWindowSizeButton[i].Display();
        }
        if(GameHandle->GameScreen.GetFullScreen("server"))
        {
            ServerWindowSizeButton[12].SetText("Fullscreen: on");
            ServerWindowSizeButton[12].SetCommand("setserverfullscreen false");
        }
        else
        {
            ServerWindowSizeButton[12].SetText("Fullscreen: off");
            ServerWindowSizeButton[12].SetCommand("setserverfullscreen true");
        }

        ServerWindowSizeButton[12].Area.SetDisabled(false);
        ServerWindowSizeButton[12].SetPosition(VideoOptionsWindow.GetPosition().x + 25.0f, VideoOptionsWindow.GetPosition().y + 1675.0f);
        ServerWindowSizeButton[12].Display();

        VerticalSyncButton.Area.SetDisabled(false);
        SetFrameLimitButton.Area.SetDisabled(false);
        FrameLimitInputBar.Area.SetDisabled(false);

        GameHandle->GameScreen.Draw(Text.CreateTranslated("Global", FontList.FindFontWithName("VideoOptionsLabel"), {VideoOptionsWindow.GetPosition().x + 25.0f, VideoOptionsWindow.GetPosition().y + 1825.0f}, GameHandle->GameScreen.GetViewScale()));

        if(GameHandle->GameScreen.GetVerticalSync())
        {
            VerticalSyncButton.SetText("Vertical synchronization: on");
            VerticalSyncButton.SetCommand("setverticalsync false");
        }
        else
        {
            VerticalSyncButton.SetText("Vertical synchronization: off");
            VerticalSyncButton.SetCommand("setverticalsync true");
        }

        SetFrameLimitButton.SetCommand("setframelimit " + FrameLimitInputBar.Area.GetText());

        VerticalSyncButton.SetPosition(VideoOptionsWindow.GetPosition().x + 25.0f, VideoOptionsWindow.GetPosition().y + 2125.0f);
        SetFrameLimitButton.SetPosition(VideoOptionsWindow.GetPosition().x + 500.0f, VideoOptionsWindow.GetPosition().y + 1975.0f);
        FrameLimitInputBar.SetPosition(VideoOptionsWindow.GetPosition().x + 25.0f, VideoOptionsWindow.GetPosition().y + 1975.0f);

        VerticalSyncButton.Display();
        SetFrameLimitButton.Display();
        FrameLimitInputBar.Display();

        VideoOptionsCloseButton.SetPosition(VideoOptionsWindow.GetPosition().x + 0.0f, VideoOptionsWindow.GetPosition().y + 2375.0f);

        VideoOptionsResetButton.SetPosition(VideoOptionsWindow.GetPosition().x + 4600.0f, VideoOptionsWindow.GetPosition().y + 2125.0f);

        VideoOptionsCloseButton.Area.SetDisabled(false);
        VideoOptionsResetButton.Area.SetDisabled(false);

        VideoOptionsCloseButton.Display();
        VideoOptionsResetButton.Display();

    }
    else
    {
        for(int i = 0; i < 13; i++)
        {
            MenuWindowSizeButton[i].Area.SetDisabled(true);
            GameWindowSizeButton[i].Area.SetDisabled(true);
            MapEditorWindowSizeButton[i].Area.SetDisabled(true);
            ServerWindowSizeButton[i].Area.SetDisabled(true);
        }
        VerticalSyncButton.Area.SetDisabled(true);
        SetFrameLimitButton.Area.SetDisabled(true);
        FrameLimitInputBar.Area.SetDisabled(true);
        VideoOptionsCloseButton.Area.SetDisabled(true);
        VideoOptionsResetButton.Area.SetDisabled(true);
    }

    AuthorsWindow.Display();
    if(AuthorsWindow.IsVisible())
    {
        AuthorsButtonClose.SetPosition(AuthorsWindow.GetPosition().x, AuthorsWindow.GetPosition().y + 2375);
        AuthorsButtonClose.Area.SetDisabled(false);

        sf::VertexArray Lines(sf::Quads, 4);

        Lines[0].color = sf::Color(112, 141, 129, 255);
        Lines[1].color = sf::Color(112, 141, 129, 255);
        Lines[2].color = sf::Color(148, 174, 137, 255);
        Lines[3].color = sf::Color(148, 174, 137, 255);

        Lines[0].position = AuthorsWindow.GetPosition();
        Lines[1].position = sf::Vector2f(AuthorsWindow.GetPosition().x + (float) AuthorsWindow.GetInsideSize().x, AuthorsWindow.GetPosition().y);
        Lines[3].position = sf::Vector2f(AuthorsWindow.GetPosition().x, AuthorsWindow.GetPosition().y + (float) AuthorsWindow.GetInsideSize().y);
        Lines[2].position = sf::Vector2f(AuthorsWindow.GetPosition().x + (float) AuthorsWindow.GetInsideSize().x, AuthorsWindow.GetPosition().y + (float) AuthorsWindow.GetInsideSize().y);

        for(int i = 0; i < 4; i++)
        {
            Lines[i].position.x *= GameHandle->GameScreen.GetViewScale();
            Lines[i].position.y *= GameHandle->GameScreen.GetViewScale();
        }

        GameHandle->GameScreen.Draw(Lines);

        GameHandle->GameScreen.Draw(Text.CreateTranslated("Directed by", FontList.FindFontWithName("AuthorsTitle"), AuthorsWindow.GetPosition() + sf::Vector2f(1125.0f, 15.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));
        GameHandle->GameScreen.Draw(Text.Create("Ernest Mezyk", FontList.FindFontWithName("Authors"),AuthorsWindow.GetPosition() + sf::Vector2f(1125.0f, 115.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));

        GameHandle->GameScreen.Draw(Text.CreateTranslated("Written by", FontList.FindFontWithName("AuthorsTitle"), AuthorsWindow.GetPosition() + sf::Vector2f(1125.0f, 315.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));
        // GameHandle->GameScreen.Draw(Text.Create("Szymon Kazmierczak", FontList.FindFontWithName("Authors"),AuthorsWindow.GetPosition() + sf::Vector2f(1125.0f, 415.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));

        GameHandle->GameScreen.Draw(Text.CreateTranslated("Programmers", FontList.FindFontWithName("AuthorsTitle"), AuthorsWindow.GetPosition() + sf::Vector2f(1125.0f, 615.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));
        GameHandle->GameScreen.Draw(Text.Create("Ernest Mezyk", FontList.FindFontWithName("Authors"), AuthorsWindow.GetPosition() + sf::Vector2f(1125.0f, 715.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));
        // GameHandle->GameScreen.Draw(Text.Create("Alan Hudela", FontList.FindFontWithName("Authors"), AuthorsWindow.GetPosition() + sf::Vector2f(1125.0f, 815.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));

        GameHandle->GameScreen.Draw(Text.CreateTranslated("Art", FontList.FindFontWithName("AuthorsTitle"), AuthorsWindow.GetPosition() + sf::Vector2f(1125.0f, 1015.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));
        GameHandle->GameScreen.Draw(Text.Create("???", FontList.FindFontWithName("Authors"), AuthorsWindow.GetPosition() + sf::Vector2f(1125.0f, 1115.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));

        GameHandle->GameScreen.Draw(Text.CreateTranslated("Music", FontList.FindFontWithName("AuthorsTitle"), AuthorsWindow.GetPosition() + sf::Vector2f(1125.0f, 1315.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));
        GameHandle->GameScreen.Draw(Text.Create("???", FontList.FindFontWithName("Authors"), AuthorsWindow.GetPosition() + sf::Vector2f(1125.0f, 1415.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));

        GameHandle->GameScreen.Draw(Text.CreateTranslated("Sound effects", FontList.FindFontWithName("AuthorsTitle"), AuthorsWindow.GetPosition() + sf::Vector2f(1125.0f, 1615.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));
        GameHandle->GameScreen.Draw(Text.Create("???", FontList.FindFontWithName("Authors"), AuthorsWindow.GetPosition() + sf::Vector2f(1125.0f, 1715.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));

        GameHandle->GameScreen.Draw(Text.CreateTranslated("Level design", FontList.FindFontWithName("AuthorsTitle"), AuthorsWindow.GetPosition() + sf::Vector2f(1125.0f, 1915.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));
        GameHandle->GameScreen.Draw(Text.Create("???", FontList.FindFontWithName("Authors"), AuthorsWindow.GetPosition() + sf::Vector2f(1125.0f, 2015.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));


        GameHandle->GameScreen.Draw(Text.CreateTranslated("Translation", FontList.FindFontWithName("AuthorsTitle"),AuthorsWindow.GetPosition() + sf::Vector2f(2250.0f, 15.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));
        GameHandle->GameScreen.Draw(Text.Create("Ernest Mezyk", FontList.FindFontWithName("Authors"),AuthorsWindow.GetPosition() + sf::Vector2f(2250.0f, 115.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));
        GameHandle->GameScreen.Draw(Text.Create("???", FontList.FindFontWithName("Authors"),AuthorsWindow.GetPosition() + sf::Vector2f(2250.0f, 215.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));
        GameHandle->GameScreen.Draw(Text.Create("??", FontList.FindFontWithName("Authors"),AuthorsWindow.GetPosition() + sf::Vector2f(2250.0f, 315.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));

        GameHandle->GameScreen.Draw(Text.CreateTranslated("Testers", FontList.FindFontWithName("AuthorsTitle"),AuthorsWindow.GetPosition() + sf::Vector2f(2250.0f, 515.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));
        GameHandle->GameScreen.Draw(Text.Create("???", FontList.FindFontWithName("Authors"),AuthorsWindow.GetPosition() + sf::Vector2f(2250.0f, 615.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));


        GameHandle->GameScreen.Draw(Text.CreateTranslated("Other", FontList.FindFontWithName("AuthorsTitle"),AuthorsWindow.GetPosition() + sf::Vector2f(3375.0f, 15.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));

        GameHandle->GameScreen.Draw(Text.Create("SFML", FontList.FindFontWithName("Authors"),AuthorsWindow.GetPosition() + sf::Vector2f(3375.0f, 115.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));
        GameHandle->GameScreen.Draw(Text.Create("Laurent Gomila", FontList.FindFontWithName("Authors"),AuthorsWindow.GetPosition() + sf::Vector2f(3375.0f, 215.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));

        GameHandle->GameScreen.Draw(Text.Create("RapidXml", FontList.FindFontWithName("Authors"),AuthorsWindow.GetPosition() + sf::Vector2f(3375.0f, 415.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));
        GameHandle->GameScreen.Draw(Text.Create("Marcin Kalicinski", FontList.FindFontWithName("Authors"),AuthorsWindow.GetPosition() + sf::Vector2f(3375.0f, 515.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));

        GameHandle->GameScreen.Draw(Text.Create("PixelPerfectCollision", FontList.FindFontWithName("Authors"),AuthorsWindow.GetPosition() + sf::Vector2f(3375.0f, 715.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));
        GameHandle->GameScreen.Draw(Text.Create("Ernesto Alejo", FontList.FindFontWithName("Authors"),AuthorsWindow.GetPosition() + sf::Vector2f(3375.0f, 815.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));

        GameHandle->GameScreen.Draw(Text.Create("Text conversion", FontList.FindFontWithName("Authors"),AuthorsWindow.GetPosition() + sf::Vector2f(3375.0f, 1015.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));
        GameHandle->GameScreen.Draw(Text.Create("Paul McKenzie", FontList.FindFontWithName("Authors"),AuthorsWindow.GetPosition() + sf::Vector2f(3375.0f, 1115.0f), GameHandle->GameScreen.GetViewScale(), AlignCenter));

        AuthorsButtonClose.Display();
    }
    else
    {
        AuthorsButtonClose.Area.SetDisabled(true);
    }

    CharacterInfoWindow.Display();
}

inline void tfp::Interface::DrawTerrainWindowContent()
{
    /// Zawartosc przybornika
    if(TerrainSelectWindow.IsVisible())
    {
        if(SetTile == "terrain")
        {
            if(TerrainNamesIndexPrevious == TerrainWindowTileSetIndex && TerrainList.IsGraphicDriverTerrainLoadingBoostEnabled() && !TerrainSelectWindow.HasMoved())
            {
                TerrainNamesIndexPrevious = TerrainWindowTileSetIndex;
                sf::RenderStates State;
                State.texture = &TerrainList.GetTextureBuffer();
                GameHandle->GameScreen.DrawVertex(&TerrainWindowVertexBoostList[0], TerrainWindowVertexBoostList.size(), sf::Quads, State);
            }
            else
            {
                if(TerrainList.IsGraphicDriverTerrainLoadingBoostEnabled())
                {
                    TerrainWindowVertexBoostList.resize(0);
                }
                float PositionX = 0;
                float PositionY = 0;
                float PositionScale = GameHandle->GameScreen.GetViewScale();
                sf::Vector2f WindowPosition = TerrainSelectWindow.GetPosition();
                /// Wszystkie tereny
                for(unsigned i = TerrainWindowTileSetIndex * 100; i < TerrainList.GetTerrainArray().size() && i < (TerrainWindowTileSetIndex + 1) * 100; i++)
                {
                    if(TerrainList.IsGraphicDriverTerrainLoadingBoostEnabled())
                    {
                        PositionX = (WindowPosition.x + (i % 10) * 200) * PositionScale;
                        PositionY = (WindowPosition.y + ((i - (i % 10)) % 100) / 10 * 200) * PositionScale;
                        TerrainWindowVertexPoint.position = {PositionX, PositionY};
                        TerrainWindowVertexPoint.texCoords = TerrainList.FindTerrainWithName(TerrainList.GetTerrainArray()[i].Name).TextureBufferPosition;
                        TerrainWindowVertexBoostList.push_back(TerrainWindowVertexPoint);

                        TerrainWindowVertexPoint.position.x += 200.0f * PositionScale;
                        TerrainWindowVertexPoint.texCoords.x += 200.0f;
                        TerrainWindowVertexBoostList.push_back(TerrainWindowVertexPoint);

                        TerrainWindowVertexPoint.position.y += 200.0f * PositionScale;
                        TerrainWindowVertexPoint.texCoords.y += 200.0f;
                        TerrainWindowVertexBoostList.push_back(TerrainWindowVertexPoint);

                        TerrainWindowVertexPoint.position.x -= 200.0f * PositionScale;
                        TerrainWindowVertexPoint.texCoords.x -= 200.0f;
                        TerrainWindowVertexBoostList.push_back(TerrainWindowVertexPoint);
                    }
                    else
                    {
                        TerrainSelectWindow.Draw(Sprite.Create(TerrainList.FindTerrainWithName(TerrainList.GetTerrainArray()[i].Name).Texture,
                                                       (i % 10) * 200,
                                                       ((i - (i % 10)) % 100) / 10 * 200,
                                                       GameHandle->GameScreen.GetViewScale()
                                                       ));
                    }
                }

                if(TerrainList.IsGraphicDriverTerrainLoadingBoostEnabled())
                {
                    sf::RenderStates State;
                    State.texture = &TerrainList.GetTextureBuffer();
                    GameHandle->GameScreen.DrawVertex(&TerrainWindowVertexBoostList[0], TerrainWindowVertexBoostList.size(), sf::Quads, State);
                }

            }

            /// Ten gownik wybranego terenu (bedzie osobno na razie sie renderowal)
            TerrainSelectWindow.Draw(Sprite.Create(TerrainList.GetSelectedTerrainTexture(),
                                               (TerrainWindowTileIndex % 10) * 200,
                                               ((TerrainWindowTileIndex - (TerrainWindowTileIndex % 10)) % 100) / 10 * 200,
                                               GameHandle->GameScreen.GetViewScale()
                                               ));
        }

        /// DO ZROBIENIA WYSWIETLANIE LISTY OBIEKTOW
        if(SetTile == "object")
        {
            // unused sf::Vector2f WindowPosition = TerrainSelectWindow.GetPosition();
            /// Wszystkie tereny
            for(unsigned i = TerrainWindowTileSetIndex * 100; i < ObjectGifList.GetList().size() && i < (TerrainWindowTileSetIndex + 1) * 100; i++)
            {
                float ResizeScale1 =  200.0f / ObjectGifList.GetList()[i].FrameWidth;
                float ResizeScale2 =  200.0f / ObjectGifList.GetList()[i].FrameHeight;
                float ResizeScaleFinal;
                if(ResizeScale1 < ResizeScale2) ResizeScaleFinal = ResizeScale1;
                    else ResizeScaleFinal = ResizeScale2;

                    TerrainSelectWindow.Draw(Sprite.Create(ObjectGifList.GetList()[i].GifTexture[0],
                                                   (i % 10) * 200,
                                                   ((i - (i % 10)) % 100) / 10 * 200,
                                                   GameHandle->GameScreen.GetViewScale(),
                                                    GameHandle->GameScreen.GetViewScale(),
                                                    ResizeScaleFinal,
                                                    ResizeScaleFinal
                                                   ));
            }

            /// Ten gownik wybranego terenu (bedzie osobno na razie sie renderowal)
            TerrainSelectWindow.Draw(Sprite.Create(TerrainList.GetSelectedTerrainTexture(),
                                               (TerrainWindowTileIndex % 10) * 200,
                                               ((TerrainWindowTileIndex - (TerrainWindowTileIndex % 10)) % 100) / 10 * 200,
                                               GameHandle->GameScreen.GetViewScale()
                                               ));
        }

    }

}

inline void tfp::Interface::TerrainWindowOperations()
{
    /// Jesli jest zly numer ustawiony to reset
    AddTileSetIndex(0);

    /// Jesli LCONTROL jest wcisniety
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && GameHandle->GameScreen.IsFocused())
    {
        if(SetTile == "terrain")
        {
            GameHandle->GameMap.SetTerrainPreview(false);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                /// Stawianie terenu na mapie
                if(!TerrainSelectWindow.IsMouseInsideWindow())
                {
                    int PozX = (int) (GameHandle->GameMouse.GetMousePositionOnMap().x / 200.0f);
                    int PozY = (int) (GameHandle->GameMouse.GetMousePositionOnMap().y / 200.0f);
                    PlaceTerrainTerrainID = TerrainWindowTileIndex + (TerrainWindowTileSetIndex * 100);

                    GameHandle->GameMap.SetTerrainNoPause(TerrainList.GetTerrainArray()[PlaceTerrainTerrainID].Name, PozX, PozY);
                }
            }
            else
            {
                /// Przerwa w stawianiu
                GameHandle->GameMap.SetTerrainPause();
                int PozX = (int) (GameHandle->GameMouse.GetMousePositionOnMap().x / 200.0f);
                int PozY = (int) (GameHandle->GameMouse.GetMousePositionOnMap().y / 200.0f);
                PlaceTerrainTerrainID = TerrainWindowTileIndex + (TerrainWindowTileSetIndex * 100);
                if(PlaceTerrainTerrainID < TerrainList.GetTerrainArray().size())
                    GameHandle->GameMap.SetTerrainPreview(TerrainList.GetTerrainArray()[PlaceTerrainTerrainID].Name, PozX, PozY);
                else GameHandle->GameMap.SetTerrainPreview(false);
            }
        }
    }
    else if(GameHandle->GameScreen.IsFocused()) // Jescli LControl NIE jest wcisniety
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            /// Wybieranie terenu
            if(TerrainSelectWindow.IsMouseInsideBorders() && TerrainSelectWindow.GetMousePosition().y < 2000.0f)
            {
                int PozX = (int) (TerrainSelectWindow.GetMousePosition().x / 200.0f);
                int PozY = (int) (TerrainSelectWindow.GetMousePosition().y / 200.0f);
                TerrainWindowTileIndex = PozX + PozY * 10;
            }
            /// Stawianie terenu na mapie
            else if(SetTile == "terrain")
            {
                int PozX = (int) (GameHandle->GameMouse.GetMousePositionOnMap().x / 200.0f);
                int PozY = (int) (GameHandle->GameMouse.GetMousePositionOnMap().y / 200.0f);
                PlaceTerrainTerrainID = TerrainWindowTileIndex + (TerrainWindowTileSetIndex * 100);

                if(PlaceTerrainLeftButtonDown == false && !WindowGlobalData.IsMouseInsideAnyWindow(GameHandle))
                {
                    PlaceTerrainStart = sf::Vector2i(PozX, PozY);
                    PlaceTerrainEnd = sf::Vector2i(PozX, PozY);
                    PlaceTerrainLeftButtonDown = true;
                    if(PlaceTerrainTerrainID < TerrainList.GetTerrainArray().size())
                    {
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                            GameHandle->GameMap.SetTerrainRectPreview(TerrainList.GetTerrainArray()[PlaceTerrainTerrainID].Name, PlaceTerrainStart, PlaceTerrainEnd, true);
                        else
                            GameHandle->GameMap.SetTerrainRectPreview(TerrainList.GetTerrainArray()[PlaceTerrainTerrainID].Name, PlaceTerrainStart, PlaceTerrainEnd);
                    }

                }
                else if(PlaceTerrainLeftButtonDown == true)
                {
                    PlaceTerrainEnd = sf::Vector2i(PozX, PozY);
                    if(PlaceTerrainTerrainID < TerrainList.GetTerrainArray().size())
                    {
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                            GameHandle->GameMap.SetTerrainRectPreview(TerrainList.GetTerrainArray()[PlaceTerrainTerrainID].Name, PlaceTerrainStart, PlaceTerrainEnd, true);
                        else
                            GameHandle->GameMap.SetTerrainRectPreview(TerrainList.GetTerrainArray()[PlaceTerrainTerrainID].Name, PlaceTerrainStart, PlaceTerrainEnd);
                    }

                }


            }
            else if(SetTile == "object")
            {

                if(PlaceTerrainLeftButtonDown == false && !WindowGlobalData.IsMouseInsideAnyWindow(GameHandle))
                {
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    {
                        PlaceTerrainLeftButtonDown = true;
                        float PozX = GameHandle->GameMouse.GetMousePositionOnMap().x;
                        float PozY = GameHandle->GameMouse.GetMousePositionOnMap().y;

                        GameHandle->GameMap.RemoveObject(PozX, PozY);
                    }
                    else
                    {
                        PlaceTerrainLeftButtonDown = true;
                        float PozX = GameHandle->GameMouse.GetMousePositionOnMap().x;
                        float PozY = GameHandle->GameMouse.GetMousePositionOnMap().y;
                        int ObjectID = TerrainWindowTileIndex + (TerrainWindowTileSetIndex * 100);

                        if(ObjectID < (int) ObjectGifList.GetList().size())
                        {
                            GameHandle->GameMap.AddObject(ObjectGifList.GetList()[ObjectID].GifName, PozX, PozY);
                        }
                    }
                }
            }
        }
        else if(PlaceTerrainLeftButtonDown == true && SetTile == "terrain")
        {
            PlaceTerrainLeftButtonDown = false;
            if(TerrainList.GetTerrainArray().size() > PlaceTerrainTerrainID)
            {
                GameHandle->GameMap.SetTerrainRectPreview(false);
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    GameHandle->GameMap.SetTerrainRect(TerrainList.GetTerrainArray()[PlaceTerrainTerrainID].Name, PlaceTerrainStart, PlaceTerrainEnd, true);
                else
                    GameHandle->GameMap.SetTerrainRect(TerrainList.GetTerrainArray()[PlaceTerrainTerrainID].Name, PlaceTerrainStart, PlaceTerrainEnd);
            }
        }
        else if(SetTile == "terrain")
        {
            int PozX = (int) (GameHandle->GameMouse.GetMousePositionOnMap().x / 200.0f);
            int PozY = (int) (GameHandle->GameMouse.GetMousePositionOnMap().y / 200.0f);
            PlaceTerrainTerrainID = TerrainWindowTileIndex + (TerrainWindowTileSetIndex * 100);
            if(PlaceTerrainTerrainID < TerrainList.GetTerrainArray().size())
                GameHandle->GameMap.SetTerrainPreview(TerrainList.GetTerrainArray()[PlaceTerrainTerrainID].Name, PozX, PozY);
            else GameHandle->GameMap.SetTerrainPreview(false);
        }
        else if(SetTile == "object")
        {
            PlaceTerrainLeftButtonDown = false;

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            {
                GameHandle->GameMap.SetObjectPreview(false);
            }
            else
            {
                float PozX = GameHandle->GameMouse.GetMousePositionOnMap().x;
                float PozY = GameHandle->GameMouse.GetMousePositionOnMap().y;
                unsigned ObjectID = TerrainWindowTileIndex + (TerrainWindowTileSetIndex * 100);
                if(ObjectID < ObjectGifList.GetList().size())
                    GameHandle->GameMap.SetObjectPreview(ObjectGifList.GetList()[ObjectID].GifName, PozX, PozY);
                else GameHandle->GameMap.SetObjectPreview(false);
            }
        }
    }
}

inline void tfp::Interface::DrawForms(std::string &GameType)
{
    if(GameType == "game")
    {
        GameChat.ChatInput.Area.SetDisabled(false);
        GameChat.DrawChat();
    }
    else
    {
        GameChat.ChatInput.Area.SetDisabled(true);
    }
    if(GameType == "menu")
    {
        HostGameButton.Area.SetDisabled(false);
        SingleplayerGameButton.Area.SetDisabled(false);
        JoinGameButton.Area.SetDisabled(false);
        JoinGameIpInput.Area.SetDisabled(false);
        JoinGamePortInput.Area.SetDisabled(false);

        HostGameButton.SetPosition(4000.f, 50.0f);
        SingleplayerGameButton.SetPosition(4000.f, 250.0f);
        JoinGameButton.SetPosition(4000.f, 3175.0f);
        JoinGameIpInput.SetPosition(4000.f, 2975.0f);
        JoinGamePortInput.SetPosition(5050.f, 2975.0f);

        std::string TmpIp = JoinGameIpInput.Area.GetText();
        std::string TmpPort = JoinGamePortInput.Area.GetText();
        if(TmpIp == "") TmpIp = "localhost";
        if(TmpPort == "") TmpPort = "5726";

        JoinGameButton.SetCommand("joingame " + TmpIp + " " + TmpPort);

        HostGameButton.Display();
        SingleplayerGameButton.Display();
        JoinGameButton.Display();
        JoinGameIpInput.Display();
        JoinGamePortInput.Display();


    }
    else
    {
        HostGameButton.Area.SetDisabled(true);
        SingleplayerGameButton.Area.SetDisabled(true);
        JoinGameButton.Area.SetDisabled(true);
        JoinGameIpInput.Area.SetDisabled(true);
        JoinGamePortInput.Area.SetDisabled(true);

    }
    if(GameType == "server")
    {
        DrawConnectedUserList();

        JoinServerGameButton.Area.SetDisabled(false);
        ServerIpInput.Area.SetDisabled(false);
        ServerPortInput.Area.SetDisabled(false);

        JoinServerGameButton.SetPosition(4000.f, 50.0f);
        RunServerButton.SetPosition(4000.f, 3175.0f);
        StopServerButton.SetPosition(5000.f, 3175.0f);
        ServerIpInput.SetPosition(4000.f, 2975.0f);
        ServerPortInput.SetPosition(5050.f, 2975.0f);

        std::string TmpIp = ServerIpInput.Area.GetText();
        std::string TmpPort = ServerPortInput.Area.GetText();
        if(TmpIp == "") TmpIp = "localhost";
        if(TmpPort == "") TmpPort = "5726";

        RunServerButton.SetCommand("startserver " + TmpIp + " " + TmpPort);
        JoinServerGameButton.SetCommand("joingame " + TmpIp + " " + TmpPort);


        if(GameHandle->GameNetworkServer.IsTurnOn())
        {
            RunServerButton.Area.SetDisabled(true);
            StopServerButton.Area.SetDisabled(false);
            StopServerButton.Display();
        }
        else
        {
            RunServerButton.Area.SetDisabled(false);
            StopServerButton.Area.SetDisabled(true);
            RunServerButton.Display();
        }
        JoinServerGameButton.Display();
        ServerIpInput.Display();
        ServerPortInput.Display();

    }
    else
    {
        RunServerButton.Area.SetDisabled(true);
        StopServerButton.Area.SetDisabled(true);
        JoinServerGameButton.Area.SetDisabled(false);
        ServerIpInput.Area.SetDisabled(true);
        ServerPortInput.Area.SetDisabled(true);

    }

}

inline void tfp::Interface::DrawConnectedUserList()
{
    std::wstring RenderText = Language.Translate("Connected users") + L": ";

    std::vector<tfp::NetworkServer::ClientNode> ClientList = GameHandle->GameNetworkServer.GetClientList();

    for(unsigned i = 0; i < ClientList.size(); i++)
    {
        RenderText += L"\n\t" + tfp::StringToWString(ClientList[i].ClientIp.toString()) + L":" + tfp::IntToWString(ClientList[i].ClientPort);
    }


    GameHandle->GameScreen.Draw(Text.Create(RenderText, FontList.FindFontWithName("ConnectedUserList"), {5.0f, 5.0f}, GameHandle->GameScreen.GetViewScale()));


}

inline void tfp::Interface::DrawCommandLine()
{
    if(CommandLineVisible)
    {
        GameHandle->GameScreen.Draw(Sprite.Create(InterfaceCommandLineTexture, 0, 0, GameHandle->GameScreen.GetViewScale()));
        GameHandle->GameScreen.Draw(Text.Create(GetCommandLineInput(),FontList.FindFontWithName("CommandListInput"), sf::Vector2f(55.0f, 1110.f), GameHandle->GameScreen.GetViewScale()));
        for(int i = 0; i < CommandLineOutputLines; i++)
            GameHandle->GameScreen.Draw(Text.Create(CommandLineOutput[i],FontList.FindFontWithName("CommandList"), sf::Vector2f(55.0f, 55.0f + i * 90.0f), GameHandle->GameScreen.GetViewScale()));
    }
}

void tfp::Interface::SetZindexVisible(bool State)
{
    IndexZHelpVisible = State;
}

inline void tfp::Interface::DrawZIndexHelp()
{
    if(IndexZHelpVisible)
    {
        float PositionY = GameHandle->GameScreen.GetViewSize().y / 4;
        float PositionX = 0;
        float Scale = GameHandle->GameScreen.GetViewScale();
        if(GameHandle->GameMouse.GetMousePosition().x < GameHandle->GameScreen.GetViewSize().x / 2)
        {
            PositionX = GameHandle->GameScreen.GetViewSize().x - 1000.0f * Scale;
        }

        sf::VertexArray Background(sf::Quads, 4);
        Background[0].position = sf::Vector2f(PositionX, PositionY);
        Background[1].position = sf::Vector2f(PositionX + 1000.0f * Scale, PositionY);
        Background[2].position = sf::Vector2f(PositionX + 1000.0f * Scale, PositionY + 1000 * Scale);
        Background[3].position = sf::Vector2f(PositionX, PositionY + 1000 * Scale);

        Background[0].color = sf::Color(0 , 0, 0, 230);
        Background[1].color = sf::Color(0 , 0, 0, 230);
        Background[2].color = sf::Color(0 , 0, 0, 230);
        Background[3].color = sf::Color(0 , 0, 0, 230);

        GameHandle->GameScreen.Draw(Background);

        std::wstring TextToDraw = L"0 - " + Language.Translate("ground")
                                + L"\n1 - " + Language.Translate("ground")
                                + L"\n2 - " + Language.Translate("ground")
                                + L"\n3 - " + Language.Translate("characters")
                                + L"\n4 - " + Language.Translate("sky")
                                + L"\n5 - " + Language.Translate("sky")
                                + L"\n6 - " + Language.Translate("sky")
                                + L"\n7 - " + Language.Translate("spells");
        GameHandle->GameScreen.Draw(Text.Create(TextToDraw, FontList.FindFontWithName("ZIndexHelp"), {PositionX + 25.0f * Scale, PositionY + 25.0f * Scale}, /*GameHandle->GameScreen.GetViewScale()*/ 1.0f, tfp::AlignLeft, 95 * Scale));



        if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            IndexZHelpVisible = false;
        }
    }
}

const bool tfp::Interface::DisplayInterface(std::string GameType)
{
    if(GameHandle == nullptr) return false;
    LoadAssetsIfNotLoaded();
    DrawBackground(GameType);
    if(GameType == "mapeditor") DrawGrid();
    if(GameType == "game") DrawSpecialEffects();
    CloseNotSuitableWindows(GameType);
    if(GameType == "game") DrawUserInterface();
    DrawWindows();
    DrawForms(GameType);
    if(GameType == "mapeditor") TerrainWindowOperations();
    if(GameType == "mapeditor") DrawZIndexHelp();
    DrawCommandLine();
    DisplayFps();
    /// Initializing loading
    if(GameType == "game"  && !GameHandle->GameNetworkClient.IsConnected())
    {
        LoadingScreen.Draw("Connecting to the server...", GameHandle);
    }

    /// Load Debug messages
    LoadDebugMessages();

    return true;
}

void tfp::Interface::SetGameHandle(tfp::Game *Handle)
{
    GameHandle = Handle;

    GameChat.SetGameHandle(Handle);

    RainEffect.SetGameHandle(Handle);
    SnowEffect.SetGameHandle(Handle);
    StormEffect.SetGameHandle(Handle);
    NightEffect.SetGameHandle(Handle);

    CommandLineFocusArea.Reset(GameHandle, sf::Vector2f(0.0f,0.0f),sf::Vector2f(6000.0f,1228.0f), true);
    InventoryWindow.Reset(GameHandle, sf::Rect<int>(6000, 3000, 800, 1500), "Inventory");
    CharacterInfoWindow.Reset(GameHandle, sf::Rect<int>(6000, 0, 400, 600), "Character");
    TerrainSelectWindow.Reset(GameHandle, sf::Rect<int>(6000, 3000, 2000, 3000), "Terrain picker");
    OptionsWindow.Reset(GameHandle, sf::Rect<int>(GameHandle->GameScreen.GetOriginalViewSize().x / 2 - 500.0f, GameHandle->GameScreen.GetOriginalViewSize().y / 2 - 562.5f,
                                                 1000.0f, 1125.0f), "Options");

    LanguageWindow.Reset(GameHandle, sf::Rect<int>(GameHandle->GameScreen.GetOriginalViewSize().x / 2 - 500.0f, GameHandle->GameScreen.GetOriginalViewSize().y / 2 - 500.0f,
                                                 1000.0f, 1000.0f), "Language");

    AuthorsWindow.Reset(GameHandle, sf::Rect<int>(GameHandle->GameScreen.GetOriginalViewSize().x / 2 - 2250.0f, GameHandle->GameScreen.GetOriginalViewSize().y / 2 - 1250.0f,
                                                 4500.0f, 2500.0f), "Authors");

    ControlsWindow.Reset(GameHandle, sf::Rect<int>(GameHandle->GameScreen.GetOriginalViewSize().x / 2 - 2250.0f, GameHandle->GameScreen.GetOriginalViewSize().y / 2 - 1250.0f,
                                                 4500.0f, 2500.0f), "Controls");


    VideoOptionsWindow.Reset(GameHandle, sf::Rect<int>(GameHandle->GameScreen.GetOriginalViewSize().x / 2 - 2562.5f, GameHandle->GameScreen.GetOriginalViewSize().y / 2 - 1250.0f,
                                                 5125.0f, 2500.0f), "Video options");



    ServerIpInput.SetGameHandle(GameHandle);
    ServerIpInput.SetSize(1000.5f, 150.0f);
    ServerIpInput.SetPosition(7000.0f, 3300.0f);
    ServerIpInput.SetInputType(tfp::TextType::TextTypeString);
    ServerIpInput.SetMaxCharacters(15);
    ServerIpInput.Area.SetTextMaxLength(15);
    ServerIpInput.SetPlaceHolder("Server IP");

    ServerPortInput.SetGameHandle(GameHandle);
    ServerPortInput.SetSize(900.5f, 150.0f);
    ServerPortInput.SetPosition(7000.0f, 3300.0f);
    ServerPortInput.SetInputType(tfp::TextType::TextTypeString);
    ServerPortInput.SetMaxCharacters(14);
    ServerPortInput.Area.SetTextMaxLength(5);
    ServerPortInput.SetPlaceHolder("Server port");

    RunServerButton.SetGameHandle(GameHandle);
    RunServerButton.SetPosition(7000.0f, 3000.0f);
    RunServerButton.SetSize(950.0f, 150.0f);
    RunServerButton.SetText("Launch");
    RunServerButton.SetCommand("startserver");

    StopServerButton.SetGameHandle(GameHandle);
    StopServerButton.SetPosition(7000.0f, 3000.0f);
    StopServerButton.SetSize(950.0f, 150.0f);
    StopServerButton.SetText("Stop");
    StopServerButton.SetCommand("stopserver");

    JoinServerGameButton.SetGameHandle(GameHandle);
    JoinServerGameButton.SetPosition(7000.0f, 3000.0f);
    JoinServerGameButton.SetSize(1950.0f, 150.0f);
    JoinServerGameButton.SetText("Join game");
    JoinServerGameButton.SetCommand("joingame");

    HostGameButton.SetGameHandle(GameHandle);
    HostGameButton.SetPosition(7000.0f, 3000.0f);
    HostGameButton.SetSize(1950.0f, 150.0f);
    HostGameButton.SetText("Host game");
    HostGameButton.SetCommand("server");

    SingleplayerGameButton.SetGameHandle(GameHandle);
    SingleplayerGameButton.SetPosition(7000.0f, 3000.0f);
    SingleplayerGameButton.SetSize(1950.0f, 150.0f);
    SingleplayerGameButton.SetText("Singleplayer");
    SingleplayerGameButton.SetCommand("singleplayer");

    JoinGameButton.SetGameHandle(GameHandle);
    JoinGameButton.SetPosition(7000.0f, 3000.0f);
    JoinGameButton.SetSize(1950.0f, 150.0f);
    JoinGameButton.SetText("Join game");
    JoinGameButton.SetCommand("joingame");

    JoinGameIpInput.SetGameHandle(GameHandle);
    JoinGameIpInput.SetSize(1000.5f, 150.0f);
    JoinGameIpInput.SetPosition(7000.0f, 3300.0f);
    JoinGameIpInput.SetInputType(tfp::TextType::TextTypeString);
    JoinGameIpInput.SetMaxCharacters(15);
    JoinGameIpInput.Area.SetTextMaxLength(15);
    JoinGameIpInput.SetPlaceHolder("Server IP");


    JoinGamePortInput.SetGameHandle(GameHandle);
    JoinGamePortInput.SetSize(900.5f, 150.0f);
    JoinGamePortInput.SetPosition(7000.0f, 3300.0f);
    JoinGamePortInput.SetInputType(tfp::TextType::TextTypeString);
    JoinGamePortInput.SetMaxCharacters(14);
    JoinGamePortInput.Area.SetTextMaxLength(5);
    JoinGamePortInput.SetPlaceHolder("Server port");

    for(int i = 0; i < 9; i++)
    {
        LanguageButtonSelect[i].SetGameHandle(GameHandle);
        LanguageButtonSelect[i].SetPosition(7000.0f, 3000.0f);
        LanguageButtonSelect[i].SetSize(1000.0f, 125.0f);
        LanguageButtonSelect[i].SetText("");
        LanguageButtonSelect[i].SetCommand("setlanguage");
    }

    for(int i = 0; i < 13; i++)
    {
        MenuWindowSizeButton[i].SetGameHandle(GameHandle);
        MenuWindowSizeButton[i].SetPosition(7000.0f, 3000.0f);
        MenuWindowSizeButton[i].SetSize(400.0f, 125.0f);
    }
    MenuWindowSizeButton[12].SetSize(1000.0f, 125.0f);

    for(int i = 0; i < 13; i++)
    {
        GameWindowSizeButton[i].SetGameHandle(GameHandle);
        GameWindowSizeButton[i].SetPosition(7000.0f, 3000.0f);
        GameWindowSizeButton[i].SetSize(400.0f, 125.0f);
    }
    GameWindowSizeButton[12].SetSize(1000.0f, 125.0f);

    for(int i = 0; i < 13; i++)
    {
        MapEditorWindowSizeButton[i].SetGameHandle(GameHandle);
        MapEditorWindowSizeButton[i].SetPosition(7000.0f, 3000.0f);
        MapEditorWindowSizeButton[i].SetSize(400.0f, 125.0f);
    }
    MapEditorWindowSizeButton[12].SetSize(1000.0f, 125.0f);

    for(int i = 0; i < 13; i++)
    {
        ServerWindowSizeButton[i].SetGameHandle(GameHandle);
        ServerWindowSizeButton[i].SetPosition(7000.0f, 3000.0f);
        ServerWindowSizeButton[i].SetSize(400.0f, 125.0f);
    }
    ServerWindowSizeButton[12].SetSize(1000.0f, 125.0f);

    MenuWindowSizeButton[0].SetText("640x360");
    MenuWindowSizeButton[0].SetCommand("setmenuwindowsize 640 360");
    MenuWindowSizeButton[1].SetText("800x450");
    MenuWindowSizeButton[1].SetCommand("setmenuwindowsize 800 450");
    MenuWindowSizeButton[2].SetText("1024x600");
    MenuWindowSizeButton[2].SetCommand("setmenuwindowsize 1024 600");
    MenuWindowSizeButton[3].SetText("1280x720");
    MenuWindowSizeButton[3].SetCommand("setmenuwindowsize 1280 720");
    MenuWindowSizeButton[4].SetText("1366x768");
    MenuWindowSizeButton[4].SetCommand("setmenuwindowsize 1366 768");
    MenuWindowSizeButton[5].SetText("1600x900");
    MenuWindowSizeButton[5].SetCommand("setmenuwindowsize 1600 900");
    MenuWindowSizeButton[6].SetText("1920x1080");
    MenuWindowSizeButton[6].SetCommand("setmenuwindowsize 1920 1080");
    MenuWindowSizeButton[7].SetText("2048x1152");
    MenuWindowSizeButton[7].SetCommand("setmenuwindowsize 2048 1152");
    MenuWindowSizeButton[8].SetText("2560x1440");
    MenuWindowSizeButton[8].SetCommand("setmenuwindowsize 2560 1440");
    MenuWindowSizeButton[9].SetText("3072x1728");
    MenuWindowSizeButton[9].SetCommand("setmenuwindowsize 3072 1728");
    MenuWindowSizeButton[10].SetText("4096x2304");
    MenuWindowSizeButton[10].SetCommand("setmenuwindowsize 4096 2304");
    MenuWindowSizeButton[11].SetText("8192x4608");
    MenuWindowSizeButton[11].SetCommand("setmenuwindowsize 8192 4608");

    GameWindowSizeButton[0].SetText("640x360");
    GameWindowSizeButton[0].SetCommand("setgamewindowsize 640 360");
    GameWindowSizeButton[1].SetText("800x450");
    GameWindowSizeButton[1].SetCommand("setgamewindowsize 800 450");
    GameWindowSizeButton[2].SetText("1024x600");
    GameWindowSizeButton[2].SetCommand("setgamewindowsize 1024 600");
    GameWindowSizeButton[3].SetText("1280x720");
    GameWindowSizeButton[3].SetCommand("setgamewindowsize 1280 720");
    GameWindowSizeButton[4].SetText("1366x768");
    GameWindowSizeButton[4].SetCommand("setgamewindowsize 1366 768");
    GameWindowSizeButton[5].SetText("1600x900");
    GameWindowSizeButton[5].SetCommand("setgamewindowsize 1600 900");
    GameWindowSizeButton[6].SetText("1920x1080");
    GameWindowSizeButton[6].SetCommand("setgamewindowsize 1920 1080");
    GameWindowSizeButton[7].SetText("2048x1152");
    GameWindowSizeButton[7].SetCommand("setgamewindowsize 2048 1152");
    GameWindowSizeButton[8].SetText("2560x1440");
    GameWindowSizeButton[8].SetCommand("setgamewindowsize 2560 1440");
    GameWindowSizeButton[9].SetText("3072x1728");
    GameWindowSizeButton[9].SetCommand("setgamewindowsize 3072 1728");
    GameWindowSizeButton[10].SetText("4096x2304");
    GameWindowSizeButton[10].SetCommand("setgamewindowsize 4096 2304");
    GameWindowSizeButton[11].SetText("8192x4608");
    GameWindowSizeButton[11].SetCommand("setgamewindowsize 8192 4608");

    MapEditorWindowSizeButton[0].SetText("640x360");
    MapEditorWindowSizeButton[0].SetCommand("setmapeditorwindowsize 640 360");
    MapEditorWindowSizeButton[1].SetText("800x450");
    MapEditorWindowSizeButton[1].SetCommand("setmapeditorwindowsize 800 450");
    MapEditorWindowSizeButton[2].SetText("1024x600");
    MapEditorWindowSizeButton[2].SetCommand("setmapeditorwindowsize 1024 600");
    MapEditorWindowSizeButton[3].SetText("1280x720");
    MapEditorWindowSizeButton[3].SetCommand("setmapeditorwindowsize 1280 720");
    MapEditorWindowSizeButton[4].SetText("1366x768");
    MapEditorWindowSizeButton[4].SetCommand("setmapeditorwindowsize 1366 768");
    MapEditorWindowSizeButton[5].SetText("1600x900");
    MapEditorWindowSizeButton[5].SetCommand("setmapeditorwindowsize 1600 900");
    MapEditorWindowSizeButton[6].SetText("1920x1080");
    MapEditorWindowSizeButton[6].SetCommand("setmapeditorwindowsize 1920 1080");
    MapEditorWindowSizeButton[7].SetText("2048x1152");
    MapEditorWindowSizeButton[7].SetCommand("setmapeditorwindowsize 2048 1152");
    MapEditorWindowSizeButton[8].SetText("2560x1440");
    MapEditorWindowSizeButton[8].SetCommand("setmapeditorwindowsize 2560 1440");
    MapEditorWindowSizeButton[9].SetText("3072x1728");
    MapEditorWindowSizeButton[9].SetCommand("setmapeditorwindowsize 3072 1728");
    MapEditorWindowSizeButton[10].SetText("4096x2304");
    MapEditorWindowSizeButton[10].SetCommand("setmapeditorwindowsize 4096 2304");
    MapEditorWindowSizeButton[11].SetText("8192x4608");
    MapEditorWindowSizeButton[11].SetCommand("setmapeditorwindowsize 8192 4608");

    ServerWindowSizeButton[0].SetText("640x360");
    ServerWindowSizeButton[0].SetCommand("setserverwindowsize 640 360");
    ServerWindowSizeButton[1].SetText("800x450");
    ServerWindowSizeButton[1].SetCommand("setserverwindowsize 800 450");
    ServerWindowSizeButton[2].SetText("1024x600");
    ServerWindowSizeButton[2].SetCommand("setserverwindowsize 1024 600");
    ServerWindowSizeButton[3].SetText("1280x720");
    ServerWindowSizeButton[3].SetCommand("setserverwindowsize 1280 720");
    ServerWindowSizeButton[4].SetText("1366x768");
    ServerWindowSizeButton[4].SetCommand("setserverwindowsize 1366 768");
    ServerWindowSizeButton[5].SetText("1600x900");
    ServerWindowSizeButton[5].SetCommand("setserverwindowsize 1600 900");
    ServerWindowSizeButton[6].SetText("1920x1080");
    ServerWindowSizeButton[6].SetCommand("setserverwindowsize 1920 1080");
    ServerWindowSizeButton[7].SetText("2048x1152");
    ServerWindowSizeButton[7].SetCommand("setserverwindowsize 2048 1152");
    ServerWindowSizeButton[8].SetText("2560x1440");
    ServerWindowSizeButton[8].SetCommand("setserverwindowsize 2560 1440");
    ServerWindowSizeButton[9].SetText("3072x1728");
    ServerWindowSizeButton[9].SetCommand("setserverwindowsize 3072 1728");
    ServerWindowSizeButton[10].SetText("4096x2304");
    ServerWindowSizeButton[10].SetCommand("setserverwindowsize 4096 2304");
    ServerWindowSizeButton[11].SetText("8192x4608");
    ServerWindowSizeButton[11].SetCommand("setserverwindowsize 8192 4608");

    VerticalSyncButton.SetGameHandle(GameHandle);
    VerticalSyncButton.SetPosition(7000.0f, 3000.0f);
    VerticalSyncButton.SetSize(1250.0f,125.0f);
    VerticalSyncButton.SetText("Vertical synchronization: off");
    VerticalSyncButton.SetCommand("setverticalsync true");

    SetFrameLimitButton.SetGameHandle(GameHandle);
    SetFrameLimitButton.SetPosition(7000.0f, 3000.0f);
    SetFrameLimitButton.SetSize(775.0f,125.0f);
    SetFrameLimitButton.SetText("Set frame limit");
    SetFrameLimitButton.SetCommand("setframelimit 60");

    FrameLimitInputBar.SetGameHandle(GameHandle);
    FrameLimitInputBar.SetSize(400.5f, 125.0f);
    FrameLimitInputBar.SetPosition(7000.0f, 3300.0f);
    FrameLimitInputBar.SetInputType(tfp::TextType::TextTypeInt);
    FrameLimitInputBar.SetMaxCharacters(5);
    FrameLimitInputBar.Area.SetText(tfp::IntToString(GameHandle->GameScreen.GetFramerateLimit()));

    VideoOptionsCloseButton.SetGameHandle(GameHandle);
    VideoOptionsCloseButton.SetPosition(7000.0f, 3000.0f);
    VideoOptionsCloseButton.SetSize(5125.0f,125.0f);
    VideoOptionsCloseButton.SetText("Close");
    VideoOptionsCloseButton.SetCommand("videooptions false");

    VideoOptionsResetButton.SetGameHandle(GameHandle);
    VideoOptionsResetButton.SetPosition(7000.0f, 3000.0f);
    VideoOptionsResetButton.SetSize(500.0f,125.0f);
    VideoOptionsResetButton.SetText("Reset");
    VideoOptionsResetButton.SetCommand("resetvideooptions");

    LanguageButtonSelect[6].SetSize(500.0f,125.0f);
    LanguageButtonSelect[7].SetSize(500.0f,125.0f);
    LanguageButtonSelect[6].SetCommand("selectlanguageprevious");
    LanguageButtonSelect[7].SetCommand("selectlanguagenext");
    LanguageButtonSelect[8].SetCommand("selectlanguage false");

    LanguageButtonSelect[6].SetText("<<<");
    LanguageButtonSelect[7].SetText(">>>");
    LanguageButtonSelect[8].SetText("Close");

    OptionsMenu.SetGameHandle(GameHandle);
    OptionsMenu.SetPosition(7000.0f, 3000.0f);
    OptionsMenu.SetSize(1000.0f,125.0f);
    OptionsMenu.SetText("Menu");
    OptionsMenu.SetCommand("menu");

    OptionsControls.SetGameHandle(GameHandle);
    OptionsControls.SetPosition(7000.0f, 3000.0f);
    OptionsControls.SetSize(1000.0f,125.0f);
    OptionsControls.SetText("Controls");
    OptionsControls.SetCommand("controls");

    OptionsVideoOptions.SetGameHandle(GameHandle);
    OptionsVideoOptions.SetPosition(7000.0f, 3000.0f);
    OptionsVideoOptions.SetSize(1000.0f,125.0f);
    OptionsVideoOptions.SetText("Video options");
    OptionsVideoOptions.SetCommand("videooptions");

    OptionsMapEditor.SetGameHandle(GameHandle);
    OptionsMapEditor.SetPosition(7000.0f, 3000.0f);
    OptionsMapEditor.SetSize(1000.0f,125.0f);
    OptionsMapEditor.SetText("Map editor");
    OptionsMapEditor.SetCommand("mapeditor");

    OptionsLanguage.SetGameHandle(GameHandle);
    OptionsLanguage.SetPosition(7000.0f, 3000.0f);
    OptionsLanguage.SetSize(1000.0f,125.0f);
    OptionsLanguage.SetText("Language");
    OptionsLanguage.SetCommand("selectlanguage");

    OptionsAuthors.SetGameHandle(GameHandle);
    OptionsAuthors.SetPosition(7000.0f, 3000.0f);
    OptionsAuthors.SetSize(1000.0f,125.0f);
    OptionsAuthors.SetText("Authors");
    OptionsAuthors.SetCommand("authors true");

    OptionsExit.SetGameHandle(GameHandle);
    OptionsExit.SetPosition(7000.0f, 3000.0f);
    OptionsExit.SetSize(1000.0f,125.0f);
    OptionsExit.SetText("Exit");
    OptionsExit.SetCommand("exit");

    OptionsExitAll.SetGameHandle(GameHandle);
    OptionsExitAll.SetPosition(7000.0f, 3000.0f);
    OptionsExitAll.SetSize(1000.0f,125.0f);
    OptionsExitAll.SetText("Exit all");
    OptionsExitAll.SetCommand("exitall");

    OptionsClose.SetGameHandle(GameHandle);
    OptionsClose.SetPosition(7000.0f, 3000.0f);
    OptionsClose.SetSize(1000.0f,125.0f);
    OptionsClose.SetText("Close");
    OptionsClose.SetCommand("options false");

    TerrainSelectButtonNext.SetGameHandle(GameHandle);
    TerrainSelectButtonNext.SetPosition(7000.0f, 3000.0f);
    TerrainSelectButtonNext.SetSize(1000.0f,125.0f);
    TerrainSelectButtonNext.SetText(">>>");
    TerrainSelectButtonNext.SetCommand("nexttileset");

    TerrainSelectButtonPrevious.SetGameHandle(GameHandle);
    TerrainSelectButtonPrevious.SetPosition(6000.0f, 3000.0f);
    TerrainSelectButtonPrevious.SetSize(1000.0f,125.0f);
    TerrainSelectButtonPrevious.SetText("<<<");
    TerrainSelectButtonPrevious.SetCommand("previoustileset");

    TerrainSelectButtonTerrain.SetGameHandle(GameHandle);
    TerrainSelectButtonTerrain.SetPosition(6000.0f, 3150.0f);
    TerrainSelectButtonTerrain.SetSize(500.0f,125.0f);
    TerrainSelectButtonTerrain.SetText("Terrain");
    TerrainSelectButtonTerrain.SetCommand("settilemode terrain");

    TerrainSelectButtonObjects.SetGameHandle(GameHandle);
    TerrainSelectButtonObjects.SetPosition(6500.0f, 3150.0f);
    TerrainSelectButtonObjects.SetSize(500.0f,125.0f);
    TerrainSelectButtonObjects.SetText("Objects");
    TerrainSelectButtonObjects.SetCommand("settilemode object");

    TerrainSelectButtonSpecial.SetGameHandle(GameHandle);
    TerrainSelectButtonSpecial.SetPosition(7000.0f, 3150.0f);
    TerrainSelectButtonSpecial.SetSize(500.0f,125.0f);
    TerrainSelectButtonSpecial.SetText("Special");
    TerrainSelectButtonSpecial.SetCommand("settilemode special");

    TerrainSelectButtonMobs.SetGameHandle(GameHandle);
    TerrainSelectButtonMobs.SetPosition(7000.0f, 3150.0f);
    TerrainSelectButtonMobs.SetSize(500.0f,125.0f);
    TerrainSelectButtonMobs.SetText("Mobs");
    TerrainSelectButtonMobs.SetCommand("settilemode mob");

    TerrainSelectButtonSetMapSize.SetGameHandle(GameHandle);
    TerrainSelectButtonSetMapSize.SetPosition(7000.0f, 3300.0f);
    TerrainSelectButtonSetMapSize.SetSize(1000.0f,125.0f);
    TerrainSelectButtonSetMapSize.SetText("Set map size");
    TerrainSelectButtonSetMapSize.SetCommand("setmapsize 20 20");

    TerrainSelectButtonSetGridSize.SetGameHandle(GameHandle);
    TerrainSelectButtonSetGridSize.SetPosition(7000.0f, 3300.0f);
    TerrainSelectButtonSetGridSize.SetSize(1000.0f,125.0f);
    TerrainSelectButtonSetGridSize.SetText("Set grid size");
    TerrainSelectButtonSetGridSize.SetCommand("setgridsize 200 200");

    TerrainSelectButtonSetZIndex.SetGameHandle(GameHandle);
    TerrainSelectButtonSetZIndex.SetPosition(7000.0f, 3300.0f);
    TerrainSelectButtonSetZIndex.SetSize(1000.0f,125.0f);
    TerrainSelectButtonSetZIndex.SetText("Set Z-Index");
    TerrainSelectButtonSetZIndex.SetCommand("setzindex 0");

    TerrainSelectButtonSetZIndexHelp.SetGameHandle(GameHandle);
    TerrainSelectButtonSetZIndexHelp.SetPosition(7000.0f, 3300.0f);
    TerrainSelectButtonSetZIndexHelp.SetSize(500.0f,125.0f);
    TerrainSelectButtonSetZIndexHelp.SetText("???");
    TerrainSelectButtonSetZIndexHelp.SetCommand("showzindexhelp");



    TerrainSelectInputSetGridSizeX.SetGameHandle(GameHandle);
    TerrainSelectInputSetGridSizeX.SetSize(500.0f, 125.0f);
    TerrainSelectInputSetGridSizeX.SetInputType(tfp::TextTypeInt);
    TerrainSelectInputSetGridSizeX.SetMaxCharacters(7);
    TerrainSelectInputSetGridSizeX.Area.SetTextMaxLength(4);
    TerrainSelectInputSetGridSizeX.SetPlaceHolder("0");

    TerrainSelectInputSetGridSizeY.SetGameHandle(GameHandle);
    TerrainSelectInputSetGridSizeY.SetSize(500.0f, 125.0f);
    TerrainSelectInputSetGridSizeY.SetInputType(tfp::TextTypeInt);
    TerrainSelectInputSetGridSizeY.SetMaxCharacters(7);
    TerrainSelectInputSetGridSizeY.Area.SetTextMaxLength(4);
    TerrainSelectInputSetGridSizeY.SetPlaceHolder("0");

    TerrainSelectInputSetMapSizeX.SetGameHandle(GameHandle);
    TerrainSelectInputSetMapSizeX.SetSize(500.0f, 125.0f);
    TerrainSelectInputSetMapSizeX.SetInputType(tfp::TextTypeInt);
    TerrainSelectInputSetMapSizeX.SetMaxCharacters(7);
    TerrainSelectInputSetMapSizeX.Area.SetTextMaxLength(4);
    TerrainSelectInputSetMapSizeX.SetPlaceHolder("0");

    TerrainSelectInputSetZIndex.SetGameHandle(GameHandle);
    TerrainSelectInputSetZIndex.SetSize(500.0f, 125.0f);
    TerrainSelectInputSetZIndex.SetInputType(tfp::TextTypeInt);
    TerrainSelectInputSetZIndex.SetMaxCharacters(7);
    TerrainSelectInputSetZIndex.Area.SetTextMaxLength(4);
    TerrainSelectInputSetZIndex.SetPlaceHolder("0");

    TerrainSelectInputSetMapSizeY.SetGameHandle(GameHandle);
    TerrainSelectInputSetMapSizeY.SetSize(500.0f, 125.0f);
    TerrainSelectInputSetMapSizeY.SetInputType(tfp::TextTypeInt);
    TerrainSelectInputSetMapSizeY.SetMaxCharacters(7);
    TerrainSelectInputSetMapSizeY.Area.SetTextMaxLength(4);
    TerrainSelectInputSetMapSizeY.SetPlaceHolder("0");

    TerrainSelectButtonDisableGrid.SetGameHandle(GameHandle);
    TerrainSelectButtonDisableGrid.SetPosition(7000.0f, 3300.0f);
    TerrainSelectButtonDisableGrid.SetSize(1000.0f,125.0f);
    TerrainSelectButtonDisableGrid.SetText("Disable grid");
    TerrainSelectButtonDisableGrid.SetCommand("enablegrid");

    TerrainSelectButtonHideGrid.SetGameHandle(GameHandle);
    TerrainSelectButtonHideGrid.SetPosition(7000.0f, 3300.0f);
    TerrainSelectButtonHideGrid.SetSize(1000.0f,125.0f);
    TerrainSelectButtonHideGrid.SetText("Hide grid");
    TerrainSelectButtonHideGrid.SetCommand("showgrid");

    TerrainSelectButtonLockCamera.SetGameHandle(GameHandle);
    TerrainSelectButtonLockCamera.SetPosition(7000.0f, 3300.0f);
    TerrainSelectButtonLockCamera.SetSize(1000.0f,125.0f);
    TerrainSelectButtonLockCamera.SetText("Lock camera");
    TerrainSelectButtonLockCamera.SetCommand("lockcamera");

    TerrainSelectButtonUnlockCamera.SetGameHandle(GameHandle);
    TerrainSelectButtonUnlockCamera.SetPosition(7000.0f, 3300.0f);
    TerrainSelectButtonUnlockCamera.SetSize(1000.0f,125.0f);
    TerrainSelectButtonUnlockCamera.SetText("Unlock camera");
    TerrainSelectButtonUnlockCamera.SetCommand("unlockcamera");

    TerrainSelectButtonLoadMap.SetGameHandle(GameHandle);
    TerrainSelectButtonLoadMap.SetPosition(7000.0f, 3300.0f);
    TerrainSelectButtonLoadMap.SetSize(1000.0f,125.0f);
    TerrainSelectButtonLoadMap.SetText("Load map");
    TerrainSelectButtonLoadMap.SetCommand("loadmap");

    TerrainSelectButtonSaveMap.SetGameHandle(GameHandle);
    TerrainSelectButtonSaveMap.SetPosition(7000.0f, 3300.0f);
    TerrainSelectButtonSaveMap.SetSize(1000.0f,125.0f);
    TerrainSelectButtonSaveMap.SetText("Save map");
    TerrainSelectButtonSaveMap.SetCommand("savemap");

    AuthorsButtonClose.SetGameHandle(GameHandle);
    AuthorsButtonClose.SetPosition(7000.0f, 3300.0f);
    AuthorsButtonClose.SetSize(4500.0f,125.0f);
    AuthorsButtonClose.SetText("Close");
    AuthorsButtonClose.SetCommand("authors false");

    ResetControlsButton.SetGameHandle(GameHandle);
    ResetControlsButton.SetPosition(7000.0f, 3300.0f);
    ResetControlsButton.SetSize(500.0f,125.0f);
    ResetControlsButton.SetText("Reset");
    ResetControlsButton.SetCommand("resetcontrols");

    CloseControlsButton.SetGameHandle(GameHandle);
    CloseControlsButton.SetPosition(7000.0f, 3300.0f);
    CloseControlsButton.SetSize(4500.0f,125.0f);
    CloseControlsButton.SetText("Close");
    CloseControlsButton.SetCommand("controls false");

    HealthBar.SetPosition(50.0f, 50.0f);
    HealthBar.SetSize(800.0f, 100.0f);
    HealthBar.SetGameHandle(Handle);
    HealthBar.SetColor({229, 68, 68});
    HealthBar.SetValue(700);
    HealthBar.SetMaxValue(1000);
    HealthBar.SetMode(tfp::LoadingBar::FullMode);

    ManaBar.SetPosition(50.0f, 175.0f);
    ManaBar.SetSize(800.0f, 100.0f);
    ManaBar.SetGameHandle(Handle);
    ManaBar.SetColor({127, 175, 226});
    ManaBar.SetValue(123);
    ManaBar.SetMaxValue(250);
    ManaBar.SetMode(tfp::LoadingBar::FullMode);


    ShowConsoleInputBar.SetGameHandle(GameHandle);
    ShowConsoleInputBar.SetSize(712.5f, 100.0f);
    ShowConsoleInputBar.SetPosition(7000.0f, 3300.0f);
    ShowConsoleInputBar.SetInputType(tfp::TextType::TextTypeKey);
    ShowConsoleInputBar.SetMaxCharacters(20);
    ShowConsoleInputBar.Area.SetKeyConfigActionName("ShowConsole");

    ShowOptionsInputBar.SetGameHandle(GameHandle);
    ShowOptionsInputBar.SetSize(712.5f, 100.0f);
    ShowOptionsInputBar.SetPosition(7000.0f, 3300.0f);
    ShowOptionsInputBar.SetInputType(tfp::TextType::TextTypeKey);
    ShowOptionsInputBar.SetMaxCharacters(20);
    ShowOptionsInputBar.Area.SetKeyConfigActionName("ShowOptions");

    ShowTerrainSelectInputBar.SetGameHandle(GameHandle);
    ShowTerrainSelectInputBar.SetSize(712.5f, 100.0f);
    ShowTerrainSelectInputBar.SetPosition(7000.0f, 3300.0f);
    ShowTerrainSelectInputBar.SetInputType(tfp::TextType::TextTypeKey);
    ShowTerrainSelectInputBar.SetMaxCharacters(20);
    ShowTerrainSelectInputBar.Area.SetKeyConfigActionName("ShowTerrainSelect");

    UndoTerrainChangesInputBar.SetGameHandle(GameHandle);
    UndoTerrainChangesInputBar.SetSize(712.5f, 100.0f);
    UndoTerrainChangesInputBar.SetPosition(7000.0f, 3300.0f);
    UndoTerrainChangesInputBar.SetInputType(tfp::TextType::TextTypeKey);
    UndoTerrainChangesInputBar.SetMaxCharacters(20);
    UndoTerrainChangesInputBar.Area.SetKeyConfigActionName("UndoTerrainChanges");

    RedoTerrainChangesInputBar.SetGameHandle(GameHandle);
    RedoTerrainChangesInputBar.SetSize(712.5f, 100.0f);
    RedoTerrainChangesInputBar.SetPosition(7000.0f, 3300.0f);
    RedoTerrainChangesInputBar.SetInputType(tfp::TextType::TextTypeKey);
    RedoTerrainChangesInputBar.SetMaxCharacters(20);
    RedoTerrainChangesInputBar.Area.SetKeyConfigActionName("RedoTerrainChanges");

    ShowInventoryInputBar.SetGameHandle(GameHandle);
    ShowInventoryInputBar.SetSize(712.5f, 100.0f);
    ShowInventoryInputBar.SetPosition(7000.0f, 3300.0f);
    ShowInventoryInputBar.SetInputType(tfp::TextType::TextTypeKey);
    ShowInventoryInputBar.SetMaxCharacters(20);
    ShowInventoryInputBar.Area.SetKeyConfigActionName("ShowInventory");

    ShowCharacterInfoInputBar.SetGameHandle(GameHandle);
    ShowCharacterInfoInputBar.SetSize(712.5f, 100.0f);
    ShowCharacterInfoInputBar.SetPosition(7000.0f, 3300.0f);
    ShowCharacterInfoInputBar.SetInputType(tfp::TextType::TextTypeKey);
    ShowCharacterInfoInputBar.SetMaxCharacters(20);
    ShowCharacterInfoInputBar.Area.SetKeyConfigActionName("ShowCharacterInfo");

    OpenChatInputBar.SetGameHandle(GameHandle);
    OpenChatInputBar.SetSize(712.5f, 100.0f);
    OpenChatInputBar.SetPosition(7000.0f, 3300.0f);
    OpenChatInputBar.SetInputType(tfp::TextType::TextTypeKey);
    OpenChatInputBar.SetMaxCharacters(20);
    OpenChatInputBar.Area.SetKeyConfigActionName("OpenChat");

    ScreenshotInputBar.SetGameHandle(GameHandle);
    ScreenshotInputBar.SetSize(712.5f, 100.0f);
    ScreenshotInputBar.SetPosition(7000.0f, 3300.0f);
    ScreenshotInputBar.SetInputType(tfp::TextType::TextTypeKey);
    ScreenshotInputBar.SetMaxCharacters(20);
    ScreenshotInputBar.Area.SetKeyConfigActionName("Screenshot");


    for(int i = 0; i < 100; i++)
    {
        InventoryDragableArray[i].Reset(GameHandle, {7000.0f, 3300.0f}, {200.0f, 200.0f}, true);
        if(i > 7) InventoryDragableArray[i].SetDisabled(true);
        else InventoryDragableArray[i].SetDisabled(false);
    }


}

void tfp::Interface::ShowCommandLine(bool Show)
{
    CommandLineVisible = Show;
    if(Show)
    {
        CommandLineFocusArea.SetDisabled(false);
        CommandLineFocusArea.SetActive(true);
    }
    else
    {
        CommandLineFocusArea.SetActive(false);
        CommandLineFocusArea.SetDisabled(true);
    }
}

const bool tfp::Interface::IsCommandLineVisible()
{
    return CommandLineVisible;
}

void tfp::Interface::SendCommandLineInput(char Character)
{
    if(CommandLineVisible == false || !IsCommandLineActive()) return;

    else if(Character == 96 || Character == 126) /** Nic **/;
    else if(Character == 127) CommandLineInput = "";
    else if(Character == 8) // Backspace
    {
        if(CommandLineInput.size() > 0) CommandLineInput.resize(CommandLineInput.size() - 1);
    }
    else if(Character == 13)
    {
        /// Runn command ...
        CommandsToRun.push(CommandLineInput);
        LastCommand = CommandLineInput;
        CommandLineInput.resize(0);
    }
    else if(Character > 31 && Character < 128 && CommandLineInput.size() < 140 /*74*/) CommandLineInput += Character;
}

std::string tfp::Interface::GetCommandLineInput()
{
    if(CommandLineFocusArea.IsActive())
        return CommandLineInput + "|";
    else return CommandLineInput;
}

void tfp::Interface::SendCommandLineOutputLine(std::string Line)
{
    for(int i = 0; i < CommandLineOutputLines - 1; i++)
        CommandLineOutput[i] = CommandLineOutput[i+1];
    CommandLineOutput[CommandLineOutputLines - 1] = Line;
}
void tfp::Interface::SendKeyPressed(sf::Event Key)
{
    if(Key.key.code == sf::Keyboard::Up)
    {
        CommandLineInput = LastCommand;
    }
    else if(Key.key.code == sf::Keyboard::Down)
    {
        CommandLineInput = "";
    }
}

const bool tfp::Interface::IsCommandQueueEmpty() const
{
    if(CommandsToRun.empty()) return true;
    else return false;
}


std::string tfp::Interface::GetCommandToRun()
{
    std::string Return;
    if(CommandsToRun.size() > 0)
    {
        Return = CommandsToRun.front();
        CommandsToRun.pop();
    }
    return Return;
}

sf::Vector2i tfp::Interface::GetGridSize()
{
    if(GridEnabled == false)
        return {0,0};
    else return {(int) GridSize.x, (int) GridSize.y};
}
