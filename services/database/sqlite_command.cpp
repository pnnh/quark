#include "sqlite_command.h"

#include "quark/types/Exception.h"

#include <utility>

quark::MTSqliteCommand::MTSqliteCommand(sqlite3_stmt *stmt,
                                        std::string sqlText) : stmtPtr(stmt),
                                                               sqlText(std::move(sqlText)) {
}

quark::MTSqliteCommand::~MTSqliteCommand() {
    if (this->stmtPtr != nullptr)
        sqlite3_finalize(this->stmtPtr);
}

int quark::MTSqliteCommand::BindInt(std::string name, int value) {
    auto index = sqlite3_bind_parameter_index(this->stmtPtr, name.c_str());
    auto rc = sqlite3_bind_int(this->stmtPtr, index, value);
    return rc;
}

int quark::MTSqliteCommand::BindString(std::string name, std::string value) {
    auto index = sqlite3_bind_parameter_index(this->stmtPtr, name.c_str());

    auto rc = sqlite3_bind_text(this->stmtPtr, index, value.c_str(), -1, SQLITE_TRANSIENT);
    return rc;
}


int quark::MTSqliteCommand::Reset() {
    auto rc = sqlite3_reset(this->stmtPtr);
    return rc;
}

quark::MTSqliteResult *quark::MTSqliteCommand::Run() {
    auto row = 0;
    auto sqlResult = new MTSqliteResult();
    while (true) {
        int step = sqlite3_step(stmtPtr);
        if (step == SQLITE_ROW) {
            auto sqlRow = std::make_shared<MTSqliteRow>();
            auto count = sqlite3_column_count(stmtPtr);
            for (int colIndex = 0; colIndex < count; ++colIndex) {
                auto colType = sqlite3_column_type(stmtPtr, colIndex);
                auto colName = sqlite3_column_name(stmtPtr, colIndex);

                auto sqlColumn = std::make_shared<MTSqliteColumn>(colType, colIndex, colName);

                switch (colType) {
                    case SQLITE_TEXT: {
                        auto colText = sqlite3_column_text(stmtPtr, colIndex);
                        auto colTextString = std::string(reinterpret_cast<const char *>(colText));
                        sqlColumn->setStringValue(std::move(colTextString));
                        break;
                    }
                    case SQLITE_INTEGER: {
                        sqlColumn->setIntValue(sqlite3_column_int(stmtPtr, colIndex));
                        break;
                    }
                    case SQLITE_FLOAT: {
                        sqlColumn->setFloatValue(sqlite3_column_double(stmtPtr, colIndex));
                        break;
                    }
                    case SQLITE_NULL: {
                        sqlColumn->setNull();
                        break;
                    }
                    default:
                        break;
                }

                sqlRow->appendColumn(sqlColumn);
            }
            sqlResult->appendRow(sqlRow);
            row++;
        } else if (step == SQLITE_DONE) {
            break;
        }
    }
    return sqlResult;
}

QKSqliteCommand *MTSqliteCommandToQKSqliteCommand(std::unique_ptr<quark::MTSqliteCommand> &&instance) {
    auto qkCmd = new QKSqliteCommand();
    qkCmd->mtSqliteCommand = new std::unique_ptr(std::move(instance));
    return qkCmd;
}

int QKSqliteCommandBindInt(QKSqliteCommand *instance, QKString *name, int value) {
    auto mtCmd = static_cast<std::unique_ptr<quark::MTSqliteCommand> *>(instance->mtSqliteCommand);
    return (*mtCmd)->BindInt(QKStringToStdString(name), value);
}

int QKSqliteCommandBindString(QKSqliteCommand *instance, QKString *name, QKString *value) {
    auto mtCmd = static_cast<std::unique_ptr<quark::MTSqliteCommand> *>(instance->mtSqliteCommand);

    return (*mtCmd)->BindString(QKStringToStdString(name), QKStringToStdString(value));
}

QKSqliteResult *QKSqliteCommandRun(QKSqliteCommand *instance) {
    auto mtCmd = static_cast<std::unique_ptr<quark::MTSqliteCommand> *>(instance->mtSqliteCommand);
    auto mtResult = (*mtCmd)->Run();
    auto qkResult = MTSqliteResultToQKSqliteResult(mtResult);
    return qkResult;
}

int QKSqliteCommandClose(QKSqliteCommand *instance) {
    auto mtCmd = static_cast<std::unique_ptr<quark::MTSqliteCommand> *>(instance->mtSqliteCommand);
    delete mtCmd;
    return 0;
}
