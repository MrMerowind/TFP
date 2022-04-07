/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"


tfp::NetworkServer::NetworkServer()
    :GameHandle(nullptr), Timeout(50.0f), TurnOn(false), FreeId(0), ServerThread(&ServerLoop, this) {}

tfp::NetworkServer::~NetworkServer()
{
    if(TurnOn == true)
        Debug.Info("NetworkServer: Stopping server");
    TurnOn = false;
    ServerThread.wait();
}

void tfp::NetworkServer::SetGameHandle(tfp::Game *GameHandle_)
{
    GameHandle = GameHandle_;
}


sf::IpAddress &tfp::NetworkServer::GetServerIp()
{
    return ServerIp;
}

unsigned short &tfp::NetworkServer::GetServerPort()
{
    return ServerPort;
}

void tfp::NetworkServer::Run(sf::IpAddress ServerIp_, int ServerPort_)
{
    if(TurnOn)
    {
        Debug.Warning("Server is already running");
        return;
    }
    ServerIp = ServerIp_;
    ServerPort = ServerPort_;
    Debug.Info("NetworkClient: Running server on " + ServerIp.toString() + ":" + tfp::IntToString(ServerPort));
    ServerThread.launch();
}

void tfp::NetworkServer::Stop()
{
    if(!TurnOn)
    {
        Debug.Warning("Server is already stopped");
        return;
    }
    Debug.Info("NetworkServer: Stopping server");
    TurnOn = false;
}

void tfp::NetworkServer::SendCommandToClients(std::string Command, int Id)
{
    if(Id == -1)
    {
        CommandsToSend.push(Command);
    }
    else
    {
        for(unsigned i = 0; i < ClientList.size(); i++)
        {
            if(ClientList[i].ClientId == Id)
            {
                ServerSocket.setBlocking(true);
                ServerSocket.send(Command.c_str(), Command.size() + 1, ClientList[i].ClientIp, ClientList[i].ClientPort);
                break;
            }
        }
    }

}

bool tfp::NetworkServer::IsTurnOn()
{
    return TurnOn;
}

std::vector<tfp::NetworkServer::ClientNode> &tfp::NetworkServer::GetClientList()
{
    return ClientList;
}

void tfp::NetworkServer::ServerLoop()
{
    sf::Socket::Status ServerSocketStatus;
    if(ServerPort != 0) ServerSocketStatus = ServerSocket.bind(ServerPort, ServerIp);
    else
    {
        ServerSocketStatus = ServerSocket.bind(sf::Socket::AnyPort, ServerIp);
        ServerPort = ServerSocket.getLocalPort();
    }

    if(ServerSocketStatus == sf::Socket::Status::Error)
    {
        Debug.Warning("NetworkServer: Can not bind to a port " + tfp::IntToString(ServerPort));
        return;
    }
    TurnOn = true;
    Debug.Info("NetworkServer: Server started");
    while(TurnOn)
    {
        if(TurnOn == false)
        {
            while(!CommandsToSend.empty())
                CommandsToSend.pop();
            break;
        }
        if(GameHandle == nullptr)
        {
            Debug.Warning("NetworkServer: Game handle not set. Stopping server.");
            TurnOn = false;
            break;
        }
        RunCommands();
        MobMovement();
        RandomCheatCheck();

        ServerSocket.setBlocking(false);
        std::size_t Received = 0;
        sf::IpAddress SenderIp;
        unsigned short SenderPort;
        if(ServerSocket.receive(Buffer, (std::size_t) 1000, Received, SenderIp, SenderPort) == sf::Socket::Status::Done);
        {
            if(SenderIp.toString() != "0.0.0.0")
                ReadCommand(Buffer, SenderIp, SenderPort);
        }
        ServerSocket.setBlocking(true);
        while(!CommandsToSend.empty())
        {
            for(unsigned  i = 0; i < ClientList.size(); i++)
            {
                ServerSocket.send(CommandsToSend.front().c_str(), CommandsToSend.front().size() + 1, ClientList[i].ClientIp, ClientList[i].ClientPort);
            }
            CommandsToSend.pop();
        }
        sf::sleep(sf::milliseconds(100));


    }
    ServerSocket.unbind();
    Debug.Info("NetworkServer: Server stopped");
}

void tfp::NetworkServer::ReadCommand(std::string Command, sf::IpAddress Ip, unsigned short Port)
{
    for(unsigned i = 0; i < ClientList.size(); i++)
    {
        if(ClientList[i].ClientIp == Ip && ClientList[i].ClientPort == Port)
        {
            ClientList[i].ClientLastCommandTime = tfp::Seconds();
        }
    }

    if(Command == "");
    else if(tfp::SplitString(Command, 0, ' ', false) == "newplayer")
    {
        bool Exist = false;
        for(unsigned i = 0; i < ClientList.size(); i++)
        {
            if(ClientList[i].ClientIp == Ip && ClientList[i].ClientPort == Port)
            {
                SendCommandToClients("setclientid " + tfp::IntToString(ClientList[i].ClientId), ClientList[i].ClientId);
                Exist = true;
                break;
            }
        }

        if(!Exist)
        {
            tfp::NetworkServer::ClientNode TmpClientNode;
            TmpClientNode.ClientConnected = true;
            TmpClientNode.ClientId = FreeId++;
            TmpClientNode.ClientIp = Ip;
            TmpClientNode.ClientPort = Port;
            TmpClientNode.ClientLastCommandTime = tfp::Seconds();
            ClientList.push_back(TmpClientNode);
            SendCommandToClients("setclientid " + tfp::IntToString(TmpClientNode.ClientId), TmpClientNode.ClientId);

            Debug.Info("NetworkServer: New player " + Ip.toString() + ":" + tfp::IntToString(Port));
        }

    }
}

void tfp::NetworkServer::MobMovement()
{

}

void tfp::NetworkServer::RandomCheatCheck()
{

}

void tfp::NetworkServer::RunCommands()
{

}
