#pragma once

#include "quark/types/string.h"

#ifdef __cplusplus


extern "C" {
#endif

typedef struct {
	void *mtSqlSvc;
} QKSqliteService;

CXAPI QKSqliteService *QKSqliteServiceCreate(QKString *message);

CXAPI void QKSqliteServiceDelete(QKSqliteService *instance);

CXAPI QKString *QKSqliteVersion(QKSqliteService *instance);


#ifdef __cplusplus
}


#include <sqlite3.h>
#include <memory>
#include <quark/build.h>

#include "SqliteCommand.hpp"
#include "quark/types/Exception.h"
#include "quark/services/database/SqliteResult.h"

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

		SqliteResult runSql(const std::string &text);

		SqliteResult runSql(const std::string &&text);

		std::shared_ptr<SqliteCommand> createCommand(const std::string &text);

		void runSqlBatch(const std::vector<std::string> &sqlTextVector);

		std::string sqliteVersion();

	private:
		sqlite3 *sqlite3Database;
	};
}


#endif
