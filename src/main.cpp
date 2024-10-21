#include <format>
#include <iostream>

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;
    std::cout << std::format("hello world!{}", "") << std::endl;
    return 0;
}
