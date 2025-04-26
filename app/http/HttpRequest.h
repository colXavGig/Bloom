#include <string>
#include <curl/curl.h>

class HttpRequest {
public:
    HttpRequest(const std::string& url);
    ~HttpRequest();

    void setJsonBody(const std::string& json);
    std::string sendPost();

private:
    std::string _url;
    std::string _json;
};