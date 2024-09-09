#ifndef CURLREQUEST_H
#define CURLREQUEST_H

#include <string>
#include <curl/curl.h>

class CurlRequest
{
public:
    CurlRequest();
    ~CurlRequest();

    std::string performGetRequest(const std::string &url);

private:
    CURL *curl;
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *s);
};

#endif // CURLREQUEST_H
