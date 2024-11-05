#pragma once
#include "algorithm/Trie.h"
#include <leveldb/db.h>
#include <memory>
#include <string>

namespace database {
    class UseDatabase {
    public:
        UseDatabase(std::shared_ptr<std::unique_ptr<leveldb::DB>> database);
        ~UseDatabase() = default;
    public:
        std::vector<std::string> searchPinyin(std::string pinyin);
        std::vector<std::string> pinyinToCode(std::string pinyin);
        void codeToReadings(std::string code);
    private:
        std::shared_ptr<std::unique_ptr<leveldb::DB>> database;
        algorithm::Trie trie;
    };
} // namespace database
