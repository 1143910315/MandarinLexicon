#pragma once
namespace download
{
    class DownloadAsset
    {
    private:
        DownloadAsset() = default;
        ~DownloadAsset() = default;
        // 禁止外部拷贝构造
        DownloadAsset(const DownloadAsset& single) = delete;
        // 禁止外部赋值操作
        const DownloadAsset& operator=(const DownloadAsset& single) = delete;
        public:
        static void downloadUnihan();
    };
    
    
} // namespace download
