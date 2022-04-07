/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef INTERFACE_HPP_INCLUDED
#define INTERFACE_HPP_INCLUDED

namespace tfp
{
    class Interface
    {
    private:
        sf::Texture InterfaceCommandLineTexture;
        sf::Texture InventoryGridTexture;
        bool CommandLineVisible;
        std::string CommandLineInput;
        int LastDebugMessage;
        std::string FpsCounter;
        bool Fps;
        time_t LastTimeFpsCount;
        #define CommandLineOutputLines 11
        std::string CommandLineOutput[CommandLineOutputLines];
        std::queue<std::string> CommandsToRun;
        std::string LastCommand;
        tfp::Game *GameHandle;
        tfp::FocusArea CommandLineFocusArea;
        /// Stawianie terenu
        sf::Vector2i PlaceTerrainStart;
        sf::Vector2i PlaceTerrainEnd;
        unsigned PlaceTerrainTerrainID;
        bool PlaceTerrainLeftButtonDown;
        sf::Vector2f GridSize;
        sf::Vector2f GridShift;
        bool GridEnabled;
        bool ShowGridEnabled;
        std::vector<sf::Vertex> TerrainWindowVertexBoostList;
        sf::Vertex TerrainWindowVertexPoint;
        unsigned TerrainNamesIndexPrevious;
        std::string SetTile;
        int DraggedItemId;
        bool IndexZHelpVisible;
    private:
        inline void LoadAssetsIfNotLoaded();
        inline void DrawGrid();
        inline void DrawSpecialEffects();
        inline void CloseNotSuitableWindows(std::string &GameType);
        inline void DrawUserInterface();
        inline void DrawWindows();
        inline void DrawForms(std::string &GameType);
        inline void DrawTerrainWindowContent();
        inline void DrawCommandLine();
        inline void DrawConnectedUserList();
        inline void TerrainWindowOperations();
        inline void DrawZIndexHelp();
        inline void DrawBackground(std::string &GameType);
    public:
        tfp::Chat GameChat;

        tfp::specialeffects::Rain RainEffect;
        tfp::specialeffects::Snow SnowEffect;
        tfp::specialeffects::Storm StormEffect;
        tfp::specialeffects::Night NightEffect;

        unsigned TerrainWindowTileSetIndex;
        unsigned TerrainWindowTileIndex;
        unsigned TerrainWindowTileZIndex;

        unsigned LanguageNamesIndex;
        /// Okna (W kolejnosci od renderowanego na gorze do renderowanego na dole

        tfp::Button AuthorsButtonClose;
        tfp::Window AuthorsWindow;


        tfp::Button VideoOptionsResetButton;
        tfp::Button VideoOptionsCloseButton;
        tfp::Button VerticalSyncButton;
        tfp::Button SetFrameLimitButton;
        tfp::InputBar FrameLimitInputBar;
        tfp::Button ServerWindowSizeButton[13];
        tfp::Button MapEditorWindowSizeButton[13];
        tfp::Button GameWindowSizeButton[13];
        tfp::Button MenuWindowSizeButton[13];
        tfp::Window VideoOptionsWindow;

        tfp::Button ResetControlsButton;
        tfp::Button CloseControlsButton;
        tfp::InputBar ScreenshotInputBar;
        tfp::InputBar ShowCharacterInfoInputBar;
        tfp::InputBar ShowInventoryInputBar;
        tfp::InputBar RedoTerrainChangesInputBar;
        tfp::InputBar UndoTerrainChangesInputBar;
        tfp::InputBar ShowTerrainSelectInputBar;
        tfp::InputBar ShowOptionsInputBar;
        tfp::InputBar ShowConsoleInputBar;
        tfp::InputBar OpenChatInputBar;
        tfp::Window ControlsWindow;

        tfp::Button LanguageButtonSelect[9];
        tfp::Window LanguageWindow;

        tfp::Button OptionsMenu;
        tfp::Button OptionsControls;
        tfp::Button OptionsVideoOptions;
        tfp::Button OptionsMapEditor;
        tfp::Button OptionsLanguage;
        tfp::Button OptionsAuthors;
        tfp::Button OptionsExit;
        tfp::Button OptionsExitAll;
        tfp::Button OptionsClose;
        tfp::Window OptionsWindow;

        tfp::Window CharacterInfoWindow;


        tfp::DragableArea InventoryDragableArray[100];
        tfp::Window InventoryWindow;


