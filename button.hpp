/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

namespace tfp
{
    class Button
    {
    private:
        sf::Vector2f Position;
        sf::Vector2f Size;
        std::string Name;
        std::string Command;
        tfp::Game *GameHandle;
    public:
        tfp::ClickableArea Area;
    public:
        /// Konstruktor
        Button(sf::Vector2f Position = sf::Vector2f(0.0f, 0.0f), sf::Vector2f Size = sf::Vector2f(0.0f, 0.0f), std::string Text = "");
        /// Destruktor
        ~Button();
        /// Wyswietlenie przycisku
        void Display();
        /// Ustawienie pozycji przycisku
        void SetPosition(float PositionX, float PositionY);
        /// Przesuniecie przysicku
        void Move(float PositionX, float PositionY);
        /// Ustawienie wymierow przysicku
        void SetSize(float Width, float Height);
        /// Ustawienie wskaznika na okno gry
        void SetGameHandle(tfp::Game *Handle);
        /// Ustawienie komendy do wywolania po wcisnieciu przysicku
        void SetCommand(std::string Command);
        /// Ustawienie napisu na przycisku
        void SetText(std::string Text);
    };

    class LoadingBar
    {
    public:
        enum Mode
        {
            None,
            PercentageMode,
            ValueMode,
            MaxValueMode,
            FullMode
        };
    private:
        sf::Vector2f Position;
        sf::Vector2f Size;
        std::string RenderText;
        int Value;
        int MaxValue;
        sf::Color BarColor;
        sf::Color UnderBarColor;
        tfp::Game *GameHandle;
        Mode BarMode;
    public:
        /// Konstruktor
        LoadingBar(sf::Vector2f Position = sf::Vector2f(0.0f, 0.0f), sf::Vector2f Size = sf::Vector2f(0.0f, 0.0f), tfp::LoadingBar::Mode DisplayMode = tfp::LoadingBar::None);
        /// Destruktor
        ~LoadingBar();
        /// Wyswietlenie przycisku
        void Display();
        /// Ustawienie pozycji przycisku
        void SetPosition(float PositionX, float PositionY);
        /// Przesuniecie przysicku
        void Move(float PositionX, float PositionY);
        /// Ustawienie wymierow przysicku
        void SetSize(float Width, float Height);
        /// Ustawienie wskaznika na okno gry
        void SetGameHandle(tfp::Game *Handle);
        /// Ustawia wartosc paska
        void SetValue(int Value_);
        /// Ustawia maksymalna wartosc paska
        void SetMaxValue(int MaxValue);
        /// Ustawia tryb wyswietlania paska
        void SetMode(tfp::LoadingBar::Mode BarMode);
        /// Ustawia kolor paska
        void SetColor(sf::Color BarColor);
        /// Ustawia kolor tla pod paskiem
        void SetUnderColor(sf::Color UnderBarColor);

    };


    class InputBar
    {
    private:
        sf::Vector2f Position;
        sf::Vector2f Size;
        std::string RenderText;
        int MaximumCharacters;
        sf::Color UnderBarColor;
        tfp::Game *GameHandle;
        std::string PlaceHolder;
        std::wstring TranslatedPlaceHolder;
    public:
        tfp::InputArea Area;
    public:
        /// Konstruktor
        InputBar(sf::Vector2f Position = sf::Vector2f(0.0f, 0.0f), sf::Vector2f Size = sf::Vector2f(0.0f, 0.0f));
        /// Destruktor
        ~InputBar();
        /// Wyswietlenie przycisku
        void Display();
        /// Ustawienie pozycji przycisku
        void SetPosition(float PositionX, float PositionY);
        /// Przesuniecie przysicku
        void Move(float PositionX, float PositionY);
        /// Ustawienie wymierow przysicku
        void SetSize(float Width, float Height, bool Relative = true);
        /// Ustawienie wskaznika na okno gry
        void SetGameHandle(tfp::Game *Handle);
        /// Ustawia maksymalna wartosc paska
        void SetMaxCharacters(int MaxCharacters);
        /// Ustawia kolor tla pod wyswietlanym tekstem
        void SetUnderColor(sf::Color UnderBarColor);
        /// Ustawia tryb wpisywanych znakow
        void SetInputType(tfp::TextType InputType);
        /// Ustawia tekst wyswietlany gdy nic nie jest wpisane
        void SetPlaceHolder(std::string Text);
        /// Ustawia rpzetlumaczony tekst wyswietlany gdy nic nie jest wpisane
        void SetTranslatedPlaceHolder(std::wstring Text);

    };
}

#endif // BUTTON_HPP_INCLUDED
