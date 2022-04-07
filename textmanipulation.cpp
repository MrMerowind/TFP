/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"

std::string tfp::SplitString(std::string Text, int Index, char Symbol, bool DeleteSpaces)
{
    std::string Return;
    bool Quote = false;
    for(unsigned int i = 0; i < Text.size(); i++)
    {
        if(Text[i] == '"') Quote = !Quote;
        else if(Quote && Index == 0) Return += Text[i];
        else if(Quote);
        else if(Text[i] == Symbol) Index--;
        else if(Index == 0 && (DeleteSpaces == false || Text[i] != ' ')) Return += Text[i];
    }
    return Return;
}

std::wstring tfp::SplitString(std::wstring Text, int Index, wchar_t Symbol, bool DeleteSpaces)
{
    std::wstring Return;
    bool Quote = false;
    for(unsigned int i = 0; i < Text.size(); i++)
    {
        if(Text[i] == L'"') Quote = !Quote;
        else if(Quote && Index == 0) Return += Text[i];
        else if(Quote);
        else if(Text[i] == Symbol) Index--;
        else if(Index == 0 && (DeleteSpaces == false || Text[i] != L' ')) Return += Text[i];
    }
    return Return;
}

int tfp::Lesser(int Value1, int Value2)
{
    if(Value1 < Value2) return Value1;
    else return Value2;
}

int tfp::Greater(int Value1, int Value2)
{
    if(Value1 < Value2) return Value2;
    else return Value1;
}

int tfp::StringToInt(std::string Text)
{
    bool Negative = false;
    int Return = 0;
    for(unsigned int i = 0; i < Text.size(); i++)
    {
        if(Text[i] >= 48 && Text[i] <= 57) Return = Return * 10 + Text[i] - 48;
        else if(Text[i] == '-' && Return == 0) Negative = true;
    }
    if(Negative) Return = - Return;
    return Return;
}

bool tfp::StringToBool(std::string Text)
{
    if(Text.size() < 1) return false;
    else if(Text[0] == 't' || Text[0] == 'T' || Text[0] == '1' || Text[0] == 'y' || Text[0] == 'Y') return true;
    else return false;
}

float tfp::StringToFloat(std::string Text)
{
    bool Negative = false;
    bool Coma = false;
    int DigitsAfterComa = 0;
    float Return = 0.0f;
    for(unsigned int i = 0; i < Text.size(); i++)
    {
        if(Text[i] == '.' || Text[i] == ',') Coma=true;
        else if(Text[i] >= 48 && Text[i] <= 57)
        {
                Return = Return * 10 + Text[i] - 48;
                if(Coma == true) DigitsAfterComa++;
        }
        else if(Text[i] == '-' && Return == 0) Negative = true;
    }
    if(Negative) Return = - Return;
    Return /= (float)pow(10,DigitsAfterComa);
    return Return;
}

unsigned tfp::NotBelowZero(int Value)
{
    if(Value < 0) return 0;
    else return (unsigned)Value;
}

std::string tfp::IntToString(int Value, int Digits)
{
    int Digit;
    bool Negative = false;
    std::string Return;
    if(Value == 0)
    {
        Return = "0";
        return Return;
    }
    else if(Value < 0)
    {
        Negative = true;
        Value = - Value;
    }
    while(Value != 0)
    {
        Digit = Value % 10;
        Return = char(Digit + 48) + Return;
        Value /= 10;
    }
    if(Negative)
    {
        while(Return.size() < NotBelowZero(Digits - 1)) Return = '0' + Return;
        Return = '-' + Return;
    }
    else while(Return.size() < NotBelowZero(Digits)) Return = '0' + Return;
    return Return;
}

std::string tfp::Int64ToString(int64_t Value, int Digits)
{
    int Digit;
    bool Negative = false;
    std::string Return;
    if(Value == 0)
    {
        Return = "0";
        return Return;
    }
    else if(Value < 0)
    {
        Negative = true;
        Value = - Value;
    }
    while(Value != 0)
    {
        Digit = Value % 10;
        Return = char(Digit + 48) + Return;
        Value /= 10;
    }
    if(Negative)
    {
        while(Return.size() < NotBelowZero(Digits - 1)) Return = '0' + Return;
        Return = '-' + Return;
    }
    else while(Return.size() < NotBelowZero(Digits)) Return = '0' + Return;
    return Return;
}

