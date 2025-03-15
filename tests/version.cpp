#include "version.h"
#include "quark/services/database/sqlite_service.h"
#include <iostream>

void cxxSqliteStatParams() {
    auto sqlSvc = quark::MTSqliteService("polaris.sqlite");
    auto sqlText = "SELECT $str as strVal, $int as intVal;";
    auto sqlCmd{sqlSvc.createCommand(sqlText)};
    sqlCmd->BindString("$str", "hello呀哈哈");
    sqlCmd->BindInt("$int", 128);
    auto sqlResult = sqlCmd->Run();
    auto sqlRow = sqlResult->getRow(0);
    auto strCol = sqlRow->getColumn("strVal");
    auto strColValue = strCol->getStringValue();
    std::cout << "cSqliteStatParams: " << strColValue << std::endl;

    std::string userInput;
    std::getline(std::cin, userInput);
}
