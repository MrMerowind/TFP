/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"

tfp::Screen::Screen()
    :MenuWidth(800), GameWidth(800), MapEditorWidth(800), ServerWidth(800), MenuHeight(450), GameHeight(450), MapEditorHeight(450), ServerHeight(450), ViewWidth(6000), ViewHeight(3375), ViewOriginalWidth(6000), ViewOriginalHeight(3375), ViewHorizontalCenter(0),
    ViewVerticalCenter(0), FramerateLimit(0), VerticalSync(false), WindowTitle(L"Game Title"), MenuFullScreen(false), GameFullScreen(false), MapEditorFullScreen(false), ServerFullScreen(false), Focus(true), GameHandle(nullptr)
{
    /// Wczytywanie configu
    std::fstream ScreenConfigFile;
    std::string ScreenConfigFileName = "Config/Screen.config";
    ScreenConfigFile.open(ScreenConfigFileName, std::ios::in);
    if(ScreenConfigFile.good())
    {
        std::string Line;
        while(!ScreenConfigFile.eof())
        {
            getline(ScreenConfigFile,Line);
            if(Line == "");
            else if(Line[0] == '#');
            else if(tfp::SplitString(Line,0) == "MenuWidth")
            {
                MenuWidth = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "GameWidth")
            {
                GameWidth = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "MapEditorWidth")
            {
                MapEditorWidth = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "ServerWidth")
            {
                ServerWidth = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "MenuHeight")
            {
                MenuHeight = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "GameHeight")
            {
                GameHeight = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "MapEditorHeight")
            {
                MapEditorHeight = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "ServerHeight")
            {
                ServerHeight = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "ViewWidth")
            {
                #if VIEW_TEST == 1
                    ViewOriginalWidth = tfp::StringToInt(tfp::SplitString(Line,1));
                #endif // VIEW_TEST
            }
            else if(tfp::SplitString(Line,0) == "ViewHeight")
            {
                #if VIEW_TEST == 1
                    ViewOriginalHeight = tfp::StringToInt(tfp::SplitString(Line,1));
                #endif // VIEW_TEST
            }
            else if(tfp::SplitString(Line,0) == "ViewVerticalCenter")
            {
                #if VIEW_TEST == 1
                    ViewVerticalCenter = tfp::StringToInt(tfp::SplitString(Line,1));
                #endif // VIEW_TEST
            }
            else if(tfp::SplitString(Line,0) == "ViewHorizontalCenter")
            {
                #if VIEW_TEST == 1
                    ViewHorizontalCenter = tfp::StringToInt(tfp::SplitString(Line,1));
                #endif // VIEW_TEST
            }
            else if(tfp::SplitString(Line,0) == "FramerateLimit")
            {
                FramerateLimit = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "VerticalSync")
            {
                VerticalSync = tfp::StringToBool(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "MenuFullScreen")
            {
                MenuFullScreen = tfp::StringToBool(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "GameFullScreen")
            {
                GameFullScreen = tfp::StringToBool(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "MapEditorFullScreen")
            {
                MapEditorFullScreen = tfp::StringToBool(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "ServerFullScreen")
            {
                ServerFullScreen = tfp::StringToBool(tfp::SplitString(Line,1));
            }
            else
            {
                Debug.Warning("Unknow line in: " + ScreenConfigFileName + "  -  " + Line);
            }
        }
        ScreenConfigFile.close();
    }
    else
    {
        Debug.Warning("Can not open Config/Screen.config");
    }

    View.reset(sf::FloatRect(ViewHorizontalCenter, ViewVerticalCenter, ViewWidth, ViewHeight));
    View.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
}

tfp::Screen::~Screen()
{

}

const int tfp::Screen::GetFramerateLimit() const
{
    return FramerateLimit;
}

void tfp::Screen::ResetSettings()
{
    MenuWidth = 1366;
    GameWidth = 1366;
    MapEditorWidth = 1366;
    ServerWidth = 1366;
    MenuHeight = 768;
    GameHeight = 768;
    MapEditorHeight = 768;
    ServerHeight = 768;
    ViewOriginalWidth = 6000;
    ViewOriginalHeight = 3375;
    ViewHorizontalCenter = 0;
    ViewVerticalCenter = 0;
    FramerateLimit = 0;
    VerticalSync = false;
    MenuFullScreen = false;
    GameFullScreen = false;
    MapEditorFullScreen = false;
    ServerFullScreen = false;
    SaveSettings();
    for(int i = 0; i < GameManager.GamesOpen(); i++)
    {
        GameManager.GetGame(i).GameScreen.Resize();
    }
}

void tfp::Screen::Resize(int Width_, int Height_, bool FullScreen_)
{
    if(GameHandle->GetGameType() == "menu")
    {
        if(Width_ > 0 && Height_ > 0)
        {
            MenuWidth = Width_;
            MenuHeight = Height_;
            if(MenuHeight <= 0) MenuHeight = MenuWidth * 9 / 16;
            MenuFullScreen = FullScreen_;
            if(MenuFullScreen) Window.create(sf::VideoMode(MenuWidth, MenuHeight), WindowTitle, sf::Style::Fullscreen);
            else Window.create(sf::VideoMode(MenuWidth, MenuHeight), WindowTitle, sf::Style::Close);
            Window.setView(View);
        }
    }
    else if(GameHandle->GetGameType() == "game")
    {
        if(Width_ > 0 && Height_ > 0)
        {
            GameWidth = Width_;
            GameHeight = Height_;
            if(GameHeight <= 0) GameHeight = GameWidth * 9 / 16;
            GameFullScreen = FullScreen_;
            if(GameFullScreen) Window.create(sf::VideoMode(GameWidth, GameHeight), WindowTitle, sf::Style::Fullscreen);
            else Window.create(sf::VideoMode(GameWidth, GameHeight), WindowTitle, sf::Style::Close);
            Window.setView(View);
        }
    }
    else if(GameHandle->GetGameType() == "mapeditor")
    {
        if(Width_ > 0 && Height_ > 0)
        {
            MapEditorWidth = Width_;
            MapEditorHeight = Height_;
            if(MapEditorHeight <= 0) MapEditorHeight = MapEditorWidth * 9 / 16;
            MapEditorFullScreen = FullScreen_;
            if(MapEditorFullScreen) Window.create(sf::VideoMode(MapEditorWidth, MapEditorHeight), WindowTitle, sf::Style::Fullscreen);
            else Window.create(sf::VideoMode(MapEditorWidth, MapEditorHeight), WindowTitle, sf::Style::Close);
            Window.setView(View);
        }
    }
    else if(GameHandle->GetGameType() == "server")
    {
        if(Width_ > 0 && Height_ > 0)
        {
            ServerWidth = Width_;
            ServerHeight = Height_;
            if(ServerHeight <= 0) ServerHeight = ServerWidth * 9 / 16;
            ServerFullScreen = FullScreen_;
            if(ServerFullScreen) Window.create(sf::VideoMode(ServerWidth, ServerHeight), WindowTitle, sf::Style::Fullscreen);
            else Window.create(sf::VideoMode(ServerWidth, ServerHeight), WindowTitle, sf::Style::Close);
            Window.setView(View);
        }
    }
}

void tfp::Screen::Resize()
{
    std::fstream ScreenConfigFile;
    std::string ScreenConfigFileName = "Config/Screen.config";
    ScreenConfigFile.open(ScreenConfigFileName, std::ios::in);
    if(ScreenConfigFile.good())
    {
        std::string Line;
        while(!ScreenConfigFile.eof())
        {
            getline(ScreenConfigFile,Line);
            if(Line == "");
            else if(Line[0] == '#');
            else if(tfp::SplitString(Line,0) == "MenuWidth")
            {
                MenuWidth = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "GameWidth")
            {
                GameWidth = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "MapEditorWidth")
            {
                MapEditorWidth = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "ServerWidth")
            {
                ServerWidth = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "MenuHeight")
            {
                MenuHeight = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "GameHeight")
            {
                GameHeight = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "MapEditorHeight")
            {
                MapEditorHeight = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "ServerHeight")
            {
                ServerHeight = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "ViewWidth")
            {
                #if VIEW_TEST == 1
                    ViewOriginalWidth = tfp::StringToInt(tfp::SplitString(Line,1));
                #endif // VIEW_TEST
            }
            else if(tfp::SplitString(Line,0) == "ViewHeight")
            {
                #if VIEW_TEST == 1
                    ViewOriginalHeight = tfp::StringToInt(tfp::SplitString(Line,1));
                #endif // VIEW_TEST
            }
            else if(tfp::SplitString(Line,0) == "ViewVerticalCenter")
            {
                #if VIEW_TEST == 1
                    ViewVerticalCenter = tfp::StringToInt(tfp::SplitString(Line,1));
                #endif // VIEW_TEST
            }
            else if(tfp::SplitString(Line,0) == "ViewHorizontalCenter")
            {
                #if VIEW_TEST == 1
                    ViewHorizontalCenter = tfp::StringToInt(tfp::SplitString(Line,1));
                #endif // VIEW_TEST
            }
            else if(tfp::SplitString(Line,0) == "FramerateLimit")
            {
                FramerateLimit = tfp::StringToInt(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "VerticalSync")
            {
                VerticalSync = tfp::StringToBool(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "MenuFullScreen")
            {
                MenuFullScreen = tfp::StringToBool(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "GameFullScreen")
            {
                GameFullScreen = tfp::StringToBool(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "MapEditorFullScreen")
            {
                MapEditorFullScreen = tfp::StringToBool(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "ServerFullScreen")
            {
                ServerFullScreen = tfp::StringToBool(tfp::SplitString(Line,1));
            }
            else
            {
                Debug.Warning("Unknow line in: " + ScreenConfigFileName + "  -  " + Line);
            }
        }
        ScreenConfigFile.close();
    }
    else
    {
        Debug.Warning("Can not open Config/Screen.config");
    }

    View.reset(sf::FloatRect(ViewHorizontalCenter, ViewVerticalCenter, ViewWidth, ViewHeight));
    View.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
    if(GameHandle->GetGameType() == "menu")
    {
        if(MenuFullScreen) Window.create(sf::VideoMode(MenuWidth, MenuHeight), WindowTitle, sf::Style::Fullscreen);
        else Window.create(sf::VideoMode(MenuWidth, MenuHeight), WindowTitle, sf::Style::Close);
        Window.setView(View);
    }
    else if(GameHandle->GetGameType() == "game")
    {
        if(GameFullScreen) Window.create(sf::VideoMode(GameWidth, GameHeight), WindowTitle, sf::Style::Fullscreen);
        else Window.create(sf::VideoMode(GameWidth, GameHeight), WindowTitle, sf::Style::Close);
        Window.setView(View);
    }
    else if(GameHandle->GetGameType() == "mapeditor")
    {
        if(MapEditorFullScreen) Window.create(sf::VideoMode(MapEditorWidth, MapEditorHeight), WindowTitle, sf::Style::Fullscreen);
        else Window.create(sf::VideoMode(MapEditorWidth, MapEditorHeight), WindowTitle, sf::Style::Close);
        Window.setView(View);
    }
    else if(GameHandle->GetGameType() == "server")
    {
        if(ServerFullScreen) Window.create(sf::VideoMode(ServerWidth, ServerHeight), WindowTitle, sf::Style::Fullscreen);
        else Window.create(sf::VideoMode(ServerWidth, ServerHeight), WindowTitle, sf::Style::Close);
        Window.setView(View);
    }
}

void tfp::Screen::SetViewSize(int Width_, int Height_)
{
    ViewWidth = Width_;
    ViewHeight = Height_;
    if(ViewHeight <= 0) ViewHeight = ViewWidth * 9 / 16;
    View.setSize(sf::Vector2f(ViewWidth,ViewHeight));
    View.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
    View.setCenter(sf::Vector2f(std::floor(ViewWidth / 2.0f), std::floor(ViewHeight / 2.0f)));
    Window.setView(View);
}

void tfp::Screen::Draw(const sf::Drawable &Drawable)
{
    Window.draw(Drawable);
}

void tfp::Screen::DrawVertex(const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type, const sf::RenderStates& states)
{
    Window.draw(vertices, vertexCount, type, states);
}

const bool tfp::Screen::IsWindowOpen()
{
    if(Window.isOpen()) return true;
    else return false;
}

void tfp::Screen::SetViewScale(float Scale)
{
    ViewWidth = (int) (ViewOriginalWidth * Scale);
    ViewHeight = (int) (ViewOriginalHeight * Scale);
}

sf::Event tfp::Screen::GetScreenEvent()
{
    sf::Event Return = ScreenEvents.front();
    ScreenEvents.pop();
    return Return;
}

const bool tfp::Screen::IsEventInQueue()
{
    if(ScreenEvents.size() > 0) return true;
    else return false;
}

void tfp::Screen::Clear()
{
    Window.clear(sf::Color(244, 247, 190));
}

void tfp::Screen::Close()
{
    Window.close();
    AreaList.UnregisterGame(GameHandle);
    WindowGlobalData.UnregisterWindows(GameHandle);
}

void tfp::Screen::DisplayWindow()
{
    sf::Event Event;
    while(Window.pollEvent(Event))
    {
        ScreenEvents.push(Event);
        AreaList.SendEvent(Event);
    }

    if(Window.isOpen())
    {
        if(GameManager.GetFrameLimit() != FramerateLimit)
        {
            FramerateLimit = GameManager.GetFrameLimit();
            Window.setFramerateLimit(FramerateLimit);
        }
        if(GameManager.GetVerticalSync() != VerticalSync)
        {
            VerticalSync = GameManager.GetVerticalSync();
            Window.setVerticalSyncEnabled(VerticalSync);
        }
        if(IsFocused()) Window.display();
    }
}

void tfp::Screen::SetFocus(bool State)
{
    Focus = State;
}

void tfp::Screen::SetGameHandle(tfp::Game *Handle)
{
    GameHandle = Handle;
    if(GameHandle->GetGameType() == "menu")
    {
        if(MenuFullScreen) Window.create(sf::VideoMode(MenuWidth, MenuHeight), WindowTitle, sf::Style::Fullscreen);
        else Window.create(sf::VideoMode(MenuWidth, MenuHeight), WindowTitle, sf::Style::Close);
    }
    else if(GameHandle->GetGameType() == "game")
    {
        if(GameFullScreen) Window.create(sf::VideoMode(GameWidth, GameHeight), WindowTitle, sf::Style::Fullscreen);
        else Window.create(sf::VideoMode(GameWidth, GameHeight), WindowTitle, sf::Style::Close);
    }
    else if(GameHandle->GetGameType() == "mapeditor")
    {
       if(MapEditorFullScreen) Window.create(sf::VideoMode(MapEditorWidth, MapEditorHeight), WindowTitle, sf::Style::Fullscreen);
        else Window.create(sf::VideoMode(MapEditorWidth, MapEditorHeight), WindowTitle, sf::Style::Close);
    }
    else if(GameHandle->GetGameType() == "server")
    {
        if(ServerFullScreen) Window.create(sf::VideoMode(ServerWidth, ServerHeight), WindowTitle, sf::Style::Fullscreen);
        else Window.create(sf::VideoMode(ServerWidth, ServerHeight), WindowTitle, sf::Style::Close);
    }
    else
    {
        Debug.Error("Game window can not be created. Unknown game window type: " + GameHandle->GetGameType());
    }

    Window.setView(View);
    Window.setFramerateLimit(FramerateLimit);
    Window.setVerticalSyncEnabled(VerticalSync);
}

const bool &tfp::Screen::IsFocused() const
{
    return Focus;
}

sf::RenderWindow &tfp::Screen::GetRenderWindowHandle()
{
    return Window;
}

const sf::Vector2i tfp::Screen::GetWindowSize()
{
    if(GameHandle->GetGameType() == "menu")
    {
        return sf::Vector2i(MenuWidth, MenuHeight);
    }
    else if(GameHandle->GetGameType() == "game")
    {
        return sf::Vector2i(GameWidth, GameHeight);
    }
    else if(GameHandle->GetGameType() == "mapeditor")
    {
        return sf::Vector2i(MapEditorWidth, MapEditorHeight);
    }
    else if(GameHandle->GetGameType() == "server")
    {
        return sf::Vector2i(ServerWidth, ServerHeight);
    }
    else
    {
        Debug.Warning("Unknown game window type: " + GameHandle->GetGameType());
        return {MenuWidth, MenuHeight};
    }
}

const sf::Vector2i tfp::Screen::GetViewSize()
{
    return sf::Vector2i(ViewWidth, ViewHeight);
}

const sf::Vector2i tfp::Screen::GetOriginalViewSize()
{
    return sf::Vector2i(ViewOriginalWidth, ViewOriginalHeight);
}

const float tfp::Screen::GetViewScale()
{
    float Return = (float)ViewWidth / (float)ViewOriginalWidth;
    return Return;
}

void tfp::Screen::SetWindowTitle(std::wstring Title)
{
    WindowTitle = Title;
    Window.setTitle(WindowTitle);
}

bool tfp::Screen::GetFullScreen(std::string GameType)
{
    if(GameType == "menu") return MenuFullScreen;
    else if(GameType == "game") return GameFullScreen;
    else if(GameType == "mapeditor") return MapEditorFullScreen;
    else if(GameType == "server") return ServerFullScreen;
    else
    {
        Debug.Error("GetFullScreen(): Wrong game window type");
        return false;
    }
}

void tfp::Screen::SetFullScreen(std::string GameType, bool State)
{
    if(GameType == "menu")
    {
        MenuFullScreen = State;
        for(int i = 0; i < GameManager.GamesOpen(); i++)
        {
            if(GameManager.GetGame(i).GameScreen.IsWindowOpen() && GameManager.GetGame(i).GetGameType() == GameType)
            {
                GameManager.GetGame(i).GameScreen.Resize(MenuWidth, MenuHeight, MenuFullScreen);
            }
        }
    }
    else if(GameType == "game")
    {
        GameFullScreen = State;
        for(int i = 0; i < GameManager.GamesOpen(); i++)
        {
            if(GameManager.GetGame(i).GameScreen.IsWindowOpen() && GameManager.GetGame(i).GetGameType() == GameType)
            {
                GameManager.GetGame(i).GameScreen.Resize(GameWidth, GameHeight, GameFullScreen);
            }
        }
    }
    else if(GameType == "mapeditor")
    {
        MapEditorFullScreen = State;
        for(int i = 0; i < GameManager.GamesOpen(); i++)
        {
            if(GameManager.GetGame(i).GameScreen.IsWindowOpen() && GameManager.GetGame(i).GetGameType() == GameType)
            {
                GameManager.GetGame(i).GameScreen.Resize(MapEditorWidth, MapEditorHeight, MapEditorFullScreen);
            }
        }
    }
    else if(GameType == "server")
    {
        ServerFullScreen = State;
        for(int i = 0; i < GameManager.GamesOpen(); i++)
        {
            if(GameManager.GetGame(i).GameScreen.IsWindowOpen() && GameManager.GetGame(i).GetGameType() == GameType)
            {
                GameManager.GetGame(i).GameScreen.Resize(ServerWidth, ServerHeight, ServerFullScreen);
            }
        }
    }
    else
    {
        Debug.Error("SetFullScreen(): Wrong game window type");
    }
    SaveSettings();
}

void tfp::Screen::SetWindowSize(std::string GameType, int NewWidth, int NewHeight)
{
    if(GameType == "menu")
    {
        MenuWidth = NewWidth;
        MenuHeight = NewHeight;
        for(int i = 0; i < GameManager.GamesOpen(); i++)
        {
            if(GameManager.GetGame(i).GameScreen.IsWindowOpen() && GameManager.GetGame(i).GetGameType() == GameType)
            {
                GameManager.GetGame(i).GameScreen.Resize(MenuWidth, MenuHeight, MenuFullScreen);
            }
        }
    }
    else if(GameType == "game")
    {
        GameWidth = NewWidth;
        GameHeight = NewHeight;
        for(int i = 0; i < GameManager.GamesOpen(); i++)
        {
            if(GameManager.GetGame(i).GameScreen.IsWindowOpen() && GameManager.GetGame(i).GetGameType() == GameType)
            {
                GameManager.GetGame(i).GameScreen.Resize(GameWidth, GameHeight, GameFullScreen);
            }
        }
    }
    else if(GameType == "mapeditor")
    {
        MapEditorWidth = NewWidth;
        MapEditorHeight = NewHeight;
        for(int i = 0; i < GameManager.GamesOpen(); i++)
        {
            if(GameManager.GetGame(i).GameScreen.IsWindowOpen() && GameManager.GetGame(i).GetGameType() == GameType)
            {
                GameManager.GetGame(i).GameScreen.Resize(MapEditorWidth, MapEditorHeight, MapEditorFullScreen);
            }
        }
    }
    else if(GameType == "server")
    {
        ServerWidth = NewWidth;
        ServerHeight = NewHeight;
        for(int i = 0; i < GameManager.GamesOpen(); i++)
        {
            if(GameManager.GetGame(i).GameScreen.IsWindowOpen() && GameManager.GetGame(i).GetGameType() == GameType)
            {
                GameManager.GetGame(i).GameScreen.Resize(ServerWidth, ServerHeight, ServerFullScreen);
            }
        }
    }
    else
    {
        Debug.Error("SetWindowSize(): Wrong game window type");
    }
    SaveSettings();
}

bool tfp::Screen::GetVerticalSync()
{
    return VerticalSync;
}

void tfp::Screen::SetVerticalSync(bool State)
{
    VerticalSync = State;
    for(int i = 0; i < GameManager.GamesOpen(); i++)
    {
        GameManager.GetGame(i).GameScreen.SetVerticalSync(VerticalSync);
    }
    SaveSettings();
}

void tfp::Screen::SaveSettings()
{
    std::string Line;
    std::fstream ConfigFile;
    ConfigFile.open("Config/Screen.config", std::ios::out);
    if(ConfigFile.good())
    {
        ConfigFile << "#May be overwritten" << std::endl;
        ConfigFile << "#Do not edit untill necessary" << std::endl;
        ConfigFile << "#Delete content for reset" << std::endl;
        ConfigFile << "MenuWidth: " << tfp::IntToString(MenuWidth) << std::endl;
        ConfigFile << "MenuHeight: " << tfp::IntToString(MenuHeight) << std::endl;
        ConfigFile << "MenuFullScreen: " << tfp::BoolToString(MenuFullScreen) << std::endl;
        ConfigFile << "GameWidth: " << tfp::IntToString(GameWidth) << std::endl;
        ConfigFile << "GameHeight: " << tfp::IntToString(GameHeight) << std::endl;
        ConfigFile << "GameFullScreen: " << tfp::BoolToString(GameFullScreen) << std::endl;
        ConfigFile << "MapEditorWidth: " << tfp::IntToString(MapEditorWidth) << std::endl;
        ConfigFile << "MapEditorHeight: " << tfp::IntToString(MapEditorHeight) << std::endl;
        ConfigFile << "MapEditorFullScreen: " << tfp::BoolToString(MapEditorFullScreen) << std::endl;
        ConfigFile << "ServerWidth: " << tfp::IntToString(ServerWidth) << std::endl;
        ConfigFile << "ServerHeight: " << tfp::IntToString(ServerHeight) << std::endl;
        ConfigFile << "ServerFullScreen: " << tfp::BoolToString(ServerFullScreen) << std::endl;
        ConfigFile << "FramerateLimit: " << tfp::IntToString(FramerateLimit) << std::endl;
        ConfigFile << "VerticalSync: " << tfp::BoolToString(VerticalSync) << std::endl;
        #if VIEW_TEST == 1
            ConfigFile << "#Testing enabled " << std::endl;
        #else
            ConfigFile << "#Disabled values " << std::endl;
        #endif // VIEW_TEST
        ConfigFile << "ViewWidth: " << tfp::IntToString(ViewWidth) << std::endl;
        ConfigFile << "ViewHeight: " << tfp::IntToString(ViewHeight) << std::endl;
        ConfigFile << "ViewVerticalCenter: " << tfp::IntToString(ViewVerticalCenter) << std::endl;
        ConfigFile << "ViewHorizontalCenter: " << tfp::IntToString(ViewHorizontalCenter) << std::endl;
        ConfigFile.close();
        Debug.Info("Graphic configuration saved");
    }
    else
    {
        Debug.Warning("Can not open file Config/Screen.config");
    }
}