std::wstring tfp::IntToWString(int Value, int Digits)
{
    int Digit;
    bool Negative = false;
    std::wstring Return;
    if(Value == 0)
    {
        Return = L"0";
        return Return;
    }
    else if(Value < 0)
    {
        Negative = true;
        Value = - Value;
    }
    while(Value != 0)
    {
        Digit = Value % 10;
        Return = wchar_t(Digit + 48) + Return;
        Value /= 10;
    }
    if(Negative)
    {
        while(Return.size() < NotBelowZero(Digits - 1)) Return = L'0' + Return;
        Return = L'-' + Return;
    }
    else while(Return.size() < NotBelowZero(Digits)) Return = L'0' + Return;
    return Return;
}

std::string tfp::FloatToString(float Value, int Precision)
{
    std::stringstream ss;
    if(Value - floor(Value) == 0.0f)
    {
        ss << std::setprecision(0) << std::fixed << Value;
    }
    else
    {
        ss << std::setprecision(Precision) << std::fixed << Value;
    }
    std::string Return;
    ss >> Return;
    return Return;
}

std::wstring tfp::FloatToWString(float Value, int Precision)
{
    std::wstringstream ss;
    if(Value - floor(Value) == 0.0f)
    {
        ss << std::setprecision(0) << std::fixed << Value;
    }
    else
    {
        ss << std::setprecision(Precision) << std::fixed << Value;
    }

    std::wstring Return;
    ss >> Return;
    return Return;
}

std::string tfp::BoolToString(bool Value)
{
    if(Value) return "True";
    else return "False";
}

float tfp::RoundToFloat(float Value)
{
    float Return = floor(Value);
    if(Value - Return < 0.5f) Return += 1.0f;
    return Return;
}


int tfp::RoundToInt(float Value)
{
    float Return = floor(Value);
    if(Value - Return < 0.5f) Return += 1.0f;
    return static_cast<int>(Return);
}

int tfp::CountSymbolsInText(std::string Text, char Symbol)
{
    int Return = 0;
    for(unsigned i = 0; i < Text.size(); i++)
    {
        if(Text[i] == Symbol) Return++;
    }
    return Return;
}

std::string tfp::IgnoreWords(std::string Text, int NumberOfWords, bool FromEnd)
{
    std::string Return;
    if(FromEnd)
    {
        for(int i = Text.size() - 1; i >= 0; i--)
        {
            if(NumberOfWords == 0)
            {
                Return += Text[i];
            }
            else if(Text[i] == ' ') NumberOfWords--;
        }
        std::reverse(Return.begin(), Return.end());
    }
    else
    {
        for(unsigned i = 0; i < Text.size(); i++)
        {
            if(NumberOfWords == 0)
            {
                Return += Text[i];
            }
            else if(Text[i] == ' ') NumberOfWords--;
        }
    }


    return Return;
}


std::string tfp::PathToFileTitle(std::string Path)
{
    int i = Path.size() - 1;
    std::string Return;
    if(CountSymbolsInText(Path, '.') > 0)
    {
        while(i >= 0 && Path[i--] != '.');
    }
    while(i >=0 && Path[i] != '\\' && Path[i] != '/')
    {
        Return += Path[i];
        i--;
    }
    std::reverse(Return.begin(), Return.end());
    return Return;
}

std::string tfp::PathToFileTitleWithExtension(std::string Path)
{
    int i = Path.size() - 1;
    std::string Return;
    while(i >=0 && Path[i] != '\\' && Path[i] != '/')
    {
        Return += Path[i];
        i--;
    }
    std::reverse(Return.begin(), Return.end());
    return Return;
}

std::wstring tfp::StringToWString(const std::string& s)
{
    std::wstring temp(s.length(),L' ');
    std::copy(s.begin(), s.end(), temp.begin());
    return temp;
}


std::string tfp::WStringToString(const std::wstring& s)
{
    std::string temp(s.length(), ' ');
    std::copy(s.begin(), s.end(), temp.begin());
    return temp;
}

void tfp::SwapIfGreater(int &Left, int &Right)
{
    if(Left > Right)
    {
        int Tmp = Left;
        Left = Right;
        Right = Tmp;
    }
}

