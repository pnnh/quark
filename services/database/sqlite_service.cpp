
#include "sqlite_service.h"
#include <sqlite3.h>
#include <quark/types/string.h>

quark::MTSqliteService::MTSqliteService(): sqlite3Database(nullptr) {
}

quark::MTSqliteService::MTSqliteService(const std::string &path) {
    sqlite3 *db;
    auto cPath = path.c_str();
    int rc = sqlite3_open(cPath, &db);
    if (rc) throw quark::PSException("Can't open database", sqlite3_errmsg(db));

    this->sqlite3Database = db;
}

quark::MTSqliteService::~MTSqliteService() {
    auto rc = sqlite3_close(this->sqlite3Database);
    if (rc) {
        std::cerr << "Can't close database: " << rc << " " << sqlite3_errmsg(this->sqlite3Database) << std::endl;
    }
}

quark::MTSqliteResult* quark::MTSqliteService::runSql(const std::string &sqlText) {
    std::unique_ptr<MTSqliteCommand> command {createCommand(sqlText)};
    auto runResult =command->Run();
    if (runResult == nullptr) throw PSException("Can't run sql command");
    return runResult;
}

quark::MTSqliteResult* quark::MTSqliteService::runSql(const std::string &&text) {
    return runSql(text);
}

quark::MTSqliteCommand* quark::MTSqliteService::createCommand(const std::string &sqlText) {
    sqlite3_stmt *stmt;
    auto rc = sqlite3_prepare_v2(this->sqlite3Database, sqlText.c_str(), static_cast<int>(sqlText.length() + 1),
                                 &stmt, nullptr);
    if (rc)
    {
        auto sqlErr = sqlite3_errmsg(this->sqlite3Database);
        throw PSException("Can't prepare statement", sqlErr);
    }

    return new MTSqliteCommand(stmt, sqlText);
}

void quark::MTSqliteService::runSqlBatch(const std::vector<std::string> &sqlTextVector) {
    for (const auto &sqlText: sqlTextVector) {
        runSql(sqlText);
    }
}

std::string quark::MTSqliteService::sqliteVersion() {
    std::unique_ptr<MTSqliteResult> sqlResult { runSql("SELECT sqlite_version() as version;")};
    if (sqlResult == nullptr) throw PSException("Can't get sqlite version");
    auto rowCount = sqlResult->getRowCount();
    if (rowCount < 1) throw PSException("Can't get sqlite version");
    auto row = sqlResult->getRow(0);
    auto verColumn = row -> getColumn(0);
    if (verColumn == nullptr) throw PSException("Can't get sqlite version");

    return verColumn ->getStringValue();
}

std::string quark::MTSqliteService::sqliteErrMsg() const {
    auto cErr = sqlite3_errmsg(this->sqlite3Database);
    return cErr;
}

QKSqliteService *QKSqliteServiceCreate(QKString *message) {
    auto path = QKStringToStdString(message);
    auto qkSvc = new QKSqliteService{};
    qkSvc->mtSqlSvc = new quark::MTSqliteService(path);
    return qkSvc;
}

void QKSqliteServiceDelete(QKSqliteService *instance) {
    if (instance == nullptr) return;
    if (instance->mtSqlSvc != nullptr) {
        auto ptr = static_cast<quark::MTSqliteService *>(instance->mtSqlSvc);
        delete ptr;
        instance->mtSqlSvc = nullptr;
    }
    delete instance;
}

QKString *QKSqliteVersion(QKSqliteService *instance) {
    auto ptr = static_cast<quark::MTSqliteService *>(instance->mtSqlSvc);
    auto version = ptr->sqliteVersion();
    auto result = StdStringToQKStringPtr(version);
    return result;
}

QKSqliteResult *QKSqliteRunSql(QKSqliteService *instance, QKString *sqlText) {
    auto ptr = static_cast<quark::MTSqliteService *>(instance->mtSqlSvc);
    auto stdSqlText = QKStringToStdString(sqlText);
    auto mtSqlResult = ptr->runSql(stdSqlText);
    auto qkSqlResult = new QKSqliteResult{};
    qkSqlResult->mtSqlResult = mtSqlResult;
    return qkSqlResult;
}

QKSqliteCommand* QKSqliteServiceCreateCommand(QKSqliteService* instance, QKString* sqlText)
{
    auto svcPtr = static_cast<quark::MTSqliteService *>(instance->mtSqlSvc);
    auto stdSqlText = QKStringToStdString(sqlText);
    auto mtSqlCmd = svcPtr->createCommand(stdSqlText);
    return MTSqliteCommandToQKSqliteCommand(mtSqlCmd);
}
