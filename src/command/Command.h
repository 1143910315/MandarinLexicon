#pragma once
#include <functional>
#include <memory>
#include <string>
namespace command {
    class Command {
    public:
        // 获取单实例对象
        static std::shared_ptr<Command> instance();
        // 禁止外部拷贝构造
        Command(const Command& single) = delete;
        // 禁止外部赋值操作
        const Command& operator=(const Command& single) = delete;
        // 虚析构函数，确保派生类对象能够正确释放
        virtual ~Command() {
        }
        virtual std::shared_ptr<Command> addCommand(std::string title) = 0;
        virtual void addCommand(std::string title, std::function<void()> callback) = 0;
        virtual void execute() = 0;
    protected:
        // 禁止外部构造
        Command() = default;
    };
}
