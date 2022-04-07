/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef CLIENT_HPP_INCLUDED
#define CLIENT_HPP_INCLUDED

namespace tfp
{
    class NetworkClient
    {
    private:
        tfp::Game *GameHandle;
        unsigned short ServerPort;
        sf::IpAddress ServerIp;
        bool Connected;
        int ClientId;
        sf::UdpSocket ClientSocket;
        sf::Thread ClientThread;
        // std::queue<std::string> ReceivedCommands;
        std::queue<std::string> CommandsToSend;
        char Buffer[1024];
        time_t LastSendCommand;

        /// Communication with a server
        void ClientLoop();
        /// Prepares commands for a server
        void ClientActions();
    public:
        /// Constructor
        NetworkClient();
        /// Destructor
        ~NetworkClient();
        /// Set game handle
        void SetGameHandle(tfp::Game *GameHandle);
        /// Starts client in a new thread
        void Run(std::string ServerIp, int ServerPort);
        /// Starts client in a new thread with a given server
        void Run(tfp::NetworkServer &ReferenceServer);
        /// Stops client thread
        void Stop();
        /// Sends command to a server
        void SendCommandToServer(std::string Command);
        /// Sets client ID
        void SetClientId(int ClientId);
        /// Return if client is connected to a server
        bool IsConnected();

    };
}


#endif // CLIENT_HPP_INCLUDED
