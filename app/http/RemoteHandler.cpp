#include "RemoteHandler.h"
#include <iostream>
#include <sstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

RemoteHandler::RemoteHandler(const std::string& url) : _url(url) {
    curl_global_init(CURL_GLOBAL_ALL);
}

RemoteHandler::~RemoteHandler() {
    curl_global_cleanup();
}

void RemoteHandler::setJsonBody(GardenTag& tag) {
    _json = tag.toJson().dump();  // Convert the GardenTag object to JSON string
}


static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string RemoteHandler::push(GardenTag& tag) { 
    CURL* curl = curl_easy_init();

    setJsonBody(tag);
    
    std::string response;

    if (curl) {
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, _url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, _json.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, _json.length());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            std::cerr << "Request failed: " << curl_easy_strerror(res) << std::endl;

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    return response;
}

GardenTag& RemoteHandler::pull() {
    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, _url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);  // <--- tells cURL to use GET
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            std::cerr << "GET request failed: " << curl_easy_strerror(res) << std::endl;

        curl_easy_cleanup(curl);
    }

    nlohmann::json data = nlohmann::json::parse(response);
    // return response;
    throw std::runtime_error("Not implemented yet");
}