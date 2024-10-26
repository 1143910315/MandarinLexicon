#include "command/Command.h"
#include "DownloadAsset.h"
#include "DownloadCommand.h"

void download::DownloadCommand::init() {
    auto subCommand = command::Command::instance()->addCommand("下载资源");
    subCommand->addCommand("下载Unihan.zip", []() {
        DownloadAsset::downloadUnihan();
    });
}
