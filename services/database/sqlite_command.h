#pragma once


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
    class MTSqliteCommand {
    public:
        explicit MTSqliteCommand(sqlite3 *sqlite3Database, sqlite3_stmt *stmt, std::string sqlText);

        ~MTSqliteCommand();

        void ChangeSqlText(const std::string &text);

        void BindInt(const std::string &name, int value);

        void BindString(const std::string &name, const std::string &value);

        void Reset();

        std::shared_ptr<MTSqliteResult> Run();

    private:
        std::string sqlText{};
        sqlite3_stmt *stmt;
        sqlite3 *sqlite3Database;
    };
}

#endif
