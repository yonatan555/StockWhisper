#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <string>
#include <curl/curl.h>
#include <iostream>
#include <string>

using namespace std;

class HTTPRequest
{
public:
    HTTPRequest(string apiKey);
    ~HTTPRequest();
    string getStockPrice(const string &url);
    string getStockPrice(const string &url, const string stockName);

private:
    curl_slist *headers = NULL;
    CURL *curl;
    string apiKey;
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, string *s);
};

#endif // HTTPREQUEST_H