std::string tfp::SfmlEventToString(sf::Event Event)
{
    if(Event.key.code == sf::Keyboard::Q) return "Q";
    if(Event.key.code == sf::Keyboard::W) return "W";
    if(Event.key.code == sf::Keyboard::E) return "E";
    if(Event.key.code == sf::Keyboard::R) return "R";
    if(Event.key.code == sf::Keyboard::T) return "T";
    if(Event.key.code == sf::Keyboard::Y) return "Y";
    if(Event.key.code == sf::Keyboard::U) return "U";
    if(Event.key.code == sf::Keyboard::I) return "I";
    if(Event.key.code == sf::Keyboard::O) return "O";
    if(Event.key.code == sf::Keyboard::P) return "P";
    if(Event.key.code == sf::Keyboard::A) return "A";
    if(Event.key.code == sf::Keyboard::S) return "S";
    if(Event.key.code == sf::Keyboard::D) return "D";
    if(Event.key.code == sf::Keyboard::F) return "F";
    if(Event.key.code == sf::Keyboard::G) return "G";
    if(Event.key.code == sf::Keyboard::H) return "H";
    if(Event.key.code == sf::Keyboard::J) return "J";
    if(Event.key.code == sf::Keyboard::K) return "K";
    if(Event.key.code == sf::Keyboard::L) return "L";
    if(Event.key.code == sf::Keyboard::Z) return "Z";
    if(Event.key.code == sf::Keyboard::X) return "X";
    if(Event.key.code == sf::Keyboard::C) return "C";
    if(Event.key.code == sf::Keyboard::V) return "V";
    if(Event.key.code == sf::Keyboard::B) return "B";
    if(Event.key.code == sf::Keyboard::N) return "N";
    if(Event.key.code == sf::Keyboard::M) return "M";
    if(Event.key.code == sf::Keyboard::Num0) return "0";
    if(Event.key.code == sf::Keyboard::Num1) return "1";
    if(Event.key.code == sf::Keyboard::Num2) return "2";
    if(Event.key.code == sf::Keyboard::Num3) return "3";
    if(Event.key.code == sf::Keyboard::Num4) return "4";
    if(Event.key.code == sf::Keyboard::Num5) return "5";
    if(Event.key.code == sf::Keyboard::Num6) return "6";
    if(Event.key.code == sf::Keyboard::Num7) return "7";
    if(Event.key.code == sf::Keyboard::Num8) return "8";
    if(Event.key.code == sf::Keyboard::Num9) return "9";
    if(Event.key.code == sf::Keyboard::Numpad0) return "0";
    if(Event.key.code == sf::Keyboard::Numpad1) return "1";
    if(Event.key.code == sf::Keyboard::Numpad2) return "2";
    if(Event.key.code == sf::Keyboard::Numpad3) return "3";
    if(Event.key.code == sf::Keyboard::Numpad4) return "4";
    if(Event.key.code == sf::Keyboard::Numpad5) return "5";
    if(Event.key.code == sf::Keyboard::Numpad6) return "6";
    if(Event.key.code == sf::Keyboard::Numpad7) return "7";
    if(Event.key.code == sf::Keyboard::Numpad8) return "8";
    if(Event.key.code == sf::Keyboard::Numpad9) return "9";
    if(Event.key.code == sf::Keyboard::Add) return "+";
    if(Event.key.code == sf::Keyboard::BackSlash) return "\\";
    if(Event.key.code == sf::Keyboard::Comma) return ",";
    if(Event.key.code == sf::Keyboard::Dash) return "-";
    if(Event.key.code == sf::Keyboard::Divide) return "/";
    if(Event.key.code == sf::Keyboard::End) return "End";
    if(Event.key.code == sf::Keyboard::Equal) return "=";
    if(Event.key.code == sf::Keyboard::Escape) return "Escape";
    if(Event.key.code == sf::Keyboard::Home) return "Home";
    if(Event.key.code == sf::Keyboard::Insert) return "Insert";
    if(Event.key.code == sf::Keyboard::Multiply) return "*";
    if(Event.key.code == sf::Keyboard::PageDown) return "PageDown";
    if(Event.key.code == sf::Keyboard::PageUp) return "PageUp";
    if(Event.key.code == sf::Keyboard::Pause) return "Pause";
    if(Event.key.code == sf::Keyboard::Period) return ".";
    if(Event.key.code == sf::Keyboard::Quote) return "\"";
    if(Event.key.code == sf::Keyboard::RBracket) return "]";
    if(Event.key.code == sf::Keyboard::LBracket) return "[";
    if(Event.key.code == sf::Keyboard::SemiColon) return ";";
    if(Event.key.code == sf::Keyboard::Slash) return "/";
    if(Event.key.code == sf::Keyboard::Subtract) return "-";
    if(Event.key.code == sf::Keyboard::Tab) return "Tab";
    if(Event.key.code == sf::Keyboard::Tilde) return "~";
    if(Event.key.code == sf::Keyboard::Up) return "Up";
    if(Event.key.code == sf::Keyboard::Left) return "Left";
    if(Event.key.code == sf::Keyboard::Down) return "Down";
    if(Event.key.code == sf::Keyboard::Right) return "Right";
    if(Event.key.code == sf::Keyboard::Down) return "Down";
    if(Event.key.code == sf::Keyboard::BackSpace) return "Backspace";
    if(Event.key.code == sf::Keyboard::Delete) return "Delete";
    if(Event.key.code == sf::Keyboard::Return) return "Return";
    if(Event.key.code == sf::Keyboard::Space) return "Space";
    if(Event.key.code == sf::Keyboard::Unknown) return "Unknown";
    if(Event.key.code == sf::Keyboard::F1) return "F1";
    if(Event.key.code == sf::Keyboard::F2) return "F2";
    if(Event.key.code == sf::Keyboard::F3) return "F3";
    if(Event.key.code == sf::Keyboard::F4) return "F4";
    if(Event.key.code == sf::Keyboard::F5) return "F5";
    if(Event.key.code == sf::Keyboard::F6) return "F6";
    if(Event.key.code == sf::Keyboard::F7) return "F7";
    if(Event.key.code == sf::Keyboard::F8) return "F8";
    if(Event.key.code == sf::Keyboard::F9) return "F9";
    if(Event.key.code == sf::Keyboard::F10) return "F10";
    if(Event.key.code == sf::Keyboard::F11) return "F11";
    if(Event.key.code == sf::Keyboard::F12) return "F12";
    if(Event.key.code == sf::Keyboard::F13) return "F13";
    if(Event.key.code == sf::Keyboard::F14) return "F14";
    if(Event.key.code == sf::Keyboard::F15) return "F15";
    return "Unknown";
}

