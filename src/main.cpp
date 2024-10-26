#include "command/Command.h"
#include "download/DownloadCommand.h"
#ifdef _WIN32
#include <Windows.h>
#endif
int main(int argc, char **argv) {
    (void)argc;
    (void)argv;
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    download::DownloadCommand::init();
    while (command::Command::instance()->execute()) {
    }
    return 0;
}
