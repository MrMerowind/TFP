/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef SERVER_HPP_INCLUDED
#define SERVER_HPP_INCLUDED

namespace tfp
{
    class NetworkServer
    {
    public:
        struct ClientNode
        {
            unsigned short ClientPort;
            sf::IpAddress ClientIp;
            int ClientId;
            bool ClientConnected;
            time_t ClientLastCommandTime;
        };
    private:
        tfp::Game *GameHandle;
        float Timeout;
        bool TurnOn;

        int FreeId;
        unsigned short ServerPort;
        sf::IpAddress ServerIp;
        sf::UdpSocket ServerSocket;
        sf::Thread ServerThread;
        // std::queue<std::string> ReceivedCommands;
        std::queue<std::string> CommandsToSend;
        char Buffer[1024];

        /// Communication with clients
        void ServerLoop();
        void MobMovement();
        void RandomCheatCheck();
        void RunCommands();
        void SendCommands();
        void ReadCommand(std::string Command, sf::IpAddress Ip, unsigned short Port);

        /// Game data
        std::vector<tfp::NetworkServer::ClientNode> ClientList;
        std::vector<tfp::Map> MapList;
        std::vector<tfp::Player> PlayerList;


    public:
        /// Constructor
        NetworkServer();
        /// Destructor
        ~NetworkServer();
        /// Set game handle
        void SetGameHandle(tfp::Game *GameHandle);
        /// Starts server in a new thread
        void Run(sf::IpAddress ServerIp, int ServerPort);
        /// Stops server thread
        void Stop();
        /// Sends command to a server
        void SendCommandToClients(std::string Command, int Id = -1);
        /// Gets server ip
        sf::IpAddress &GetServerIp();
        /// Gets server port
        unsigned short &GetServerPort();
        /// Returns if server is on
        bool IsTurnOn();
        //// Zwraca liste podlaczonych klientow
        std::vector<tfp::NetworkServer::ClientNode> &GetClientList();


    };
}


#endif // SERVER_HPP_INCLUDED
