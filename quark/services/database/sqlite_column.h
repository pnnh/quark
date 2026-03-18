#pragma once

#include "quark/core/string/string.h"
#include <quark/quark.h>

#ifdef __cplusplus

extern "C" {
#endif

QKAPI const int QKSqliteValueNull = 0;
QKAPI const int QKSqliteValueString = 1;
QKAPI const int QKSqliteValueInt = 2;
QKAPI const int QKSqliteValueDouble = 3;


typedef struct {
    void *mtSqliteColumn;
} QKSqliteColumn;


QKAPI QKString *QKSQliteColumnGetStringValue(QKSqliteColumn *instance, int *resultCode);

QKAPI int QKSQliteColumnGetIntValue(QKSqliteColumn *instance, int *resultCode);

QKAPI int QKSQliteColumnGetDoubleValue(QKSqliteColumn *instance, int *resultCode);

QKAPI QKString *QKSQliteColumnGetName(QKSqliteColumn *instance, int *resultCode);

QKAPI int QKSQliteColumnGetValueType(QKSqliteColumn *instance, int *resultCode);

#ifdef __cplusplus
}

#include <iostream>
#include <string>
#include <variant>
#include <memory>

namespace quark {
    typedef std::variant<std::string, long, double> MTSqliteValue;

    // 和上方MTSqliteValue类型定义一致
    inline enum {
        StringIndex = 0,
        LongIndex = 1,
        DoubleIndex = 2
    } MTSqliteValueIndex;

    class MTSqliteColumn {
    public:
        MTSqliteColumn();

        MTSqliteColumn(int colType, int colIndex, const std::string &&colName);

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

        [[nodiscard]] MTSqliteValue getVariantValue() const;

        static QKSqliteColumn *MTSqliteColumnToQKSqliteColumn(std::shared_ptr<quark::MTSqliteColumn> mtSqlCol);

    private:
        int colType;
        int colIndex;
        std::string colName;
        bool colIsNull{};

        MTSqliteValue variantValue;
    };
}


#endif