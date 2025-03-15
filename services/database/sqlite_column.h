#pragma once

#include "quark/types/string.h"

#ifdef __cplusplus

extern "C" {
#endif

CXAPI const int QKSqliteValueNull = 0;
CXAPI const int QKSqliteValueString = 1;
CXAPI const int QKSqliteValueInt = 2;
CXAPI const int QKSqliteValueDouble = 3;


typedef struct {
    void *mtSqliteColumn;
} QKSqliteColumn;


CXAPI QKString *QKSQliteColumnGetStringValue(QKSqliteColumn *instance);

CXAPI int QKSQliteColumnGetIntValue(QKSqliteColumn *instance);

CXAPI int QKSQliteColumnGetDoubleValue(QKSqliteColumn *instance);

CXAPI QKString *QKSQliteColumnGetName(QKSqliteColumn *instance);

CXAPI int QKSQliteColumnGetValueType(QKSqliteColumn *instance);

#ifdef __cplusplus
}

#include <iostream>
#include <string>
#include <variant>

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

    private:
        int colType;
        int colIndex;
        std::string colName;
        bool colIsNull{};

        MTSqliteValue variantValue;
    };
}

QKSqliteColumn *MTSqliteColumnToQKSqliteColumn(std::shared_ptr<quark::MTSqliteColumn> mtSqlCol);

#endif
