/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"

tfp::Game::Game(std::string GameType)
    :GameType(GameType), PreviousCameraPosition({-215.2f, -5416.6f}), NotActiveFor(0.0f), TerrainChanged(true) /// Random camera position so its not 0,0 so terrain vertex is loaded the first time
{
    LoadingScreen.DisplayOnScreen("Initializing loading...", this);
    GameInterface.SetGameHandle(this);
    GameMouse.SetGameHandle(this);
    GameCommandBlock.SetGameHandle(this);
    GameMap.SetGameHandle(this);
    GameScreen.SetGameHandle(this);
    GameNetworkClient.SetGameHandle(this);
    GameNetworkServer.SetGameHandle(this);
    #if TEST == 1
    ControlledPlayerAnimation.SetSkinName("MageTest");
    // ControlledPlayerAnimation.SetPosition(15.0f * 200, 15.0f * 200);
    ControlledPlayer.SetDestination({0.0f, 0.0f});
    ControlledPlayer.SetPosition({0.0f, 0.0f});
    #endif // TEST

}

tfp::Game::~Game()
{
    GameMap.Unload();
}

void tfp::Game::Events()
{
    GameFunctionTimes.StartFunctionTimer("Game events");
    GameCamera.CalculateShake();
    sf::Event GameScreenEvent;
    while(GameScreen.IsEventInQueue())
    {
        GameScreenEvent = GameScreen.GetScreenEvent();
        /// Window controling
        if(GameScreenEvent.type == sf::Event::LostFocus) GameScreen.SetFocus(false);
        else if(GameScreenEvent.type == sf::Event::GainedFocus) GameScreen.SetFocus(true);
        else if(GameScreenEvent.type == sf::Event::Closed) GameScreen.Close();

        if(GameScreen.IsFocused() == false) continue;

        /// Key pressed
        if(GameScreenEvent.type == sf::Event::KeyPressed)
        {
            if(!AreaList.IsInputAreaActive() && KeyConfig.IsKeyEventEqual("ShowConsole", GameScreenEvent)) GameInterface.ShowCommandLine(!(GameInterface.IsCommandLineVisible()));

            if(KeyConfig.IsKeyEventEqual("Screenshot", GameScreenEvent))
            {
                sf::Image ScreenshotImage = GameScreen.GetRenderWindowHandle().capture();
                std::string ScreenshotFileName = "Screenshots/Screenshot_" + tfp::Date("Y_M_D__h_m_s.jpg");
                ScreenshotImage.saveToFile(ScreenshotFileName);
            }

            if(!AreaList.IsInputAreaActive() && !GameInterface.IsCommandLineActive())
            {
                if(true)
                {
                    if(KeyConfig.IsKeyEventEqual("ShowOptions", GameScreenEvent))
                    {
                        if(GameInterface.LanguageWindow.IsVisible() || GameInterface.AuthorsWindow.IsVisible() || GameInterface.ControlsWindow.IsVisible() ||
                           GameInterface.VideoOptionsWindow.IsVisible())
                        {
                            GameInterface.LanguageWindow.Show(false);
                            GameInterface.AuthorsWindow.Show(false);
                            GameInterface.ControlsWindow.Show(false);
                            GameInterface.VideoOptionsWindow.Show(false);
                        }
                        else GameInterface.OptionsWindow.Show(!GameInterface.OptionsWindow.IsVisible());

                    }
                }
                if(GetGameType() == "menu")
                {

                }
                else if(GetGameType() == "game")
                {
                    if(KeyConfig.IsKeyEventEqual("ShowInventory", GameScreenEvent)) GameInterface.InventoryWindow.Show(!GameInterface.InventoryWindow.IsVisible());
                    if(KeyConfig.IsKeyEventEqual("ShowCharacterInfo", GameScreenEvent)) GameInterface.CharacterInfoWindow.Show(!GameInterface.CharacterInfoWindow.IsVisible());
                    if(KeyConfig.IsKeyEventEqual("OpenChat", GameScreenEvent)) GameInterface.GameChat.OpenChat();
                }
                else if(GetGameType() == "mapeditor")
                {
                    if(KeyConfig.IsKeyEventEqual("ShowTerrainSelect", GameScreenEvent)) GameInterface.TerrainSelectWindow.Show(!GameInterface.TerrainSelectWindow.IsVisible());
                    if(KeyConfig.IsKeyEventEqual("UndoTerrainChanges", GameScreenEvent)) GameMap.UndoTerrainChanges();
                    if(KeyConfig.IsKeyEventEqual("RedoTerrainChanges", GameScreenEvent)) GameMap.RedoTerrainChanges();
                }
                else if(GetGameType() == "server")
                {

                }
            }

            GameInterface.SendKeyPressed(GameScreenEvent);
        }
        /// Text entered
        if(GameScreenEvent.type == sf::Event::TextEntered && GameScreenEvent.text.unicode < 128)
        {
            GameInterface.SendCommandLineInput(static_cast<char>(GameScreenEvent.text.unicode));
        }
        if(GameScreenEvent.type == sf::Event::MouseButtonPressed)
        {
            if(GameScreenEvent.mouseButton.button == sf::Mouse::Right && GameType == "game")
            {
                ControlledPlayer.SetDestination(GameMouse.GetMousePositionOnMap());
            }
        }

    }
    GameMouse.LoadData();
    while(!GameInterface.IsCommandQueueEmpty())
    {
        std::string Command = GameInterface.GetCommandToRun();
        GameCommandBlock.RunCommand(Command);
        // Debug.Command(Command);
    }
    if(GetGameType() == "mapeditor")
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) GameCamera.Move(-5000 * Clock.GetDeltaTime(), 0 * Clock.GetDeltaTime());
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) GameCamera.Move(5000 * Clock.GetDeltaTime(), 0 * Clock.GetDeltaTime());
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) GameCamera.Move(0 * Clock.GetDeltaTime(), -5000 * Clock.GetDeltaTime());
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) GameCamera.Move(0 * Clock.GetDeltaTime(), 5000 * Clock.GetDeltaTime());
        if(!GameInterface.IsCommandLineActive())
        {
            GameCamera.Move(GameMouse.GetRightMouseButtonDeltaDragScaled());
        }
        if(!GameMap.IsLoaded())
        {

        }

    }
    else if(GetGameType() == "game")
    {

    }
    GameFunctionTimes.StopFunctionTimer("Game events");
}

