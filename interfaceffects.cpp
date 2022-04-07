/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"

tfp::specialeffects::Rain::Rain()
:GameHandle(nullptr), Density(0), TimeBuffer(0.0f), CreationSpeed(0.1f), FallSpeed(5.0f)
{
    RainDropVertexUp.color = sf::Color(255, 255, 255, 0);
    RainDropVertexDown.color = sf::Color(255, 255, 255, 255);
}

tfp::specialeffects::Rain::~Rain()
{
    DropList.clear();
    GameHandle = nullptr;
}

tfp::specialeffects::Snow::Snow()
:GameHandle(nullptr), Density(0), TimeBuffer(0.0f), CreationSpeed(0.1f), FallSpeed(5.0f)
{
    SnowDropVertex.color = sf::Color::White;
}

tfp::specialeffects::Snow::~Snow()
{
    DropList.clear();
    GameHandle = nullptr;
}

tfp::specialeffects::Night::Night()
:GameHandle(nullptr), Darkness(0), DarknessOpacity(100), Lighter(false) {}

tfp::specialeffects::Night::~Night()
{
    GameHandle = nullptr;
}

tfp::specialeffects::Storm::Storm()
    :GameHandle(nullptr), LightningTimeSpan({0, 0}), TimeBuffer(0.0f), LightningTime(0.0f), LightningDuration(0.75f), NextLightning(0.0f) {}

tfp::specialeffects::Storm::~Storm()
{
    GameHandle = nullptr;
}

void tfp::specialeffects::Rain::SetGameHandle(tfp::Game *Handle)
{
    GameHandle = Handle;
}

void tfp::specialeffects::Rain::Display()
{
    if(GameHandle == nullptr) return;

    /// Tworzenie
    TimeBuffer += Clock.GetDeltaTime();
    if(TimeBuffer >= CreationSpeed)
    {
        while(TimeBuffer >= CreationSpeed)
            TimeBuffer -= CreationSpeed;
        Create();
    }

    /// Przesuwanie i zabijanie
    for(unsigned i = 0; i < DropList.size(); i++)
    {
        DropList[i].Position.x += Clock.GetDeltaTime() * (float) (DropList[i].RandomTilt) * 10.0f;
        DropList[i].Position.y += Clock.GetDeltaTime() * FallSpeed /** DropList[i].LifeSpan * 0.002f */ * 3.0f * DropList[i].Length;
        DropList[i].AliveFor += Clock.GetDeltaTime();
        if(DropList[i].Position.y > DropList[i].LifeSpan || DropList[i].Length < 2.0f || DropList[i].AliveFor > 5.0f)
        {
            DropList.erase(DropList.begin() + i);
            VertexList.erase(VertexList.begin() + i * 2, VertexList.begin() + i * 2 + 2);
            i--;
        }
        else if(DropList[i].Position.y + DropList[i].Length > DropList[i].LifeSpan)
        {
            DropList[i].Length = DropList[i].LifeSpan - DropList[i].Position.y;
        }

    }

    /// Renderowanie
    if(DropList.size() > 0)
    {
        for(unsigned i = 0, j = 0; i < DropList.size(); i++, j+=2)
        {

            VertexList[j].position = sf::Vector2f(DropList[i].Position.x - GameHandle->GameCamera.GetPosition().x, DropList[i].Position.y - GameHandle->GameCamera.GetPosition().y);
            VertexList[j+1].position = sf::Vector2f(DropList[i].Position.x + (float) DropList[i].RandomTilt - GameHandle->GameCamera.GetPosition().x, DropList[i].Position.y + DropList[i].Length - GameHandle->GameCamera.GetPosition().y);
        }
        GameHandle->GameScreen.DrawVertex(&VertexList[0], VertexList.size(), sf::Lines);
    }

}

