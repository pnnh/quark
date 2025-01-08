#include "logger.hpp"
#include "logger.h"

#include <iostream>

#ifdef WIN32
#include <hstring.h>
#include <tchar.h>
#endif


void quark::Logger::LogInfo(const std::string& message)
{
    int a = 10;
    std::cout << "[INFO] " << message << a << std::endl;
}

void quark::Logger::LogInfo(std::initializer_list<std::string> messageList)
{
#ifdef WIN32
    OutputDebugString(_T("My output string."));
#endif


    std::string fullMessage;
    for (const std::string& item : messageList)
    {
        fullMessage += " " + item;
    }
    std::cout << "[INFO] " << fullMessage << std::endl;
}

void MTLogInfo(const char* message)
{
    std::cout << "[INFO] " << message << std::endl;
}