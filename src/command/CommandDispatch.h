#pragma once
#include "Command.h"
#include <functional>
#include <memory>
#include <string>
#include <vector>
namespace command {
    class CommandDispatch : public Command {
    public:
        CommandDispatch() = default;
        std::shared_ptr<Command> addCommand(std::string title) override;
        void addCommand(std::string title, std::function<void()> callback) override;
        bool execute() override;
    private:
        // 禁止外部拷贝构造
        CommandDispatch(const CommandDispatch& single) = delete;
        // 禁止外部赋值操作
        const CommandDispatch& operator=(const CommandDispatch& single) = delete;
    private:
        std::vector<std::tuple<std::string, std::shared_ptr<Command>>> commandList;
    };
}
