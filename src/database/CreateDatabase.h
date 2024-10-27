#pragma once
#include <string>
namespace database {
    class CreateDatabase {
    private:
        CreateDatabase() = default;
        ~CreateDatabase() = default;
        // 禁止外部拷贝构造
        CreateDatabase(const CreateDatabase& single) = delete;
        // 禁止外部赋值操作
        const CreateDatabase& operator=(const CreateDatabase& single) = delete;
    public:
        static bool readingsToDatabase(std::string textFileName, std::string databaseDirectory);
    };
} // namespace database