void tfp::specialeffects::Rain::Create()
{
    tfp::specialeffects::Rain::Drop DropTmp;
    for(int i = 0; i < Density; i++)
    {
        DropTmp.Position = sf::Vector2f((float) Generator.RandomInt(0, (int) GameHandle->GameScreen.GetViewSize().x + 10000) - 5000.0f, -5000.0f + Generator.RandomInt(0, 4000));
        DropTmp.Length = (float) Generator.RandomInt(80, 450);
        DropTmp.LifeSpan = (float) Generator.RandomInt(1000, (int) GameHandle->GameScreen.GetViewSize().y + 10000) - 5000;

        DropTmp.Position.x += GameHandle->GameCamera.GetPosition().x;
        DropTmp.Position.y += GameHandle->GameCamera.GetPosition().y;
        DropTmp.LifeSpan += GameHandle->GameCamera.GetPosition().y;

        DropTmp.RandomTilt = Generator.RandomInt(0, 10) - 5;
        DropTmp.AliveFor = 0.0f;
        DropList.push_back(DropTmp);
        VertexList.push_back(RainDropVertexUp);
        VertexList.push_back(RainDropVertexDown);
    }
}


void tfp::specialeffects::Rain::SetDensity(int Value)
{
    if(Value < 0)
    {
        Density = 0;
        Debug.Command("Rain is disabled on 0 density. Density can not be lower than 0");
    }
    else if(Value > 200)
    {
        Density = 200;
        Debug.Command("Maximum rain density can not be higher than 200. Setting to 200 density");
    }
    else
    {
        Density = Value;
    }
}

void tfp::specialeffects::Rain::SetCreationSpeed(float TimeBetweenCreation)
{
    CreationSpeed = TimeBetweenCreation;
}

void tfp::specialeffects::Rain::SetFallSpeed(float Speed)
{
    FallSpeed = Speed;
}

/// Snow


void tfp::specialeffects::Snow::SetGameHandle(tfp::Game *Handle)
{
    GameHandle = Handle;
}

void tfp::specialeffects::Snow::Display()
{
    if(GameHandle == nullptr) return;

    /// Tworzenie
    TimeBuffer += Clock.GetDeltaTime();
    if(TimeBuffer >= CreationSpeed)
    {
        while(TimeBuffer >= CreationSpeed)
            TimeBuffer -= CreationSpeed;
        Create();
    }

    /// Przesuwanie i zabijanie
    for(unsigned i = 0; i < DropList.size(); i++)
    {
        DropList[i].Position.x += Clock.GetDeltaTime() * (float) (DropList[i].RandomTilt) * 6.0f;
        DropList[i].Position.y += Clock.GetDeltaTime() * FallSpeed /** DropList[i].LifeSpan * 0.002f */ * 9.0f * DropList[i].Length;
        DropList[i].AliveFor += Clock.GetDeltaTime();
        if(DropList[i].Position.y > DropList[i].LifeSpan /*|| DropList[i].Length < 1.0f || DropList[i].AliveFor > 5.0f*/)
        {
            DropList.erase(DropList.begin() + i);
            VertexList.erase(VertexList.begin() + i * 4, VertexList.begin() + i * 4 + /*7*/4);
            i--;
        }

    }

    /// Renderowanie

    if(DropList.size() > 0)
    {
        for(unsigned i = 0; i < DropList.size(); i++)
        {
            VertexList[i * /*8*/4 + 0].position = sf::Vector2f(DropList[i].Position.x - GameHandle->GameCamera.GetPosition().x, DropList[i].Position.y - GameHandle->GameCamera.GetPosition().y);
            VertexList[i * /*8*/4 + 1].position = sf::Vector2f(DropList[i].Position.x - GameHandle->GameCamera.GetPosition().x + DropList[i].Length, DropList[i].Position.y - GameHandle->GameCamera.GetPosition().y);
            VertexList[i * /*8*/4 + 2].position = sf::Vector2f(DropList[i].Position.x - GameHandle->GameCamera.GetPosition().x + DropList[i].Length, DropList[i].Position.y - GameHandle->GameCamera.GetPosition().y + DropList[i].Length);
            VertexList[i * /*8*/4 + 3].position = sf::Vector2f(DropList[i].Position.x - GameHandle->GameCamera.GetPosition().x, DropList[i].Position.y - GameHandle->GameCamera.GetPosition().y + DropList[i].Length);
        }
        GameHandle->GameScreen.DrawVertex(&VertexList[0], VertexList.size(), sf::Quads);
    }

}

