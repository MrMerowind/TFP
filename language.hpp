/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef LANGUAGE_HPP_INCLUDED
#define LANGUAGE_HPP_INCLUDED

namespace tfp
{

    class LanguageClass
    {
    private:
        bool Loaded;
        std::wstring LanguageName;
        std::string LanguageLocale;
        struct DictionaryWord
        {
            std::wstring Word;
            std::wstring Translation;
            /// Konstruktor
            DictionaryWord(std::wstring Word, std::wstring Translation);
        };
        std::vector<DictionaryWord> Dictionary;
    public:
        std::vector<std::string> LanguageNameList;
    public:
        /// Konstruktor
        LanguageClass();
        /// Destruktor
        ~LanguageClass();
        /// Wczytuje slownik z podanym jezykiem
        const bool LoadDictionary(std::wstring LanguageName);
        /// Czysci slownik
        void UnloadDictionary();
        /// Tlumaczy tekst na wybrany jezyk
        std::wstring Translate(std::string Text);
        /// Wczytuje informacje o kodowaniu
        bool LoadLocale(std::string Language);
        /// Ustawia informacje o kodowaniu ponownie
        void ResetLocale();

    };
}


#endif // LANGUAGE_HPP_INCLUDED
