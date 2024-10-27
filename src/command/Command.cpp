#include "Command.h"
#include "CommandDispatch.h"
#include <mutex>

std::shared_ptr<command::Command> command::Command::instance() {
    static std::once_flag flag;
    static std::shared_ptr<Command> single;
    std::call_once(flag, []() {
        single = std::make_shared<CommandDispatch>();
    });
    return single;
}