void tfp::specialeffects::Snow::Create()
{
    tfp::specialeffects::Snow::Drop DropTmp;
    for(int i = 0; i < Density; i++)
    {
        DropTmp.Position = sf::Vector2f((float) Generator.RandomInt(0, (int) GameHandle->GameScreen.GetViewSize().x + 10000) - 5000.0f, -5000.0f + Generator.RandomInt(0, 4000));
        DropTmp.Length = (float) Generator.RandomInt(15, 30);
        DropTmp.LifeSpan = (float) Generator.RandomInt(1000, (int) GameHandle->GameScreen.GetViewSize().y + 10000) - 5000;

        DropTmp.Position.x += GameHandle->GameCamera.GetPosition().x;
        DropTmp.Position.y += GameHandle->GameCamera.GetPosition().y;
        DropTmp.LifeSpan += GameHandle->GameCamera.GetPosition().y;


        DropTmp.RandomTilt = Generator.RandomInt(0, 100) - 50;
        DropTmp.AliveFor = 0.0f;
        DropList.push_back(DropTmp);
        VertexList.push_back(SnowDropVertex);
        VertexList.push_back(SnowDropVertex);
        VertexList.push_back(SnowDropVertex);
        VertexList.push_back(SnowDropVertex);
    }
}


void tfp::specialeffects::Snow::SetDensity(int Value)
{
    if(Value < 0)
    {
        Density = 0;
        Debug.Command("Snow is disabled on 0 density. Density can not be lower than 0");
    }
    else if(Value > 200)
    {
        Density = 200;
        Debug.Command("Maximum rain density can not be higher than 200. Setting to 200 density");
    }
    else
    {
        Density = Value;
    }
}

void tfp::specialeffects::Snow::SetCreationSpeed(float TimeBetweenCreation)
{
    CreationSpeed = TimeBetweenCreation;
}

void tfp::specialeffects::Snow::SetFallSpeed(float Speed)
{
    FallSpeed = Speed;
}


/// Night

void tfp::specialeffects::Night::SetGameHandle(tfp::Game *Handle)
{
    GameHandle = Handle;
}

void tfp::specialeffects::Night::SetLighter(bool State)
{
    Lighter = State;
}

