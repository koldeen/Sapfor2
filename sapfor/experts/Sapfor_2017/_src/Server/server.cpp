#if _WIN32
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <ws2tcpip.h>
#endif

#include <thread>
#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>

#if _WIN32
#include <filesystem>
#include <direct.h>
namespace fs = std::filesystem;
#define getcwd _getcwd
#else 
//с++14 unix + -lstdc++fs
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#include <unistd.h> 
#endif
#include <stdlib.h>
#include <string.h>
#include <signal.h>

using namespace std;

#if _WIN32
//link with Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

#define SPF_NAME     "Components\\Sapfor_F.exe"
#define SPF_NAME_NEW "Components\\Sapfor_F_new.exe"

#define SPC_NAME     "Components\\Sapfor_C.exe"
#define SPC_NAME_NEW "Components\\Sapfor_C_new.exe"

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

#define SPC_NAME "Components/Sapfor_C"
#define SPC_NAME_NEW "Components/Sapfor_C_new"

#define VIZ_NAME "Components/VisualSapfor.jar"
#define VIZ_NAME_NEW "Components/VisualSapfor_new.jar"

void WSACleanup() { }
int  WSAGetLastError() { return 0; }
void Sleep(int millisec) { usleep(millisec * 2000); }

#endif

#define __print(prefix, format, ...) do {\
   printf((string("%s: ") + format + string("\n")).c_str(), prefix, ##__VA_ARGS__); \
   fflush(NULL); \
} while (0)

#define SERV "[SERVER]"

static const char* version = "2";

extern void __bst_create(const char* name);
extern bool __bst_tryToLock();
extern void __bst_unlock();


static void signal_handler(int s)
{
    __print(SERV, "Caught signal %d", s);
    __bst_unlock();
    exit(1);
}

static int getPort(const SOCKET& listenSocket)
{
    sockaddr_in info;
    socklen_t len = sizeof(info);
    memset(&info, 0, len);

    int err = getsockname(listenSocket, (sockaddr*)&info, &len);
    if (err != 0)
    {
        __print(SERV, "Error of getaddrinfo(): %d", err);
        WSACleanup();
        __bst_unlock();
        exit(1);
    }
    return ntohs(info.sin_port);
}

