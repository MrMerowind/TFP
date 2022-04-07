#ifndef CHAT_HPP_INCLUDED
#define CHAT_HPP_INCLUDED

namespace tfp
{

    class Chat
    {
    private:
        std::vector<std::string> ChatList;
        tfp::Game *GameHandle;
        bool ClearChat;
    public:
        tfp::InputBar ChatInput;
    public:
        Chat();
        ~Chat();
        void DrawChat();
        void SetGameHandle(tfp::Game *Handle);
        void SendMessage();
        void OpenChat();
    };
}

#endif // CHAT_HPP_INCLUDED
