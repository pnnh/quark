#pragma once

#include "quark/core/types/string.h"
#include "sqlite_result.h"

#ifdef __cplusplus

extern "C" {
#endif

typedef struct {
    void *mtSqliteCommand;
} QKSqliteCommand;

CXAPI int QKSqliteCommandBindInt(QKSqliteCommand *instance, QKString *name, int value);

CXAPI int QKSqliteCommandBindString(QKSqliteCommand *instance, QKString *name, QKString *value);

CXAPI QKSqliteResult *QKSqliteCommandRun(QKSqliteCommand *instance);

CXAPI int QKSqliteCommandClose(QKSqliteCommand *instance);

#ifdef __cplusplus
}

#include <sqlite3.h>
#include <memory>

#include "sqlite_result.h"

namespace quark {
    class CXAPI MTSqliteCommand {
    public:
        MTSqliteCommand(sqlite3_stmt *stmt, std::string sqlText);

        MTSqliteCommand(const MTSqliteCommand &mtSqlCmd) = delete;

        MTSqliteCommand &operator=(const MTSqliteCommand &mtSqlCmd) = delete;

        MTSqliteCommand(MTSqliteCommand &&mtSqlCmd) = delete;

        MTSqliteCommand &operator=(MTSqliteCommand &&mtSqlCmd) = delete;

        ~MTSqliteCommand();

        int BindInt(std::string name, int value);

        int BindString(std::string name, std::string value);

        MTSqliteResult *Run();

        int Reset();

    private:
        std::string sqlText{};
        sqlite3_stmt *stmtPtr;
    };
}

QKSqliteCommand *MTSqliteCommandToQKSqliteCommand(std::unique_ptr<quark::MTSqliteCommand> &&instance);

#endif
