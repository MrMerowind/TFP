/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef MOUSE_HPP_INCLUDED
#define MOUSE_HPP_INCLUDED

namespace tfp
{
    class Mouse{
    private:
        sf::Vector2f Position;
        sf::Mouse MouseData;
        tfp::Game *GameHandle;
        bool LeftMouseButtonDown;
        bool RightMouseButtonDown;

        sf::Vector2f LeftMouseButtonDragStart;
        sf::Vector2f RightMouseButtonDragStart;

        sf::Vector2f LeftMouseButtonDragDelta;
        sf::Vector2f RightMouseButtonDragDelta;

    public:
        /// Konstruktor
        Mouse();
        /// Destruktor
        ~Mouse();
        /// Zwraca pozycje myszy w oknie
        const sf::Vector2f &GetMousePosition();
        /// Zwraca przeskalowana pozycje myszy w oknie
        const sf::Vector2f GetMousePositionScaled();
        /// Zwraca pozycje myszy na mapie
        const sf::Vector2f GetMousePositionOnMap();
        /// Zwraca bezposredni obiekt sf::Mouse
        sf::Mouse &GetMouse();
        /// Ustawia uchwyt gry
        void SetGameHandle(tfp::Game *Handle);
        /// Pobiera informacje o myszce
        void LoadData();
        /// Zwraca przeciagniecie lewym przyciskiem myszy
        const sf::Vector2f GetLeftMouseButtonDeltaDrag() const;
        /// Zwraca przeciagniecie prawym przyciskiem myszy
        const sf::Vector2f GetRightMouseButtonDeltaDrag() const;
        /// Zwraca przeskalowane przeciagniecie lewym przyciskiem myszy
        const sf::Vector2f GetLeftMouseButtonDeltaDragScaled();
        /// Zwraca przeskalowane przeciagniecie prawym przyciskiem myszy
        const sf::Vector2f GetRightMouseButtonDeltaDragScaled();
    };
}

#endif // MOUSE_HPP_INCLUDED