void tfp::Game::MoveCameraOnControledPlayer()
{
    if(GetGameType() != "game") return;
    if(!GameCamera.IsLockedOnPlayer()) return;
    GameFunctionTimes.StartFunctionTimer("Move camera on controlled player");
    sf::Vector2f SmothMoveVector;
    SmothMoveVector.x = ControlledPlayerAnimation.GetPosition().x;
    SmothMoveVector.x -= GameScreen.GetViewSize().x / 2.0f;
    SmothMoveVector.x -= GameCamera.GetPosition().x;
    // Juz jest odjeta tutaj polowa animacji
    // SmothMoveVector.x -= ControlledPlayerAnimation.GetWidth() / 2.0f;

    SmothMoveVector.y = ControlledPlayerAnimation.GetPosition().y;
    SmothMoveVector.y -= GameScreen.GetViewSize().y / 2.0f;
    SmothMoveVector.y -= GameCamera.GetPosition().y;
    GameCamera.SmoothMove(SmothMoveVector.x, SmothMoveVector.y);
    GameFunctionTimes.StopFunctionTimer("Move camera on controlled player");
}

void tfp::Game::RenderFrame()
{
    GameFunctionTimes.StartFunctionTimer("Render frame");
    if(!GameScreen.IsWindowOpen()) return;
    Events();
    /// Drawing
    if(GameScreen.IsFocused())
    {
        GameScreen.Clear();
        MoveCameraOnControledPlayer();
        DrawTerrain();
        DrawObjects();
        DrawInterface();
        NotActiveFor = 0.0f;
    }
    else /// Closing if not active for 5 seconds and is menu
    {
        NotActiveFor += Clock.GetDeltaTime();
        if(NotActiveFor > 5.0f && GetGameType() == "menu" && GameManager.GamesOpen() > 1)
        {
            GameScreen.Close();
        }
    }
    GameScreen.DisplayWindow();
    GameFunctionTimes.StopFunctionTimer("Render frame");
}

void tfp::Game::DrawInterface()
{
    if(GameInterface.DisplayInterface(GetGameType()) == false)
    {
        Debug.Error("Drawing interface on nullptr screen");
    }
}

void tfp::Game::DrawCharacters(tfp::SortedVector<tfp::Animation> &ObjectList, bool &CharactersDrawn, int Index)
{
    if(GetGameType() != "game")
    {
        CharactersDrawn = true;
        return;
    }
    /// Postac gracza
    if(ObjectList[Index].PositionZ > 3 ||
       (ObjectList[Index].PositionZ == 3 && ObjectList[Index].Position.y > ControlledPlayerAnimation.GetPosition().y) ||
       (ObjectList[Index].PositionZ == 3 && ObjectList[Index].Position.y == ControlledPlayerAnimation.GetPosition().y
        && ObjectList[Index].Position.x >= ControlledPlayerAnimation.GetPosition().x))
    {
        ControlledPlayerAnimation.DrawCharacter(this, Clock.GetDeltaTime(), ControlledPlayer.MovementSpeed, ControlledPlayer.AttackSpeed);
        CharactersDrawn = true;
    }


}

void tfp::Game::DrawCharacters()
{
    if(GetGameType() != "game") return;
    GameFunctionTimes.StartFunctionTimer("Draw characters");
    /// Postac gracza
    /* Stara funkcja */
    ControlledPlayerAnimation.SetDestinationPosition(ControlledPlayer.GetDestination());
    ControlledPlayerAnimation.SetCurrentPosition(ControlledPlayer.GetPosition());
    ControlledPlayerAnimation.DrawCharacter(this, Clock.GetDeltaTime() ,ControlledPlayer.MovementSpeed, ControlledPlayer.AttackSpeed);

    /* Nowa funkcja */
    /*ControlledPlayerAnimation.DrawCharacter(this, ControlledPlayer, Clock.GetDeltaTime());
    GameFunctionTimes.StopFunctionTimer("Draw characters");*/
}


