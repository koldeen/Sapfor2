#pragma once

#include <string>
#include <vector>

class MessageManager
{
private:
    static std::vector<std::wstring> cachedMessages;
    static int WinHandler;
    static int Started;
    static std::wstring firstLvlMessage;
    static std::wstring secondLvlMessage;
    
    static void sendMessage(const std::wstring &toSend);
public:
    static void clearCache() { cachedMessages.clear(); }
    static void setWinHandler(const int winH);
    static void sendFirstLvl(const std::wstring &str)
    {
        firstLvlMessage = str;
        sendMessage(firstLvlMessage);
    }

    static void sendSecondLvl(const std::wstring &str)
    {
        secondLvlMessage = str;
        sendMessage(firstLvlMessage + L"\n" + secondLvlMessage);
    }

    static void sendProgress(const std::wstring& str);
    static int init();
};