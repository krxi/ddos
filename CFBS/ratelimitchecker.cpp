#include <string>
#include <curl/curl.h>
#include <condition_variable>
#include <iostream> 
#include <string>
#include <format>



size_t WriteCallbacks(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
using namespace std::chrono_literals;
int rateCheck(const std::string& url, const std::string& proxy, const std::string& proxyAuth, const std::string& ua, const std::string& cookie) {

    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();

    int limit_def = 20;
    bool limited = false;

    if (curl) {
        while (limited == false) { 
            for (int i = 0; i < limit_def; i++) {
                struct curl_slist* headers = NULL;

                headers = curl_slist_append(headers, std::format("User-Agent: {}", ua).c_str());
                headers = curl_slist_append(headers, std::format("Cookie: cf_clearance={}", cookie).c_str());

                curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_PROXY, proxy.c_str());
                curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, proxyAuth.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallbacks);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

                res = curl_easy_perform(curl);
                if (res != CURLE_OK) {
                    throw std::runtime_error("Curl perform error: " + std::to_string(res));
                }
                long response_code;
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
                if (response_code != 200) {
                    std::cout << "Resp code !!: " << response_code << std::endl;
                    limited = true;
                    std::cout << "Rate limit detected. Value: " << limit_def << std::endl;
                    break;
                }
                else {

                    std::cout << "Suan: " << i << std::endl;
                }
                std::this_thread::sleep_for(50ms);
            }
            limit_def += 1;
            std::this_thread::sleep_for(10000ms);
        }
        curl_easy_cleanup(curl); // Moved outside of the infinite loop
    }
    return limit_def;
}

