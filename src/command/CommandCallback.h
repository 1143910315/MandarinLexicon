#pragma once
#include "Command.h"
namespace command {
    class CommandCallback : public Command {
    public:
        CommandCallback(std::function<void()> callback);
        // 禁止外部拷贝构造
        CommandCallback(const CommandCallback& single) = delete;
        // 禁止外部赋值操作
        const CommandCallback& operator=(const CommandCallback& single) = delete;
        std::shared_ptr<Command> addCommand(std::string title) override;
        void addCommand(std::string title, std::function<void()> callback) override;
        bool execute() override;
    private:

        std::function<void()> callbackFunction;
    };
} // namespace Command
