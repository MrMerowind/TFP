/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"

#if SYSTEM_WINDOWS == 1
std::string tfp::OpenFileName(tfp::Game *GameHandle, std::string Filter, std::string Directory)
{
    OPENFILENAME ofn = { sizeof(OPENFILENAME) };
    const char filter[] = "Map files\0*.MAP\0";
    char file[4096] = "";

    ofn.hwndOwner = GameHandle->GameScreen.GetRenderWindowHandle().getSystemHandle();
    ofn.lpstrFilter = filter;
    ofn.nFilterIndex = 1;
    ofn.lpstrFile = file;
    ofn.nMaxFile = sizeof file;
    ofn.lpstrInitialDir = "Maps\\";
    ofn.Flags = OFN_NOCHANGEDIR | OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NONETWORKBUTTON;

    GetOpenFileName(&ofn);
    std::string Return = ofn.lpstrFile;
    Return = tfp::PathToFileTitle(Return);
    if(Return != "")
        Debug.Info("Opening file: " + Return);
    return Return;
}

std::string tfp::SaveFileName(tfp::Game *GameHandle, std::string Filter, std::string Directory)
{
    OPENFILENAME ofn = { sizeof(OPENFILENAME) };
    const char filter[] = "Map files\0*.MAP\0";
    char file[4096] = "";

    ofn.hwndOwner = GameHandle->GameScreen.GetRenderWindowHandle().getSystemHandle();
    ofn.lpstrFilter = filter;
    ofn.nFilterIndex = 1;
    ofn.lpstrFile = file;
    ofn.nMaxFile = sizeof file;
    ofn.lpstrInitialDir = "Maps\\";
    ofn.Flags = OFN_NOCHANGEDIR | OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NONETWORKBUTTON;

    GetSaveFileName(&ofn);
    std::string Return = ofn.lpstrFile;
    Return = tfp::PathToFileTitle(Return);
    if(Return != "")
        Debug.Info("Saving to file: " + Return);
    return Return;
}
#endif // SYSTEM_WINDOWS

#if SYSTEM_LINUX == 1

std::string tfp::OpenFileName(std::string Filter, std::string Directory)
{
    // Debug.Info("Opening file: " + "");
    Debug.Warning("Opening file is not supported in Linux");
    return "";
}

std::string tfp::SaveFileName(std::string Filter, std::string Directory)
{
    // Debug.Info("Saving to file: " + "");
    Debug.Warning("Saving file is not supported in Linux");
    return "";
}

#endif // SYSTEM_LINUX

#if SYSTEM_IOS == 1

std::string tfp::OpenFileName(std::string Filter = "All files\0*.*\0", std::string Directory = ".\\")
{
    // Debug.Info("Opening file: " + "");
    Debug.Warning("Opening file is not supported in MacOS");
    return "";
}

std::string tfp::SaveFileName(std::string Filter = "All files\0*.*\0", std::string Directory = ".\\")
{
    // Debug.Info("Saving to file: " + "");
    Debug.Warning("Saving file is not supported in MacOS");
    return "";
}

#endif // SYSTEM_MAC_OS
