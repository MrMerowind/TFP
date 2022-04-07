/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"

tfp::NetworkClient::NetworkClient()
    :GameHandle(nullptr), ServerPort(0), ServerIp("localhost"), Connected(false), ClientId(-1), ClientThread(&ClientLoop, this), LastSendCommand(tfp::Seconds()) {}

tfp::NetworkClient::~NetworkClient()
{
    if(Connected == true)
        Debug.Info("NetworkClient: Stopping client");
    Connected = false;
    ClientThread.wait();
}

void tfp::NetworkClient::ClientLoop()
{
    ClientSocket.bind(sf::Socket::AnyPort, sf::IpAddress::Broadcast);
    Connected = true;
    Debug.Info("NetworkClient: Client started");
    while(true)
    {
        if(Connected == false)
        {
            while(!CommandsToSend.empty())
                CommandsToSend.pop();

            break;
        }
        if(GameHandle == nullptr)
        {
            Debug.Warning("NetworkClient: Game handle not set. Disconnecting.");
            Connected = false;
            break;
        }

        ClientActions();

        ClientSocket.setBlocking(false);
        std::size_t Received = 0;
        sf::IpAddress SenderIp;
        unsigned short SenderPort;
        if(ClientSocket.receive(Buffer, (std::size_t) 1000, Received, SenderIp, SenderPort) == sf::Socket::Status::Done);
        {
            if(SenderIp.toString() == "0.0.0.0");
            else if(SenderIp == ServerIp)
            {
                if(SenderPort != ServerPort)
                {
                    Debug.Warning("NetworkClient: Received command from different port. Changing port to: " + tfp::IntToString(SenderPort));
                    ServerPort = SenderPort;
                }
                GameHandle->GameCommandBlock.RunCommand(Buffer);
            }
            else
            {
                Debug.Warning("NetworkClient: Received command from unknown server: " + SenderIp.toString() + ":" +  tfp::IntToString(SenderPort) + " ("  + Buffer + ")");
            }
        }
        ClientSocket.setBlocking(true);
        while(!CommandsToSend.empty())
        {
            ClientSocket.send(CommandsToSend.front().c_str(), CommandsToSend.front().size() + 1, ServerIp, ServerPort);
            CommandsToSend.pop();
        }
        sf::sleep(sf::milliseconds(100));

    }
    ClientSocket.unbind();
    Debug.Info("NetworkClient: Client stopped");
}

void tfp::NetworkClient::SetGameHandle(tfp::Game *GameHandle_)
{
    GameHandle = GameHandle_;
}

void tfp::NetworkClient::Run(std::string ServerIp_, int ServerPort_)
{
    ServerIp = ServerIp_;
    ServerPort = ServerPort_;
    Debug.Info("NetworkClient: Connecting client to " + ServerIp.toString() + ':' + tfp::IntToString(ServerPort));
    ClientThread.launch();
}

void tfp::NetworkClient::Run(tfp::NetworkServer &ReferenceServer)
{
    ServerIp = ReferenceServer.GetServerIp();
    ServerPort = ReferenceServer.GetServerPort();
    Debug.Info("NetworkClient: Connecting client to " + ServerIp.toString() + ':' + tfp::IntToString(ServerPort));
    ClientThread.launch();
}

void tfp::NetworkClient::Stop()
{
    Connected = false;
    Debug.Info("NetworkClient: Stopping client");
}

void tfp::NetworkClient::SendCommandToServer(std::string Command)
{
    CommandsToSend.push(Command);
    LastSendCommand = tfp::Seconds();
}

void tfp::NetworkClient::ClientActions()
{
    /// Handshake (initializing connection)
    if(ClientId == -1)
    {
        ClientId = -2;
        SendCommandToServer("newplayer");
        return;
    }
    if(ClientId == -2)
    {
        if(LastSendCommand < tfp::Seconds() - 10) ClientId = -1;
        return;
    }

    /// Sending statistics



    /// Downloading map



    /// Sending information about movement and actions

}

void tfp::NetworkClient::SetClientId(int ClientId_)
{
    ClientId = ClientId_;
    Connected = true;
}

bool tfp::NetworkClient::IsConnected()
{
    if(ClientId >= 0 && Connected) return true;
    else return false;
}
