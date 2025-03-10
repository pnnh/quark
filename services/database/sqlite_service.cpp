
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

quark::MTSqliteResult quark::MTSqliteService::runSql(const std::string &sqlText) {
    auto command = createCommand(sqlText);
    auto runResult = command->Run();
    if (runResult == nullptr) throw PSException("Can't run sql command");
    return *runResult;
}

quark::MTSqliteResult quark::MTSqliteService::runSql(const std::string &&text) {
    return runSql(text);
}

std::shared_ptr<quark::MTSqliteCommand> quark::MTSqliteService::createCommand(const std::string &sqlText) {
    sqlite3_stmt *stmt;
    auto rc = sqlite3_prepare_v2(this->sqlite3Database, sqlText.c_str(), static_cast<int>(sqlText.length() + 1),
                                 &stmt, nullptr);
    auto sqlErr = sqlite3_errmsg(this->sqlite3Database);
    if (rc) throw PSException("Can't prepare statement", sqlErr);

    return std::make_shared<MTSqliteCommand>(this->sqlite3Database, stmt, sqlText);
}

void quark::MTSqliteService::runSqlBatch(const std::vector<std::string> &sqlTextVector) {
    for (const auto &sqlText: sqlTextVector) {
        runSql(sqlText);
    }
}

std::string quark::MTSqliteService::sqliteVersion() {
    auto sqlResult = runSql("SELECT sqlite_version() as version;");
    auto verColumn = sqlResult.getColumn(0, 0);
    if (!verColumn.has_value()) throw PSException("Can't get sqlite version");

    return verColumn.value().getStringValue();
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
    qkSqlResult->mtSqlResult = new quark::MTSqliteResult(mtSqlResult);
    return qkSqlResult;
}
