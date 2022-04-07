/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"

tfp::Gif::Gif()
:GifName("Unknown"), Folder("Animation/"), GifPath("Graphics/Animation/Unknown.png"), Collider(true), SecondsPerFrame(1.0f), FrameWidth(200), FrameHeight(200), Frames(1)
{

}

tfp::Gif::Gif(std::string GifName_, std::string Folder_)
:GifName(GifName_), Folder(Folder_), GifPath("Graphics/Animation/Unknown.png"), Collider(true), SecondsPerFrame(1.0f), FrameWidth(200), FrameHeight(200), Frames(1)
{
    Load(GifName, Folder);
}

tfp::Gif::~Gif() {}

tfp::GifListClass::GifListClass(std::string Folder_)
:Folder(Folder_), Loaded(false) {}

tfp::GifListClass::~GifListClass()
{
    UnloadAll();
}

tfp::Animation::Animation()
:Name("Unknown"), TimeRunning(0.0f), Position({0.0f, 0.0f}), PositionZ(2), Type(tfp::Animation::ObjectAnimation) {}

tfp::Animation::Animation(tfp::Animation &Right)
:Name(Right.Name), TimeRunning(Right.TimeRunning), Position(Right.Position), Size(Right.Size), PositionZ(Right.PositionZ), Type(Right.Type){}

tfp::Animation::Animation(std::string AnimationName, AnimationType Type, float PositionX, float PositionY)
:Name(AnimationName), TimeRunning(0.0f), Position(PositionX, PositionY), PositionZ(2), Type(Type)
{
    tfp::Gif *GifHandle = nullptr;

    if(Type == tfp::Animation::ObjectAnimation) GifHandle = &ObjectGifList.FindGifWithName(Name);
    else if(Type == tfp::Animation::SpellAnimation) GifHandle = &SpellGifList.FindGifWithName(Name);
    else if(Type == tfp::Animation::CharacterAnimation) GifHandle = &CharacterGifList.FindGifWithName(Name);
    else if(Type == tfp::Animation::MobAnimation) GifHandle = &MobGifList.FindGifWithName(Name);
    else
    {
        Debug.Error("Unknown animation type");
        GifHandle = &ObjectGifList.FindGifWithName(Name);
        return;
    }

    Size = {(float) GifHandle->FrameWidth, (float) GifHandle->FrameHeight};
}

tfp::Animation::~Animation() {}

