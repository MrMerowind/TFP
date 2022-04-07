/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"

tfp::GameManagerClass::GameManagerClass()
    :FramerateLimit(100)
{
    std::fstream ConfigFile;
    ConfigFile.open("Config/screen.config", std::ios::in);
    if(!ConfigFile.good())
    {
        Debug.Warning("Can not open: Config/Screen.config");
    }
    else
    {
        std::string Line;
        while(!ConfigFile.eof())
        {
            std::getline(ConfigFile, Line);
            if(Line == "");
            else if(Line[0] == '#');
            else if(tfp::SplitString(Line, 0) == "FramerateLimit")
            {
                FramerateLimit = tfp::StringToInt(tfp::SplitString(Line, 1));
            }
            else if(tfp::SplitString(Line, 0) == "VerticalSync")
            {
                VerticalSync = tfp::StringToBool(tfp::SplitString(Line, 1));
            }
        }
        ConfigFile.close();
    }

}

tfp::GameManagerClass::~GameManagerClass()
{
    for(unsigned i = 0; i < GameList.size(); i++)
        delete GameList[i];
}

void tfp::GameManagerClass::DestroyClosedGames()
{
    for(unsigned i = 0; i < GameList.size(); i++)
    {
        if(!GameList[i]->GameScreen.IsWindowOpen())
        {
            delete GameList[i];
            GameList.erase(GameList.begin() + i);
            i--;
        }
    }

}

const bool tfp::GameManagerClass::IsAnyWindowOpen() const
{
    for(unsigned i = 0; i < GameList.size(); i++)
        if(GameList[i]->GameScreen.IsWindowOpen()) return true;
    return false;
}

void tfp::GameManagerClass::CreateGame(std::string Option, std::string Command)
{
    if(Option == "mapeditor")
    {
        GameList.push_back(new tfp::Game(Option));
        GameList[GameList.size() - 1]->GameScreen.SetViewSize(10000, 5625);
        GameList[GameList.size() - 1]->GameScreen.SetWindowTitle(Language.Translate("Map editor"));
    }
    else if(Option == "game")
    {
        GameList.push_back(new tfp::Game(Option));
        GameList[GameList.size() - 1]->GameScreen.SetViewSize(6000, 3375);
        GameList[GameList.size() - 1]->GameScreen.SetWindowTitle(Language.Translate("The Fulman Project - Game In Development"));
        GameList[GameList.size() - 1]->GameCamera.LockOnPlayer(true);
        if(Command != "")
        {
            if(tfp::SplitString(Command, 1, ' ', false) != "")
            {
                GameList[GameList.size() - 1]->GameNetworkClient.Run(tfp::SplitString(Command, 1, ' ', false), tfp::StringToInt(tfp::SplitString(Command, 2, ' ', false)));
            }
            else
            {
                GameList[GameList.size() - 1]->GameNetworkClient.Run("localhost", 5726);
            }
        }
    }
    else if(Option == "singleplayer")
    {
        GameList.push_back(new tfp::Game("game"));
        GameList[GameList.size() - 1]->GameScreen.SetViewSize(6000, 3375);
        GameList[GameList.size() - 1]->GameScreen.SetWindowTitle(Language.Translate("The Fulman Project - Game In Development"));
        GameList[GameList.size() - 1]->GameCamera.LockOnPlayer(true);
        GameList[GameList.size() - 1]->GameNetworkServer.Run("localhost", 0);
        while(!GameList[GameList.size() - 1]->GameNetworkServer.IsTurnOn())sf::sleep(sf::milliseconds(10));
        GameList[GameList.size() - 1]->GameNetworkClient.Run(GameList[GameList.size() - 1]->GameNetworkServer);
    }
    else if(Option == "menu")
    {
        GameList.push_back(new tfp::Game(Option));
        GameList[GameList.size() - 1]->GameScreen.SetWindowTitle(Language.Translate("Menu"));
    }
    else if(Option == "server")
    {
        GameList.push_back(new tfp::Game(Option));
        GameList[GameList.size() - 1]->GameScreen.SetWindowTitle(Language.Translate("Server"));
    }

}

const int tfp::GameManagerClass::GamesOpen() const
{
    return GameList.size();
}

tfp::Game &tfp::GameManagerClass::GetGame(unsigned Index) const
{
    if(Index > GameList.size()) Debug.Error("GameManager  -  Index does not exist");
    return (*GameList[Index]);
}

void tfp::GameManagerClass::SetFrameLimit(int Frames)
{
    if(Frames < 0) Frames = 0;
    FramerateLimit = Frames;
}

const int tfp::GameManagerClass::GetFrameLimit() const
{
    return FramerateLimit;
}

void tfp::GameManagerClass::RenderFrames()
{
    for(int i = 0; i < GamesOpen(); i++)
    {
        GetGame(i).RenderFrame();
        if(GetGame(i).GameCommandBlock.IsGameManagerCommandListEmpty() == false)
        {
            std::string Cmd = GetGame(i).GameCommandBlock.GetGameManagerCommand();
            if(tfp::SplitString(Cmd, 0, ' ', false) == "mapeditor")
            {
                CreateGame("mapeditor");
            }
            else if(tfp::SplitString(Cmd, 0, ' ', false) == "newgame")
            {
                CreateGame("game");
            }
            else if(tfp::SplitString(Cmd, 0, ' ', false) == "singleplayer")
            {
                CreateGame("singleplayer");
            }
            else if(tfp::SplitString(Cmd, 0, ' ', false) == "joingame")
            {
                CreateGame("game", Cmd);
            }
            else if(tfp::SplitString(Cmd, 0, ' ', false) == "menu")
            {
                CreateGame("menu");
            }
            else if(tfp::SplitString(Cmd, 0, ' ', false) == "server")
            {
                CreateGame("server");
            }


        }
    }

}

bool tfp::GameManagerClass::GetVerticalSync()
{
    return VerticalSync;
}

void tfp::GameManagerClass::SetVerticalSync(bool State)
{
    VerticalSync = State;
}

void tfp::GameManagerClass::ResetWindowTitles()
{
    for(unsigned i = 0; i < GameList.size(); i++)
    {
        if(!GameList[i]->GameScreen.IsWindowOpen()) continue;
        if(GameList[i]->GetGameType() == "mapeditor") GameList[i]->GameScreen.SetWindowTitle(Language.Translate("Map editor"));
        else if(GameList[i]->GetGameType() == "menu") GameList[i]->GameScreen.SetWindowTitle(Language.Translate("The Fulman Project - Game In Development"));
        else if(GameList[i]->GetGameType() == "game") GameList[i]->GameScreen.SetWindowTitle(Language.Translate("The Fulman Project - Game In Development"));
        else if(GameList[i]->GetGameType() == "server") GameList[i]->GameScreen.SetWindowTitle(Language.Translate("Server"));
    }
}
