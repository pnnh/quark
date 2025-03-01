#pragma once

#include "quark/types/string.h"
#include "SqliteResult.h"
#include "SqliteCommand.h"
#include <sqlite3.h>

#ifdef __cplusplus


extern "C" {
#endif

typedef struct {
	void *mtSqlSvc;
} QKSqliteService;

CXAPI QKSqliteService *QKSqliteServiceCreate(QKString *message);

CXAPI void QKSqliteServiceDelete(QKSqliteService *instance);

CXAPI QKString *QKSqliteVersion(QKSqliteService *instance);

CXAPI QKSqliteResult *QKSqliteRunSql(QKSqliteService *instance, QKString *sqlText);


#ifdef __cplusplus
}

#include "quark/types/Exception.h"


#include <memory>

namespace quark {
	class CXAPI SqliteService {
	public:
		SqliteService();

		explicit SqliteService(const std::string &path);

		~SqliteService();

		SqliteService(const SqliteService &) = delete;

		SqliteService &operator=(const SqliteService &) = delete;

		SqliteService(SqliteService &&) = delete;

		SqliteService &operator=(SqliteService &&) = delete;

		MTSqliteResult runSql(const std::string &text);

		MTSqliteResult runSql(const std::string &&text);

		std::shared_ptr<MTSqliteCommand> createCommand(const std::string &text);

		void runSqlBatch(const std::vector<std::string> &sqlTextVector);

		std::string sqliteVersion();

	private:
		sqlite3 *sqlite3Database;
	};
}


#endif
