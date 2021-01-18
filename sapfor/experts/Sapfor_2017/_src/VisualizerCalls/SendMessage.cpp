#include <string>
#include <locale>
#include <vector>
#include <iostream>

#include "SendMessage.h"
#include "../Utils/utils.h"
#include "get_information.h"

#ifdef _WIN32
#include <Windows.h>
#include <winsock.h>

#define WM_USER        0x0400 //сообщения для обработчика сообщений
#define STATUS_MESSAGE WM_USER + 16

// link with Ws2_32.lib
#pragma comment(lib,"Ws2_32.lib")

#else
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SOCKET int
#define INVALID_SOCKET (SOCKET)(~0)
#define SOCKADDR sockaddr 
#define closesocket close

void WSACleanup() { }
int  WSAGetLastError() { return 0; }
void Sleep(int millisec) { usleep(millisec * 1000); }

#endif

using std::wstring;
using std::string;
using std::vector;

static SOCKET clientSocket = INVALID_SOCKET;

#define __print(prefix, format, ...) do {\
   printf((string("%s: ") + format + string("\n")).c_str(), prefix, ##__VA_ARGS__); \
   fflush(NULL); \
} while (0)

#define CLIENT "[SAPFOR]"

static int doRecv(SOCKET& soc, string& command)
{
    int count = 0; //общее количество прочитаного
    int err = 0; //количество прочитанного на данной итерации.
    const int maxSize = 4096; //максимальный размер прочитываемой за раз порции.
    char* buf = NULL; //буфер
    do
    {
        buf = new char[maxSize + 1];
        err = recv(soc, buf, maxSize, 0);
        if (err > 0)
        {
            count += err;
            buf[err] = '\0';
            command += buf;
        }
        delete[] buf;
        buf = NULL;

    } while (err > 0 && command.back() != '\n');
    __print(CLIENT, "'%s' length='%d'\n", command.c_str(), command.length());
    return err < 0 ? err : count;
}

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

        for (int z = 0; sI != message.size() && z < countElems; ++z, ++sI)
            par += message[sI];
        if (sI == message.size())
            return -3;
        pars.push_back(par);
    }

    string d = "", toPrint = "";
    for (; sI != message.size() && message[sI] != ' '; ++sI)
        d += message[sI];

    if (d[d.size() - 1] == '\n' && d.size() >= 2)
        toPrint = d.substr(0, d.size() - 2);
    else
        toPrint = d;

    __print(CLIENT, "Read port from '%s'", toPrint.c_str());
    if (sscanf(d.c_str(), "%d", &winH) != 1)
    {
        __print(CLIENT, "PORT ERROR");
        return -4;
    }
    else
        __print(CLIENT, "PORT = %d", winH);

    return 0;
}

void sendMessage_1lvl(const wstring& toSend)     { MessageManager::sendFirstLvl (toSend); }
void sendMessage_2lvl(const wstring& toSend)     { MessageManager::sendSecondLvl(toSend); }
void sendMessage_progress(const wstring& toSend) { MessageManager::sendProgress (toSend); }

static string utf8_encode(const wstring& wstr)
{
    if (wstr.empty())
        return string();
#ifdef _WIN32
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
    string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
#else
    /*char* buf = NULL;
    int size_needed = wcstombs(buf, wstr.c_str(), sizeof(char));
	printf("%d for \n", size_needed);
    buf = new char[size_needed + 1];
    wcstombs(buf, wstr.c_str(), sizeof(char));
    string strTo(buf);
    delete[] buf;*/

    string strTo(wstr.size(), 0);
    for (int z = 0; z < wstr.size(); ++z)
        strTo[z] = wstr[z];
#endif
    return strTo;
}

/*static wstring utf8_decode(const string& str)
{
    if (str.empty())
        return wstring();

    int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), NULL, 0);
    wstring wstr;
    wstr.resize(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), &wstr[0], size_needed);
    return wstr;
}*/

void MessageManager::sendMessage(const wstring& toSend)
{
    if (WinHandler > 0) //to C#
    {
#ifdef _WIN32
        cachedMessages.push_back(toSend);
        PostMessage((HWND)WinHandler, STATUS_MESSAGE, (WPARAM)(cachedMessages.back().c_str()), (LPARAM)cachedMessages.back().size());
#endif
    }
    else if (WinHandler < -1) // to JAVA
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
            if (iResult < 0)
                printf("Wrong send is %d\n", iResult);
        }
    }
}

