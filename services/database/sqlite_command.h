#pragma once
#include "sqlite_service.h"


#ifdef __cplusplus

extern "C" {
#endif

typedef struct {
    void *mtSqliteCommand;
} QKSqliteCommand;

#ifdef __cplusplus
}

#include <sqlite3.h>
#include <memory>

#include "sqlite_result.h"

namespace quark {
    class CXAPI MTSqliteCommand {
    public:
        MTSqliteCommand(const MTSqliteService *sqliteService, sqlite3_stmt *stmt, std::string sqlText);

        MTSqliteCommand(const MTSqliteCommand &mtSqlCmd) = delete;

        MTSqliteCommand &operator=(const MTSqliteCommand &mtSqlCmd) = delete;

        MTSqliteCommand(MTSqliteCommand &&mtSqlCmd) = delete;

        MTSqliteCommand &operator=(MTSqliteCommand &&mtSqlCmd) = delete;

        ~MTSqliteCommand();

        void BindInt(const std::string &name, int value);

        void BindString(const std::string &name, const std::string &value);

        std::shared_ptr<MTSqliteResult> Run();

    private:
        std::string sqlText{};
        sqlite3_stmt *stmtPtr;
        const MTSqliteService *sqliteService;
    };
}

QKSqliteCommand *MTSqliteCommandToQKSqliteCommand(quark::MTSqliteCommand *instance);

#endif
