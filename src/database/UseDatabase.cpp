#include "UseDatabase.h"
#include <format>

database::UseDatabase::UseDatabase(std::shared_ptr<std::unique_ptr<leveldb::DB>> database) : database(database) {
    std::string value;
    auto status = (*database)->Get(leveldb::ReadOptions(), "reading_Trie", &value);
    if (status.ok()) {
        nlohmann::json::parse(value).get_to(trie);
    }
}

std::vector<std::string> database::UseDatabase::searchPinyin(std::string pinyin) {
    std::vector<std::string> result;
    trie.search(pinyin, result);
    return result;
}

std::vector<std::string> database::UseDatabase::pinyinToCode(std::string pinyin) {
    std::string value;
    std::vector<std::string> result;
    auto status = (*database)->Get(leveldb::ReadOptions(), std::format("readingToCode_{}", pinyin), &value);
    if (status.ok()) {
        nlohmann::json::parse(value).get_to(result);
    }
    return result;
}

void database::UseDatabase::codeToReadings(std::string code) {
}
