#pragma once
namespace database {
    class DatabaseCommand {
    private:
        DatabaseCommand() = default;
        ~DatabaseCommand() = default;
        // 禁止外部拷贝构造
        DatabaseCommand(const DatabaseCommand& single) = delete;
        // 禁止外部赋值操作
        const DatabaseCommand& operator=(const DatabaseCommand& single) = delete;
    public:
        static void init();
    private:
        static void removeQuotes(std::string& str);
    };
} // namespace database