void tfp::Gif::Load(std::string GifName_, std::string Folder_)
{
    GifName = GifName_;
    Folder = Folder_;

    /// Loadin animation
    std::string AnimationFilePath = Folder + "/" + GifName + ".animation";
    std::fstream AnimationFile;
    AnimationFile.open(AnimationFilePath.c_str(), std::ios::in);
    if(AnimationFile.good())
    {
        std::string Line;
        while(!AnimationFile.eof())
        {
            std::getline(AnimationFile, Line);

            if(Line == "");
            else if(Line[0] == '#');
            else if(tfp::SplitString(Line, 0) == "GifPath")
            {
                GifPath = tfp::SplitString(Line, 1);
            }
            else if(tfp::SplitString(Line, 0) == "SecondsPerFrame")
            {
                SecondsPerFrame = tfp::StringToFloat(tfp::SplitString(Line, 1));
            }
            else if(tfp::SplitString(Line, 0) == "FrameWidth")
            {
                FrameWidth = tfp::StringToInt(tfp::SplitString(Line, 1));
            }
            else if(tfp::SplitString(Line, 0) == "FrameHeight")
            {
                FrameHeight = tfp::StringToInt(tfp::SplitString(Line, 1));
            }
            else if(tfp::SplitString(Line, 0) == "Frames")
            {
                Frames = tfp::StringToInt(tfp::SplitString(Line, 1));
            }
            else if(tfp::SplitString(Line, 0) == "Collider")
            {
                Collider = tfp::StringToBool(tfp::SplitString(Line, 1));
            }
            else
            {
                Debug.Warning("Animation unknown line: " + Line + " in " + AnimationFilePath);
            }
        }
        AnimationFile.close();
    }
    else
    {
        Debug.Warning("Can not open: " + AnimationFilePath);
    }

    /// Loading textures
    sf::Image GifImageBuffer;
    if(!GifImageBuffer.loadFromFile(GifPath))
    {
        Debug.Warning("Animation: Can not load image: " + GifPath);
    }
    if(GifImageBuffer.getSize().x <= 0 || GifImageBuffer.getSize().y <= 0)
    {
        Debug.Warning("Animation: Image size: " + tfp::IntToString(GifImageBuffer.getSize().x) + "x" + tfp::IntToString(GifImageBuffer.getSize().y));
    }

    /// Gif colider image
    for(int i = 0; i < Frames; i++)
    {
        GifImage.push_back(sf::Image());
        GifImage[GifImage.size() - 1 ].create(FrameWidth, FrameHeight, sf::Color(0, 0, 0, 0));
        GifImage[GifImage.size() - 1].copy(GifImageBuffer, 0, 0, sf::Rect<int>(i * FrameWidth, 0, FrameWidth, FrameHeight), true);

        // Debug.Warning("Animation: GifImage size: " + tfp::IntToString(GifImage[GifImage.size() - 1].getSize().x) + "x" + tfp::IntToString(GifImage[GifImage.size() - 1].getSize().y));

        GifTexture.push_back(sf::Texture());
        GifTexture[GifTexture.size() - 1].loadFromImage(GifImage[GifImage.size() - 1], sf::Rect<int>(0, 0, FrameWidth, FrameHeight));
    }
    /// Gif texture
    if(Collider)
    {
        for(int i = 0; i < Frames; i++)
        {
            GifColliderImage.push_back(sf::Image());
            GifColliderImage[GifColliderImage.size() - 1 ].create(FrameWidth, FrameHeight, sf::Color(0, 0, 0, 0));
            GifColliderImage[GifColliderImage.size() - 1].copy(GifImageBuffer, 0, 0, sf::Rect<int>(i * FrameWidth, FrameHeight, FrameWidth, FrameHeight), true);
            GifColliderTexture.push_back(sf::Texture());
            GifColliderTexture[GifColliderTexture.size() - 1].loadFromImage(GifColliderImage[GifColliderImage.size() - 1]);
        }
    }
    Debug.Info("Animation loaded: " + GifName + " (" + Folder + ")");
}

bool tfp::GifListClass::IsLoaded()
{
    return Loaded;
}

std::vector<tfp::Gif> &tfp::GifListClass::GetList()
{
    return List;
}

void tfp::GifListClass::LoadGifFiles(tfp::Game *GameHandle)
{
    std::string DisplayedLoadingText ;
    if(Folder == "ObjectAnimation") DisplayedLoadingText = "Loading object animations...";
    else if(Folder == "SpellAnimation") DisplayedLoadingText = "Loading spell animations...";
    else if(Folder == "CharacterAnimation") DisplayedLoadingText = "Loading character animations...";
    else if(Folder == "MobAnimation") DisplayedLoadingText = "Loading enemy animations...";
    else if(Folder == "SpecialObjectAnimation") DisplayedLoadingText = "Loading special object animations...";
    else
    {
        Debug.Error("AnimationList: Unknown animation type: " + Folder);
    }

    LoadingScreen.DisplayOnScreen(DisplayedLoadingText, GameHandle);

    UnloadAll();

    tfp::ListFilesInDirectory(Folder, "Cache/AnimationList.txt");


    std::string Line;
    std::queue<std::string> ToLoadList;
    std::fstream ConfigFile;
    ConfigFile.open("Cache/AnimationList.txt", std::ios::in);
    if(ConfigFile.good())
    {
        while(!ConfigFile.eof())
        {
            getline(ConfigFile,Line);
            Line = tfp::PathToFileTitle(Line);
            if(Line == "") continue;
            ToLoadList.push(Line);
        }
        ConfigFile.close();
    }
    else
    {
        Debug.Warning("Can not load Cache/AnimationList.txt");
        return;
    }

    /// Ladowanie terenu
    int ToLoadQuantity = ToLoadList.size();
    for(int i = 0; i < ToLoadQuantity; i++)
    {
        LoadingScreen.DisplayOnScreen(DisplayedLoadingText, GameHandle, std::floor(((i + 1.0f) / (float) ToLoadQuantity) * 100.0f));
        List.push_back(tfp::Gif());
        List[List.size() - 1].Load(ToLoadList.front(), Folder);
        ToLoadList.pop();
    }
    Loaded = true;
}

