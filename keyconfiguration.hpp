/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef KEYCONFIGURATION_HPP_INCLUDED
#define KEYCONFIGURATION_HPP_INCLUDED

namespace tfp
{

    class KeyConfigClass
    {
    public:
        struct Node
        {
            int KeyCode;
            bool KeySystem;
            bool KeyAlt;
            bool KeyShift;
            bool KeyControl;
            std::string ActionName;
        };
    private:
        std::vector<tfp::KeyConfigClass::Node> KeyConfigList;

    public:
        KeyConfigClass();
        ~KeyConfigClass();
        void LoadDefaultConfig();
        void LoadUserConfig();
        void SaveUserConfig();
        void UnloadConfig();
        void SetAction(std::string Action, sf::Event &KeyCombination);
        void SetAction(std::string Action, int Code, bool Shift, bool Alt, bool Control, bool System);
        std::string GetActionInString(std::string Action);
        bool IsKeyEventEqual(std::string Name, sf::Event &Event);
        std::vector<tfp::KeyConfigClass::Node> &GetKeyConfigList();
    };
}

#endif // KEYCONFIGURATION_HPP_INCLUDED
