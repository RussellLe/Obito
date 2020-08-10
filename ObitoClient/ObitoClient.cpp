#include "client_context.h"
#include <iostream>
#include <string>


int socketClientScript()
{
    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA data;
    if (WSAStartup(sockVersion, &data) != 0) return 0;

    while (true)
    {
        SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sclient == INVALID_SOCKET)
        {
            printf("invalid socket!");
            return 0;
        }

        sockaddr_in serAddr;//处理服务端地址的结构，包含地址族、端口、ip地址
        serAddr.sin_family = AF_INET;//IP地址族
        serAddr.sin_port = htons(8888);//服务端端口
        serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//服务端ip

        if (connect(sclient, (sockaddr*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
        {
            printf("connect error !");
            closesocket(sclient);
            return 0;
        }

        //发送数据
        std::string sendData;
        std::cin >> sendData;
        send(sclient, sendData.c_str(), strlen(sendData.c_str()), 0);

        //接收数据
        char recData[255];
        int ret = recv(sclient, recData, 255, 0);
        if (ret > 0) {
            recData[ret] = '\0';
            printf(recData);
        }
        closesocket(sclient);
    }

    WSACleanup();
}


int main()
{
    obito::client::ClientContext client("127.0.0.1",8888);
    std::string command;
    while (std::getline(std::cin, command))
    {
        client.sendCommand(command);
    }
    return 0;
}