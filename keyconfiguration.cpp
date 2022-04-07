/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"


tfp::KeyConfigClass::KeyConfigClass()
{
    LoadDefaultConfig();
    LoadUserConfig();
}

tfp::KeyConfigClass::~KeyConfigClass()
{
    UnloadConfig();
}

void tfp::KeyConfigClass::LoadDefaultConfig()
{
    std::string Line;
    std::fstream ConfigFile;
    std::string ConfigFileName = "Config/DefaultKeyConfig.config";
    ConfigFile.open(ConfigFileName, std::ios::in);
    if(ConfigFile.good())
    {
        std::string Line;
        while(!ConfigFile.eof())
        {
            getline(ConfigFile,Line);
            if(Line == "");
            else if(Line[0] == '#');
            else
            {
                std::string Name = tfp::SplitString(Line, 0);
                std::string Key = tfp::SplitString(Line, 1, ':', false);
                tfp::KeyConfigClass::Node Event;
                Event.KeyAlt = false;
                Event.KeyControl = false;
                Event.KeyShift = false;
                Event.KeySystem = false;
                Event.KeyCode = -1;
                int Parts = tfp::CountSymbolsInText(Key, ' ') + 1;
                for(int i = 0; i < Parts; i++)
                {
                    std::string KeyPart = tfp::SplitString(Key, i, ' ', false);
                    if(KeyPart == "");
                    else if(KeyPart == "Ctrl") Event.KeyControl = true;
                    else if(KeyPart == "Shift") Event.KeyShift = true;
                    else if(KeyPart == "Alt") Event.KeyAlt = true;
                    else if(KeyPart == "System") Event.KeySystem = true;
                    else
                    {
                        Event.KeyCode = tfp::StringToInt(KeyPart);
                    }
                }
                SetAction(Name, Event.KeyCode, Event.KeyShift, Event.KeyAlt, Event.KeyControl, Event.KeySystem);
            }
        }
        ConfigFile.close();
        Debug.Info("Default key configuration loaded");
    }
    else
    {
        Debug.Warning("Can not open Config/DefaultKeyConfig.config");
        return;
    }
}

void tfp::KeyConfigClass::LoadUserConfig()
{
    std::string Line;
    std::fstream ConfigFile;
    std::string ConfigFileName = "Config/UserKeyConfig.config";
    ConfigFile.open(ConfigFileName, std::ios::in);
    if(ConfigFile.good())
    {
        std::string Line;
        while(!ConfigFile.eof())
        {
            getline(ConfigFile,Line);
            if(Line == "");
            else if(Line[0] == '#');
            else
            {
                std::string Name = tfp::SplitString(Line, 0);
                std::string Key = tfp::SplitString(Line, 1, ':', false);
                tfp::KeyConfigClass::Node Event;
                Event.KeyAlt = false;
                Event.KeyControl = false;
                Event.KeyShift = false;
                Event.KeySystem = false;
                Event.KeyCode = -1;
                int Parts = tfp::CountSymbolsInText(Key, ' ') + 1;
                for(int i = 0; i < Parts; i++)
                {
                    std::string KeyPart = tfp::SplitString(Key, i, ' ', false);
                    if(KeyPart == "");
                    else if(KeyPart == "Ctrl") Event.KeyControl = true;
                    else if(KeyPart == "Shift") Event.KeyShift = true;
                    else if(KeyPart == "Alt") Event.KeyAlt = true;
                    else if(KeyPart == "System") Event.KeySystem = true;
                    else
                    {
                        Event.KeyCode = tfp::StringToInt(KeyPart);
                    }
                }
                SetAction(Name, Event.KeyCode, Event.KeyShift, Event.KeyAlt, Event.KeyControl, Event.KeySystem);
            }
        }
        ConfigFile.close();
        Debug.Info("User key configuration loaded");
    }
    else
    {
        Debug.Warning("Can not open Config/UserKeyConfig.config");
        return;
    }
}

void tfp::KeyConfigClass::SaveUserConfig()
{
    std::fstream ConfigFile;
    std::string ConfigFileName = "Config/UserKeyConfig.config";
    ConfigFile.open(ConfigFileName, std::ios::out);
    if(ConfigFile.good())
    {
        std::string Line;
        for(unsigned i = 0; i < KeyConfigList.size(); i++)
        {
            ConfigFile << KeyConfigList[i].ActionName << ":";
            if(KeyConfigList[i].KeySystem) ConfigFile << "System ";
            if(KeyConfigList[i].KeyControl) ConfigFile << "Ctrl ";
            if(KeyConfigList[i].KeyAlt) ConfigFile << "Alt ";
            if(KeyConfigList[i].KeyShift) ConfigFile << "Shift ";
            ConfigFile << tfp::IntToString(static_cast<int>(KeyConfigList[i].KeyCode)) << std::endl;
        }
        ConfigFile.close();
    }
    else
    {
        Debug.Warning("Can not open Config/UserKeyConfig.config");
        return;
    }
}