std::string tfp::SfmlEventIDToString(int ID)
{
    if(ID == (int) sf::Keyboard::Q) return "Q";
    if(ID == (int) sf::Keyboard::W) return "W";
    if(ID == (int) sf::Keyboard::E) return "E";
    if(ID == (int) sf::Keyboard::R) return "R";
    if(ID == (int) sf::Keyboard::T) return "T";
    if(ID == (int) sf::Keyboard::Y) return "Y";
    if(ID == (int) sf::Keyboard::U) return "U";
    if(ID == (int) sf::Keyboard::I) return "I";
    if(ID == (int) sf::Keyboard::O) return "O";
    if(ID == (int) sf::Keyboard::P) return "P";
    if(ID == (int) sf::Keyboard::A) return "A";
    if(ID == (int) sf::Keyboard::S) return "S";
    if(ID == (int) sf::Keyboard::D) return "D";
    if(ID == (int) sf::Keyboard::F) return "F";
    if(ID == (int) sf::Keyboard::G) return "G";
    if(ID == (int) sf::Keyboard::H) return "H";
    if(ID == (int) sf::Keyboard::J) return "J";
    if(ID == (int) sf::Keyboard::K) return "K";
    if(ID == (int) sf::Keyboard::L) return "L";
    if(ID == (int) sf::Keyboard::Z) return "Z";
    if(ID == (int) sf::Keyboard::X) return "X";
    if(ID == (int) sf::Keyboard::C) return "C";
    if(ID == (int) sf::Keyboard::V) return "V";
    if(ID == (int) sf::Keyboard::B) return "B";
    if(ID == (int) sf::Keyboard::N) return "N";
    if(ID == (int) sf::Keyboard::M) return "M";
    if(ID == (int) sf::Keyboard::Num0) return "0";
    if(ID == (int) sf::Keyboard::Num1) return "1";
    if(ID == (int) sf::Keyboard::Num2) return "2";
    if(ID == (int) sf::Keyboard::Num3) return "3";
    if(ID == (int) sf::Keyboard::Num4) return "4";
    if(ID == (int) sf::Keyboard::Num5) return "5";
    if(ID == (int) sf::Keyboard::Num6) return "6";
    if(ID == (int) sf::Keyboard::Num7) return "7";
    if(ID == (int) sf::Keyboard::Num8) return "8";
    if(ID == (int) sf::Keyboard::Num9) return "9";
    if(ID == (int) sf::Keyboard::Numpad0) return "0";
    if(ID == (int) sf::Keyboard::Numpad1) return "1";
    if(ID == (int) sf::Keyboard::Numpad2) return "2";
    if(ID == (int) sf::Keyboard::Numpad3) return "3";
    if(ID == (int) sf::Keyboard::Numpad4) return "4";
    if(ID == (int) sf::Keyboard::Numpad5) return "5";
    if(ID == (int) sf::Keyboard::Numpad6) return "6";
    if(ID == (int) sf::Keyboard::Numpad7) return "7";
    if(ID == (int) sf::Keyboard::Numpad8) return "8";
    if(ID == (int) sf::Keyboard::Numpad9) return "9";
    if(ID == (int) sf::Keyboard::Add) return "+";
    if(ID == (int) sf::Keyboard::BackSlash) return "\\";
    if(ID == (int) sf::Keyboard::Comma) return ",";
    if(ID == (int) sf::Keyboard::Dash) return "-";
    if(ID == (int) sf::Keyboard::Divide) return "/";
    if(ID == (int) sf::Keyboard::End) return "End";
    if(ID == (int) sf::Keyboard::Equal) return "=";
    if(ID == (int) sf::Keyboard::Escape) return "Escape";
    if(ID == (int) sf::Keyboard::Home) return "Home";
    if(ID == (int) sf::Keyboard::Insert) return "Insert";
    if(ID == (int) sf::Keyboard::Multiply) return "*";
    if(ID == (int) sf::Keyboard::PageDown) return "PageDown";
    if(ID == (int) sf::Keyboard::PageUp) return "PageUp";
    if(ID == (int) sf::Keyboard::Pause) return "Pause";
    if(ID == (int) sf::Keyboard::Period) return ".";
    if(ID == (int) sf::Keyboard::Quote) return "\"";
    if(ID == (int) sf::Keyboard::RBracket) return "]";
    if(ID == (int) sf::Keyboard::LBracket) return "[";
    if(ID == (int) sf::Keyboard::SemiColon) return ";";
    if(ID == (int) sf::Keyboard::Slash) return "/";
    if(ID == (int) sf::Keyboard::Subtract) return "-";
    if(ID == (int) sf::Keyboard::Tab) return "Tab";
    if(ID == (int) sf::Keyboard::Tilde) return "~";
    if(ID == (int) sf::Keyboard::Up) return "Up";
    if(ID == (int) sf::Keyboard::Left) return "Left";
    if(ID == (int) sf::Keyboard::Down) return "Down";
    if(ID == (int) sf::Keyboard::Right) return "Right";
    if(ID == (int) sf::Keyboard::Down) return "Down";
    if(ID == (int) sf::Keyboard::BackSpace) return "Backspace";
    if(ID == (int) sf::Keyboard::Delete) return "Delete";
    if(ID == (int) sf::Keyboard::Return) return "Return";
    if(ID == (int) sf::Keyboard::Space) return "Space";
    if(ID == (int) sf::Keyboard::Unknown) return "Unknown";
    if(ID == (int) sf::Keyboard::F1) return "F1";
    if(ID == (int) sf::Keyboard::F2) return "F2";
    if(ID == (int) sf::Keyboard::F3) return "F3";
    if(ID == (int) sf::Keyboard::F4) return "F4";
    if(ID == (int) sf::Keyboard::F5) return "F5";
    if(ID == (int) sf::Keyboard::F6) return "F6";
    if(ID == (int) sf::Keyboard::F7) return "F7";
    if(ID == (int) sf::Keyboard::F8) return "F8";
    if(ID == (int) sf::Keyboard::F9) return "F9";
    if(ID == (int) sf::Keyboard::F10) return "F10";
    if(ID == (int) sf::Keyboard::F11) return "F11";
    if(ID == (int) sf::Keyboard::F12) return "F12";
    if(ID == (int) sf::Keyboard::F13) return "F13";
    if(ID == (int) sf::Keyboard::F14) return "F14";
    if(ID == (int) sf::Keyboard::F15) return "F15";
    return "Unknown";
}


float tfp::VectorLength(float a, float b)
{
    /*if(a < 0) a = -a;
    if(b < 0) b = -b;*/
    float Length = std::sqrt(std::pow(a, 2) + std::pow(b, 2));
    return Length;
}

float tfp::VectorLength(sf::Vector2f Vector)
{
    /*if(Vector.x < 0) Vector.x = -Vector.x;
    if(Vector.y < 0) Vector.y = -Vector.y;*/
    float Length = std::sqrt(std::pow(Vector.x, 2) + std::pow(Vector.y, 2));
    return Length;
}

sf::Vector2f tfp::NormalizeVector(sf::Vector2f Vector)
{
    float VectorLength = tfp::VectorLength(Vector);
    if(VectorLength != 0)
    {
        Vector.x /= VectorLength;
        Vector.y /= VectorLength;
    }
    return Vector;
}
