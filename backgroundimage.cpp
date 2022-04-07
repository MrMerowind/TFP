#include "includes.hpp"
#include "globalobjects.hpp"

tfp::BackgroundImageClass::BackgroundImageClass()
    :Loaded(false) {}

tfp::BackgroundImageClass::~BackgroundImageClass() {}


void tfp::BackgroundImageClass::LoadAll(tfp::Game *GameHandle)
{
    /// Listowanie plikow
    tfp::ListFilesInDirectory("BackgroundImage", "Cache/BackgroundImage.txt");

    /// Wczytywanie listy plikow
    std::queue<std::string> ToLoadList;

    std::fstream CacheFile;
    CacheFile.open("Cache/BackgroundImage.txt", std::ios::in);
    if(!CacheFile.good())
    {
        Debug.Error("Can not open Cache/BackgroundImage.txt");
    }

    std::string Line;
    while(!CacheFile.eof())
    {
        getline(CacheFile,Line);
        Line = tfp::PathToFileTitleWithExtension(Line);
        if(Line == "") continue;
        ToLoadList.push(Line);
    }

    CacheFile.close();

    if(ToLoadList.size() <= 0)
    {
        Debug.Error("BackgroundImage: Nothing to load");
        Loaded = false;
        return;
    }

    /// Wczytywanie tekstur

    int ToLoadQuantity = ToLoadList.size();
    for(int i = 0; i < ToLoadQuantity; i++)
    {
        LoadingScreen.DisplayOnScreen("Loading backgrounds...", GameHandle, std::floor(((i + 1.0f) / (float) ToLoadQuantity) * 100.0f));

        List.push_back(tfp::BackgroundImageClass::Background());
        List[i].Name = tfp::PathToFileTitle(ToLoadList.front());
        List[i].Texture.loadFromFile("BackgroundImage/" + ToLoadList.front());
        List[i].Width = List[i].Texture.getSize().x;
        List[i].Height = List[i].Texture.getSize().y;
        List[i].Loaded = true;
        Debug.Info("BackgroundImage loaded: " + List[i].Name);
        ToLoadList.pop();
    }

    Loaded = true;
}

void tfp::BackgroundImageClass::UnloadAll()
{
    if(Loaded)
    {
        Loaded = false;
        List.clear();
        Debug.Info("BackgroundImage cleared");
    }
}

std::vector<tfp::BackgroundImageClass::Background> &tfp::BackgroundImageClass::GetBackgroundList()
{
    return List;
}

/*
tfp::BackgroundImageClass::Background &tfp::BackgroundImageClass::FindBackgroundWithName(std::string BackgroundName)
{
    for(int i = 0; i < List.size(); i++)
    {
        if(List[i].Name == BackgroundName) return List[i];
    }

    Debug.Warning("BackgroundImage: Can not find " + BackgroundName);

    if(List.size() < 1)
    {
        Debug.Error("BackgroundImage: All backgrounds missing");
        /// Co tu sie ma dziac ????????????????????????
        throw std::logic_error("BackgroundImage: All backgrounds missing");
    }
    else
    {
        return List[0];
    }
}*/

void tfp::BackgroundImageClass::Draw(std::string BackgroundName, tfp::Game *GameHandle)
{
    for(unsigned i = 0; i < List.size(); i++)
    {
        if(List[i].Name == BackgroundName)
        {
            if(List[i].Loaded)
            {
                float Scale = (float) GameHandle->GameScreen.GetViewSize().x / (float) List[i].Width;
                GameHandle->GameScreen.Draw(Sprite.Create(List[i].Texture, 0, 0, Scale, Scale));
                return;
            }
            else
            {
                return;
            }
        }
    }

    Debug.Warning("BackgroundImage: Can not find " + BackgroundName);
    List.push_back(tfp::BackgroundImageClass::Background());
    List[List.size() - 1].Loaded = false;
    List[List.size() - 1].Name = BackgroundName;
    return;

}

bool tfp::BackgroundImageClass::IsLoaded()
{
    return Loaded;
}

