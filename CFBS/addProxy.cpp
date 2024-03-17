#include <string>
#include <fstream>
#include <vector> 
#include <iostream> 
#include <sstream>

std::vector<std::pair<std::pair<std::string, int>, std::pair<std::string, std::string>>> addProxies(std::string value, std::vector<std::pair<std::pair<std::string, int>, std::pair<std::string, std::string>>> proxies) {
    std::ifstream file(value);
    std::string line;
    std::vector<std::pair<std::pair<std::string, int>, std::pair<std::string, std::string>>> baba = proxies;
    while (getline(file, line)) {
        std::string token;
        std::stringstream ss(line);
        std::vector<std::string> temporary;
        while (std::getline(ss, token, ':')) {
            temporary.push_back(token);
        }
        if (temporary[0].empty() || temporary[1].empty() || temporary[2].empty() || temporary[3].empty()) {
            std::cout << "Err to add vector. Please fix your shit txt file bro XXAXAXAXAX" << std::endl;
        }
        else {

            std::string ipport = temporary[0] + ":" + temporary[1];
            std::string userpass = temporary[2] + ":" + temporary[3];
            baba.push_back(std::pair(std::pair(temporary[0], stoi(temporary[1])), std::pair(temporary[2], temporary[3])));
            temporary.clear();
        }
    }
    return baba;
}

