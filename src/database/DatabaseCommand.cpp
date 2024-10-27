#include "command/Command.h"
#include "CreateDatabase.h"
#include "DatabaseCommand.h"
#include <iostream>

void database::DatabaseCommand::init() {
    auto operateDatabaseCommand = command::Command::instance()->addCommand("数据库操作");
    auto createDatabaseCommand = operateDatabaseCommand->addCommand("从原始数据生成数据库");
    createDatabaseCommand->addCommand("从Unihan_Readings.txt生成拼音数据库", []() {
        std::string textFileName;
        std::string databaseDirectory;
        std::cout << "请输入Unihan_Readings.txt的路径:";
        std::cin >> textFileName;
        std::cout << "请输入数据库保存的目录:";
        std::cin >> databaseDirectory;
        if (std::cin) {
            removeQuotes(textFileName);
            removeQuotes(databaseDirectory);
            if (CreateDatabase::readingsToDatabase(textFileName, databaseDirectory)) {
                std::cout << "数据库创建成功" << std::endl;
            } else {
                std::cout << "数据库创建失败" << std::endl;
            }
        } else {
            std::cin.clear();
        }
    });
}

void database::DatabaseCommand::removeQuotes(std::string& str) {
    if (!str.empty()) {
        // 检查并去除开头的双引号
        if (str.front() == '"') {
            str.erase(0, 1);
        }

        // 检查并去除结尾的双引号
        if (!str.empty() && str.back() == '"') {
            str.pop_back();
        }
    }
}
