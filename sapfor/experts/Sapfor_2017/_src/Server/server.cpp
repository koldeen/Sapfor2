#include <thread>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <ws2tcpip.h>
// link with Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

int initServer(SOCKET& listenSocket, const string& address, int port)
{
    WSADATA wsaData = { 0 };
    int resultc = WSAStartup(MAKEWORD(2, 0), &wsaData);
    if (resultc != 0)
    {
        printf("result of WSAStartup is %d\n", resultc);
        return 1;
    }

    addrinfo* result = NULL, * ptr = NULL, hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    int iResult = getaddrinfo(address.c_str(), to_string(port).c_str(), &hints, &result);
    if (iResult != 0)
    {
        cout << "Ошибка getaddrinfo: " << iResult;
        WSACleanup();
        return 1;
    }

    listenSocket = INVALID_SOCKET;
    listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (listenSocket == INVALID_SOCKET)
    {
        cout << "Error at socket(): " << WSAGetLastError();
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    iResult = bind(listenSocket, result->ai_addr, result->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        cout << "Bind failed with error: " << WSAGetLastError();
        freeaddrinfo(result);
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        cout << "Listen failed with error: " << WSAGetLastError();
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    return 0;
}

static int initClient(SOCKET& javaSocket, const string& address, int port)
{
    javaSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (javaSocket == INVALID_SOCKET)
    {
        printf("[SERVER] Wrnog java socket\n");
        return -1;
    }

    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr(address.c_str());
    clientService.sin_port = htons(port);
    int result = connect(javaSocket, (SOCKADDR*)(&clientService), sizeof(clientService));

    if (result != 0)
        printf("[SERVER] Error %d of connect to socket %s:%d\n", WSAGetLastError(), address.c_str(), port);

    return result;
}

static void runSapfor(const string command)
{
    int id = system(command.c_str());
    printf("[SERVER-th1] sapfor done with exit code %d\n", id);
}

static string utf8_encode(const wstring& wstr)
{
    if (wstr.empty())
        return string();

    int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
    string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
    return strTo;
}

static wstring utf8_decode(const string& str)
{
    if (str.empty())
        return wstring();

    int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), NULL, 0);
    wstring wstr;
    wstr.resize(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), &wstr[0], size_needed);
    return wstr;
}

int main()
{
    SOCKET serverSoc, javaSoc;
    if (initServer(serverSoc, "127.0.0.1", 8889) != 0) // create server for Sapfor
        return -1;

    const int countOfTry = 15;
    char *buf = new char[10000];
    int err;
    while (true)
    {
        int t = 0;
        while (initClient(javaSoc, "127.0.0.1", 8890) != 0) // connect to JAVA
        {
            ++t;
            if (t == countOfTry)
            {
                printf("[SERVER] can not connect to JAVA, exit\n");
                exit(1);
            }
            Sleep(500);
        }

        while (javaSoc != INVALID_SOCKET)
        {
            thread sapfor(runSapfor, string("Sapfor_F.exe -client"));
            sapfor.detach();

            SOCKET ClientSocket = INVALID_SOCKET;
            ClientSocket = accept(serverSoc, NULL, NULL);

            if (ClientSocket != INVALID_SOCKET)
                printf("[SERVER] sapfor connected\n");

            while (ClientSocket != INVALID_SOCKET)
            {
                string command = "";
                err = recv(javaSoc, buf, 10000, 0);
                if (err <= 0)
                {
                    printf("[SERVER] error recv from java\n");
                    closesocket(javaSoc);
                    closesocket(ClientSocket);
                    break;
                }
                else
                {
                    buf[err] = '\0';
                    command = buf;
                    if (command == "restart: ")
                    {
                        printf("[SERVER] restart sapfor\n");
                        closesocket(ClientSocket);
                        break;
                    }
                    else if (command == "close: ")
                    {
                        printf("[SERVER] shutdown\n");
                        closesocket(ClientSocket);
                        closesocket(javaSoc);

                        Sleep(500);
                        exit(0);
                        break;
                    }
                }

                err = send(ClientSocket, command.c_str(), command.size(), 0);
                if (err != command.size())
                {
                    printf("[SERVER] error send\n");
                    closesocket(ClientSocket);
                }
                
                string retCode = "";
                err = recv(ClientSocket, buf, 10000, 0);
                if (err <= 0)
                {
                    printf("[SERVER] error recv\n");
                    closesocket(ClientSocket);
                }
                else
                {
                    buf[err] = '\0';
                    retCode = buf;
                    if (retCode == "WRONG")
                    {
                        printf("[SERVER] WRONG recv\n");
                        closesocket(ClientSocket);
                    }
                }

                err = send(javaSoc, retCode.c_str(), retCode.size(), 0);
                if (err != retCode.size())
                {
                    printf("[SERVER] error send to java\n");
                    closesocket(ClientSocket);
                    closesocket(javaSoc);
                    closesocket(ClientSocket);
                    break;
                }
            }
            printf("[SERVER] invalid sapfor socket, try to restart next\n");
            Sleep(500);
        }
    }
    return 0;
}

