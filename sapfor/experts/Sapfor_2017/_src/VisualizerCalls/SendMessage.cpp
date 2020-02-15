#include <string>
#include <vector>
#include "SendMessage.h"
#include <iostream>

using std::wstring;
using std::string;
using std::vector;

static int decodeMessage(const string& message, vector<string>& pars, int &winH, int countPars)
{
    int sI = 0;
    for (int z = 0; z < countPars; ++z)
    {
        string d = "";
        for ( ;sI != message.size() && message[sI] != ' '; ++sI)
            d += message[sI];        
        if (sI == message.size())
            return -1;
        ++sI;

        int countElems = -1;
        if (sscanf(d.c_str(), "%d", &countElems) != 1)
            return -2;

        string par = "";

        for (z = 0; sI != message.size() && z < countElems; ++z, ++sI)
            par += message[sI];
        if (sI == message.size())
            return -3;
        pars.push_back(par);
    }

    string d = "";
    for (; sI != message.size() && message[sI] != ' '; ++sI)
        d += message[sI];
    if (sscanf(d.c_str(), "%d", &winH) != 1)
        return -4;

    return 0;
}

#ifdef WIN32
#include <Windows.h>
#include <winsock.h>

#include "../Utils/utils.h"
#include "get_information.h"

// link with Ws2_32.lib
#pragma comment(lib,"Ws2_32.lib")

void sendMessage_1lvl(const wstring& toSend) { MessageManager::sendFirstLvl(toSend); }
void sendMessage_2lvl(const wstring& toSend) { MessageManager::sendSecondLvl(toSend); }
void sendMessage_progress(const wstring& toSend) { MessageManager::sendProgress(toSend); }


#define WM_USER        0x0400 //сообщения для обработчика сообщений
#define STATUS_MESSAGE WM_USER + 16

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

static SOCKET clientSocket = INVALID_SOCKET;

static int connectAndCreate(SOCKET &socket_t, string address, int port)
{
    socket_t = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_t == INVALID_SOCKET)
    {
        printf("Wrong  socket\n");
        return -1;
    }

    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr(address.c_str());
    clientService.sin_port = htons(port);
    int result = connect(socket_t, (SOCKADDR*)(&clientService), sizeof(clientService));

    if (result != 0)
    {
        printf("Wrong connect to socket %d\n", WSAGetLastError());
        return -1;
    }
    return 0;
}

void MessageManager::sendProgress(const std::wstring& str)
{
    if (WinHandler == -2) // to JAVA
    {
        string result = utf8_encode(L"progress:" + str + L"\n");
        const char* ret = result.c_str();

        int size = result.size();
        int iResult = send(clientSocket, ret, size, 0);
        if (iResult == SOCKET_ERROR)
            printf("Wrong send is %d\n", iResult);
    }
}

void MessageManager::sendMessage(const wstring& toSend)
{
    if (WinHandler > 0)
    {
        cachedMessages.push_back(toSend);
        PostMessage((HWND)WinHandler, STATUS_MESSAGE, (WPARAM)(cachedMessages.back().c_str()), (LPARAM)cachedMessages.back().size());
    }
    else if (WinHandler == -2) // to JAVA
    {        
        vector<wstring> splited;
        splitString(toSend, '\n', splited);
        
        int i = 1;
        for (auto& elem : splited)
        {
            string result = utf8_encode(L"message_" + std::to_wstring(i++) + L":" + elem + L"\n");
            const char* ret = result.c_str();

            int size = result.size();
            int iResult = send(clientSocket, ret, size, 0);
            if (iResult == SOCKET_ERROR)
                printf("Wrong send is %d\n", iResult);
        }
    }
}

void MessageManager::setWinHandler(const int winH) 
{
    if (winH == -2) // to JAVA
    {
        if (MessageManager::init() != 0)
        {
            WinHandler = -1;
            return;
        }

        if (connectAndCreate(clientSocket, "127.0.0.1", 8888) != 0)
        {
            WinHandler = -1;
            return;
        }
    }
    else if (winH == -1 && WinHandler == -2) // close JAVA
    {
        if (Started == 0)
        {
            Sleep(100);
            closesocket(clientSocket);
            clientSocket == INVALID_SOCKET;
        }
    }
    WinHandler = winH;
}

