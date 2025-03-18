#pragma once

#include "quark/build.h"

#ifdef __cplusplus

extern "C" {
#endif

typedef struct {
    void *mtStr;
} QKString;

CXAPI QKString *QKStringCreate(char *data);

CXAPI char *QKStringGetData(QKString *qkStr);


#ifdef __cplusplus
}

#include <format>
#include <string>
#include <vector>

namespace quark {
    class MTString {
    public:
        explicit MTString();

        explicit MTString(std::string stdString);

        MTString &operator=(const MTString &other);

        template<typename... Args>
        static std::string DynamicPrint(std::string_view rt_fmt_str, Args &&... args);

        static bool IsBlank(const std::string &str);

        static bool StartsWith(const std::string &str, const std::string &prefix);

        static std::string LeftReplace(const std::string &str,
                                       const std::string &prefix,
                                       const std::string &newPrefix);

        static bool EndsWith(const std::string &str, const std::string &suffix);

        static std::vector<std::string> SplitChar(const std::string &str,
                                                  char delimiter);

        static std::vector<std::string> SplitString(const std::string &str,
                                                    const std::string &delimiter);

        static std::string toLower(const std::string &str);

        static std::string toUpper(const std::string &str);

        static std::string trimAll(const std::string &orgStr, const std::string &str);

        static std::string trimLeft(const std::string &orgStr,
                                    const std::string &str);

        static std::string trimRight(const std::string &orgStr,
                                     const std::string &str);

        std::string toStdString() const;

        char *getCString() const;

    private:
        std::string stringValue;
    };

    std::string strToLower(const std::string &str);
} // namespace quark

quark::MTString QKStringToMTString(QKString *str);

std::string QKStringToStdString(QKString *str);

QKString StdStringToQKString(std::string stdString);

QKString *StdStringToQKStringPtr(const std::string &stdString);
#endif
