/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"


#if SYSTEM_WINDOWS == 1

void tfp::ListFilesInDirectory(std::string Directory, std::string ToFilePath)
{
    std::string TmpStr;
    std::fstream SaveFile;
    SaveFile.open(ToFilePath.c_str(), std::ios::out);
    if(!SaveFile.good())
    {

        Debug.Warning("Can not open " + ToFilePath);
        return;
    }
    DIR* DirectoryPointer = opendir(Directory.c_str());
    struct dirent* Position = 0;
    while(true)
    {
        Position = readdir(DirectoryPointer);
        if(!Position) break;
        TmpStr = Position->d_name;
        if(TmpStr == "") continue;
        else if(TmpStr == ".") continue;
        else if(TmpStr == "..") continue;
        SaveFile << TmpStr << std::endl;
    }
    closedir(DirectoryPointer);
    SaveFile.close();
}


#endif // SYSTEM_WINDOWS


#if SYSTEM_LINUX == 1

Problem?

#endif // SYSTEM_LINUX
