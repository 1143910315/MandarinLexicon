#include "Trie.h"
#include <format>

algorithm::Trie &algorithm::Trie::insert(const std::string &word) {
    insert(icu::UnicodeString::fromUTF8(word), 0);
    return *this;
}

algorithm::Trie &algorithm::Trie::insert(const icu::UnicodeString &word) {
    insert(word, 0);
    return *this;
}

bool algorithm::Trie::search(const std::string &word) {
    return search(icu::UnicodeString::fromUTF8(word), 0);
}

bool algorithm::Trie::search(const icu::UnicodeString &word) {
    return search(word, 0);
}

void algorithm::Trie::search(const std::string &word, std::vector<std::string> &result) {
    result.clear();
    auto prefix = icu::UnicodeString::fromUTF8(word);
    algorithm::Trie &next = *this;
    icu::UnicodeString codePoint;
    std::string key;
    for (int32_t i = 0; i < prefix.length(); i = prefix.moveIndex32(i, 1)) {
        codePoint.setTo(prefix.char32At(i));
        if (next.children.contains(codePoint.toUTF8String(key))) {
            next = next.children[key];
        } else {
            return;
        }
    }
    next.search(result, word);
}

void algorithm::Trie::insert(const icu::UnicodeString &word, int32_t point) {
    if (point == word.length()) {
        isEnd = true;
    } else {
        std::string key;
        icu::UnicodeString codePoint;
        codePoint.setTo(word.char32At(point));
        children.emplace(codePoint.toUTF8String(key), Trie());
        children[key].insert(word, word.moveIndex32(point, 1));
    }
}

bool algorithm::Trie::search(const icu::UnicodeString &word, int32_t point) {
    if (point == word.length()) {
        return isEnd;
    }
    std::string key;
    icu::UnicodeString codePoint;
    codePoint.setTo(word.char32At(point));
    if (children.contains(codePoint.toUTF8String(key))) {
        return children[key].search(word, word.moveIndex32(point, 1));
    }
    return false;
}

void algorithm::Trie::search(std::vector<std::string> &result, const std::string &prefix) {
    if (isEnd) {
        result.push_back(prefix);
    }
    for (auto &[key, value] : children) {
        value.search(result, prefix + key);
    }
}