void tfp::specialeffects::Night::Display()
{
    if(GameHandle == nullptr) return;


    if(Lighter)
    {
        sf::VertexArray Line(sf::Quads, 20);

        float TemporaryDarkness = Darkness * (DarknessOpacity / 100.0f);

        sf::Color TmpColor = sf::Color(127 - (int) (127.0f * (TemporaryDarkness / 255.0f)),
                                       63 - (int) (63.0f * (TemporaryDarkness / 255.0f)),
                                       (int) (30.0f * (TemporaryDarkness / 255.0f)),
                                       (int) (200.0f * (TemporaryDarkness / 255.0f)));

        for(int i = 0; i < 20; i++)
            Line[i].color = TmpColor;

        Line[0].position = sf::Vector2f(0.0f, 0.0f);
        Line[1].position = sf::Vector2f((GameHandle->GameScreen.GetViewSize().x - GameHandle->GameScreen.GetViewSize().y) / 2.0f, 0.0f);
        Line[2].position = sf::Vector2f((GameHandle->GameScreen.GetViewSize().x - GameHandle->GameScreen.GetViewSize().y) / 2.0f, GameHandle->GameScreen.GetViewSize().y);
        Line[3].position = sf::Vector2f(0.0f, GameHandle->GameScreen.GetViewSize().y);

        Line[4].position = sf::Vector2f((GameHandle->GameScreen.GetViewSize().x - GameHandle->GameScreen.GetViewSize().y) / 2.0f + GameHandle->GameScreen.GetViewSize().y, 0.0f);
        Line[5].position = sf::Vector2f(GameHandle->GameScreen.GetViewSize().x, 0.0f);
        Line[6].position = sf::Vector2f(GameHandle->GameScreen.GetViewSize().x, GameHandle->GameScreen.GetViewSize().y);
        Line[7].position = sf::Vector2f((GameHandle->GameScreen.GetViewSize().x - GameHandle->GameScreen.GetViewSize().y) / 2.0f + GameHandle->GameScreen.GetViewSize().y, GameHandle->GameScreen.GetViewSize().y);


        Line[8].position = sf::Vector2f(GameHandle->GameScreen.GetViewSize().x / 2.0f, GameHandle->GameScreen.GetViewSize().y / 2.0f);
        Line[9].position = Line[1].position;
        Line[10].position = Line[4].position;

        Line[11].position = sf::Vector2f(GameHandle->GameScreen.GetViewSize().x / 2.0f, GameHandle->GameScreen.GetViewSize().y / 2.0f);
        Line[12].position = Line[1].position;
        Line[13].position = Line[2].position;

        Line[14].position = sf::Vector2f(GameHandle->GameScreen.GetViewSize().x / 2.0f, GameHandle->GameScreen.GetViewSize().y / 2.0f);
        Line[15].position = Line[7].position;
        Line[16].position = Line[4].position;

        Line[17].position = sf::Vector2f(GameHandle->GameScreen.GetViewSize().x / 2.0f, GameHandle->GameScreen.GetViewSize().y / 2.0f);
        Line[18].position = Line[7].position;
        Line[19].position = Line[2].position;/*

        Line[8].position = Line[2].position;
        Line[9].position = Line[1].position;
        Line[10].position = Line[4].position;

        Line[11].position = Line[7].position;
        Line[12].position = Line[1].position;
        Line[13].position = Line[2].position;

        Line[14].position = Line[1].position;
        Line[15].position = Line[7].position;
        Line[16].position = Line[4].position;

        Line[17].position = Line[4].position;
        Line[18].position = Line[7].position;
        Line[19].position = Line[2].position;*/

        Line[8].color = sf::Color(0, 0, 0, 0);
        Line[11].color = sf::Color(0, 0, 0, 0);
        Line[14].color = sf::Color(0, 0, 0, 0);
        Line[17].color = sf::Color(0, 0, 0, 0);

        GameHandle->GameScreen.DrawVertex(&Line[0], 8, sf::Quads);
        GameHandle->GameScreen.DrawVertex(&Line[8], 12, sf::Triangles);

    }
    else
    {
        sf::VertexArray Line(sf::Quads, 4);

        float TemporaryDarkness = Darkness * (DarknessOpacity / 100.0f);

        sf::Color TmpColor = sf::Color(127 - (int) (127.0f * (TemporaryDarkness / 255.0f)),
                                       63 - (int) (63.0f * (TemporaryDarkness / 255.0f)),
                                       (int) (30.0f * (TemporaryDarkness / 255.0f)),
                                       (int) (200.0f * (TemporaryDarkness / 255.0f)));

        for(int i = 0; i < 4; i++)
            Line[i].color = TmpColor;
        Line[0].position = sf::Vector2f(0.0f, 0.0f);
        Line[1].position = sf::Vector2f(GameHandle->GameScreen.GetViewSize().x, 0.0f);
        Line[2].position = sf::Vector2f(GameHandle->GameScreen.GetViewSize().x, GameHandle->GameScreen.GetViewSize().y);
        Line[3].position = sf::Vector2f(0.0f, GameHandle->GameScreen.GetViewSize().y);

        GameHandle->GameScreen.DrawVertex(&Line[0], 4, sf::Quads);
    }


}

