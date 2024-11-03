#include "command/Command.h"
#include "CreateDatabase.h"
#include "DatabaseCommand.h"
#include "UseDatabase.h"
#include <iostream>
#include <memory>

void database::DatabaseCommand::init() {
    std::shared_ptr<std::string> databaseDirectory = std::make_shared<std::string>();
    auto operateDatabaseCommand = command::Command::instance()->addCommand("数据库操作", [databaseDirectory]() {
        std::string directory;
        std::cout << "请输入数据库保存的目录:";
        std::cin >> directory;
        if (std::cin) {
            *databaseDirectory = removeQuotes(directory);
            return true;
        } else {
            std::cin.clear();
            return false;
        }
    });
    auto createDatabaseCommand = operateDatabaseCommand->addCommand("从原始数据生成数据库");
    auto useDatabaseCommand = operateDatabaseCommand->addCommand("使用现有数据库");
    createDatabaseCommand->addCommand("从Unihan_Readings.txt生成拼音数据库", [databaseDirectory]() {
        std::string textFileName;
        std::cout << "请输入Unihan_Readings.txt的路径:";
        std::cin >> textFileName;
        if (std::cin) {
            removeQuotes(textFileName);
            if (CreateDatabase::readingsToDatabase(textFileName, *databaseDirectory)) {
                std::cout << "数据库创建成功" << std::endl;
            } else {
                std::cout << "数据库创建失败" << std::endl;
            }
        } else {
            std::cin.clear();
        }
        return true;
    });
    useDatabaseCommand->addCommand("根据拼音查找汉字", [databaseDirectory]() {
        std::string pinyin;
        while (true) {
            std::cout << "请输入拼音:";
            std::cin >> pinyin;
            if (!std::cin) {
                break;
            }
            UseDatabase::readingsToCode(pinyin, *databaseDirectory);
        }
        std::cin.clear();
        return true;
    });
}

std::string& database::DatabaseCommand::removeQuotes(std::string& str) {
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
    return str;
}
