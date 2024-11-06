#include "command/Command.h"
#include "CreateDatabase.h"
#include "DatabaseCommand.h"
#include "UseDatabase.h"
#include <iostream>
#include <leveldb/db.h>
#include <memory>

void database::DatabaseCommand::init() {
    std::shared_ptr<std::unique_ptr<leveldb::DB>> database = std::make_shared<std::unique_ptr<leveldb::DB>>(nullptr);
    auto operateDatabaseCommand = command::Command::instance()->addCommand("数据库操作", [database]() {
        std::string directory;
        std::cout << "请输入数据库保存的目录:";
        std::cin >> directory;
        if (std::cin) {
            // 创建数据库选项
            leveldb::Options options;
            options.create_if_missing = true;
            // 创建一个原始指针来接收DB对象
            leveldb::DB *rawDb = nullptr;

            // 打开或创建一个数据库
            leveldb::Status status = leveldb::DB::Open(options, removeQuotes(directory), &rawDb);
            if (!status.ok()) {
                std::cerr << "输入的目录无法创建数据库: " << status.ToString() << std::endl;
                return false;
            }
            // 将原始指针转移到unique_ptr中
            *database = std::unique_ptr<leveldb::DB>(rawDb);
            return true;
        } else {
            std::cin.clear();
            return false;
        }
    });
    auto createDatabaseCommand = operateDatabaseCommand->addCommand("从原始数据生成数据库");
    auto useDatabaseCommand = operateDatabaseCommand->addCommand("使用现有数据库");
    createDatabaseCommand->addCommand("从Unihan_Readings.txt生成拼音数据库", [database]() {
        std::string textFileName;
        std::cout << "请输入Unihan_Readings.txt的路径:";
        std::cin >> textFileName;
        if (std::cin) {
            removeQuotes(textFileName);
            if (CreateDatabase::readingsToDatabase(textFileName, database)) {
                std::cout << "数据库创建成功" << std::endl;
            } else {
                std::cout << "数据库创建失败" << std::endl;
            }
        } else {
            std::cin.clear();
        }
        return true;
    });
    useDatabaseCommand->addCommand("根据拼音查找汉字", [database]() {
        std::string prefixPinyin;
        UseDatabase useDatabase = database;
        while (true) {
            std::cout << "请输入拼音:";
            std::cin >> prefixPinyin;
            if (!std::cin) {
                break;
            }
            for (auto& pinyin : useDatabase.searchPinyin(prefixPinyin)) {
                std::cout << "拼音：" << pinyin << std::endl;
                std::cout << "文字：";
                for (auto& code : useDatabase.pinyinToCode(pinyin)) {
                    std::cout << code;
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
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
