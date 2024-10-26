#pragma once
namespace download {
    class DownloadCommand {
    private:
        DownloadCommand() = default;
        ~DownloadCommand() = default;
        // 禁止外部拷贝构造
        DownloadCommand(const DownloadCommand& single) = delete;
        // 禁止外部赋值操作
        const DownloadCommand& operator=(const DownloadCommand& single) = delete;
    public:
        static void init();
    };
} // namespace download
