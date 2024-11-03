#include "DownloadAsset.h"
#include <httplib.h>
#include <iostream>

void download::DownloadAsset::downloadUnihan() {
    // https://www.unicode.org/charts/unihan.html
    // 创建一个客户端实例
    httplib::Client cli("https://www.unicode.org");

    // 发送 GET 请求
    auto res = cli.Get("/Public/UCD/latest/ucd/Unihan.zip");

    // 检查响应状态码
    if (res && res->status == 200) {
        // 将响应内容写入文件
        std::ofstream file("Unihan.zip", std::ios::binary);
        if (file.is_open()) {
            // 将响应体作为二进制数据写入文件
            file.write(res->body.data(), res->body.size());
            file.close();
            std::cout << "File downloaded successfully!" << std::endl;
        } else {
            std::cerr << "Unable to open file for writing." << std::endl;
        }
    } else {
        std::cerr << "Failed to download file: " << httplib::to_string(res.error()) << std::endl;
    }
}
