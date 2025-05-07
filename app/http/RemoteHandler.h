#pragma once
#include <string>
#include <curl/curl.h>

#include "../fileSystemManagement/garden_tags/GardenTag.h"

class RemoteHandler {
public:
    RemoteHandler(const std::string& url);
    ~RemoteHandler();

    std::string push(GardenTag& garden);
    
    GardenTag& pull();
    
    private:
    std::string _url;
    std::string _json;

    void setJsonBody(GardenTag& tag);
};