static int connectAndCreate(SOCKET& socket_t, string address, int port)
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
        __print(CLIENT, "Wrong connect to socket %d\n", WSAGetLastError());
        return -1;
    }
    return 0;
}

void MessageManager::setWinHandler(const int winH)
{
    if (winH < -1) // to JAVA
    {
        if (MessageManager::init() != 0)
        {
            WinHandler = -1;
            return;
        }

        __print(CLIENT, "set handler with PORT = %d", winH);
        if (connectAndCreate(clientSocket, "127.0.0.1", winH == -2 ? 8888 : -winH) != 0)
        {
            WinHandler = -1;
            return;
        }        

    }
    else if (winH == -1 && WinHandler < -1) // close JAVA
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

//from get_information.cpp
extern bool showDebug;

static int send(SOCKET& client, const wstring& messageIn)
{
    wstring message = messageIn;
    for (int z = 0; z < message.size(); ++z)
        if (message[z] == L'\n')
            message[z] = L'\t';
    message += L"\n";

    string result = utf8_encode(message);
    string size = std::to_string(result.size());

    if (showDebug)
    {
        wprintf(L"%s: Original message '%s'", CLIENT, message.c_str());
        printf("%s: Converted message '%s'", CLIENT, result.c_str());
    }

    int err = send(client, size.c_str(), size.size(), 0);
    __print(CLIENT, "Send message size: %d", (int)result.size());
    if (err != size.size())
    {
        __print(CLIENT, "Error of send(): %d", err); // exit
        return -1;
    }

    char buf;
    recv(client, &buf, 1, 0);

    err = send(client, result.c_str(), result.size(), 0);    
    __print(CLIENT, "Send message with size %d", (int)result.size());

    if (err != result.size())
    {
        __print(CLIENT, "Error of send(): %d", err); // exit
        return -1;
    }
    else
    {
        err = recv(client, &buf, 1, 0);
        if (err != 1)
        {
            __print(CLIENT, "Error of recv(): %d", err); // exit
            return -1;
        }
        else
            return 0;
    }
}

void MessageManager::sendProgress(const std::wstring& str)
{
    if (WinHandler < -1) // to JAVA
    {
        string result = utf8_encode(L"progress:" + str + L"\n");
        const char* ret = result.c_str();

        int size = result.size();
        int iResult = send(clientSocket, ret, size, 0);
        if (iResult == -1)
            __print(CLIENT, "Error of send(): %d", iResult);
    }
}

int MessageManager::init()
{
#if _WIN32	
    if (Started == -1)
    {
        WSADATA wsaData = { 0 };
        int result = WSAStartup(MAKEWORD(2, 0), &wsaData);
        if (result != 0)
        {
            __print(CLIENT, "Wrong WSAStartup(): %d", result);
            Started = -2;
        }
        else
            Started = 0;
    }    
#else
    Started = 0;
#endif
    return Started;
}

SOCKET client = INVALID_SOCKET;

void sendErrorCode(const wstring& message)
{
    send(client, message);
    closesocket(client);
    client = INVALID_SOCKET;
}

void RunSapforAsClient(int serverPort)
{
    if (MessageManager::init() != 0)
        return;

    client = INVALID_SOCKET;
    if (connectAndCreate(client, "127.0.0.1", serverPort > 0 ? serverPort : 8889) != 0)
        return;
     
    while (true)
    {
        wstring result = L"";
        string message = "";

        __print(CLIENT, "start recv message");
        int count = doRecv(client, message);
        __print(CLIENT, "end recv message with size %d", count);
        if (count > 0)
        {
            string code;
            /*string copy = message;
            if (copy.back() == '\n')
                copy = copy.erase(copy.size() - 1);
            __print(CLIENT, "Recv message: '%s'", copy.c_str());*/

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
                __print(CLIENT, "Wrong message");

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
                __print(CLIENT, "Wrong code of message: %s", code.c_str()); // exit
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
            closesocket(client);
            __print(CLIENT, "Socket was closed");
            break;
        }
        else // error
        {
            closesocket(client);
            __print(CLIENT, "Recv return error code %d", count);
            break;
        }
    }
}

vector<wstring> MessageManager::cachedMessages = vector<wstring>();
int MessageManager::WinHandler = -1;
wstring MessageManager::firstLvlMessage = L"";
wstring MessageManager::secondLvlMessage = L"";
int MessageManager::Started = -1;