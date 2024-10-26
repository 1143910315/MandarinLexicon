#include "CommandCallback.h"

command::CommandCallback::CommandCallback(std::function<void()> callback) : callbackFunction(callback) {
}

std::shared_ptr<command::Command> command::CommandCallback::addCommand(std::string title) {
    return instance();
}

void command::CommandCallback::addCommand(std::string title, std::function<void()> callback) {
    callbackFunction = callback;
}

bool command::CommandCallback::execute() {
    callbackFunction();
    return true;
}
