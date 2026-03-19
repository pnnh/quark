#pragma once
#include <quark/quark.h>


#ifdef __cplusplus

extern "C" {
#endif

typedef struct {
    void *mtStr;
} QKString;

QKAPI QKString *QKStringCreate(const char *data);
QKAPI int QKStringDelete(QKString * qkStr);

QKAPI char *QKStringGetData(QKString *qkStr);


#ifdef __cplusplus
}

#include <format>
#include <string>
#include <vector>

namespace quark {
    class QKAPI MTString {
    public:
        explicit MTString();

        explicit MTString(std::string stdString);

        MTString &operator=(const MTString &other);

        template<typename... Args>
        static std::string DynamicPrint(std::string_view rt_fmt_str, Args &&... args) {
            return std::vformat(rt_fmt_str, std::make_format_args(args...));
        }

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

    QKAPI std::string strToLower(const std::string &str);
} // namespace quark

QKAPI quark::MTString QKStringToMTString(QKString *str);

QKAPI std::string QKStringToStdString(QKString *str);

QKAPI QKString StdStringToQKString(std::string stdString);

QKAPI QKString *StdStringToQKStringPtr(const std::string &stdString);
#endif
