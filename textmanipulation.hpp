/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef TEXTMANIPULATION_HPP_INCLUDED
#define TEXTMANIPULATION_HPP_INCLUDED

namespace tfp
{
    /// Zwraca (Index) czesc tekstu rozdzielonego przez (Symbol). (DeleteSpaces) - bez spacji
    std::string SplitString(std::string Text, int Index = 0, char Symbol = ':', bool DeleteSpaces = true);
    /// Zwraca (Index) czesc tekstu rozdzielonego przez (Symbol). (DeleteSpaces) - bez spacji
    std::wstring SplitString(std::wstring Text, int Index = 0, wchar_t Symbol = ':', bool DeleteSpaces = true);
    /// Liczy ilosc wystapien znaku w tekscie
    int CountSymbolsInText(std::string Text, char Symbol);
    /// Zamienia tekst na liczbe
    int StringToInt(std::string Text);
    /// Zamienia tekst na wartosc logiczna
    bool StringToBool(std::string Text);
    /// Zamienia tekst na liczbe calkowita
    float StringToFloat(std::string Text);
    /// Zamienia liczbe na string
    std::string IntToString(int Value, int Digits = 0);
    /// Zamienia liczbe na string
    std::string Int64ToString(int64_t Value, int Digits = 0);
    /// Zamienia liczbe na wstring
    std::wstring IntToWString(int Value, int Digits = 0);
    /// Zamienia liczbe calkowita na tekst
    std::string FloatToString(float Value, int Precision = 2);
    /// Zamienia liczbe calkowita na tekst
    std::wstring FloatToWString(float Value, int Precision = 2);
    /// Zamienia wartosc logiczna na tekst
    std::string BoolToString(bool Value);
    /// Zmienia liczbe na zero jesli jest ujemna
    unsigned NotBelowZero(int Value);
    /// Zamiana sciezki na nazwe pliku bez rozszerzenia
    std::string PathToFileTitle(std::string Path);
    /// Zamiana sciezki na nazwe pliku z rozszezeniem
    std::string PathToFileTitleWithExtension(std::string Path);
    /// Pomija x pierwszych wyrazow
    std::string IgnoreWords(std::string Value, int NumberOfWords, bool FromEnd = false);
    /// Zamienia tekst ascii na szeroki tekst
    std::wstring StringToWString(const std::string& s);
    /// Zamienia szeroki tekst na tekst ascii
    std::string WStringToString(const std::wstring& s);
    /// Zwraca mniejsza liczbe
    int Lesser(int Value1, int Value2);
    /// Zwraca wieksza liczbe
    int Greater(int Value1, int Value2);
    /// Zaokragla liczbe
    int RoundToInt(float Value);
    /// Zaokragla liczbe
    float RoundToFloat(float Value);
    /// Zamienia liczby ze soba jesli pierwsza jest wieksza od drugiej
    void SwapIfGreater(int &Left, int &Right);
    /// Zamienia smfl event na string
    std::string SfmlEventToString(sf::Event Event);
    /// Zamienia smfl event id na string
    std::string SfmlEventIDToString(int ID);
    /// Oblicza dlugosc wektora
    float VectorLength(float a, float b);
    /// Oblicza dlugosc wektora
    float VectorLength(sf::Vector2f Vector);
    /// Normalizuje wektor (dzielenie wektoru przez jego dlugosc)
    sf::Vector2f NormalizeVector(sf::Vector2f Vector);



}

#endif // TEXTMANIPULATION_HPP_INCLUDED
