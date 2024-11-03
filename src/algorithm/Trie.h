#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <unicode/unistr.h>
#include <unicode/ustream.h>
#include <unicode/utf8.h>
#include <unordered_map>
#include <vector>

namespace algorithm {
    class Trie {
    public:
        Trie() = default;
        ~Trie() = default;
        Trie& insert(const std::string& word);
        Trie& insert(const icu::UnicodeString& word);
        bool search(const std::string& word);
        bool search(const icu::UnicodeString& word);
        void search(const std::string& word, std::vector<std::string>& result);
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Trie, children, isEnd)
    private:
        void insert(const icu::UnicodeString& word, int32_t point);
        bool search(const icu::UnicodeString& word, int32_t point);
        void search(std::vector<std::string>& result, const std::string& prefix);
        std::unordered_map<std::string, Trie> children;
        bool isEnd = false;
    };
} // namespace algorithm
