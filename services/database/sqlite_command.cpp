#include "sqlite_command.h"

#include "quark/types/Exception.h"

#include <utility>

quark::MTSqliteCommand::MTSqliteCommand(const MTSqliteService *sqliteService, sqlite3_stmt *stmt,
                                        std::string sqlText) : sqliteService(sqliteService), stmtPtr(stmt),
                                                               sqlText(std::move(sqlText)) {
}

quark::MTSqliteCommand::~MTSqliteCommand() {
    if (this->stmtPtr != nullptr)
        sqlite3_finalize(this->stmtPtr);
}

void quark::MTSqliteCommand::BindInt(const std::string &name, int value) {
    auto index = sqlite3_bind_parameter_index(this->stmtPtr, name.c_str());
    auto rc = sqlite3_bind_int(this->stmtPtr, index, value);
    if (rc) throw PSException("Can't bind int value", this->sqliteService->sqliteErrMsg());
}

void quark::MTSqliteCommand::BindString(const std::string &name, const std::string &value) {
    auto index = sqlite3_bind_parameter_index(this->stmtPtr, name.c_str());
    auto rc = sqlite3_bind_text(this->stmtPtr, index, value.c_str(), -1, nullptr);
    if (rc) throw PSException("Can't bind string value", this->sqliteService->sqliteErrMsg());
}

void quark::MTSqliteCommand::Reset() {
    auto rc = sqlite3_reset(this->stmtPtr);
    if (rc) throw PSException("Can't reset statement", this->sqliteService->sqliteErrMsg());
}

std::shared_ptr<quark::MTSqliteResult> quark::MTSqliteCommand::Run() {
    auto row = 0;
    auto sqlResult = std::make_shared<MTSqliteResult>();
    while (true) {
        int step = sqlite3_step(stmtPtr);
        if (step == SQLITE_ROW) {
            MTSqliteRow sqlRow;
            // int bytes;
            // const unsigned char* text;
            auto count = sqlite3_column_count(stmtPtr);
            for (int colIndex = 0; colIndex < count; ++colIndex) {
                //bytes = sqlite3_column_bytes(stmt, 0);
                auto colType = sqlite3_column_type(stmtPtr, colIndex);
                auto colName = sqlite3_column_name(stmtPtr, colIndex);

                // auto colNameString = std::string(reinterpret_cast<const char*>(colName));
                auto sqlColumn = MTSqliteColumn(colType, colIndex, colName);

                switch (colType) {
                    case SQLITE_TEXT: {
                        auto colText = sqlite3_column_text(stmtPtr, colIndex);
                        auto colTextString = std::string(reinterpret_cast<const char *>(colText));
                        sqlColumn.setStringValue(std::move(colTextString));
                        break;
                    }
                    case SQLITE_INTEGER: {
                        sqlColumn.setIntValue(sqlite3_column_int(stmtPtr, colIndex));
                        break;
                    }
                    case SQLITE_FLOAT: {
                        sqlColumn.setFloatValue(sqlite3_column_double(stmtPtr, colIndex));
                        break;
                    }
                    case SQLITE_NULL: {
                        sqlColumn.setNull();
                        break;
                    }
                    default: { break; }
                }

                sqlRow.appendColumn(std::move(sqlColumn));
            }
            sqlResult->appendRow(std::move(sqlRow));
            row++;
        } else if (step == SQLITE_DONE) {
            break;
        } else {
            throw PSException("Can't step statement: ", this->sqliteService->sqliteErrMsg());
        }
    }
    return sqlResult;
}

QKSqliteCommand *MTSqliteCommandToQKSqliteCommand(const quark::MTSqliteCommand &instance) {
    auto newMtCmd = new quark::MTSqliteCommand(instance);
    auto qkCmd = new QKSqliteCommand();
    qkCmd->mtSqliteCommand = newMtCmd;
    return qkCmd;
}
