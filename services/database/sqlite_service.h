#pragma once

#include "quark/types/string.h"
#include "sqlite_result.h"
#include "sqlite_command.h"

#ifdef __cplusplus


extern "C" {
#endif

typedef struct {
	void *mtSqlSvc;
} QKSqliteService;

CXAPI QKSqliteService *QKSqliteServiceCreate(QKString *message);
CXAPI void QKSqliteServiceDelete(QKSqliteService *instance);

CXAPI QKSqliteCommand *QKSqliteServiceCreateCommand(QKSqliteService *instance, QKString *sqlText);


CXAPI QKString *QKSqliteVersion(QKSqliteService *instance);

CXAPI QKSqliteResult *QKSqliteRunSql(QKSqliteService *instance, QKString *sqlText);


#ifdef __cplusplus
}

#include "quark/types/Exception.h"
#include <sqlite3.h>
#include <memory>

namespace quark {
	class CXAPI MTSqliteService {
	public:
		MTSqliteService();

		explicit MTSqliteService(const std::string &path);

		~MTSqliteService();

		MTSqliteService(const MTSqliteService &) = delete;

		MTSqliteService &operator=(const MTSqliteService &) = delete;

		MTSqliteService(MTSqliteService &&) = delete;

		MTSqliteService &operator=(MTSqliteService &&) = delete;

		MTSqliteResult* runSql(const std::string &text);

		MTSqliteResult* runSql(const std::string &&text);

		MTSqliteCommand* createCommand(const std::string &text);

		void runSqlBatch(const std::vector<std::string> &sqlTextVector);

		std::string sqliteVersion();

		[[nodiscard]] std::string sqliteErrMsg() const;

	private:
		sqlite3 *sqlite3Database;
	};
}


#endif