void tfp::KeyConfigClass::UnloadConfig()
{
    KeyConfigList.clear();
    Debug.Info("Key configuration unloaded");
}

void tfp::KeyConfigClass::SetAction(std::string Action, sf::Event &KeyCombination)
{
    for(unsigned i = 0; i < KeyConfigList.size(); i++)
    {
        if(KeyConfigList[i].ActionName == Action)
        {
            KeyConfigList[i].KeyAlt = KeyCombination.key.alt;
            KeyConfigList[i].KeyControl = KeyCombination.key.control;
            KeyConfigList[i].KeyShift = KeyCombination.key.shift;
            KeyConfigList[i].KeySystem = KeyCombination.key.system;
            KeyConfigList[i].KeyCode = static_cast<int>(KeyCombination.key.code);
            return;
        }
    }
    KeyConfigList.push_back(tfp::KeyConfigClass::Node());
    KeyConfigList[KeyConfigList.size() - 1].ActionName = Action;
    KeyConfigList[KeyConfigList.size() - 1].KeyAlt = KeyCombination.key.alt;
    KeyConfigList[KeyConfigList.size() - 1].KeyControl = KeyCombination.key.control;
    KeyConfigList[KeyConfigList.size() - 1].KeyShift = KeyCombination.key.shift;
    KeyConfigList[KeyConfigList.size() - 1].KeySystem = KeyCombination.key.system;
    KeyConfigList[KeyConfigList.size() - 1].KeyCode = static_cast<int>(KeyCombination.key.code);
}

bool tfp::KeyConfigClass::IsKeyEventEqual(std::string Name, sf::Event &Event)
{
    for(unsigned i = 0; i < KeyConfigList.size(); i++)
    {
        if(KeyConfigList[i].ActionName == Name)
        {
            if(Event.type == sf::Event::KeyPressed && KeyConfigList[i].KeyAlt == Event.key.alt
                && KeyConfigList[i].KeyControl == Event.key.control && KeyConfigList[i].KeyShift == Event.key.shift
                 && KeyConfigList[i].KeySystem == Event.key.system && KeyConfigList[i].KeyCode == (int) Event.key.code) return true;
            else return false;
        }
    }
    Debug.Warning("Unknown key action name: " + Name);
    return false;
}

void tfp::KeyConfigClass::SetAction(std::string Action, int Code, bool Shift, bool Alt, bool Control, bool System)
{
    for(unsigned i = 0; i < KeyConfigList.size(); i++)
    {
        if(KeyConfigList[i].ActionName == Action)
        {
            KeyConfigList[i].KeyAlt = Alt;
            KeyConfigList[i].KeyControl = Control;
            KeyConfigList[i].KeyShift = Shift;
            KeyConfigList[i].KeySystem = System;
            KeyConfigList[i].KeyCode = Code;
            return;
        }
    }
    KeyConfigList.push_back(tfp::KeyConfigClass::Node());
    KeyConfigList[KeyConfigList.size() - 1].ActionName = Action;
    KeyConfigList[KeyConfigList.size() - 1].KeyAlt = Alt;
    KeyConfigList[KeyConfigList.size() - 1].KeyControl = Control;
    KeyConfigList[KeyConfigList.size() - 1].KeyShift = Shift;
    KeyConfigList[KeyConfigList.size() - 1].KeySystem = System;
    KeyConfigList[KeyConfigList.size() - 1].KeyCode = Code;
}

std::string tfp::KeyConfigClass::GetActionInString(std::string Action)
{
    for(unsigned i = 0; i < KeyConfigList.size(); i++)
    {
        if(KeyConfigList[i].ActionName == Action)
        {
            std::string Return = "";
            if(KeyConfigList[i].KeySystem) Return += "System + ";
            if(KeyConfigList[i].KeyControl) Return += "Ctrl + ";
            if(KeyConfigList[i].KeyAlt) Return += "Alt + ";
            if(KeyConfigList[i].KeyShift) Return += "Shift + ";
            Return += tfp::SfmlEventIDToString(KeyConfigList[i].KeyCode);
            return Return;
        }
    }
    Debug.Warning("Unknown key action: " + Action);
    return "";
}

std::vector<tfp::KeyConfigClass::Node> &tfp::KeyConfigClass::GetKeyConfigList()
{
    return KeyConfigList;
}
