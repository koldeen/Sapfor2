#if _WIN32
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <ws2tcpip.h>
#endif

#include <thread>
#include <iostream>
#include <string>
#include <algorithm>
#include <filesystem>
#include <stdlib.h>
#include <string.h>

namespace fs = std::filesystem;
using namespace std;

#if _WIN32
//link with Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

#define SPF_NAME     "Components\\Sapfor_F.exe"
#define SPF_NAME_NEW "Components\\Sapfor_F_new.exe"

#define VIZ_NAME     "Components\\VisualSapfor.jar"
#define VIZ_NAME_NEW "Components\\VisualSapfor_new.jar"
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

#define SPF_NAME "Components/Sapfor_F"
#define SPF_NAME_NEW "Components/Sapfor_F_new"

#define VIZ_NAME "Components/VisualSapfor.jar"
#define VIZ_NAME_NEW "Components/VisualSapfor_new.jar"

void WSACleanup() { }
int  WSAGetLastError() { return 0; }
void Sleep(int millisec) { usleep(millisec * 1000); }

#endif

int initServer(SOCKET& listenSocket, const string& address, int port)
{
    int iResult;
#if _WIN32	
    WSADATA wsaData = { 0 };
    int resultc = WSAStartup(MAKEWORD(2, 0), &wsaData);
    if (resultc != 0)
    {
        printf("result of WSAStartup is %d\n", resultc);
        return 1;
    }
#endif

#if _WIN32
    addrinfo* result = NULL, hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    iResult = getaddrinfo(address.c_str(), to_string(port).c_str(), &hints, &result);
    if (iResult != 0)
    {
        cout << "Ошибка getaddrinfo: " << iResult;
        WSACleanup();
        return 1;
    }

    listenSocket = INVALID_SOCKET;
    listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
#else
    listenSocket = socket(AF_INET, SOCK_STREAM, 0);
#endif
    if (listenSocket < 0)
    {
        cout << "Error at socket(): " << listenSocket;
        WSACleanup();
        return 1;
    }

#if _WIN32
    iResult = bind(listenSocket, result->ai_addr, result->ai_addrlen);
#else
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    iResult = bind(listenSocket, (struct sockaddr*) & addr, sizeof(addr));
#endif
    if (iResult < 0)
    {
        cout << "Bind failed with error: " << iResult;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    iResult = listen(listenSocket, 1);
    if (iResult < 0)
    {
        cout << "Listen failed with error: " << iResult;
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

static bool spfRun = false;
static void runSapfor(const string command)
{
    spfRun = true;
    printf("[SERVER-th1] try to start sapfor\n");
    int id = system(command.c_str());
    printf("[SERVER-th1] sapfor done with exit code %d\n", id);
    spfRun = false;
}

static bool vizRun = false;
static void runVisulizer(const string command)
{
    vizRun = true;
    printf("[SERVER-th2] try to start visualizer\n");
    int id = system(command.c_str());
    printf("[SERVER-th2] visualizer done with exit code %d\n", id);
    vizRun = false;
}

static bool doCommand(SOCKET& clientSoc, SOCKET& javaSoc, const string& command, bool& needToUpdateViz)
{
    if (command.find("restart:") == 0)
    {
        printf("[SERVER] restart sapfor\n");
        closesocket(clientSoc);
        clientSoc = INVALID_SOCKET;
        return true;
    }
    else if (command.find("close:") == 0)
    {
        printf("[SERVER] shutdown\n");
        closesocket(clientSoc);
        closesocket(javaSoc);
        javaSoc = clientSoc = INVALID_SOCKET;

        Sleep(500);
        exit(0);
    }
    else if (command.find("update:") == 0)
    {
        printf("[SERVER] update visualizer\n");
        closesocket(clientSoc);
        closesocket(javaSoc);
        javaSoc = clientSoc = INVALID_SOCKET;

        //wait shutdown of viz
        while (vizRun)
            ;
        needToUpdateViz = true;
        //copy new version
        if (fs::exists(VIZ_NAME_NEW))
        {
            error_code err;
            fs::copy_file(VIZ_NAME_NEW, VIZ_NAME, err);
            printf("[SERVER] updated with error code %d: %s\n", err.value(), err.message().c_str());
        }
        else
            printf("[SERVER] can not find new version of visualizer in '%s' path\n", VIZ_NAME_NEW);
        //restart
        return true;
    }
    else if (command.find("update_spf:") == 0)
    {
        printf("[SERVER] update sapfor\n");
        closesocket(clientSoc);
        clientSoc = INVALID_SOCKET;

        //wait shutdown of spf
        while (spfRun)
            ;
        //copy new version
        if (fs::exists(SPF_NAME_NEW))
        {
            error_code err;
            fs::copy_file(SPF_NAME_NEW, SPF_NAME, err);
            printf("[SERVER] updated with error code %d: %s\n", err.value(), err.message().c_str());
        }
        else
            printf("[SERVER] can not find new version of sapfor in '%s' path\n", SPF_NAME_NEW);
        //restart
        return true;
    }
    else
        printf("[SERVER] recv command %s\n", command.c_str());

    return false;
}

#define DEB 0
#define SPF 1

int main(int argc, char** argv)
{
    SOCKET serverSoc, javaSoc;
    if (initServer(serverSoc, "127.0.0.1", 8889) != 0) // create server for Sapfor
        return -1;

    const int countOfTry = 5;

    const int maxSize = 1024;
    char* buf = new char[maxSize];

    int err;
    bool needToUpdateViz = true;
    string retCode = "";

    while (true)
    {
        int t = 0;
        if (!vizRun && needToUpdateViz)
        {
            needToUpdateViz = false;
            if (fs::exists(VIZ_NAME))
            {
                string toRun = string("java -Dfile.encoding=UTF-8 -jar ") + VIZ_NAME;
                thread viz(runVisulizer, toRun);
                viz.detach();
                printf("[SERVER] run visualizer from'%s' path\n", VIZ_NAME);
            }
            else
                printf("[SERVER] can not find visualizer in '%s' path\n", VIZ_NAME);
        }

#if DEB == 0
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
#endif
        {
#if SPF
            string toRun = SPF_NAME + string(" -client");
            thread sapfor(runSapfor, toRun);
            sapfor.detach();
#endif

            SOCKET clientSoc = INVALID_SOCKET;
            clientSoc = accept(serverSoc, NULL, NULL);

            if (clientSoc != INVALID_SOCKET)
                printf("[SERVER] sapfor connected\n");

            while (clientSoc != INVALID_SOCKET)
            {
#if DEB == 0
                string command = "";
                err = recv(javaSoc, buf, maxSize, 0);
                if (err <= 0)
                {
                    printf("[SERVER] error recv from java with code %d\n", err);
                    closesocket(javaSoc);
                    closesocket(clientSoc);
                    javaSoc = clientSoc = INVALID_SOCKET;
                    break;
                }
                else
                {
                    if (err >= maxSize)
                    {
                        printf("[SERVER] critical error\n");
                        exit(-1);
                    }

                    buf[err] = '\0';
                    command = buf;
                    if (doCommand(clientSoc, javaSoc, command, needToUpdateViz))
                        break;
                }
#else

                string command = "analysis:26 SPF_GetVersionAndBuildDate0 0 -1";
#endif

                err = send(clientSoc, command.c_str(), command.size(), 0);
                if (err != command.size())
                {
                    printf("[SERVER] error send\n");
                    closesocket(clientSoc);
                    clientSoc = INVALID_SOCKET;
                }
                else
                    printf("[SERVER] send command to client\n");

                err = recv(clientSoc, buf, maxSize, 0);
                int sizeLong = -1;
                char* bufLong = NULL;

                if (err <= 0)
                {
                    printf("[SERVER] error recv\n");
                    closesocket(clientSoc);
                    clientSoc = INVALID_SOCKET;
                    retCode = "WRONG\n";
                }
                else
                {
                    if (err >= maxSize)
                    {
                        printf("[SERVER] critical error\n");
                        closesocket(clientSoc);
                        closesocket(javaSoc);
                        exit(-1);
                    }

                    buf[err] = '\0';
                    err = sscanf(buf, "%d", &sizeLong);
                    if (err == -1)
                    {
                        printf("[SERVER] critical error\n");
                        closesocket(clientSoc);
                        closesocket(javaSoc);
                        exit(-1);
                    }

                    bufLong = (char*)malloc(sizeof(char) * (sizeLong + 1));
                    if (bufLong == NULL)
                    {
                        printf("[SERVER] error in malloc, exit, need to alloc %d", sizeLong + 1);
                        closesocket(clientSoc);
                        closesocket(javaSoc);
                        exit(-1);
                    }
                }

                if (retCode.find("WRONG") == string::npos)
                {
                    retCode = "";
                    err = send(clientSoc, buf, 1, 0);
                    int start = 0;
                    int sum = 0;
                    while (sum != sizeLong)
                    {
                        err = recv(clientSoc, bufLong + start, sizeLong - sum, 0);
                        if (err <= 0)
                        {
                            printf("[SERVER] error recv with code %d\n", err);
                            retCode = "WRONG\n";
                            closesocket(clientSoc);
                            clientSoc = INVALID_SOCKET;
                            break;
                        }
                        else
                            printf("[SERVER] recv from client result %d size, request size %d\n", err, sizeLong - sum);
                        sum += err;
                        start += err;
                    }
                    printf("[SERVER] recv from client total %d size\n", sum);
                
                    if (sum >= sizeLong + 1)
                    {
                        printf("[SERVER] critical error\n");
                        closesocket(clientSoc);
                        closesocket(javaSoc);
                        exit(-1);
                    }
                    bufLong[sum] = '\0';
                    retCode = bufLong;
                    free(bufLong);
                }
                err = send(clientSoc, buf, 1, 0);
#if DEB == 0
                err = send(javaSoc, retCode.c_str(), retCode.size(), 0);
                if (err != retCode.size())
                {
                    printf("[SERVER] error send to java\n");
                    closesocket(clientSoc);
                    closesocket(javaSoc);
                    javaSoc = clientSoc = INVALID_SOCKET;
                    break;
                }
                else
                    printf("[SERVER] send result to JAVA %d\n", (int)retCode.size());
#else
                printf("%s\n", retCode.c_str());
#endif
            }
            printf("[SERVER] invalid sapfor socket, try to restart\n");
            Sleep(500);
        }
    }
    return 0;
}

