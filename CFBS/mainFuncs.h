#pragma once
#include <string>
#include <vector> 

void performCurlRequest(const int time, const std::string& url, const std::string& proxy, const std::string& proxyAuth, const std::string& ua, const std::string& cookie);

std::string getRandomUserAgent(std::vector<std::string> usa); 
std::vector<std::pair<std::pair<std::string, int>, std::pair<std::string, std::string>>> addProxies(std::string value, std::vector<std::pair<std::pair<std::string, int>, std::pair<std::string, std::string>>> proxies);
std::vector<std::string> addUserAgents(std::string value, std::vector<std::string> usa);
std::string cfCookieCurl(const std::string& ua, const std::string& url, const std::string& ip, const std::string& port);
int rateCheck(const std::string& url, const std::string& proxy, const std::string& proxyAuth, const std::string& ua, const std::string& cookie);
void cfPost(const std::string& url, const std::string& proxy, const std::string& proxyAuth, const std::string& ua, const std::string& cookie, const std::string& parmetr);
void cHange();
void joiner();
void cHangeReverse();