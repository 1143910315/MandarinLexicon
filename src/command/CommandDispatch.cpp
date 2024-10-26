#include "CommandCallback.h"
#include "CommandDispatch.h"
#include <format>
#include <iostream>

std::shared_ptr<command::Command> command::CommandDispatch::addCommand(std::string title) {
    commandList.push_back(std::make_tuple<std::string, std::shared_ptr<Command>>(std::string(title), std::make_shared<CommandDispatch>()));
    return std::get<1>(commandList.back());
}

void command::CommandDispatch::addCommand(std::string title, std::function<void()> callback) {
    commandList.push_back(std::make_tuple<std::string, std::shared_ptr<Command>>(std::string(title), std::make_shared<CommandCallback>(callback)));
}

bool command::CommandDispatch::execute() {
    while (true) {
        std::string outputString = "请输入要执行的命令序号：\n";
        for (int i = 0; i < commandList.size(); i++) {
            auto& [title, command] = commandList[i];
            outputString += std::format("{}.{}\n", i + 1, title);
        }
        outputString += "0.上一级\n-1.退出";
        std::cout << outputString << std::endl;
        int input;
        std::cin >> input;
        if (input > 0 && input <= commandList.size()) {
            auto& [title, command] = commandList[input - 1];
            if (!command->execute()) {
                return false;
            }
        } else if (input == 0) {
            return true;
        } else if (input == -1) {
            return false;
        }
    }
    return true;
}
