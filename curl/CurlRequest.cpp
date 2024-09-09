#include "CurlRequest.h"
#include <iostream>

CurlRequest::CurlRequest()
{
    curl = curl_easy_init();
}

CurlRequest::~CurlRequest()
{
    if (curl)
    {
        curl_easy_cleanup(curl);
    }
}

size_t CurlRequest::WriteCallback(void *contents, size_t size, size_t nmemb, std::string *s)
{
    size_t newLength = size * nmemb;
    try
    {
        s->append((char *)contents, newLength);
    }
    catch (std::bad_alloc &e)
    {
        return 0;
    }
    return newLength;
}

std::string CurlRequest::performGetRequest(const std::string &url)
{
    std::string readBuffer;

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
        }
    }

    return readBuffer;
}