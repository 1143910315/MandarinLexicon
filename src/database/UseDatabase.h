#pragma once
#include <string>
#include <vector>
namespace database {
    class UseDatabase {
    private:
        UseDatabase() = default;
        ~UseDatabase() = default;
        // 禁止外部拷贝构造
        UseDatabase(const UseDatabase& single) = delete;
        // 禁止外部赋值操作
        const UseDatabase& operator=(const UseDatabase& single) = delete;
    public:
        static void readingsToCode(std::string pinyin, std::string databaseDirectory);
        static void codeToReadings(std::string code, std::string databaseDirectory);
    };
} // namespace database