int MessageManager::init()
{
    if (Started == -1)
    {
        WSADATA wsaData = { 0 };
        int result = WSAStartup(MAKEWORD(2, 0), &wsaData);
        if (result != 0)
        {
            printf("Wrong WSAStartup is %d\n", result);
            Started = -2;
        }
        else
            Started = 0;
    }
    return Started;
}

vector<wstring> MessageManager::cachedMessages = vector<wstring>();
int MessageManager::WinHandler = -1;
wstring MessageManager::firstLvlMessage = L"";
wstring MessageManager::secondLvlMessage = L"";

#undef WM_USER
#undef STATUS_MESSAGE

static int send(SOCKET &client, const wstring& message)
{
    string result = utf8_encode(message);
    int err = send(client, result.c_str(), result.size(), 0);
    if (err != result.size())
    {
        printf("[CLIENT] wrong send: %d\n", err); // exit
        return -1;
    }
    else
        return 0;
}

void RunSapforAsClient()
{
    if (MessageManager::init() != 0)
        return;

    SOCKET client = INVALID_SOCKET;
    if (connectAndCreate(client, "127.0.0.1", 8889) != 0)
        return;
 
    char* buf = new char[4096];
    wstring result;
    while (true)
    {        
        int count = recv(client, buf, 4096, 0);
        if (count > 0)
        {
            buf[count] = '\0';
            string message = buf;
            string code;

            int z = 0;
            for (; z < message.size(); ++z)
            {
                if (message[z] == ':')
                {
                    z++;
                    break;
                }
                else
                    code += message[z];
            }

            if (z == message.size()) // wrong message
            {
                printf("[CLIENT] wrong messages: %s\n", message.c_str());

                int err = send(client, L"WRONG");
                if (err != 0)
                    break;
                continue;
            }

            message = message.substr(z);
            

            vector<string> pars;
            int winHandler = -1;

            if (code == "analysis")
            {
                int err = decodeMessage(message, pars, winHandler, 3);
                if (err == 0)
                    result = Sapfor_RunAnalysis(pars[0].c_str(), pars[1].c_str(), pars[2].c_str(), winHandler);
                else
                    result = Sapfor_RunAnalysis(NULL, NULL, NULL, -1);
            }
            else if (code == "transformation")
            {
                int err = decodeMessage(message, pars, winHandler, 5);
                if (err == 0)
                    result = Sapfor_RunTransformation(pars[0].c_str(), pars[1].c_str(), pars[2].c_str(), pars[3].c_str(), pars[4].c_str(), winHandler);
                else
                    result = Sapfor_RunTransformation(NULL, NULL, NULL, NULL, NULL, -1);
            }
            else if (code == "modification")
            {
                int err = decodeMessage(message, pars, winHandler, 6);
                if (err == 0)
                    result = Sapfor_RunModification(pars[0].c_str(), pars[1].c_str(), pars[2].c_str(), pars[3].c_str(), pars[4].c_str(), pars[5].c_str(), winHandler);
                else
                    result = Sapfor_RunModification(NULL, NULL, NULL, NULL, NULL, NULL, -1);
            }
            else
            {
                printf("[CLIENT] wrong code: %s\n", code.c_str()); // exit
                int err = send(client, L"WRONG");
                if (err != 0)
                    break;
                continue;
            }

            int err = send(client, result.c_str());
            if (err != 0)
                break;
        }
        else if (count == 0) // close and exit
        {
            printf("[CLIENT] socket was closed\n");
            break;
        }
        else // error
        {
            printf("[CLIENT] recv return error code %d\n", count);
            break;
        }
    }
}


#else

void sendMessage_1lvl(const wstring& toSend) { }
void sendMessage_2lvl(const wstring& toSend) { }
void sendMessage_progress(const wstring& toSend) { }

vector<wstring> MessageManager::cachedMessages = vector<wstring>();
int MessageManager::WinHandler = -1;
wstring MessageManager::firstLvlMessage = L"";
wstring MessageManager::secondLvlMessage = L"";
void MessageManager::sendMessage(const wstring& toSend) { }
void MessageManager::setWinHandler(const int winH) { WinHandler = winH; }
int MessageManager::init() { }

void RunSapforAsClient() { }
#endif

int MessageManager::Started = -1;