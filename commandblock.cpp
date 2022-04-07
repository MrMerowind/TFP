/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"

tfp::CommandBlock::CommandBlock()
    :GameHandle(nullptr) {}

tfp::CommandBlock::~CommandBlock() {}

void tfp::CommandBlock::SetGameHandle(tfp::Game *Handle)
{
    GameHandle = Handle;
}

void tfp::CommandBlock::RunCommand(std::string Command)
{
    /// Macrodefinitions
    std::string MacroCommand = Command;
    std::string Macro;
    Command = "";
    int Parts = tfp::CountSymbolsInText(MacroCommand, '@') + 1;
    for(int i = 0; i < Parts; i++)
    {
        Macro = tfp::SplitString(MacroCommand, i, '@', false);
        if(i % 2 == 0)
        {
            Command += Macro;
        }
        else
        {
            if(Macro == "mousepositiononmap")
            {
                Command += tfp::IntToString(GameHandle->GameMouse.GetMousePositionOnMap().x) + " " + tfp::IntToString(GameHandle->GameMouse.GetMousePositionOnMap().y);
            }
            else if(Macro == "cameraposition")
            {
                Command += tfp::IntToString(GameHandle->GameCamera.GetPosition().x) + " " + tfp::IntToString(GameHandle->GameCamera.GetPosition().y);
            }
            else if(Macro == "");
            else
            {
                Debug.Warning("Unknown macro: " + Macro);
            }
        }
    }


    /// Commands
    if(Command == "");
    else if(tfp::SplitString(Command, 0, ' ', false) == "setwindowsize")
    {
        Debug.Command("Command disabled. Alternative:");
        Debug.Command("\tsetmenuwindowsize <width> <height>");
        Debug.Command("\tsetgamewindowsize <width> <height>");
        Debug.Command("\tsetmapeditorwindowsize <width> <height>");
        Debug.Command("\tsetserverwindowsize <width> <height>");
        /*
        if(GameHandle != nullptr)
        {
            int TmpWidth = tfp::StringToInt(tfp::SplitString(Command, 1, ' ', false));
            int TmpHeight = tfp::StringToInt(tfp::SplitString(Command, 2, ' ', false));
            GameHandle->GameScreen.Resize(TmpWidth, TmpHeight, tfp::StringToBool(tfp::SplitString(Command, 3, ' ', false)));
            Debug.Command("Window resized");
        }
        else Debug.Warning("Game handle not set");
        */
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "setmenuwindowsize")
    {
        if(GameHandle != nullptr)
        {
            int TmpWidth = tfp::StringToInt(tfp::SplitString(Command, 1, ' ', false));
            int TmpHeight = tfp::StringToInt(tfp::SplitString(Command, 2, ' ', false));
            GameHandle->GameScreen.SetWindowSize("menu", TmpWidth, TmpHeight);
        }
        else Debug.Warning("Game handle not set");
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "setgamewindowsize")
    {
        if(GameHandle != nullptr)
        {
            int TmpWidth = tfp::StringToInt(tfp::SplitString(Command, 1, ' ', false));
            int TmpHeight = tfp::StringToInt(tfp::SplitString(Command, 2, ' ', false));
            GameHandle->GameScreen.SetWindowSize("game", TmpWidth, TmpHeight);
        }
        else Debug.Warning("Game handle not set");
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "setmapeditorwindowsize")
    {
        if(GameHandle != nullptr)
        {
            int TmpWidth = tfp::StringToInt(tfp::SplitString(Command, 1, ' ', false));
            int TmpHeight = tfp::StringToInt(tfp::SplitString(Command, 2, ' ', false));
            GameHandle->GameScreen.SetWindowSize("mapeditor", TmpWidth, TmpHeight);
        }
        else Debug.Warning("Game handle not set");
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "setserverwindowsize")
    {
        if(GameHandle != nullptr)
        {
            int TmpWidth = tfp::StringToInt(tfp::SplitString(Command, 1, ' ', false));
            int TmpHeight = tfp::StringToInt(tfp::SplitString(Command, 2, ' ', false));
            GameHandle->GameScreen.SetWindowSize("server", TmpWidth, TmpHeight);
        }
        else Debug.Warning("Game handle not set");
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "setviewsize")
    {
        if(GameHandle != nullptr)
        {
            int TmpWidth = tfp::StringToInt(tfp::SplitString(Command, 1, ' ', false));
            int TmpHeight = tfp::StringToInt(tfp::SplitString(Command, 2, ' ', false));
            GameHandle->GameScreen.SetViewSize(TmpWidth, TmpHeight);
            Debug.Command("Window view resized");
        }
        else Debug.Warning("Game handle not set");
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "resetvideooptions")
    {
        GameHandle->GameScreen.ResetSettings();
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "resetcontrols")
    {
        KeyConfig.UnloadConfig();
        KeyConfig.LoadDefaultConfig();
        KeyConfig.SaveUserConfig();
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "setframelimit")
    {
        if(GameHandle != nullptr)
        {
            int NewFrameLimit = tfp::StringToInt(tfp::SplitString(Command, 1, ' ', false));
            GameManager.SetFrameLimit(NewFrameLimit);
        }
        else Debug.Warning("Game handle not set");
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "setverticalsync")
    {
        if(GameHandle != nullptr)
        {
            bool Sync = !GameManager.GetVerticalSync();
            if(tfp::SplitString(Command, 1, ' ', false) != "")
            {
                Sync = tfp::StringToBool(tfp::SplitString(Command, 1, ' ', false));
            }
            GameManager.SetVerticalSync(Sync);
        }
        else Debug.Warning("Game handle not set");
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "setgamefullscreen")
    {
        if(tfp::SplitString(Command, 1, ' ', false) == "")
            GameHandle->GameScreen.SetFullScreen("game", !GameHandle->GameScreen.GetFullScreen("game"));
        else
            GameHandle->GameScreen.SetFullScreen("game", tfp::StringToBool(tfp::SplitString(Command, 1, ' ', false)));
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "setmenufullscreen")
    {
        if(tfp::SplitString(Command, 1, ' ', false) == "")
            GameHandle->GameScreen.SetFullScreen("menu", !GameHandle->GameScreen.GetFullScreen("menu"));
        else
            GameHandle->GameScreen.SetFullScreen("menu", tfp::StringToBool(tfp::SplitString(Command, 1, ' ', false)));
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "setmapeditorfullscreen")
    {
        if(tfp::SplitString(Command, 1, ' ', false) == "")
            GameHandle->GameScreen.SetFullScreen("mapeditor", !GameHandle->GameScreen.GetFullScreen("mapeditor"));
        else
            GameHandle->GameScreen.SetFullScreen("mapeditor", tfp::StringToBool(tfp::SplitString(Command, 1, ' ', false)));
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "setserverfullscreen")
    {
        if(tfp::SplitString(Command, 1, ' ', false) == "")
            GameHandle->GameScreen.SetFullScreen("server", !GameHandle->GameScreen.GetFullScreen("server"));
        else
            GameHandle->GameScreen.SetFullScreen("server", tfp::StringToBool(tfp::SplitString(Command, 1, ' ', false)));
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "setlanguage")
    {
        if(GameHandle != nullptr)
        {
            std::string LanguageNameTmp = tfp::SplitString(Command, 1, ' ', false);
            if(LanguageNameTmp != "")
            {
                if(LanguageNameTmp[0] >= 'a' && LanguageNameTmp[0] <= 'z')
                {
                    LanguageNameTmp[0] += - 'a' + 'A';
                }
                Language.LoadDictionary(tfp::StringToWString(tfp::SplitString(Command, 1, ' ', false)));
                GameManager.ResetWindowTitles();
            }
        }
        else Debug.Warning("Game handle not set");
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "lockcamera")
    {
        if(GameHandle != nullptr)
        {
            GameHandle->GameCamera.Lock();
            Debug.Command("Camera locked");
        }
        else Debug.Warning("Game handle not set");
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "debuginfo")
    {
        if(GameHandle != nullptr)
        {
            Debug.Command("---[ Debug info: ]---");
            Debug.Command("Framerate limit: " + tfp::FloatToString(GameHandle->GameScreen.GetFramerateLimit()));
            Debug.Command("Original view size: " + tfp::FloatToString(GameHandle->GameScreen.GetOriginalViewSize().x) + ":" + tfp::FloatToString(GameHandle->GameScreen.GetOriginalViewSize().y));
            Debug.Command("View size: " + tfp::FloatToString(GameHandle->GameScreen.GetViewSize().x) + ":" + tfp::FloatToString(GameHandle->GameScreen.GetViewSize().y));
            Debug.Command("View scale: " + tfp::FloatToString(GameHandle->GameScreen.GetViewScale()));
            Debug.Command("Window size: " + tfp::FloatToString(GameHandle->GameScreen.GetWindowSize().x) + ":" + tfp::FloatToString(GameHandle->GameScreen.GetWindowSize().y));
            Debug.Command("Camera position: " + tfp::FloatToString(GameHandle->GameCamera.GetPosition().x) + ":" + tfp::FloatToString(GameHandle->GameCamera.GetPosition().y));
            Debug.Command("Camera locked: " + tfp::BoolToString(GameHandle->GameCamera.IsLocked()));
            Debug.Command("Mouse position: " + tfp::FloatToString(GameHandle->GameMouse.GetMousePosition().x) + ":" + tfp::FloatToString(GameHandle->GameMouse.GetMousePosition().y));
            Debug.Command("Mouse position scaled: " + tfp::FloatToString(GameHandle->GameMouse.GetMousePositionScaled().x) + ":" + tfp::FloatToString(GameHandle->GameMouse.GetMousePositionScaled().y));
            Debug.Command("Mouse position on map: " + tfp::FloatToString(GameHandle->GameMouse.GetMousePositionOnMap().x) + ":" + tfp::FloatToString(GameHandle->GameMouse.GetMousePositionOnMap().y));
            Debug.Command("Map loaded: " + tfp::BoolToString(GameHandle->GameMap.IsLoaded()));
            Debug.Command("Map size: " + tfp::FloatToString(GameHandle->GameMap.GetWidth()) + ":" + tfp::FloatToString(GameHandle->GameMap.GetHeight()));
            Debug.Command("Map name: " + GameHandle->GameMap.GetMapName());
            Debug.Command("---------------------");

        }
        else Debug.Warning("Game handle not set");
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "debugwindow")
    {
        if(GameHandle != nullptr)
        {
            Debug.Command("---[ Debug window: ]---");
            Debug.Command("Registered windows: " + tfp::IntToString(WindowGlobalData.GetWindowList().size()));
            Debug.Command("");
            for(unsigned i = 0; i < WindowGlobalData.GetWindowList().size(); i++)
            {

                Debug.Command("Name:" + WindowGlobalData.GetWindowList()[i]->GetWindowName());
                Debug.Command("Visible: " + tfp::BoolToString(WindowGlobalData.GetWindowList()[i]->IsVisible()));
                Debug.Command("Mouse inside window: " + tfp::BoolToString(WindowGlobalData.GetWindowList()[i]->IsMouseInsideWindow()));
                Debug.Command("Mouse inside borders: " + tfp::BoolToString(WindowGlobalData.GetWindowList()[i]->IsMouseInsideBorders()));
                uintptr_t PointerNumber = (uintptr_t) WindowGlobalData.GetWindowList()[i]->GetGameHandle();
                Debug.Command("Game handle: " + tfp::IntToString(static_cast<int>(PointerNumber)));
                Debug.Command("DragableArea active: " + tfp::BoolToString(WindowGlobalData.GetWindowList()[i]->GetWindowDragableArea().IsActive()));

                Debug.Command("");
            }
            Debug.Command("---------------------");

        }
        else Debug.Warning("Game handle not set");
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "debugarea")
    {
        if(GameHandle != nullptr)
        {
            Debug.Command("---[ Debug area: ]---");
            Debug.Command("Registered areas: " + tfp::IntToString(AreaList.GetRegisteredAreaCount()));
            Debug.Command("");
            for(int i = 0; i < AreaList.GetRegisteredAreaCount(); i++)
            {
                /// Rodzaje
                if(AreaList.GetList()[i].Type == tfp::AreaListClass::Node::Focus)
                {
                    Debug.Command("Type: Focus");
                    Debug.Command("Active: " + tfp::BoolToString(AreaList.GetList()[i].FocusAreaHandle->IsActive()));
                    Debug.Command("Disabled: " + tfp::BoolToString(AreaList.GetList()[i].FocusAreaHandle->IsDisabled()));
                    uintptr_t PointerNumber = (uintptr_t) AreaList.GetList()[i].FocusAreaHandle->GetGameHandle();
                    Debug.Command("Game handle: " + tfp::IntToString(static_cast<int>(PointerNumber)));
                }
                else if(AreaList.GetList()[i].Type == tfp::AreaListClass::Node::Dragable)
                {
                    Debug.Command("Type: Dragable");
                    Debug.Command("Active: " + tfp::BoolToString(AreaList.GetList()[i].DragableAreaHandle->IsActive()));
                    Debug.Command("Disabled: " + tfp::BoolToString(AreaList.GetList()[i].DragableAreaHandle->IsDisabled()));
                    uintptr_t PointerNumber = (uintptr_t) AreaList.GetList()[i].DragableAreaHandle->GetGameHandle();
                    Debug.Command("Game handle: " + tfp::IntToString(static_cast<int>(PointerNumber)));
                }
                else if(AreaList.GetList()[i].Type == tfp::AreaListClass::Node::Clickable)
                {
                    Debug.Command("Type: Clickable");
                    Debug.Command("Active: Undefined");
                    Debug.Command("Disabled: " + tfp::BoolToString(AreaList.GetList()[i].ClickableAreaHandle->IsDisabled()));
                    uintptr_t PointerNumber = (uintptr_t) AreaList.GetList()[i].ClickableAreaHandle->GetGameHandle();
                    Debug.Command("Game handle: " + tfp::IntToString(static_cast<int>(PointerNumber)));
                }
                else if(AreaList.GetList()[i].Type == tfp::AreaListClass::Node::Input)
                {
                    Debug.Command("Type: Input");
                    Debug.Command("Active: " + tfp::BoolToString(AreaList.GetList()[i].InputAreaHandle->IsActive()));
                    Debug.Command("Disabled: " + tfp::BoolToString(AreaList.GetList()[i].InputAreaHandle->IsDisabled()));
                    uintptr_t PointerNumber = (uintptr_t) AreaList.GetList()[i].InputAreaHandle->GetGameHandle();
                    Debug.Command("Game handle: " + tfp::IntToString(static_cast<int>(PointerNumber)));
                }

                /*
                Debug.Command("Window name:" + WindowGlobalData.GetWindowList()[i]->GetWindowName());
                Debug.Command("Window visible: " + tfp::BoolToString(WindowGlobalData.GetWindowList()[i]->IsVisible()));
                Debug.Command("Mouse inside window: " + tfp::BoolToString(WindowGlobalData.GetWindowList()[i]->IsMouseInsideWindow()));
                Debug.Command("Mouse inside borders: " + tfp::BoolToString(WindowGlobalData.GetWindowList()[i]->IsMouseInsideBorders()));
                uintptr_t PointerNumber = (uintptr_t) WindowGlobalData.GetWindowList()[i]->GetGameHandle();
                Debug.Command("Game handle: " + tfp::IntToString(static_cast<int>(PointerNumber)));
                Debug.Command("DragableArea active: " + tfp::BoolToString(WindowGlobalData.GetWindowList()[i]->GetWindowDragableArea().IsActive()));
                */
                Debug.Command("");
            }
            Debug.Command("---------------------");

        }
        else Debug.Warning("Game handle not set");
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "debugkeyconfig")
    {
        if(GameHandle != nullptr)
        {
            Debug.Info("---[ Key config ]---");
            for(unsigned i = 0; i < KeyConfig.GetKeyConfigList().size(); i++)
            {
                Debug.Info("");
                Debug.Info("Name: " + KeyConfig.GetKeyConfigList()[i].ActionName);
                Debug.Info("Key code: " + tfp::IntToString(KeyConfig.GetKeyConfigList()[i].KeyCode));
                Debug.Info("System: " + tfp::BoolToString(KeyConfig.GetKeyConfigList()[i].KeySystem));
                Debug.Info("Control: " + tfp::BoolToString(KeyConfig.GetKeyConfigList()[i].KeyControl));
                Debug.Info("Alt: " + tfp::BoolToString(KeyConfig.GetKeyConfigList()[i].KeyAlt));
                Debug.Info("Shift: " + tfp::BoolToString(KeyConfig.GetKeyConfigList()[i].KeyShift));
            }
            Debug.Info("");
            Debug.Info("--------------------");
        }
        else Debug.Warning("Game handle not set");
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "showfps")
    {
        if(GameHandle != nullptr)
        {
            GameHandle->GameInterface.ShowFps(true);
            Debug.Command("FPS counter on");
        }
        else Debug.Warning("Game handle not set");
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "nexttileset")
    {
        if(GameHandle != nullptr)
        {
            GameHandle->GameInterface.AddTileSetIndex(1);
        }
        else Debug.Warning("Game handle not set");
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "previoustileset")
    {
        if(GameHandle != nullptr)
        {
            GameHandle->GameInterface.AddTileSetIndex(-1);
        }
        else Debug.Warning("Game handle not set");
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "hidefps")
    {
        if(GameHandle != nullptr)
        {
            GameHandle->GameInterface.ShowFps(false);
            Debug.Command("FPS counter off");
        }
        else Debug.Warning("Game handle not set");
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "reloadfonts")
    {
        LoadingScreen.DisplayOnScreen("Loading fonts...", GameHandle);
        FontList.UnloadAll();
        FontList.LoadAllFonts(GameHandle);
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "reloadterrain")
    {
        LoadingScreen.DisplayOnScreen("Loading terrains...", GameHandle);
        TerrainList.UnloadAll();
        TerrainList.LoadAllTerrains(GameHandle);
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "unlockcamera")
    {
        if(GameHandle != nullptr)
        {
            GameHandle->GameCamera.Unlock();
            Debug.Command("Camera unlocked");
        }
        else Debug.Warning("Game handle not set");
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "setcameraposition")
    {
        if(GameHandle != nullptr)
        {
            float TmpPosX = tfp::StringToFloat(tfp::SplitString(Command, 1, ' ', false));
            float TmpPosY = tfp::StringToFloat(tfp::SplitString(Command, 2, ' ', false));
            GameHandle->GameCamera.SetPosition(TmpPosX, TmpPosY);
            Debug.Command("Camera moved");
        }
        else Debug.Warning("Game handle not set");
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "setviewscale")
    {
        if(GameHandle != nullptr)
        {
            // GameHandle->GameScreen.SetViewScale(tfp::StringToFloat(tfp::SplitString(Command, 1, ' ', false)));
            // Debug.Command("View scale set");
            Debug.Command("This command is disabled due to a bug");
        }
        else Debug.Warning("Game handle not set");
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "setmapsize")
    {
        if(GameHandle != nullptr)
        {
            int TmpPosX = tfp::StringToInt(tfp::SplitString(Command, 1, ' ', false));
            int TmpPosY = tfp::StringToInt(tfp::SplitString(Command, 2, ' ', false));
            GameHandle->GameMap.Resize(TmpPosX, TmpPosY);
        }
        else Debug.Warning("Game handle not set");
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "setmapname")
    {
        if(GameHandle != nullptr)
        {
            GameHandle->GameMap.SetMapName(tfp::SplitString(Command, 1, ' ', false));
        }
        else Debug.Warning("Game handle not set");
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "setwindowtitle")
    {
        if(GameHandle != nullptr)
        {
            GameHandle->GameScreen.SetWindowTitle(tfp::StringToWString(tfp::IgnoreWords(Command, 1)));
            Debug.Command("Window title set");
        }
        else Debug.Warning("Game handle not set");
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "exit")
    {
        if(GameHandle != nullptr)
        {
            GameHandle->GameScreen.Close();
        }
        else Debug.Warning("Game handle not set");
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "exitall")
    {
        for(int i = 0; i < GameManager.GamesOpen(); i++)
        {
            if(GameManager.GetGame(i).GameScreen.IsWindowOpen())
            {
                GameManager.GetGame(i).GameScreen.Close();
            }
        }
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "loadmap")
    {
        if(tfp::SplitString(Command, 1, ' ', false) == "")
            GameHandle->GameMap.LoadMap(tfp::PathToFileTitle(tfp::OpenFileName(GameHandle, "\0*.map\0", "Maps\\")));
        else
            GameHandle->GameMap.LoadMap(tfp::IgnoreWords(Command, 1));
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "savemap")
    {
        if(tfp::SplitString(Command, 1, ' ', false) == "")
            GameHandle->GameMap.SaveMap(tfp::PathToFileTitle(tfp::SaveFileName(GameHandle, "\0*.map\0", "Maps\\")));
        else
            GameHandle->GameMap.SaveMap(tfp::IgnoreWords(Command, 1));
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "showgrid")
    {
        if(tfp::SplitString(Command, 1, ' ', false) == "")
            GameHandle->GameInterface.ShowGrid(!GameHandle->GameInterface.IsGridVisible());
        else
            GameHandle->GameInterface.ShowGrid(tfp::StringToBool(tfp::SplitString(Command, 1, ' ', false)));
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "authors")
    {
        if(tfp::SplitString(Command, 1, ' ', false) == "")
            GameHandle->GameInterface.AuthorsWindow.Show(!GameHandle->GameInterface.AuthorsWindow.IsVisible());
        else
            GameHandle->GameInterface.AuthorsWindow.Show(tfp::StringToBool(tfp::SplitString(Command, 1, ' ', false)));
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "options")
    {
        if(tfp::SplitString(Command, 1, ' ', false) == "")
            GameHandle->GameInterface.OptionsWindow.Show(!GameHandle->GameInterface.OptionsWindow.IsVisible());
        else
            GameHandle->GameInterface.OptionsWindow.Show(tfp::StringToBool(tfp::SplitString(Command, 1, ' ', false)));
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "controls")
    {
        if(tfp::SplitString(Command, 1, ' ', false) == "")
            GameHandle->GameInterface.ControlsWindow.Show(!GameHandle->GameInterface.ControlsWindow.IsVisible());
        else
            GameHandle->GameInterface.ControlsWindow.Show(tfp::StringToBool(tfp::SplitString(Command, 1, ' ', false)));
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "videooptions")
    {
        if(tfp::SplitString(Command, 1, ' ', false) == "")
            GameHandle->GameInterface.VideoOptionsWindow.Show(!GameHandle->GameInterface.VideoOptionsWindow.IsVisible());
        else
            GameHandle->GameInterface.VideoOptionsWindow.Show(tfp::StringToBool(tfp::SplitString(Command, 1, ' ', false)));
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "enablegrid")
    {
        if(tfp::SplitString(Command, 1, ' ', false) == "")
            GameHandle->GameInterface.EnableGrid(!GameHandle->GameInterface.IsGridVisible());
        else
            GameHandle->GameInterface.EnableGrid(tfp::StringToBool(tfp::SplitString(Command, 1, ' ', false)));
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "selectlanguage")
    {
        if(tfp::SplitString(Command, 1, ' ', false) == "")
            GameHandle->GameInterface.LanguageWindow.Show(!GameHandle->GameInterface.LanguageWindow.IsVisible());
        else
            GameHandle->GameInterface.LanguageWindow.Show(tfp::StringToBool(tfp::SplitString(Command, 1, ' ', false)));
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "selectlanguagenext")
    {
        GameHandle->GameInterface.SetLanguageNamesIndexAdd(1);
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "selectlanguageprevious")
    {
        GameHandle->GameInterface.SetLanguageNamesIndexAdd(-1);
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "setgridsize")
    {
        if(tfp::SplitString(Command, 1, ' ', false) == "")
            GameHandle->GameInterface.SetGrid(0, 0);
        else
            GameHandle->GameInterface.SetGrid(tfp::StringToInt(tfp::SplitString(Command, 1, ' ', false)), tfp::StringToInt(tfp::SplitString(Command, 2, ' ', false)));
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "unloadmap")
    {
        GameHandle->GameMap.Unload();
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "mapeditor")
    {
        GameManagerCommandList.push(Command);
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "server")
    {
        GameManagerCommandList.push(Command);
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "menu")
    {
        GameManagerCommandList.push(Command);
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "newgame")
    {
        // GameManagerCommandList.push(Command);
        Debug.Command("This command is disabled. Use 'joingame <ip> <port>' instead");
    }
    /// Unlisted commands
    else if(tfp::SplitString(Command, 0, ' ', false) == "joingame")
    {
        GameManagerCommandList.push(Command);
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "setrain")
    {
        if(tfp::SplitString(Command, 1, ' ', false) == "")
            GameHandle->GameInterface.RainEffect.SetDensity(0);
        else
            GameHandle->GameInterface.RainEffect.SetDensity(tfp::StringToInt(tfp::SplitString(Command, 1, ' ', false)));
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "setsnow")
    {
        if(tfp::SplitString(Command, 1, ' ', false) == "")
            GameHandle->GameInterface.SnowEffect.SetDensity(0);
        else
            GameHandle->GameInterface.SnowEffect.SetDensity(tfp::StringToInt(tfp::SplitString(Command, 1, ' ', false)));
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "setnight")
    {
        if(tfp::SplitString(Command, 1, ' ', false) == "")
            GameHandle->GameInterface.NightEffect.SetDarkness(0);
        else
            GameHandle->GameInterface.NightEffect.SetDarkness(tfp::StringToInt(tfp::SplitString(Command, 1, ' ', false)));
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "setstorm")
    {
        if(tfp::SplitString(Command, 1, ' ', false) == "")
            GameHandle->GameInterface.StormEffect.SetLightningTimeSpan(0, 0);
        else
            GameHandle->GameInterface.StormEffect.SetLightningTimeSpan(tfp::StringToInt(tfp::SplitString(Command, 1, ' ', false)), tfp::StringToInt(tfp::SplitString(Command, 2, ' ', false)));
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "shakecamera")
    {
        GameHandle->GameCamera.ShakeCamera();
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "setclientid")
    {
        GameHandle->GameNetworkClient.SetClientId(tfp::StringToInt(tfp::SplitString(Command, 1, ' ', false)));
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "setlighter")
    {
        if(tfp::SplitString(Command, 1, ' ', false) == "")
            GameHandle->GameInterface.NightEffect.SetLighter(!GameHandle->GameInterface.NightEffect.IsLighterOn());
        else
            GameHandle->GameInterface.NightEffect.SetLighter(tfp::StringToBool(tfp::SplitString(Command, 1, ' ', false)));
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "reloadanimations")
    {
        ObjectGifList.LoadGifFiles(GameHandle);
        SpellGifList.LoadGifFiles(GameHandle);
        CharacterGifList.LoadGifFiles(GameHandle);
        MobGifList.LoadGifFiles(GameHandle);
        ObjectGifList.LoadGifFiles(GameHandle);
        SpecialObjectGifList.LoadGifFiles(GameHandle);
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "reloaditems")
    {
        ItemList.LoadAllItems(GameHandle);
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "settilemode")
    {
        if(GameHandle != nullptr)
        {
            GameHandle->GameInterface.SetTileBuildMode(tfp::SplitString(Command, 1, ' ', false));
        }
        else Debug.Warning("Game handle not set");
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "setinventorysize")
    {
        if(tfp::SplitString(Command, 1, ' ', false) == "")
            GameHandle->ControlledPlayer.SetInventorySize(4, 2);
        else
            GameHandle->ControlledPlayer.SetInventorySize(tfp::StringToInt(tfp::SplitString(Command, 1, ' ', false)), tfp::StringToInt(tfp::SplitString(Command, 2, ' ', false)));
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "setinventoryitem")
    {
        if(tfp::SplitString(Command, 3, ' ', false) == "")
        {
            Debug.Command("Use: setinventoryitem <item name> <quantity> <item list position> <rarity level> <improvement level>");
        }
        else
        {
            int RarityLevel = tfp::StringToInt(tfp::SplitString(Command, 4, ' ', false));
            if(RarityLevel <= 0) RarityLevel = 1;
            if(RarityLevel > 5) RarityLevel = 5;

            std::string RarityText;
            if(RarityLevel == 1) RarityText = "Broken";
            else if(RarityLevel == 2) RarityText = "Common";
            else if(RarityLevel == 3) RarityText = "Rare";
            else if(RarityLevel == 4) RarityText = "Epic";
            else if(RarityLevel == 5) RarityText = "Legendary";
            GameHandle->ControlledPlayer.SetInventoryItem(tfp::SplitString(Command, 1, ' ', false), tfp::StringToInt(tfp::SplitString(Command, 2, ' ', false)), tfp::StringToInt(tfp::SplitString(Command, 3, ' ', false)), RarityText, tfp::StringToInt(tfp::SplitString(Command, 5, ' ', false)));
        }

    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "showzindexhelp")
    {
        GameHandle->GameInterface.SetZindexVisible(true);
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "setzindex")
    {
        if(tfp::SplitString(Command, 1, ' ', false) == "")
            GameHandle->GameInterface.SetTileZIndex(0);
        else
            GameHandle->GameInterface.SetTileZIndex(tfp::StringToInt(tfp::SplitString(Command, 1, ' ', false)));
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "setgridshift")
    {
        int HorizontalShift = 0;
        int VerticalShift = 0;

        if(tfp::SplitString(Command, 1, ' ', false) != "")
        {
            HorizontalShift = tfp::StringToFloat(tfp::SplitString(Command, 1, ' ', false));
        }

        if(tfp::SplitString(Command, 2, ' ', false) != "")
        {
            VerticalShift = tfp::StringToFloat(tfp::SplitString(Command, 2, ' ', false));
        }

        GameHandle->GameInterface.SetGridShift(HorizontalShift, VerticalShift);
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "ti")
    {
        RunCommand("setinventorysize 7 8");
        RunCommand("setinventoryitem Item1 1 0 1");
        RunCommand("setinventoryitem Item2 2 1 2 2");
        RunCommand("setinventoryitem Item3 3 2 3 4");
        RunCommand("setinventoryitem Item4 4 3 4 2");
        RunCommand("setinventoryitem Item5 5 4 5 4");
        RunCommand("setinventoryitem Item6 6 5 1 2");
        RunCommand("setinventoryitem Item7 7 6 2 4");
        RunCommand("setinventoryitem Item8 8 7 3 2");
        RunCommand("setinventoryitem Item9 500 8 4 4");
        RunCommand("setinventoryitem Item10 345 9 5 3");
        RunCommand("setinventoryitem Item11 248 10 1 1");
        RunCommand("setinventoryitem TestSword 248 10 1 5");
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "startserver")
    {
        sf::IpAddress StartServerIp = "localhost";
        unsigned short StartServerPort = 5726;

        if(tfp::SplitString(Command, 1, ' ', false) != "")
        {
            StartServerIp = tfp::SplitString(Command, 1, ' ', false);
        }

        if(tfp::SplitString(Command, 2, ' ', false) != "")
        {
            StartServerPort = tfp::StringToInt(tfp::SplitString(Command, 2, ' ', false));
        }

        GameHandle->GameNetworkServer.Run(StartServerIp, StartServerPort);
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "singleplayer")
    {
        GameManagerCommandList.push(Command);
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "stopserver")
    {
        GameHandle->GameNetworkServer.Stop();
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "performance")
    {
        GameHandle->GameFunctionTimes.PrintFunctionTimes();
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "resetperformance")
    {
        GameHandle->GameFunctionTimes.ResetFunctionTimes();
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "whereami")
    {
        Debug.Command("Controlled player position: " + tfp::FloatToString(GameHandle->ControlledPlayer.GetPosition().x) + "x" + tfp::FloatToString(GameHandle->ControlledPlayer.GetPosition().y));
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "whereiscamera")
    {
        Debug.Command("Camera position: " + tfp::FloatToString(GameHandle->GameCamera.GetPosition().x) + "x" + tfp::FloatToString(GameHandle->GameCamera.GetPosition().y));
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "whereisplayer")
    {
        Debug.Command("Player position: " + tfp::FloatToString(GameHandle->ControlledPlayer.GetPosition().x) + "x" + tfp::FloatToString(GameHandle->ControlledPlayer.GetPosition().y));
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "whereisplayeranimation")
    {
        Debug.Command("Player animation: " + tfp::FloatToString(GameHandle->ControlledPlayerAnimation.GetPosition().x) + "x" + tfp::FloatToString(GameHandle->ControlledPlayerAnimation.GetPosition().y));
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "whereisplayerdestination")
    {
        Debug.Command("Player destination: " + tfp::FloatToString(GameHandle->ControlledPlayer.GetDestination().x) + "x" + tfp::FloatToString(GameHandle->ControlledPlayer.GetDestination().y));
    }
    else if(tfp::SplitString(Command, 0, ' ', false) == "whereisplayeranimationdestination")
    {
        Debug.Command("Player animation destination: " + tfp::FloatToString(GameHandle->ControlledPlayerAnimation.GetDestinationPosition().x) + "x" + tfp::FloatToString(GameHandle->ControlledPlayerAnimation.GetDestinationPosition().y));
    }
    else Debug.Command("Unknown command: " + Command);
}

std::string tfp::CommandBlock::GetGameManagerCommand()
{
    std::string Return = GameManagerCommandList.front();
    GameManagerCommandList.pop();
    return Return;
}

const bool tfp::CommandBlock::IsGameManagerCommandListEmpty() const
{
    if(GameManagerCommandList.size() > 0) return false;
    else return true;
}