tfp::Gif &tfp::GifListClass::FindGifWithName(std::string Name_)
{
    for(unsigned i = 0; i < List.size(); i++)
    {
        if(List[i].GifName == Name_) return List[i];
    }
    Debug.Warning("AnimationList: Unknown animation: " + Name_);
    List.push_back(tfp::Gif());
    List[List.size() - 1].Load(Name_, Folder);
    return List[List.size() - 1];
}

void tfp::GifListClass::UnloadAll()
{
    if(List.size() <= 0) return;

    if(Folder == "ObjectAnimation") Debug.Info("AnimationList unloaded (ObjectAnimation)");
    else if(Folder == "SpellAnimation") Debug.Info("AnimationList unloaded (SpellAnimation)");
    else if(Folder == "CharacterAnimation") Debug.Info("AnimationList unloaded (CharacterAnimation)");
    else if(Folder == "MobAnimation") Debug.Info("AnimationList unloaded (MobAnimation)");
    else if(Folder == "SpecialObjectAnimation") Debug.Info("AnimationList unloaded (SpecialObjectAnimation)");
    else
    {
        Debug.Error("AnimationList: Unknown animation type: " + Folder);
    }

    List.clear();
    Loaded = false;
}

void tfp::Animation::LoadAnimation(std::string AnimationName_, AnimationType Type_)
{
    Name = AnimationName_;
    Type = Type_;
    TimeRunning = 0.0f;
    Position = {0.0f, 0.0f};

    tfp::Gif *GifHandle = nullptr;

    if(Type == tfp::Animation::ObjectAnimation) GifHandle = &ObjectGifList.FindGifWithName(Name);
    else if(Type == tfp::Animation::SpellAnimation) GifHandle = &SpellGifList.FindGifWithName(Name);
    else if(Type == tfp::Animation::CharacterAnimation) GifHandle = &CharacterGifList.FindGifWithName(Name);
    else if(Type == tfp::Animation::MobAnimation) GifHandle = &MobGifList.FindGifWithName(Name);
    else
    {
        Debug.Error("Unknown animation type");
        GifHandle = &ObjectGifList.FindGifWithName(Name);
        return;
    }

    Size = {(float) GifHandle->FrameWidth, (float) GifHandle->FrameHeight};
}

sf::Texture &tfp::Animation::GetTexture(float DeltaTime_, float AnimationSpeed_, int Frame_)
{
    tfp::Gif *GifHandle;
    if(Type == tfp::Animation::ObjectAnimation) GifHandle = &ObjectGifList.FindGifWithName(Name);
    else if(Type == tfp::Animation::SpellAnimation) GifHandle = &SpellGifList.FindGifWithName(Name);
    else if(Type == tfp::Animation::CharacterAnimation) GifHandle = &CharacterGifList.FindGifWithName(Name);
    else if(Type == tfp::Animation::MobAnimation) GifHandle = &MobGifList.FindGifWithName(Name);
    else if(Type == tfp::Animation::SpecialObjectAnimation) GifHandle = &SpecialObjectGifList.FindGifWithName(Name);

    TimeRunning += DeltaTime_ * AnimationSpeed_;

    if(TimeRunning > GifHandle->SecondsPerFrame * GifHandle->Frames)
    {
        TimeRunning -= GifHandle->SecondsPerFrame * GifHandle->Frames;
    }

    int FrameIndex = (int) (TimeRunning / GifHandle->SecondsPerFrame) % GifHandle->Frames;
    if(Frame_ >= 0)
    {
        FrameIndex = Frame_;
    }

    return GifHandle->GifTexture[FrameIndex];
}

