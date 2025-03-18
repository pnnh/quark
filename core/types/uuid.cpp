#include "uuid.h"

#include <random>
#include <regex>

std::regex quark::MTUUID::uuid_regex = std::regex(
    "^[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}$");

bool quark::MTUUID::isUUID(const std::string& uuid_string)
{
    std::smatch match;

    if (std::regex_match(uuid_string, match, uuid_regex) &&
        uuid_string.length() == 36)
    {
        return true;
    }

    return false;
}

std::string quark::MTUUID::generateUUID()
{
    std::string uuid = "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);

    for (char& c : uuid)
    {
        if (c == 'x')
        {
            c = "0123456789abcdef"[dis(gen)];
        }
        else if (c == 'y')
        {
            c = "89ab"[dis(gen)];
        }
    }

    return uuid;
}


std::string quark::MTUUID::generateShortUUID()
{
    return generateUUID().substr(0, 8);
}

std::string quark::MTUUID::generateUUIDWithoutHyphen()
{
    std::string uuid = generateUUID();
    uuid.erase(std::remove(uuid.begin(), uuid.end(), '-'), uuid.end());
    return uuid;
}
