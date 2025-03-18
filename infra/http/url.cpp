#include "quark/infra/http/url.h"

#include <string>
#include <regex>
#include <iostream>

std::string quark::MTUrl::encode(const std::string& url)
{
    std::string result;
    for (char c : url)
    {
        if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
        {
            result += c;
        }
        else
        {
            result += '%';
            result += "0123456789ABCDEF"[static_cast<unsigned char>(c) >> 4];
            result += "0123456789ABCDEF"[static_cast<unsigned char>(c) & 15];
        }
    }
    return result;
}

std::string quark::MTUrl::decode(const std::string& url)
{
    std::string result;
    for (size_t i = 0; i < url.length(); i++)
    {
        if (url[i] == '%')
        {
            int value = std::stoi(url.substr(i + 1, 2), nullptr, 16);
            result += static_cast<char>(value);
            i += 2;
        }
        else if (url[i] == '+')
        {
            result += ' ';
        }
        else
        {
            result += url[i];
        }
    }
    return result;
}
