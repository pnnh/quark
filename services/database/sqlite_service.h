#pragma once

#include "quark/core/types/string.h"
#include "sqlite_result.h"
#include "sqlite_command.h"

#ifdef __cplusplus


extern "C" {
#endif

typedef struct
{
	void* mtSqlSvc;
} QKSqliteService;

CXAPI QKSqliteService* QKSqliteServiceCreate(QKString* message, int* resultCode);

CXAPI void QKSqliteServiceDelete(QKSqliteService* instance, int* resultCode);

CXAPI QKSqliteCommand* QKSqliteServiceCreateCommand(QKSqliteService* instance, QKString* sqlText, int* resultCode);

CXAPI QKString* QKSqliteVersion(QKSqliteService* instance, int* resultCode);

CXAPI QKSqliteResult* QKSqliteRunSql(QKSqliteService* instance, QKString* sqlText, int* resultCode);


#ifdef __cplusplus
}

#include "quark/infra/result/result.h"
#include <sqlite3.h>
#include <memory>

namespace quark
{
	class CXAPI MTSqliteService
	{
	public:
		MTSqliteService();

		explicit MTSqliteService(const std::string& path);

		~MTSqliteService();

		MTSqliteService(const MTSqliteService&) = delete;

		MTSqliteService& operator=(const MTSqliteService&) = delete;

		MTSqliteService(MTSqliteService&&) = delete;

		MTSqliteService& operator=(MTSqliteService&&) = delete;

		std::shared_ptr<MTSqliteResult> runSql(const std::string& text);

		std::unique_ptr<MTSqliteCommand> createCommand(const std::string& text);

		void runSqlBatch(const std::vector<std::string>& sqlTextVector);

		std::string sqliteVersion();

		[[nodiscard]] std::string sqliteErrMsg() const;

	private:
		sqlite3* sqlite3Database;
	};
}


#endif
