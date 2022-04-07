/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"

tfp::DebugClass::DebugClass()
    :ShowError(false), ShowInfo(false), ShowWarning(false), ShowCommand(false), LogError(false), LogInfo(false), LogWarning(false), LogCommand(false),
    DontRepeat(false), NextDebugMessageID(0), DebugMessageHistoryLimit(20)
{
    LogPath = "Logs/DebugLog_" + tfp::Date("Y_M_D_h_m") + ".log";
    DebugLogFile.open(LogPath, std::ios::out);
    if(!DebugLogFile.good()) Error("Can not create log file: " + LogPath);

    std::string Line;
    std::fstream ConfigFile;
    ConfigFile.open("Config/Debug.config", std::ios::in);
    if(ConfigFile.good())
    {
        while(!ConfigFile.eof())
        {
            getline(ConfigFile,Line);
            if(Line[0] == '#');
            else if(tfp::SplitString(Line,0) == "ShowError")
            {
                ShowError = tfp::StringToBool(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "ShowWarning")
            {
                ShowWarning = tfp::StringToBool(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "DontRepeat")
            {
                DontRepeat = tfp::StringToBool(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "ShowInfo")
            {
                ShowInfo = tfp::StringToBool(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "ShowCommand")
            {
                ShowCommand = tfp::StringToBool(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "LogWarning")
            {
                LogWarning = tfp::StringToBool(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "LogError")
            {
                LogError = tfp::StringToBool(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "LogInfo")
            {
                LogInfo = tfp::StringToBool(tfp::SplitString(Line,1));
            }
            else if(tfp::SplitString(Line,0) == "LogPath")
            {
                LogPath = tfp::SplitString(Line,1);
            }
            else if(tfp::SplitString(Line,0) == "LogCommand")
            {
                LogCommand = tfp::StringToBool(tfp::SplitString(Line,1));
            }
            else
            {
                Warning("Unknown line in Config/Debug.config: " + Line);
            }
        }
        ConfigFile.close();
    }
    else
    {
        #if WRITE_IN_CONSOLE == 1
            std::cerr << "Can not load Config/Debug.config" << std::endl;
        #endif // WRITE_IN_CONSOLE
    }
}

tfp::DebugClass::~DebugClass()
{
    DebugLogFile.close();
}

void tfp::DebugClass::Log(std::string Text)
{
    if(DebugLogFile.good())
    {
        DebugLogFile << Text << std::endl;
    }
}

void tfp::DebugClass::Error(std::string Message)
{
    if(DontRepeat && LastError == Message) return;
    else LastError = Message;
    if(ShowError)
    {
        #if WRITE_IN_CONSOLE == 1
            std::cerr << "[Error]: " << Message << std::endl;
        #endif // WRITE_IN_CONSOLE
        AddToHistory("[Error]: " + Message);
    }
    if(LogError)
        Log("[Error]: " + Message);
}

void tfp::DebugClass::Info(std::string Message)
{
    if(DontRepeat && LastError == Message) return;
    else LastError = Message;
    if(ShowInfo)
    {
        #if WRITE_IN_CONSOLE == 1
            std::cerr << "" << Message << std::endl;
        #endif // WRITE_IN_CONSOLE
        AddToHistory("" + Message);
    }
    if(LogInfo)
        Log("" + Message);
}

void tfp::DebugClass::Command(std::string Message)
{
    if(DontRepeat && LastError == Message) return;
    else LastError = Message;
    if(ShowCommand)
    {
        #if WRITE_IN_CONSOLE == 1
            std::cerr << "" << Message << std::endl;
        #endif // WRITE_IN_CONSOLE
        AddToHistory("" + Message);
    }
    if(LogCommand)
        Log("" + Message);
}

void tfp::DebugClass::Warning(std::string Message)
{
    if(DontRepeat && LastError == Message) return;
    else LastError = Message;
    if(ShowWarning)
    {
        #if WRITE_IN_CONSOLE == 1
            std::cerr << "[Warning]: " << Message << std::endl;
        #endif // WRITE_IN_CONSOLE
        AddToHistory("[Warning]: " + Message);
    }
    if(LogWarning)
        Log("[Warning]: " + Message);
}

tfp::DebugClass::DebugMessageHistory::DebugMessageHistory(std::string _Information, int _Number)
{
    Information = _Information;
    Number = _Number;
}

void tfp::DebugClass::AddToHistory(std::string Text)
{
    DebugMessageHistoryList.push_back(DebugMessageHistory(Text,NextDebugMessageID++));
    if(DebugMessageHistoryList.size() > tfp::NotBelowZero(DebugMessageHistoryLimit))
    {
        DebugMessageHistoryList.erase(DebugMessageHistoryList.begin());
    }
}

std::string tfp::DebugClass::GetDebugMessage(int Number)
{
    std::string Return;
    for(unsigned i = 0; i < DebugMessageHistoryList.size(); i++)
    {
        if(DebugMessageHistoryList[i].Number == Number)
        {
            Return = DebugMessageHistoryList[i].Information;
            break;
        }
    }
    return Return;
}

const bool tfp::DebugClass::IsDebugMessageAvailiable(int Number)
{
    if(DebugMessageHistoryList.size() <= 0) return false;
    else
    {
        if(DebugMessageHistoryList[0].Number <= Number && DebugMessageHistoryList[DebugMessageHistoryList.size() - 1].Number >= Number)
            return true;
        else return false;
    }
}
int tfp::DebugClass::WhatIsTheLowestDebugMessageNumber()
{
    if(DebugMessageHistoryList.size() <= 0) return -1;
    else return DebugMessageHistoryList[0].Number;
}
