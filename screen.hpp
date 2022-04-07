/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef SCREEN_HPP_INCLUDED
#define SCREEN_HPP_INCLUDED

namespace tfp
{
    class Screen
    {
    private:
        sf::View View;
        sf::RenderWindow Window;
    protected:
        /// Rozmiar okna
        int MenuWidth;
        int GameWidth;
        int MapEditorWidth;
        int ServerWidth;
        int MenuHeight;
        int GameHeight;
        int MapEditorHeight;
        int ServerHeight;
        /// Rozmiar widoku
        int ViewWidth;
        int ViewHeight;
        int ViewOriginalWidth;
        int ViewOriginalHeight;
        /// Srodek widoku
        int ViewHorizontalCenter;
        int ViewVerticalCenter;
        /// Limit klatek
        int FramerateLimit;
        bool VerticalSync;
        /// Nazwa kona
        std::wstring WindowTitle;
        /// Peny ekran
        bool MenuFullScreen;
        bool GameFullScreen;
        bool MapEditorFullScreen;
        bool ServerFullScreen;
        bool Focus;
        /// Eventy ekranu
        std::queue<sf::Event> ScreenEvents;
        tfp::Game *GameHandle;
    public:
        /// Konstruktor
        Screen();
        /// Destruktor
        ~Screen();
        /// Wyswietla okno i obsluguje wszystkie zdarzenia
        void DisplayWindow();
        /// Czy okno jest otwarte
        const bool IsWindowOpen();
        /// Rysowanie w oknie
        void Draw(const sf::Drawable &Drawable);
        /// Rysowanie w oknie
        void DrawVertex(const sf::Vertex* vertices, std::size_t vertexCount,
              sf::PrimitiveType type, const sf::RenderStates& states = sf::RenderStates::Default);
        /// Wyczysc
        void Clear();
        /// Pobieranie eventow ze screen
        sf::Event GetScreenEvent();
        const bool IsEventInQueue();
        /// Zamykanie okna
        void Close();
        /// Czy jest aktywne okno
        const bool &IsFocused() const;
        /// Ustawia focus okna
        void SetFocus(bool State);
        /// Pobiera limit klatek;
        const int GetFramerateLimit() const;
        /// Uzywac tylko w funkcjach sfml
        sf::RenderWindow &GetRenderWindowHandle();
        /// Wymiary okna
        const sf::Vector2i GetWindowSize();
        /// Wymiary widoku
        const sf::Vector2i GetViewSize();
        /// Wymiary oryginalne widoku
        const sf::Vector2i GetOriginalViewSize();
        /// Zmiana skali widoku
        void SetViewScale(float Scale);
        /// Zmiana rozmiaru okna
        void Resize(int Width, int Height, bool FullScreen);
        /// Reset rozmiaru okna
        void Resize();
        /// Zmiana rozmiaru widoku
        void SetViewSize(int Width, int Height);
        /// Zwraca skale zmienionej przez komendy do oryginalnej rozdzielczosci
        const float GetViewScale();
        /// Zmienia nazwe okna
        void SetWindowTitle(std::wstring Title);
        /// Ustawia wskacnik gry
        void SetGameHandle(tfp::Game *Handle);
        /// Zwraca czy pelny ekran jest wlaczony w wybranym oknie gry
        bool GetFullScreen(std::string GameType);
        /// Ustawia pelny ekran w wybranym oknie gry
        void SetFullScreen(std::string GameType, bool State);
        /// Ustawia rozmiar wybranego okna
        void SetWindowSize(std::string GameType, int NewWidth, int NewHeight);
        /// Zapisuje konfiguracje ustawien
        void SaveSettings();
        /// Zwraca czy synchronizacja pionowa jest aktywna
        bool GetVerticalSync();
        /// Ustawia synchronizacje pionowa
        void SetVerticalSync(bool State);
        /// Resetuje ustawienia
        void ResetSettings();

    };

}



#endif // SCREEN_HPP_INCLUDED
