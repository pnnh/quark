#include "sqlite_column.h"

#include <sqlite3.h>

#include "quark/infra/result/result.h"


quark::MTSqliteColumn::MTSqliteColumn() : colType(), colIndex()
{
}

quark::MTSqliteColumn::MTSqliteColumn(const int colType, const int colIndex,
                                      const std::string&& colName) : colType(colType), colIndex(colIndex),
                                                                     colName(colName)
{
    if (colIndex < 0) throw quark::MTException("列索引必须大于等于0");
}


int quark::MTSqliteColumn::getColIndex() const
{
    return colIndex;
}

std::string quark::MTSqliteColumn::getColName() const
{
    if (colName.empty()) return "column" + std::to_string(colIndex);
    return colName;
}

std::string quark::MTSqliteColumn::getStringValue() const
{
    if (variantValue.index() == StringIndex)
    {
        return std::get<std::string>(variantValue);
    }
    return "";
}

void quark::MTSqliteColumn::setStringValue(const char* value)
{
    variantValue = std::string(value);
}

void quark::MTSqliteColumn::setStringValue(const std::string& value)
{
    variantValue = value;
}

void quark::MTSqliteColumn::setStringValue(const std::string&& value)
{
    variantValue = value;
}

int quark::MTSqliteColumn::getIntValue() const
{
    return variantValue.index() == LongIndex ? static_cast<int>(std::get<long>(variantValue)) : 0;
}

void quark::MTSqliteColumn::setIntValue(int value)
{
    variantValue = static_cast<long>(value);
}

double quark::MTSqliteColumn::getFloatValue() const
{
    return variantValue.index() == DoubleIndex ? std::get<double>(variantValue) : 0.0;
}

void quark::MTSqliteColumn::setFloatValue(double value)
{
    variantValue = value;
}

quark::MTSqliteValue quark::MTSqliteColumn::getVariantValue() const
{
    return variantValue;
}

int quark::MTSqliteColumn::getColType() const
{
    return colType;
}

bool quark::MTSqliteColumn::isNull() const
{
    return colIsNull;
}

void quark::MTSqliteColumn::setNull()
{
    colIsNull = true;
}

QKSqliteColumn* quark::MTSqliteColumn::MTSqliteColumnToQKSqliteColumn(std::shared_ptr<quark::MTSqliteColumn> mtSqlCol)
{
    auto qkCol = new QKSqliteColumn();
    qkCol->mtSqliteColumn = new std::shared_ptr(std::move(mtSqlCol));
    return qkCol;
}


int QKSQliteColumnGetIntValue(QKSqliteColumn* instance, int* resultCode)
{
    auto mtSqlCol = static_cast<std::shared_ptr<quark::MTSqliteColumn>*>(instance->mtSqliteColumn);
    if (resultCode != nullptr) *resultCode = QKResultOk;
    return (*mtSqlCol)->getIntValue();
}

QKString* QKSQliteColumnGetStringValue(QKSqliteColumn* instance, int* resultCode)
{
    auto mtSqlCol = static_cast<std::shared_ptr<quark::MTSqliteColumn>*>(instance->mtSqliteColumn);
    auto stringValue = (*mtSqlCol)->getStringValue();
    if (resultCode != nullptr) *resultCode = QKResultOk;
    return StdStringToQKStringPtr(stringValue);
}

int QKSQliteColumnGetDoubleValue(QKSqliteColumn* instance, int* resultCode)
{
    auto mtSqlCol = static_cast<std::shared_ptr<quark::MTSqliteColumn>*>(instance->mtSqliteColumn);
    if (resultCode != nullptr) *resultCode = QKResultOk;
    return (*mtSqlCol)->getFloatValue();
}

int QKSQliteColumnGetValueType(QKSqliteColumn* instance, int* resultCode)
{
    auto mtSqlCol = static_cast<std::shared_ptr<quark::MTSqliteColumn>*>(instance->mtSqliteColumn);
    if (resultCode != nullptr) *resultCode = QKResultOk;
    auto sqlType = (*mtSqlCol)->getColType();
    switch (sqlType)
    {
    case SQLITE_TEXT:
        return QKSqliteValueString;
    case SQLITE_INTEGER:
        return QKSqliteValueInt;
    case SQLITE_FLOAT:
        return QKSqliteValueDouble;
    default: return QKSqliteValueNull;
    }
}

QKString* QKSQliteColumnGetName(QKSqliteColumn* instance, int* resultCode)
{
    auto mtSqlCol = static_cast<std::shared_ptr<quark::MTSqliteColumn>*>(instance->mtSqliteColumn);
    auto colName = (*mtSqlCol)->getColName();
    if (resultCode != nullptr) *resultCode = QKResultOk;
    return StdStringToQKStringPtr(colName);
}