void tfp::Game::DrawSpells()
{
    GameFunctionTimes.StartFunctionTimer("Draw spells");
    GameFunctionTimes.StopFunctionTimer("Draw spells");
}

void tfp::Game::DrawObjects()
{
    if(GetGameType() != "game" && GetGameType() != "mapeditor") return;
    GameFunctionTimes.StartFunctionTimer("Draw objects");
    tfp::SortedVector<tfp::Animation> &ObjectList = GameMap.GetObjectList();
    bool CharactersDrawn = false;
    if(GetGameType() == "mapeditor") CharactersDrawn = true;
    for(unsigned i = 0; i < ObjectList.Size(); i++)
    {
        if(!CharactersDrawn && ObjectList[i].PositionZ >= 3)
        {
            /// Renderowanie postaci
            DrawCharacters(ObjectList, CharactersDrawn, i);
        }
        GameScreen.Draw(Sprite.Create(ObjectList[i].GetTexture(Clock.GetDeltaTime()), ObjectList[i].Position.x - GameCamera.GetPosition().x, ObjectList[i].Position.y - GameCamera.GetPosition().y));
    }

    if(!CharactersDrawn)
    {
        DrawCharacters();
    }

    DrawSpells();

    if(GameMap.ObjectPreview)
    {
        tfp::Gif &GifReference = ObjectGifList.FindGifWithName(GameMap.ObjectPreviewName);
        GameScreen.Draw(Sprite.Create(GifReference.GifTexture[0], GameMap.ObjectPreviewPosition.x - GameCamera.GetPosition().x, GameMap.ObjectPreviewPosition.y - GameCamera.GetPosition().y));
    }
    GameFunctionTimes.StopFunctionTimer("Draw objects");
}

void tfp::Game::DrawTerrain()
{
    if(GetGameType() != "game" && GetGameType() != "mapeditor") return;
    GameFunctionTimes.StartFunctionTimer("Draw terrain");
    float PositionX, PositionY;

    /// Boost
    if(TerrainList.IsGraphicDriverTerrainLoadingBoostEnabled() && PreviousCameraPosition == GameCamera.GetPosition() /*&& !TerrainChanged*/)
    {
        PreviousCameraPosition = GameCamera.GetPosition();
        sf::RenderStates State;
        State.texture = &TerrainList.GetTextureBuffer();
        GameScreen.DrawVertex(&MapVertexBuffer[0], MapVertexBuffer.size(), sf::Quads, State);
        return;
    }
    TerrainChanged = false;

    if(TerrainList.IsGraphicDriverTerrainLoadingBoostEnabled())
        MapVertexBuffer.resize(0);

    for(int i = 0; i < GameMap.GetHeight(); i++)
    {
        for(int j = 0; j < GameMap.GetWidth(); j++)
        {
            PositionX = 200*j - GameCamera.GetPosition().x;
            PositionY = 200*i - GameCamera.GetPosition().y;


            if (PositionX > -200 && PositionX < GameScreen.GetViewSize().x && PositionY > -200 && PositionY < GameScreen.GetViewSize().y)
            {
                if(TerrainList.IsGraphicDriverTerrainLoadingBoostEnabled())
                {
                    MapVertexPoint.position = {PositionX, PositionY};
                    MapVertexPoint.texCoords = TerrainList.FindTerrainWithName(GameMap.GetTerrainName(i,j)).TextureBufferPosition;
                    MapVertexBuffer.push_back(MapVertexPoint);

                    MapVertexPoint.position.x += 200;
                    MapVertexPoint.texCoords.x += 200.0f;
                    MapVertexBuffer.push_back(MapVertexPoint);

                    MapVertexPoint.position.y += 200;
                    MapVertexPoint.texCoords.y += 200.0f;
                    MapVertexBuffer.push_back(MapVertexPoint);

                    MapVertexPoint.position.x -= 200;
                    MapVertexPoint.texCoords.x -= 200.0f;
                    MapVertexBuffer.push_back(MapVertexPoint);
                }
                else
                {
                    GameScreen.Draw(Sprite.Create(TerrainList.FindTerrainWithName(GameMap.GetTerrainName(i,j)).Texture, PositionX, PositionY));
                }

            }
        }
    }

    if(TerrainList.IsGraphicDriverTerrainLoadingBoostEnabled())
    {
        sf::RenderStates State;
        State.texture = &TerrainList.GetTextureBuffer();
        GameScreen.DrawVertex(&MapVertexBuffer[0], MapVertexBuffer.size(), sf::Quads, State);
        // GameScreen.Draw(Sprite.Create(TerrainList.GetTextureBuffer(), 0, 0));
    }
    GameFunctionTimes.StopFunctionTimer("Draw terrain");
}


void tfp::Game::LoopFrames()
{
    while(GameScreen.IsWindowOpen())
    {
        RenderFrame();
    }
}


void tfp::Game::SetGameType(std::string GameType_)
{
    GameType = GameType_;
}

const std::string &tfp::Game::GetGameType() const
{
    return GameType;
}