static int initServer(SOCKET& listenSocket, const string& address, int port = 0)
{
    int iResult;
#if _WIN32	
    WSADATA wsaData = { 0 };
    int resultc = WSAStartup(MAKEWORD(2, 0), &wsaData);
    if (resultc != 0)
    {
        __print(SERV, "result of WSAStartup is %d", resultc);
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
        __print(SERV, "Error of getaddrinfo(): %d", iResult);
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
        __print(SERV, "Error of socket(): %d", listenSocket);
        WSACleanup();
        return 1;
    }

	linger lin;
    lin.l_onoff = 1;
    lin.l_linger = 2;
    iResult = setsockopt(listenSocket, SOL_SOCKET, SO_LINGER, (char*)(&lin), sizeof(lin));
    if (iResult != 0)
    {
        __print(SERV, "Error of setsockopt(): %d", iResult);
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
        __print(SERV, "Bind failed with error: %d", iResult);
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    iResult = listen(listenSocket, 1);
    if (iResult < 0)
    {
        __print(SERV, "Listen failed with error: %d", iResult);
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
        __print(SERV, "Error of creating java socket");
        return -1;
    }

	linger lin;
    lin.l_onoff = 1;
    lin.l_linger = 2;
    int iResult = setsockopt(javaSocket, SOL_SOCKET, SO_LINGER, (char*)(&lin), sizeof(lin));
    if (iResult != 0)
    {
        __print(SERV, "Error of setsockopt(): %d", iResult);
        return 1;
    }
	
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr(address.c_str());
    clientService.sin_port = htons(port);
    int result = connect(javaSocket, (SOCKADDR*)(&clientService), sizeof(clientService));

    if (result != 0)
        __print(SERV, "Error %d of connect to socket %s: %d", WSAGetLastError(), address.c_str(), port);

    return result;
}

static volatile bool spfRun = false;
static volatile int retCodeF = 0;
static void runSapfor(const string command)
{
    spfRun = true;
    __print("[SERVER-th1]", "Try to start sapfor");
    retCodeF = 0;
    retCodeF = system(command.c_str());
    __print("[SERVER-th1]", "SAPFOR done with exit code %d", retCodeF);
    spfRun = false;
}

static volatile bool spcRun = false;
static volatile int retCodeC = 0;
static void runSapforC(const string command)
{
    spcRun = true;
    __print("[SERVER-th3]", "Try to start sapfor(C)");
    retCodeC = 0;
    retCodeC = system(command.c_str());
    __print("[SERVER-th3]", "SAPFOR(C) done with exit code %d", retCodeC);
    spcRun = false;
}

static volatile bool vizRun = false;
static void runVisulizer(const string command)
{
    vizRun = true;
    __print("[SERVER-th2]", "Try to start Visualizer");
    int id = system(command.c_str());
    __print("[SERVER-th2]", "Visualizer done with exit code %d", id);
    vizRun = false;
}

static bool doCommand(SOCKET& spfSoc, SOCKET& javaSoc, SOCKET& serverSoc1, SOCKET& serverSoc2, const string& command, bool& needToUpdateViz, string &returnToJava)
{
    if (command.find("restart:") == 0)
    {
        __print(SERV, "Restart SAPFOR");
        closesocket(spfSoc);
        spfSoc = INVALID_SOCKET;

        //wait shutdown of spf
        while (spfRun)
            ;

        return true;
    }
    else if (command.find("close:") == 0)
    {
        __print(SERV, "Shutdown");
        closesocket(spfSoc);
        closesocket(javaSoc);
        closesocket(serverSoc1);
        closesocket(serverSoc2);
        javaSoc = spfSoc = INVALID_SOCKET;

        Sleep(500);
        __bst_unlock();
        exit(0);
    }
    else if (command.find("update:") == 0)
    {
        __print(SERV, "Update Visualizer");
        closesocket(spfSoc);
        closesocket(javaSoc);
        javaSoc = spfSoc = INVALID_SOCKET;

        //wait shutdown of viz
        while (vizRun)
            ;

        //copy new version
        if (fs::exists(VIZ_NAME_NEW))
        {
            error_code err;
            fs::copy_file(VIZ_NAME_NEW, VIZ_NAME, fs::copy_options::overwrite_existing, err);
            __print(SERV, "Updated with error code %d: %s", err.value(), err.message().c_str());
        }
        else
            __print(SERV, "Can not find new version of Visualizer in '%s' path", VIZ_NAME_NEW);
        //restart
        needToUpdateViz = true;
        return true;
    }
    else if (command.find("update_spf:") == 0)
    {
        __print(SERV, "Update SAPFOR");
        closesocket(spfSoc);
        spfSoc = INVALID_SOCKET;

        //wait shutdown of spf
        while (spfRun)
            ;
        //copy new version
        if (fs::exists(SPF_NAME_NEW))
        {
            error_code err;
            fs::copy_file(SPF_NAME_NEW, SPF_NAME, fs::copy_options::overwrite_existing, err);
            __print(SERV, "Updated with error code %d: %s", err.value(), err.message().c_str());
        }
        else
            __print(SERV, "Can not find new version of sapfor in '%s' path", SPF_NAME_NEW);
        //restart
        return true;
    }
    else if (command.find("update_spc:") == 0)
    {
        __print(SERV, "Update SAPFOR");
        closesocket(spfSoc);
        spfSoc = INVALID_SOCKET;

        //wait shutdown of spc
        while (spcRun)
            ;
        //copy new version
        if (fs::exists(SPC_NAME_NEW))
        {
            error_code err;
            fs::copy_file(SPC_NAME_NEW, SPC_NAME, fs::copy_options::overwrite_existing, err);
            __print(SERV, "Updated with error code %d: %s", err.value(), err.message().c_str());
        }
        else
            __print(SERV, "Can not find new version of sapfor in '%s' path", SPC_NAME_NEW);
        //restart
        return true;
    }
    else if (command.find("update_server:") == 0)
    {
        __print(SERV, "Update SERVER");
        closesocket(spfSoc);
        spfSoc = INVALID_SOCKET;

        //wait shutdown of spf
        while (spfRun)
            ;

        //wait shutdown of spc
        while (spcRun)
            ;

        closesocket(javaSoc);
        javaSoc = INVALID_SOCKET;
        __print(SERV, "SAPFOR was closed, Visualizer socker was closed, exit");

        Sleep(500);
        __bst_unlock();
        exit(0);
    }
    else if (command.find("get_version:") == 0)
    {
        __print(SERV, "Get version of server: %s", version);
        returnToJava = version;
        return true;
    }
    else
    {
        string copy = command;
        if (copy.back() == '\n')
            copy = copy.erase(copy.size() - 1);
        __print(SERV, "Recv command %s", copy.c_str());
    }
    return false;
}

static void closeAndExit(const vector<SOCKET>& toClose, const string& message, int exitCode = 0)
{
    for (auto& elem : toClose)
        closesocket(elem);
    if (message != "")
        __print(SERV, "%s", message.c_str());
    __bst_unlock();
    exit(exitCode);
}

static bool isSapforDebug(int argc, char** argv)
{
    for (int z = 1; z < argc; ++z)
        if (string("-spfDeb") == argv[z])
            return true;
    return false;
}

static bool isVizDebug(int argc, char** argv)
{
    for (int z = 1; z < argc; ++z)
        if (string("-vizDeb") == argv[z])
            return true;
    return false;
}

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
    __print(SERV, "'%s' length='%d'\n", command.c_str(), command.length());
    return err < 0 ? err : count;
}

