#include "logger.h"

#include <iostream>

#ifdef WIN32
#include <hstring.h>
#include <tchar.h>
#endif

quark::MTLogger quark::MTLogger::Standard = quark::MTLogger();

void quark::MTLogger::LogInfo(const std::string& message)
{
    int a = 10;
    std::cout << "[INFO] " << message << a << std::endl;
}

void quark::MTLogger::LogInfo(std::initializer_list<std::string> messageList)
{
#ifdef WIN32
    OutputDebugString(_T("My output string."));
#endif

    std::string fullMessage;
    for (const std::string& item : messageList)
    {
        fullMessage += " " + item;
    }
    LogInfo(fullMessage);
}

void quark::MTLogger::LogError(const std::string& message)
{
    std::cerr << "[ERROR] " << message << std::endl;
}

void quark::MTLogger::LogError(std::initializer_list<std::string> messageList)
{
    std::string fullMessage;
    for (const std::string& item : messageList)
    {
        fullMessage += " " + item;
    }
    LogError(fullMessage);
}

void QKLogInfo(const char* message)
{
    quark::MTLogInfo(message);
}

void quark::MTLogInfo(const std::string& message)
{
    quark::MTLogger::Standard.LogInfo(message);
}

void quark::MTLogInfo(std::initializer_list<std::string> messageList)
{
    quark::MTLogger::Standard.LogInfo(messageList);
}

void quark::MTLogError(const std::string& message)
{
    quark::MTLogger::Standard.LogError(message);
}

void quark::MTLogError(std::initializer_list<std::string> messageList)
{
    quark::MTLogger::Standard.LogError(messageList);
}