bool tfp::specialeffects::Night::IsLighterOn()
{
    return Lighter;
}

void tfp::specialeffects::Night::SetDarkness(int Value)
{
    if(Value < 0)
    {
        Darkness = 0;
        Debug.Command("Darkness is disabled on 0 density. Darkness can not be lower than 0");
    }
    else if(Value > 255)
    {
        Darkness = 255;
        Debug.Command("Darkness can not be higher than 255. Setting to 255");
    }
    else
    {
        Darkness = Value;
    }
}

void tfp::specialeffects::Night::SetDarknessOpacity(int Value)
{
    if(Value < 0)
    {
        DarknessOpacity = 0;
        Debug.Command("Darkness opacity can not be lower than 0");
    }
    else if(Value > 100)
    {
        DarknessOpacity = 100;
        Debug.Command("Darkness opacity can not be higher than 100. Setting to 100");
    }
    else
    {
        DarknessOpacity = Value;
    }
}

void tfp::specialeffects::Storm::SetGameHandle(tfp::Game *Handle)
{
    GameHandle = Handle;
}

void tfp::specialeffects::Storm::Display()
{
    if(GameHandle == nullptr) return;

    if(LightningTimeSpan.y <= 0)
    {
        GameHandle->GameInterface.NightEffect.SetDarknessOpacity(100);
        return;
    }

    /// Przed blyskiem
    TimeBuffer += Clock.GetDeltaTime();

    /// Losowanie nowego blysku
    if(NextLightning <= 0.0f)
    {
        GameHandle->GameInterface.NightEffect.SetDarknessOpacity(100);
        NextLightning = (float) Generator.RandomInt(LightningTimeSpan.x, LightningTimeSpan.y);
        TimeBuffer = 0.0f;
        LightningTime = 0.0f;
    }
    else if(TimeBuffer > LightningDuration + NextLightning)
    {
        GameHandle->GameInterface.NightEffect.SetDarknessOpacity(100);
        NextLightning = (float) Generator.RandomInt(LightningTimeSpan.x, LightningTimeSpan.y);
        TimeBuffer = 0.0f;
        LightningTime = 0.0f;
    }

    /// W czasie blysku
    if(TimeBuffer >= NextLightning)
    {
        LightningTime = TimeBuffer - NextLightning;
        if(LightningTime < LightningDuration)
        {
            if(LightningTime > LightningDuration / 2)
            {
                LightningTime = (LightningDuration - LightningTime);
            }
            int TmpOpacity = 100 - (int) (100.0f * (LightningTime / (LightningDuration / 2.0f)));
            GameHandle->GameInterface.NightEffect.SetDarknessOpacity(TmpOpacity);

            /// Rozblysk
            sf::VertexArray Line(sf::Quads, 4);

            int TemporaryLightness = 80 -  (int) (80.0f * (TmpOpacity / 100.0f));

            for(int i = 0; i < 4; i++)
                Line[i].color = sf::Color(255, 255, 255, TemporaryLightness);

            Line[0].position = sf::Vector2f(0.0f, 0.0f);
            Line[1].position = sf::Vector2f(GameHandle->GameScreen.GetViewSize().x, 0.0f);
            Line[2].position = sf::Vector2f(GameHandle->GameScreen.GetViewSize().x, GameHandle->GameScreen.GetViewSize().y);
            Line[3].position = sf::Vector2f(0.0f, GameHandle->GameScreen.GetViewSize().y);

            GameHandle->GameScreen.Draw(Line);
        }
        else
        {
            GameHandle->GameInterface.NightEffect.SetDarknessOpacity(100);
        }

    }

}

void tfp::specialeffects::Storm::SetLightningTimeSpan(int Min, int Max)
{
    LightningTimeSpan = {Min, Max};
}

