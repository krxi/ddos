#include <curl/curl.h>
#include <string>
#include <iostream>
#include <stdexcept>
#include <format>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string cfCookieCurl(const std::string& ua, const std::string& url, const std::string& ip, const std::string& port) {
    std::string proxy = "http://" + ip + ":" + port;
    std::string useragent = "User-Agent: " + ua;
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();

    if (curl) {
        struct curl_slist* headers = NULL;

        headers = curl_slist_append(headers, useragent.c_str());

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, std::format("http://127.0.0.1:8000/kuymaks1:kuymaks1@{}:{}&{}", ip, port, url).c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cout << "Curl err";
        }
        long response_code;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        if (response_code != 200)
            std::cout << "Resp code: " << response_code << std::endl;
        curl_easy_cleanup(curl);
    }

    if (readBuffer.front() == '"' && readBuffer.back() == '"') {
        readBuffer = readBuffer.substr(1, readBuffer.length() - 2);
    }
    std::cout << "Passed: " << readBuffer << std::endl;

    return readBuffer;
}

