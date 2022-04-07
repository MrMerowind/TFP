/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"

tfp::LanguageClass::LanguageClass()
{
    std::locale::global(std::locale(""));
    setlocale(LC_ALL, ".1252");
    LanguageName = L"English";
    Loaded = false;
    std::wstring Line;
    std::wfstream ConfigFile;
    ConfigFile.open("Config/Language.config", std::ios::in);
    if(ConfigFile.good())
    {
        while(!ConfigFile.eof())
        {
            getline(ConfigFile,Line);
            if(Line == L"");
            else if(Line[0] == '#');
            else if(tfp::SplitString(Line,0) == L"Language")
            {
                LanguageName = tfp::SplitString(Line,1);
            }
            else
            {
                Debug.Warning("Unknown line in Config/Language.config: " + tfp::WStringToString(Line));
            }
        }
        ConfigFile.close();
    }
    else
    {
        Debug.Warning("Can not load Config/Language.config");
    }

    LoadDictionary(LanguageName);

    std::fstream ConfigFile2;
    std::string Line2;

    ConfigFile2.open("Language/Locale.config", std::ios::in);
    if(ConfigFile2.good())
    {
        while(!ConfigFile2.eof())
        {
            getline(ConfigFile2,Line2);
            if(Line2 == "");
            else if(Line2[0] == '#');
            else
            {
                LanguageNameList.push_back(tfp::SplitString(Line2,0));
            }
        }
        ConfigFile2.close();
    }
    else
    {
        Debug.Warning("Can not load Language/Locale.config");
    }

}

tfp::LanguageClass::~LanguageClass()
{
    UnloadDictionary();
}

tfp::LanguageClass::DictionaryWord::DictionaryWord(std::wstring Word_, std::wstring Translation_)
{
    Word = Word_;
    Translation = Translation_;
}

bool tfp::LanguageClass::LoadLocale(std::string Language)
{
    Language[0] = std::toupper(Language[0]);
    std::string Line;
    std::fstream ConfigFile;
    ConfigFile.open("Language/Locale.config", std::ios::in);
    if(ConfigFile.good())
    {
        while(!ConfigFile.eof())
        {
            getline(ConfigFile,Line);
            if(Line[0] == '#');
            else if(Line == "");
            else if(tfp::SplitString(Line,0) == Language)
            {
                std::string LocaleIdentifier = tfp::SplitString(Line,1);
                LanguageLocale = LocaleIdentifier;
                setlocale(LC_ALL, LocaleIdentifier.c_str());
                Debug.Info("Loaded locale for: " + Language + " (" + LocaleIdentifier + ")");
                ConfigFile.close();
                return true;
            }
        }
        Debug.Info("Missing Locale for: " + Language + " in Language/Locale.config");
        ConfigFile.close();
        return false;
    }
    else
    {
        Debug.Warning("Can not load Language/Locale.config");
        return false;
    }
}

const bool tfp::LanguageClass::LoadDictionary(std::wstring LanguageName_)
{
    std::wstring PreviousLanguage = LanguageName;
    UnloadDictionary();

    if(LanguageName_ == L"") return false;
    LanguageName = LanguageName_;
    std::wstring DictionaryFileName = L"Language/" + LanguageName_ + L".lang";

    if(!LoadLocale(tfp::WStringToString(LanguageName_)))
    {
        return false;
    }

	rapidxml::xml_document<wchar_t> DictionaryXmlDocument;
	rapidxml::xml_node<wchar_t> * RootNode;
	std::wifstream DictionaryXmlFile (tfp::WStringToString(DictionaryFileName));
	if(!DictionaryXmlFile.good())
    {
        Debug.Warning("Can not load language: " + tfp::WStringToString(LanguageName_));
        if(PreviousLanguage != LanguageName) LoadDictionary(PreviousLanguage);
        return false;
    }
	std::vector<wchar_t> Buffer((std::istreambuf_iterator<wchar_t>(DictionaryXmlFile)), std::istreambuf_iterator<wchar_t>());
	Buffer.push_back(L'\0');
	DictionaryXmlDocument.parse<0>(&Buffer[0]);
    RootNode = DictionaryXmlDocument.first_node(L"dictionary");

    rapidxml::xml_node<wchar_t> *TranslationNode;
    TranslationNode = RootNode->first_node(L"translation");
    while(TranslationNode != 0)
    {
        Dictionary.push_back(DictionaryWord(TranslationNode->first_attribute(L"original")->value(),TranslationNode->value()));
        TranslationNode = TranslationNode->next_sibling();
    }

    Debug.Info("Dictionary loaded");
    Loaded = true;
    /// Zapisywanie wybranego jezyka
    std::fstream LanguageConfig;
    LanguageConfig.open("Config/Language.config", std::ios::out);
    if(LanguageConfig.good())
    {
        LanguageConfig << "Language: " << tfp::WStringToString(LanguageName);
        LanguageConfig.close();
    }
    else
    {
        Debug.Warning("Can not open Config/Language.config");
    }

    return true;
}

void tfp::LanguageClass::UnloadDictionary()
{
    if(Loaded == false) return;
    Dictionary.clear();
    Loaded = false;
    Debug.Info("Dictionary unloaded");
}

std::wstring tfp::LanguageClass::Translate(std::string Text)
{
    /// Sprawdzanie czy zawiera litery
    bool ContainLetters = false;
    for(unsigned i = 0; i < Text.size(); i++)
    {
        if((Text[i] >= 'a' && Text[i] <= 'z') || (Text[i] >= 'A' && Text[i] <= 'Z'))
        {
            if(Text[i] == 'x' || Text[i] == 'X') continue;
            ContainLetters = true;
            break;
        }
    }
    if(!ContainLetters) return tfp::StringToWString(Text);

    /// Jesli zawiera litery to tlumaczymy
    for(unsigned i = 0; i < Dictionary.size(); i++)
    {
        if(Dictionary[i].Word == tfp::StringToWString(Text))
        {
            return Dictionary[i].Translation;
        }
    }
    Debug.Warning("Missing (" + tfp::WStringToString(LanguageName) + ") translation of: " + Text);
    Dictionary.push_back(DictionaryWord(tfp::StringToWString(Text), tfp::StringToWString(Text)));
    return tfp::StringToWString(Text);
}

void tfp::LanguageClass::ResetLocale()
{
    setlocale(LC_ALL, LanguageLocale.c_str());
}
