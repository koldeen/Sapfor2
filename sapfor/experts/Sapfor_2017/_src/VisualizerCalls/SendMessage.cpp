#ifdef NDEBUG
#include <Windows.h>
#include <string>
#include <vector>

#include "SendMessage.h"

using std::wstring;
using std::vector;

void sendMessage_1lvl(const wstring &toSend) { MessageManager::sendFirstLvl(toSend); }
void sendMessage_2lvl(const wstring &toSend) { MessageManager::sendSecondLvl(toSend); }


#define WM_USER        0x0400 //сообщения для обработчика сообщений
#define STATUS_MESSAGE WM_USER + 16

void MessageManager::sendMessage(const wstring &toSend)
{
    if (WinHandler != -1)
    {
        cachedMessages.push_back(toSend);
        PostMessage((HWND)WinHandler, STATUS_MESSAGE, (WPARAM)(cachedMessages.back().c_str()), (LPARAM)cachedMessages.back().size());
    }
}

vector<wstring> MessageManager::cachedMessages = vector<wstring>();
int MessageManager::WinHandler = -1;
wstring MessageManager::firstLvlMessage = L"";
wstring MessageManager::secondLvlMessage = L"";

#undef WM_USER
#undef STATUS_MESSAGE
#else
#include <string>
void sendMessage_1lvl(const std::wstring &toSend) { }
void sendMessage_2lvl(const std::wstring &toSend) { }
#endif