void tfp::Animation::Restart()
{
    TimeRunning = 0.0f;
}

sf::Image &tfp::Animation::GetColiderImage(float DeltaTime_, float AnimationSpeed_, int Frame_)
{
    tfp::Gif *GifHandle = nullptr;

    if(Type == tfp::Animation::ObjectAnimation) GifHandle = &ObjectGifList.FindGifWithName(Name);
    else if(Type == tfp::Animation::SpellAnimation) GifHandle = &SpellGifList.FindGifWithName(Name);
    else if(Type == tfp::Animation::CharacterAnimation) GifHandle = &CharacterGifList.FindGifWithName(Name);
    else if(Type == tfp::Animation::MobAnimation) GifHandle = &MobGifList.FindGifWithName(Name);
    else
    {
        Debug.Error("Unknown animation type");
        GifHandle = &ObjectGifList.FindGifWithName(Name);
    }

    TimeRunning += DeltaTime_ * AnimationSpeed_;

    while(TimeRunning > GifHandle->SecondsPerFrame * GifHandle->Frames)
    {
        TimeRunning -= GifHandle->SecondsPerFrame * GifHandle->Frames;
    }

    int FrameIndex = (int) (TimeRunning / GifHandle->SecondsPerFrame) % GifHandle->Frames;
    if(Frame_ >= 0)
    {
        FrameIndex = Frame_;
    }

    return GifHandle->GifColliderImage[FrameIndex];
}

bool tfp::Animation::operator<(tfp::Animation &Right)
{
    if(PositionZ < Right.PositionZ)
    {
        return true;
    }
    else if(PositionZ > Right.PositionZ)
    {
        return false;
    }
    else
    {
        if(Position.y < Right.Position.y)
        {
            return true;
        }
        else if(Position.y > Right.Position.y)
        {
            return false;
        }
        else
        {
            if(Position.x < Right.Position.x)
            {
                return true;
            }
            else if(Position.x > Right.Position.x)
            {
                return false;
            }
            else return false;
        }
    }
}

bool tfp::Animation::operator<=(tfp::Animation &Right)
{
    if(PositionZ < Right.PositionZ)
    {
        return true;
    }
    else if(PositionZ > Right.PositionZ)
    {
        return false;
    }
    else
    {
        if(Position.y < Right.Position.y)
        {
            return true;
        }
        else if(Position.y > Right.Position.y)
        {
            return false;
        }
        else
        {
            if(Position.x < Right.Position.x)
            {
                return true;
            }
            else if(Position.x > Right.Position.x)
            {
                return false;
            }
            else return true;
        }
    }
}

bool tfp::Animation::operator>(tfp::Animation &Right)
{
    if(PositionZ > Right.PositionZ)
    {
        return true;
    }
    else if(PositionZ < Right.PositionZ)
    {
        return false;
    }
    else
    {
        if(Position.y > Right.Position.y)
        {
            return true;
        }
        else if(Position.y < Right.Position.y)
        {
            return false;
        }
        else
        {
            if(Position.x > Right.Position.x)
            {
                return true;
            }
            else if(Position.x < Right.Position.x)
            {
                return false;
            }
            else return false;
        }
    }
}

bool tfp::Animation::operator>=(tfp::Animation &Right)
{
    if(PositionZ > Right.PositionZ)
    {
        return true;
    }
    else if(PositionZ < Right.PositionZ)
    {
        return false;
    }
    else
    {
        if(Position.y > Right.Position.y)
        {
            return true;
        }
        else if(Position.y < Right.Position.y)
        {
            return false;
        }
        else
        {
            if(Position.x > Right.Position.x)
            {
                return true;
            }
            else if(Position.x < Right.Position.x)
            {
                return false;
            }
            else return true;
        }
    }
}

bool tfp::Animation::operator==(tfp::Animation &Right)
{
    if(PositionZ == Right.PositionZ && Position == Right.Position) return true;
    else return false;
}

bool tfp::Animation::operator!=(tfp::Animation &Right)
{
    if(PositionZ == Right.PositionZ && Position == Right.Position) return false;
    else return true;
}