        tfp::InputBar TerrainSelectInputSetGridSizeX;
        tfp::InputBar TerrainSelectInputSetGridSizeY;
        tfp::Button TerrainSelectButtonSetGridSize;
        tfp::InputBar TerrainSelectInputSetMapSizeX;
        tfp::InputBar TerrainSelectInputSetMapSizeY;
        tfp::Button TerrainSelectButtonSetMapSize;
        tfp::Button TerrainSelectButtonSpecial;
        tfp::Button TerrainSelectButtonMobs;
        tfp::Button TerrainSelectButtonObjects;
        tfp::Button TerrainSelectButtonTerrain;
        tfp::Button TerrainSelectButtonNext;
        tfp::Button TerrainSelectButtonPrevious;

        tfp::InputBar TerrainSelectInputSetZIndex;
        tfp::Button TerrainSelectButtonSetZIndex;
        tfp::Button TerrainSelectButtonSetZIndexHelp;

        tfp::Button TerrainSelectButtonDisableGrid;
        tfp::Button TerrainSelectButtonHideGrid;
        tfp::Button TerrainSelectButtonLockCamera;
        tfp::Button TerrainSelectButtonUnlockCamera;
        tfp::Button TerrainSelectButtonLoadMap;
        tfp::Button TerrainSelectButtonSaveMap;
        tfp::Window TerrainSelectWindow;

        /// Menu
        tfp::Button HostGameButton;
        tfp::Button SingleplayerGameButton;
        tfp::Button JoinGameButton;
        tfp::InputBar JoinGameIpInput;
        tfp::InputBar JoinGamePortInput;


        /// Server
        tfp::Button RunServerButton;
        tfp::Button StopServerButton;
        tfp::Button JoinServerGameButton;
        tfp::InputBar ServerIpInput;
        tfp::InputBar ServerPortInput;

        /// User interface
        tfp::LoadingBar HealthBar;
        tfp::LoadingBar ManaBar;
    public:
        /// Konstruktor
        Interface();
        /// Destruktor
        ~Interface();
        /// Wyswietla interfejs, zwraca false gdy screen nie istnieje
        const bool DisplayInterface(std::string GameType);
        /// Wyswietla licznik fps
        void DisplayFps();
        /// Ustawia czy pokazac licznik fps
        void ShowFps(bool State);
        /// Zwraca czy licznik fps jest aktywny
        const bool IsFpsVisible() const;
        /// Wczytuje wiadomosci debugu
        void LoadDebugMessages();
        /// Zapisuje wskaznik do Screen na ktorym sie renderuje interfejs
        void SetGameHandle(tfp::Game *Handle);
        /// Pokazuje lub chowa linie komend
        void ShowCommandLine(bool Show);
        /// Zwraca czy konsola jest widoczna
        const bool IsCommandLineVisible();
        /// Wpisuje znak do konsoli
        void SendCommandLineInput(char Character);
        /// Zwraca komende
        std::string GetCommandLineInput();
        /// Wysyla komende
        void SendCommandLineOutputLine(std::string Line);
        /// Wysyla informacje o wcisnietm klawiszu
        void SendKeyPressed(sf::Event Key);
        /// Zwraca czy kolejka komend jest pusta
        const bool IsCommandQueueEmpty() const;
        /// Zwraca wpisana komende do uruchomienia
        std::string GetCommandToRun();
        /// Zwraca czy konsola jest aktywna
        const bool IsCommandLineActive();
        /// Ustawia indeks terenow do pokazania w okienku
        void SetTileIndex(int Value);
        /// Zwieksza indeks terenow do pokazania w okienku o podana wartosc
        void AddTileSetIndex(int Value);
        /// Zwieksza indeks jezykow do pokazania w okienku o podana wartosc
        void SetLanguageNamesIndexAdd(int Value);
        /// Wlancza siatke o podanych wymiarow
        void SetGrid(int Width, int Height);
        /// Wlancza lub wylacza widocznosc siatki
        void ShowGrid(bool State);
        /// Wlancza lub wylacza dzialanie siatki
        void EnableGrid(bool State);
        /// Zwraca czy siatka jest widoczna
        bool IsGridVisible() const;
        /// Zwraca jakie tilesy maja byc wysiwietlane w oknie wyboru terenu
        std::string GetTileBuildMode();
        /// Ustawia jakie tilesy maja byc wyswietlane w oknie wyboru terenu
        void SetTileBuildMode(std::string Mode);
        /// Ustawia Z-Indeks wstawianych obiektow
        void SetTileZIndex(unsigned Value);
        /// Zwraca rozmiar siatki
        sf::Vector2i GetGridSize();
        /// Wlacza lub wylacza pomoc o indeksie z
        void SetZindexVisible(bool State);
        /// Ustawia przesuniecie siatki
        void SetGridShift(float Horizontal, float Vertical);
        /// Zwraca przesuniecie siatki
        sf::Vector2f GetGridShift();

    };
}

#endif // INTERFACE_HPP_INCLUDED
