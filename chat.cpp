#include "includes.hpp"
#include "globalobjects.hpp"

tfp::Chat::Chat()
    :GameHandle(nullptr), ClearChat(false) {}

tfp::Chat::~Chat() {}

void tfp::Chat::DrawChat()
{
    if(GameHandle == nullptr)
    {
        Debug.Warning("Chat: Game handle not set");
        return;
    }
    if(ClearChat)
    {
        ClearChat = false;
        ChatInput.Area.SetText("");
    }
    if(!ChatInput.Area.IsActive() && ChatInput.Area.GetText() != "") SendMessage();

    std::wstring TranslatedText = /*Language.Translate("Press") +*/ L"'" + tfp::StringToWString(KeyConfig.GetActionInString("OpenChat")) + L"' " + Language.Translate("opens chat");
    ChatInput.SetTranslatedPlaceHolder(TranslatedText);
    ChatInput.Display();
}

void tfp::Chat::SetGameHandle(tfp::Game *Handle)
{
    GameHandle = Handle;
    ChatInput.SetGameHandle(Handle);
    ChatInput.SetPosition(0.0f, 3275.0f);
    ChatInput.SetSize(2000.0f ,100.0f, true);
    ChatInput.SetInputType(tfp::TextType::TextTypeString);
    ChatInput.SetMaxCharacters(47);
    ChatInput.Area.SetTextMaxLength(100);
}

void tfp::Chat::SendMessage()
{
    GameHandle->GameNetworkClient.SendCommandToServer("say " + tfp::IntToString(GameHandle->ControlledPlayer.GetID()) + " " + ChatInput.Area.GetText());
    ChatInput.Area.SetText("");
}

void tfp::Chat::OpenChat()
{
    ChatInput.Area.SetActive(true);
    ClearChat = true;
}
