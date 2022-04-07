/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef AREA_HPP_INCLUDED
#define AREA_HPP_INCLUDED

namespace tfp
{

    class AreaListClass
    {
    public:
        struct Node
        {
            enum AreaType
            {
                Focus,
                Dragable,
                Clickable,
                Input
            };
            tfp::FocusArea *FocusAreaHandle;
            tfp::DragableArea *DragableAreaHandle;
            tfp::ClickableArea *ClickableAreaHandle;
            tfp::InputArea *InputAreaHandle;
            AreaType Type;
            Node(tfp::FocusArea *Handle);
            Node(tfp::DragableArea *Handle);
            Node(tfp::ClickableArea *Handle);
            Node(tfp::InputArea *Handle);
            ~Node();

        };
    private:
        std::queue<sf::Event> EventList;
        std::vector<tfp::AreaListClass::Node> List;
        bool InputAreaActive;
    public:
        /// Konstruktor
        AreaListClass();
        /// Destruktor
        ~AreaListClass();
        /// Sprawdza aktywnosc wszystkich zarejestrowanych przyciskow
        void CheckActive();
        /// Dodaje FocusArea do listy
        void Register(tfp::FocusArea *Handle);
        /// Dodaje DragableArea do listy
        void Register(tfp::DragableArea *Handle);
        /// Dodaje ClickableArea do listy
        void Register(tfp::ClickableArea *Handle);
        /// Dodaje InputArea do listy
        void Register(tfp::InputArea *Handle);
        /// Usuwa FocusArea z listy
        void Unregister(tfp::FocusArea *Handle);
        /// Usuwa DragableArea z listy
        void Unregister(tfp::DragableArea *Handle);
        /// Usuwa ClickableArea z listy
        void Unregister(tfp::ClickableArea *Handle);
        /// Usuwa InputArea z listy
        void Unregister(tfp::InputArea *Handle);
        /// Usuwa wszystkie area o podnym wskazniku do gry
        void UnregisterGame(tfp::Game *GameHandle);
        /// Wysyla event do listy area
        void SendEvent(sf::Event &Event);
        /// Zwraca czy jakikolwiek InputArea jest aktywny
        bool &IsInputAreaActive();
        /// Zwraca liste zarejestrowanych area
        std::vector<tfp::AreaListClass::Node> &GetList();
        /// Zwraca ilosc zarejestrowanych area
        int GetRegisteredAreaCount();
    };

    class FocusArea{
        sf::Vector2f Position;
        sf::Vector2f Size;
        bool Active;
        bool Disabled;
        bool RelativeSize;
        tfp::Game *GameHandle;
    public:
        /// Konstruktor bez parametru wymaga uzycia funkcji Reset()
        FocusArea();
        /// Konstruktor z parametrami. Jesli Handle = nullptr nalezy uzyc SetGameHandle();
        FocusArea(tfp::Game *Handle, sf::Vector2f Position, sf::Vector2f Size, bool RelativeSize);
        /// Destruktor
        ~FocusArea();
        /// Resetuje rozmiar i pozycje
        void Reset(tfp::Game *Handle, sf::Vector2f Position, sf::Vector2f Size, bool RelativeSize);
        /// Tylko do ButtonGlobalList. Sprawdza czy obszar zostal aktywowany
        void CheckActiveSystem();
        /// Zwraca czy obszar jest aktywny
        const bool IsActive() const;
        /// Zwraca czy obszar jest zablokowany
        const bool &IsDisabled() const;
        /// Ustawia obszar jako aktywny
        void SetActive(bool State);
        /// Wylacza dzialane obszaru
        void SetDisabled(bool State);
        // Jesli nie ma mozliwosci ustawienia w konstruktorze
        void SetGameHandle(tfp::Game *Handle);
        /// Ustawia pozycje
        void SetPosition(sf::Vector2f NewPosition);
        /// Przesuwanie obszaru
        void Move(sf::Vector2f Distance);
        /// Zwraca uchwyt na gre
        tfp::Game* GetGameHandle();
        ///  Zwraca pozycje area
        sf::Vector2f &GetPosition();
        /// Zwraca rozmiar area
        sf::Vector2f &GetSize();
    };

