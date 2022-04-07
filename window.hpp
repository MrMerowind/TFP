/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED

namespace tfp
{
    class WindowGlobalDataClass
    {
    private:
        sf::Texture WindowBorderTextureTop;
        sf::Texture WindowBorderTextureDown;
        sf::Texture WindowBorderTextureLeft;
        sf::Texture WindowBorderTextureRight;

        sf::Texture WindowCornerTextureLeftTop;
        sf::Texture WindowCornerTextureLeftDown;
        sf::Texture WindowCornerTextureRightTop;
        sf::Texture WindowCornerTextureRightDown;

        sf::Texture WindowInsideTexture;

        int BorderWidth;
        int BorderHeight;
        std::vector<tfp::Window*> WindowList;
    public:
        /// Konstruktor
        WindowGlobalDataClass();
        /// Destruktor
        ~WindowGlobalDataClass();
        /// Zwraca teksture czesci okna
        const sf::Texture &GetTexture(int Numer) const;
        /// Zwraca szerokosc ramki
        const int &GetBorderWidth() const;
        /// Zwraca wysokosc ramki
        const int &GetBorderHeight() const;
        /// Zwraca prawde jesli mysz jest w oknie
        bool IsMouseInsideWindow(tfp::Window *Handle);
        /// Zwraca prawde jesli mysz jest w jakimkolwiek oknie
        bool IsMouseInsideAnyWindow(tfp::Game *Handle);
        /// Zwraca prawde jesli mysz jest w srodku okna
        bool IsMouseInsideBorders(tfp::Window *Handle);
        /// Dodaje okno do listy okien
        void RegisterWindow(tfp::Window *Handle);
        /// Usuwa okna z listy o podanym wskzniku gry
        void UnregisterWindows(tfp::Game *Handle);
        /// Zwraca liste zarejestrowanych okien
        std::vector<tfp::Window*> &GetWindowList();
    };

    class Window
    {
    private:
        sf::Vector2i InsideSize;
        sf::Vector2f Position;
        sf::Vector2f PositionPrevious;
        bool WindowMoved;
        std::string Name;
        bool Visible;
        tfp::Game *GameHandle;
        tfp::DragableArea WindowDragableArea;
        tfp::FocusArea WindowFocusArea; ///< Zeby nie dalo sie klikac przec okno w buttony
        void WindowEvents();
    public:
        /// Kosntruktor
        Window();
        /// Destruktor
        ~Window();
        /// Konstruktor z ustawieniem opcji okna
        Window(tfp::Game *GameHandle, sf::Rect<int> BoxInside, std::string WindowName);
        /// Ustawienie opcji okna
        void Reset(tfp::Game *GameHandle, sf::Rect<int> BoxInside, std::string WindowName);
        /// Zmiana rozmiaru okna
        void Resize(int Width, int Height);
        /// Rysowanie w srodku okna sprajtow
        void Draw(sf::Sprite &Object);
        /// Rysowanie w srodku okna tekstu
        void Draw(sf::Text &Object);
        /// Wyswietlanie okna
        void Display();
        /// Ustawia czy okno ma byc wyswietlane
        void Show(bool State);
        /// Zwraca czy okno jest widoczne
        bool IsVisible();
        /// Zwraca pozycje tytulu okna
        sf::Vector2f GetTitlePosition();
        /// Zwraca pozycje myszy w oknie
        sf::Vector2f GetMousePosition();
        /// Zwraca czy mysz znajduje sie w oknie (razem z paskiem tytulu)
        bool IsMouseInsideWindow();
        /// Zwraca czy mysz znajduje sie w srodku okna (miejscu do renderowania)
        bool IsMouseInsideBorders();
        /// Tylko do WindowGlobalData. Zwraca czy mysz znajduje sie w oknie (razem z paskiem tytulu)
        bool IsMouseInsideWindowSystem();
        /// Tylko do WindowGlobalData. Zwraca czy mysz znajduje sie w srodku okna (miejscu do renderowania)
        bool IsMouseInsideBordersSystem();
        /// Zwraca uchwyt gry
        tfp::Game *GetGameHandle();
        /// Zwraca nazwe okna
        std::string GetWindowName();
        /// Zwraca dragable area
        tfp::DragableArea &GetWindowDragableArea();
        /// Zwraca pozycje okna
        sf::Vector2f &GetPosition();
        /// Zwraca rozmiar srodka okna
        sf::Vector2i &GetInsideSize();
        /// Czy okno zostalo wyrenderowane przesuniete wzgledem poprzedniego wyrenderowania (na window display -> window events sie wylicza)
        bool HasMoved();
    };
}

#endif // WINDOW_HPP_INCLUDED