int main(int argc, char** argv)
{
    if (argc == 2 && argv[1] == string("-help"))
    {
        printf("commands:\n");
        printf("  -hashSkip\n");
        printf("  -unlock\n");
        exit(0);
    }

    signal(SIGINT, signal_handler);
    signal(SIGABRT, signal_handler);
#if _WIN32
    signal(SIGBREAK, signal_handler);
#else
    signal(SIGKILL, signal_handler);
#endif

    char buff[1024];
    char* test = getcwd(buff, 1024);

    const string path = test ? buff : argv[0];
    bool isSpfDeb = isSapforDebug(argc, argv);
    bool isVizDeb = isVizDebug(argc, argv);

    if (argc == 2 && argv[1] == string("-hashSkip"))
        ;
    else
    {
        const size_t hashOfPath = hash<string>{}(path);
        __print(SERV, "Open ot create mutex of '%s' path, hash = %zu", path.c_str(), hashOfPath);

        __bst_create(to_string(hashOfPath).c_str());
        if (argc == 2 && argv[1] == string("-unlock"))
        {
            if (!__bst_tryToLock())
            {
                __print(SERV, "Try to unlock '%s' path", path.c_str());
                __bst_unlock();
                exit(0);
            }
        }

        if (!__bst_tryToLock())
        {
            __print(SERV, "The instance of Visualizer from '%s' path was started", path.c_str());
            exit(0);
        }
    }

    setlocale(LC_ALL, "Russian");
    SOCKET serverSPF = INVALID_SOCKET, serverJAVA = INVALID_SOCKET;
    int sapforPort = 0, javaPort = 0;
    if (initServer(serverSPF, "127.0.0.1", sapforPort) != 0) // create server for Sapfor
        return -1;
    sapforPort = getPort(serverSPF);

    if (initServer(serverJAVA, "127.0.0.1", javaPort) != 0) // create server for Sapfor
    {
        closesocket(serverSPF);
        return -1;
    }
    javaPort = getPort(serverJAVA);
    
    __print(SERV, "SOCKET PORT for SAPFOR %d, SOCKET PORT for Visualizer %d", sapforPort, javaPort);

    const int maxSize = 4096;
    char* buf = new char[maxSize + 1];

    int err;
    
    SOCKET spfSoc = INVALID_SOCKET, javaSoc = INVALID_SOCKET;
    bool needToUpdateViz = true;
    int t = 0;
    while (true)
    {
        if (!vizRun && needToUpdateViz && !isVizDeb)
        {
            __print(SERV, "Run Visualizer from '%s' path with port %d", VIZ_NAME, javaPort);
            if (fs::exists(VIZ_NAME))
            {
                needToUpdateViz = false;
                string toRun = string("java -Dfile.encoding=UTF-8 -jar ") + VIZ_NAME + " --port " + to_string(javaPort);
                thread viz(runVisulizer, toRun);
                viz.detach();
                
                //wait run of viz
                //while (!vizRun) ;
            }
            else
            {
                __print(SERV, "Can not find Visualizer in '%s' path", VIZ_NAME);
                //closeAndExit({ serverSPF , serverJAVA }, "Component not found", -1);
            }
        }

        if (!spfRun && !isSpfDeb)
        {
            __print(SERV, "Run Sapfor from '%s' path with port %d", SPF_NAME, sapforPort);
            if (fs::exists(SPF_NAME))
            {
                const string toRun = SPF_NAME + string(" -client ") + to_string(sapforPort);
                thread sapfor(runSapfor, toRun);
                sapfor.detach();

                //wait run of spf
                //while (!spfRun) ;
            }
            else
            {
                __print(SERV, "Can not find Sapfor in '%s' path", SPF_NAME);
                //closeAndExit({ serverSPF , serverJAVA }, "Component not found", -1);
            }
        }

        bool spfExists = (fs::exists(SPF_NAME) || isSpfDeb);
#pragma omp parallel for
        for (int z = 0; z < 2; ++z)
        {
            if (spfSoc == INVALID_SOCKET && z == 0 && spfExists)
            {
                spfSoc = accept(serverSPF, NULL, NULL);
                if (spfSoc != INVALID_SOCKET)
                    __print(SERV, "SAPFOR connected to server");
            }

            if (javaSoc == INVALID_SOCKET && z == 1)
            {
                javaSoc = accept(serverJAVA, NULL, NULL);
                if (javaSoc != INVALID_SOCKET)
                    __print(SERV, "VISUALIZER connected to server");
            }
        }

        while ( ((spfSoc != INVALID_SOCKET && spfExists) || (!fs::exists(SPF_NAME) && !isSpfDeb)) && 
                 javaSoc != INVALID_SOCKET)
        {
            string retCode = "";
            string command = "";

            err = doRecv(javaSoc, command);
            if (err <= 0)
            {
                __print(SERV, "Error recv from Visualizer with code %d", err);
                closesocket(javaSoc);
                closesocket(spfSoc);
                javaSoc = spfSoc = INVALID_SOCKET;
                break;
            }
            else
            {
                string returnToJava = "";
                if (doCommand(spfSoc, javaSoc, serverSPF, serverJAVA, command, needToUpdateViz, returnToJava))
                {
                    if (javaSoc != INVALID_SOCKET)
                    {
                        int needToRecv = 1;
                        if (returnToJava == "")
                            buf[0] = '\n';
                        else
                        {
                            memcpy(buf, returnToJava.c_str(), sizeof(char) * returnToJava.size());
                            buf[returnToJava.size()] = '\n';
                            needToRecv = returnToJava.size();
                        }

                        int err = send(javaSoc, buf, needToRecv, 0);
                        if (err != needToRecv)
                        {
                            closesocket(javaSoc);
                            javaSoc = INVALID_SOCKET;
                        }
                        else
                        {
                            //after 'get_version' command
                            if (needToRecv > 1)
                                continue;
                        }

                    }
                    break;
                }
            }

            err = send(spfSoc, command.c_str(), command.size(), 0);
            if (err != command.size())
            {
                __print(SERV, "Error of send(): %d", err);
                closesocket(spfSoc);
                spfSoc = INVALID_SOCKET;
            }
            else
                __print(SERV, "Send command to SAPFOR");

            err = recv(spfSoc, buf, maxSize, 0);
            int sizeLong = -1;
            char* bufLong = NULL;

            if (err <= 0)
            {
                __print(SERV, "Error recv(): %d", err);
                closesocket(spfSoc);
                spfSoc = INVALID_SOCKET;

                if (spfRun)
                    retCode = "WRONG\n";
                else
                {
                    if (fs::exists(SPF_NAME))
                    {
                        if (retCodeF != 0)
                            retCode = "SIG_FAULT\n";
                        else
                            retCode = "WRONG\n";
                    }
                    else
                        retCode = "NOT_FOUND\n";
                }
            }
            else
            {
                if (err >= maxSize)
                    closeAndExit({ spfSoc , javaSoc , serverSPF , serverJAVA }, "Critical error", -1);

                buf[err] = '\0';
                err = sscanf(buf, "%d", &sizeLong);
                if (err == -1)
                    closeAndExit({ spfSoc , javaSoc , serverSPF , serverJAVA }, "Critical error", -1);

                bufLong = (char*)malloc(sizeof(char) * (sizeLong + 1));
                if (bufLong == NULL)
                {
                    __print(SERV, "Error in malloc, exit, need to alloc %d", sizeLong + 1);
                    closeAndExit({ spfSoc , javaSoc , serverSPF , serverJAVA }, "", -1);
                }
            }

            if (retCode.find("WRONG") == string::npos && 
                retCode.find("NOT_FOUND") == string::npos &&
                retCode.find("SIG_FAULT") == string::npos)
            {
                retCode = "";
                err = send(spfSoc, buf, 1, 0);
                int start = 0;
                int sum = 0;
                while (sum != sizeLong)
                {
                    err = recv(spfSoc, bufLong + start, sizeLong - sum, 0);
                    if (err <= 0)
                    {
                        __print(SERV, "Error of recv from SAPFOR with code %d", err);
                        retCode = "WRONG\n";
                        closesocket(spfSoc);
                        spfSoc = INVALID_SOCKET;
                        break;
                    }
                    else
                        __print(SERV, "Recv from SAPFOR result == %d size, request size %d", err, sizeLong - sum);
                    sum += err;
                    start += err;
                }
                __print(SERV, "Recv from SAPFOR total %d size", sum);

                if (sum >= sizeLong + 1)
                    closeAndExit({ spfSoc , javaSoc , serverSPF , serverJAVA }, "Critical error", -1);

                bufLong[sum] = '\0';
                retCode = bufLong;
                free(bufLong);
            }
            else 
                __print(SERV, "Send error code to Visualizer: %s", retCode.c_str());

            err = send(spfSoc, buf, 1, 0);

            err = send(javaSoc, retCode.c_str(), retCode.size(), 0);
            if (err != retCode.size())
            {
                __print(SERV, "Error send to Visualizer");
                closesocket(spfSoc);
                closesocket(javaSoc);
                javaSoc = spfSoc = INVALID_SOCKET;
                break;
            }
            else
                __print(SERV, "Send result to Visualizer %d", (int)retCode.size());
        }
        __print(SERV, "Invalid SAPFOR socket, try to restart");
        Sleep(500);
    }

    __bst_unlock();
    return 0;
}

