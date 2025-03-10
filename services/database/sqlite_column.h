#pragma once

#include "quark/types/string.h"

#ifdef __cplusplus

extern "C" {
#endif

typedef struct {
    void *mtSqliteColumn;
} QKSqliteColumn;

CXAPI QKSqliteColumn *QKSqliteColumnCreate();

CXAPI QKString *QKSQliteColumnGetStringValue(QKSqliteColumn *instance);

CXAPI int QKSQliteColumnGetIntValue(QKSqliteColumn *instance);

CXAPI QKSqliteColumn *QKSqliteColumnCreate();

#ifdef __cplusplus
}

#include <iostream>
#include <string>
#include <variant>

namespace quark {
    class MTSqliteColumn {
    public:
        MTSqliteColumn();

        MTSqliteColumn(int colType, int colIndex, const std::string &&colName);

        ~MTSqliteColumn();

        MTSqliteColumn(const MTSqliteColumn &);

        MTSqliteColumn &operator=(const MTSqliteColumn &);

        MTSqliteColumn(MTSqliteColumn &&) noexcept;

        MTSqliteColumn &operator=(MTSqliteColumn &&) noexcept;

        [[nodiscard]] int getColIndex() const;

        [[nodiscard]] std::string getColName() const;

        [[nodiscard]] int getColType() const;

        [[nodiscard]] bool isNull() const;

        void setNull();

        [[nodiscard]] std::string getStringValue() const;

        void setStringValue(const char *value);

        void setStringValue(const std::string &value);

        void setStringValue(const std::string &&value);

        [[nodiscard]] int getIntValue() const;

        void setIntValue(int value);

        [[nodiscard]] double getFloatValue() const;

        void setFloatValue(double value);

    private:
        int colType;
        int colIndex;
        std::string colName;
        bool colIsNull{};

        // std::string stringValue;
        // int intValue{};
        // double floatValue;

        std::variant<std::string, long, double> variantValue;
    };
}

QKSqliteColumn *MTSqliteColumnToQKSqliteColumn(const quark::MTSqliteColumn &mtSqlCol);

#endif
