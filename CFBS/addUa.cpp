#include <string>
#include <sstream>
#include <fstream>
#include <vector>

std::vector<std::string> addUserAgents(std::string value, std::vector<std::string> usa) {
    std::ifstream file(value);
    std::string line;
    std::vector<std::string> usas = usa;
    while (getline(file, line)) {
        usas.push_back(line);
    }
    return usas;
}
