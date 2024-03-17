#include <string>
#include <random>
#include <chrono>

std::string getRandomUserAgent(std::vector<std::string> usa) {
    static std::mt19937 mt(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<size_t> dist(0, usa.size() - 1);
    return usa[dist(mt)];
}