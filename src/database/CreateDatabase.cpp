#include "CreateDatabase.h"
#include <format>
#include <fstream>
#include <functional>
#include <iostream>
#include <leveldb/db.h>
#include <leveldb/status.h>
#include <leveldb/write_batch.h>
#include <map>
#include <nlohmann/json.hpp>
#include <sstream>
#include <unicode/unistr.h>
#include <unicode/ustream.h>
#include <unicode/utf8.h>

bool database::CreateDatabase::readingsToDatabase(std::string textFileName, std::string databaseDirectory) {
    static std::map<icu::UnicodeString, icu::UnicodeString> charMap = {
        { icu::UnicodeString::fromUTF8("ā"), icu::UnicodeString::fromUTF8("a") },
        { icu::UnicodeString::fromUTF8("á"), icu::UnicodeString::fromUTF8("a") },
        { icu::UnicodeString::fromUTF8("ǎ"), icu::UnicodeString::fromUTF8("a") },
        { icu::UnicodeString::fromUTF8("à"), icu::UnicodeString::fromUTF8("a") },
        { icu::UnicodeString::fromUTF8("ō"), icu::UnicodeString::fromUTF8("o") },
        { icu::UnicodeString::fromUTF8("ó"), icu::UnicodeString::fromUTF8("o") },
        { icu::UnicodeString::fromUTF8("ǒ"), icu::UnicodeString::fromUTF8("o") },
        { icu::UnicodeString::fromUTF8("ò"), icu::UnicodeString::fromUTF8("o") },
        { icu::UnicodeString::fromUTF8("ē"), icu::UnicodeString::fromUTF8("e") },
        { icu::UnicodeString::fromUTF8("é"), icu::UnicodeString::fromUTF8("e") },
        { icu::UnicodeString::fromUTF8("ě"), icu::UnicodeString::fromUTF8("e") },
        { icu::UnicodeString::fromUTF8("è"), icu::UnicodeString::fromUTF8("e") },
        { icu::UnicodeString::fromUTF8("ī"), icu::UnicodeString::fromUTF8("i") },
        { icu::UnicodeString::fromUTF8("í"), icu::UnicodeString::fromUTF8("i") },
        { icu::UnicodeString::fromUTF8("ǐ"), icu::UnicodeString::fromUTF8("i") },
        { icu::UnicodeString::fromUTF8("ì"), icu::UnicodeString::fromUTF8("i") },
        { icu::UnicodeString::fromUTF8("ū"), icu::UnicodeString::fromUTF8("u") },
        { icu::UnicodeString::fromUTF8("ú"), icu::UnicodeString::fromUTF8("u") },
        { icu::UnicodeString::fromUTF8("ǔ"), icu::UnicodeString::fromUTF8("u") },
        { icu::UnicodeString::fromUTF8("ù"), icu::UnicodeString::fromUTF8("u") },
        // 这个平声ǖ竟然没有被任何一个字的拼音用到
        { icu::UnicodeString::fromUTF8("ǖ"), icu::UnicodeString::fromUTF8("v") },
        { icu::UnicodeString::fromUTF8("ǘ"), icu::UnicodeString::fromUTF8("v") },
        { icu::UnicodeString::fromUTF8("ǚ"), icu::UnicodeString::fromUTF8("v") },
        { icu::UnicodeString::fromUTF8("ǜ"), icu::UnicodeString::fromUTF8("v") }
    };
    // 创建ifstream对象并打开文件
    auto inputFile = std::ifstream(textFileName);

    if (!inputFile.is_open()) {
        std::cerr << "无法打开文件: " << textFileName << std::endl;
        return false;
    }

    // 创建LevelDB数据库选项
    auto options = leveldb::Options();
    // 如果目录不存在，则创建它
    options.create_if_missing = true;
    // 打开或创建LevelDB数据库
    leveldb::DB *db;
    leveldb::Status status = leveldb::DB::Open(options, databaseDirectory, &db);

    if (!status.ok()) {
        std::cerr << "LevelDB初始化失败: " << status.ToString() << std::endl;
        return false;
    }
    // 使用std::unique_ptr和自定义删除器来管理数据库的生命周期
    auto dbPtr = std::unique_ptr<leveldb::DB, std::function<void(leveldb::DB *)>>(db, [&inputFile](leveldb::DB *db) {
        // 关闭文件
        inputFile.close();
        delete db;
    });

    std::string line;
    std::string code;
    std::string language;
    std::string reading;
    nlohmann::json readingCodeJson;
    nlohmann::json codeReadingJson;
    // 按行读取文件内容
    while (std::getline(inputFile, line)) {
        // 创建istringstream对象
        std::istringstream iss(line);
        char a;
        if (!(iss >> a) || a != 'U' || !(iss >> a) || a != '+') {
            continue;
        }
        if (!(iss >> code) || !(iss >> language) || !(iss >> reading)) {
            continue;
        }
        if (language != "kMandarin") {
            continue;
        }
        std::string escapeString;
        if (code.length() <= 4) {
            escapeString = std::format("\\u{:0>4}", code);
        } else {
            escapeString = std::format("\\U{:0>8}", code);
        }

        // 使用ICU的UnicodeString类来处理字符串
        icu::UnicodeString ustr = icu::UnicodeString::fromUTF8(escapeString.data());

        // 进行转义，并将UnicodeString转换为UTF-8编码的std::string
        std::string utf8String;
        ustr.unescape().toUTF8String(utf8String);
        ustr = icu::UnicodeString::fromUTF8(reading.data());
        icu::UnicodeString keyStr;
        for (int32_t i = 0; i < ustr.length(); i++) {
            ustr.extract(i, 1, keyStr);
            if (charMap.contains(keyStr)) {
                ustr.replace(i, 1, charMap[keyStr]);
            }
        }
        reading.clear();
        ustr.toUTF8String(reading);

        if (!readingCodeJson[reading].is_array()) {
            readingCodeJson[reading] = nlohmann::json::array();
        }
        if (!codeReadingJson[utf8String].is_array()) {
            codeReadingJson[utf8String] = nlohmann::json::array();
        }
        readingCodeJson[reading].push_back(utf8String);
        codeReadingJson[utf8String].push_back(reading);
    }

    // 使用WriteBatch批量写入数据
    leveldb::WriteBatch batch;
    for (auto& [key, value] : readingCodeJson.items()) {
        batch.Put(std::string("readingToCode_") + key, value.dump());
    }
    for (auto& [key, value] : codeReadingJson.items()) {
        batch.Put(std::string("codeToReading_") + key, value.dump());
    }

    status = db->Write(leveldb::WriteOptions(), &batch);
    if (!status.ok()) {
        std::cerr << "批量写入数据失败: " << status.ToString() << std::endl;
        return false;
    }
    return true;
}