    class InputArea{
        sf::Vector2f Position;
        sf::Vector2f Size;
        bool Active;
        bool Disabled;
        bool RelativeSize;
        tfp::TextType InputType;
        tfp::Game *GameHandle;
        std::string KeyConfigActionName;
        std::string InputText;
        int InputTextMaxLength;
    public:
        /// Konstruktor bez parametru wymaga uzycia funkcji Reset()
        InputArea();
        /// Konstruktor z parametrami. Jesli Handle = nullptr nalezy uzyc SetGameHandle();
        InputArea(tfp::Game *Handle, sf::Vector2f Position, sf::Vector2f Size, bool RelativeSize);
        /// Destruktor
        ~InputArea();
        /// Resetuje rozmiar i pozycje
        void Reset(tfp::Game *Handle, sf::Vector2f Position, sf::Vector2f Size, bool RelativeSize);
        /// Tylko do ButtonGlobalList. Sprawdza czy obszar zostal aktywowany
        void CheckActiveSystem();
        /// Zwraca czy obszar jest aktywny
        const bool IsActive() const;
        /// Zwraca czy obszar jest zablokowany
        const bool &IsDisabled() const;
        /// Ustawia obszar jako aktywny
        void SetActive(bool State);
        /// Wylacza dzialane obszaru
        void SetDisabled(bool State);
        // Jesli nie ma mozliwosci ustawienia w konstruktorze
        void SetGameHandle(tfp::Game *Handle);
        /// Przesuwanie obszaru
        void Move(sf::Vector2f Distance);
        /// Ustawia pozycje obszaru
        void SetPosition(sf::Vector2f Position);
        /// Ustawia pozycje obszaru
        void SetPosition(float PositionX, float PositionY);
        /// Ustaawia rozmiar
        void SetSize(sf::Vector2f Size, bool Relative);
        /// Wysyla event
        void SendEvent(sf::Event &Event);
        /// Ustawia tekst obszaru
        void SetText(std::string Text);
        /// Zwraca tekst obszaru
        std::string &GetText();
        /// Zwraca uchwyt na gre
        tfp::Game* GetGameHandle();
        ///  Zwraca pozycje area
        sf::Vector2f &GetPosition();
        /// Zwraca rozmiar area
        sf::Vector2f &GetSize();
        /// Ustawia tryb wpisywanych znakow
        void SetInputType(tfp::TextType InputType);
        /// Ustawia event klawisza jesli jest to TextTypeKey
        void SetKeyConfigActionName(std::string Name);
        /// Ustawia maksymalna ilosc znakow do wpisania
        void SetTextMaxLength(int Length);

    };

    class DragableArea{
        sf::Vector2f Position;
        sf::Vector2f Size;
        bool Active;
        bool Disabled;
        bool RelativeSize;
        bool ButtonJustPressed;
        tfp::Game *GameHandle;
    public:
        /// Konstruktor bez parametru wymaga uzycia funkcji Reset()
        DragableArea();
        /// Konstruktor z parametrami. Jesli Handle = nullptr nalezy uzyc SetGameHandle();
        DragableArea(tfp::Game *Handle, sf::Vector2f Position, sf::Vector2f Size, bool RelativeSize);
        /// Destruktor
        ~DragableArea();
        /// Resetuje rozmiar i pozycje
        void Reset(tfp::Game *Handle, sf::Vector2f Position, sf::Vector2f Size, bool RelativeSize);
        /// Tylko do ButtonGlobalList. Sprawdza czy obszar zostal aktywowany
        void CheckActiveSystem();
        /// Zwraca czy mysz jest w srodku Area
        bool IsMouseInBorders();
        /// Zwraca czy obszar jest aktywny
        const bool IsActive() const;
        /// Zwraca czy obszar jest zablokowany
        const bool &IsDisabled() const;
        /// Ustawia obszar jako aktywny
        void SetActive(bool State);
        /// Wylacza dzialane obszaru
        void SetDisabled(bool State);
        // Jesli nie ma mozliwosci ustawienia w konstruktorze
        void SetGameHandle(tfp::Game *Handle);
        /// Przesuwanie obszaru
        void Move(sf::Vector2f Distance);
        /// Ustawia pozycje obszaru
        void SetPosition(sf::Vector2f Position);
        /// Zwraca uchwyt na gre
        tfp::Game* GetGameHandle();
        ///  Zwraca pozycje area
        sf::Vector2f &GetPosition();
        /// Zwraca rozmiar area
        sf::Vector2f &GetSize();
    };

    class ClickableArea
    {
    private:
        sf::Vector2f Position;
        sf::Vector2f Size;
        bool ButtonDown;
        bool Disabled;
        bool RelativeSize;
        bool ButtonActivated;
        bool Blocked;
        tfp::Game *GameHandle;
    public:
        /// Konstruktor
        ClickableArea();
        /// Konstruktor z parametrami. Jesli Handle = nullptr nalezy uzyc SetGameHandle();
        ClickableArea(tfp::Game *Handle, sf::Vector2f Position, sf::Vector2f Size, bool RelativeSize);
        /// Destruktor
        ~ClickableArea();
        /// Resetuje rozmiar i pozycje
        void Reset(tfp::Game *Handle, sf::Vector2f Position, sf::Vector2f Size, bool RelativeSize);
        /// Jesli nie ma mozliwosci ustawienia w konstruktorze
        void SetGameHandle(tfp::Game *Handle);
        /// Tylko do ButtonGlobalList. Sprawdza czy obszar zostal aktywowany
        void CheckActiveSystem();
        /// Zwraca czy obszar jest zablokowany
        const bool &IsDisabled() const;
        /// Wylacza dzialane obszaru
        void SetDisabled(bool State);
        /// Przesuwanie obszaru
        void Move(sf::Vector2f Distance);
        /// Ustawia pozycje obszaru
        void SetPosition(sf::Vector2f Position);
        /// Ustawia wymiary obszaru
        void SetSize(sf::Vector2f Size);
        /// Zwraca uchwyt na gre
        tfp::Game* GetGameHandle();
        /// Zwraca czy jest wciskany
        bool IsButtonDown();
        /// Zwraca czy jest nacisniety
        bool IsButtonPressed();
        /// Ustawia obszar jako aktywny
        void SetActive(bool State);
        ///  Zwraca pozycje area
        sf::Vector2f &GetPosition();
        /// Zwraca rozmiar area
        sf::Vector2f &GetSize();

    };


}

#endif // AREA_HPP_INCLUDED
