
#include "sqlite_service.h"
#include <sqlite3.h>
#include <quark/core/string/string.h>

quark::MTSqliteService::MTSqliteService(const std::string &path) {
  sqlite3 *db;
  auto cPath = path.c_str();
  int rc = sqlite3_open(cPath, &db);

  if (rc) {
    const auto stdErrMsg = std::format("Can't open database: {}",
                                       sqlite3_errmsg(db));
    throw MTException(stdErrMsg);
  }

  this->sqlite3Database = db;
}

quark::MTSqliteService::~MTSqliteService() {
  auto rc = sqlite3_close(this->sqlite3Database);
  if (rc) {
    //auto stdErrMsg = std::format("Can't close database: {}", sqlite3_errmsg(this->sqlite3Database));
    // 主动退出
    exit(999);
  }
}

std::shared_ptr<quark::MTSqliteResult> quark::MTSqliteService::runSql(
    const std::string &sqlText) {
  std::unique_ptr<MTSqliteCommand> command{createCommand(sqlText)};
  auto runResult = command->Run();
  if (runResult == nullptr)
    throw MTException("Can't run sql command");
  return runResult;
}

std::unique_ptr<quark::MTSqliteCommand> quark::MTSqliteService::createCommand(
    const std::string &sqlText) {
  sqlite3_stmt *stmt;
  auto rc = sqlite3_prepare_v2(this->sqlite3Database, sqlText.c_str(),
                               static_cast<int>(sqlText.length() + 1),
                               &stmt, nullptr);
  if (rc) {
    auto stdErrMsg = std::format("Can't prepare statement: {}",
                                 sqlite3_errmsg(this->sqlite3Database));
    throw MTException(stdErrMsg);
  }

  return std::make_unique<MTSqliteCommand>(stmt, sqlText);
}

void quark::MTSqliteService::runSqlBatch(
    const std::vector<std::string> &sqlTextVector) {
  for (const auto &sqlText : sqlTextVector) {
    runSql(sqlText);
  }
}

std::string quark::MTSqliteService::sqliteVersion() {
  std::shared_ptr<MTSqliteResult> sqlResult{
      runSql("SELECT sqlite_version() as version;")};
  if (sqlResult == nullptr)
    throw MTException("Can't get sqlite version");
  auto rowCount = sqlResult->getRowCount();
  if (rowCount < 1)
    throw MTException("Can't get sqlite version");
  auto row = sqlResult->getRow(0);
  auto verColumn = row->getColumn(0);
  if (verColumn == nullptr)
    throw MTException("Can't get sqlite version");

  return verColumn->getStringValue();
}

std::string quark::MTSqliteService::sqliteErrMsg() const {
  auto cErr = sqlite3_errmsg(this->sqlite3Database);
  return cErr;
}

QKSqliteService *QKSqliteServiceCreate(QKString *message, int *resultCode) {
  auto path = QKStringToStdString(message);
  auto qkSvc = new QKSqliteService{};
  qkSvc->mtSqlSvc = new quark::MTSqliteService(path);
  return qkSvc;
}

void QKSqliteServiceDelete(QKSqliteService *instance, int *resultCode) {
  if (instance == nullptr)
    return;
  if (instance->mtSqlSvc != nullptr) {
    auto ptr = static_cast<quark::MTSqliteService *>(instance->mtSqlSvc);
    delete ptr;
    instance->mtSqlSvc = nullptr;
  }
  if (resultCode != nullptr)
    *resultCode = QKResultOk;
  delete instance;
}

QKString *QKSqliteVersion(QKSqliteService *instance, int *resultCode) {
  auto ptr = static_cast<quark::MTSqliteService *>(instance->mtSqlSvc);
  auto version = ptr->sqliteVersion();
  auto result = StdStringToQKStringPtr(version);
  if (resultCode != nullptr)
    *resultCode = QKResultOk;
  return result;
}

QKSqliteResult *QKSqliteRunSql(QKSqliteService *instance, QKString *sqlText,
                               int *resultCode) {
  auto ptr = static_cast<quark::MTSqliteService *>(instance->mtSqlSvc);
  auto stdSqlText = QKStringToStdString(sqlText);
  auto mtSqlResult = ptr->runSql(stdSqlText);
  auto qkSqlResult = new QKSqliteResult{};
  qkSqlResult->mtSqlResult = new std::shared_ptr<quark::MTSqliteResult>{
      mtSqlResult};
  if (resultCode != nullptr)
    *resultCode = QKResultOk;
  return qkSqlResult;
}

QKSqliteCommand *QKSqliteServiceCreateCommand(QKSqliteService *instance,
                                              QKString *sqlText,
                                              int *resultCode) {
  auto svcPtr = static_cast<quark::MTSqliteService *>(instance->mtSqlSvc);
  auto stdSqlText = QKStringToStdString(sqlText);
  if (resultCode != nullptr)
    *resultCode = QKResultOk;
  return quark::MTSqliteCommand::MTSqliteCommandToQKSqliteCommand(
      svcPtr->createCommand(stdSqlText));
}
