#include "HTTPRequest.hpp"

HTTPRequest::HTTPRequest(string apiKey) : apiKey(apiKey)
{
    this->headers = curl_slist_append(this->headers, ("X-RapidAPI-Key: " + apiKey).c_str());
    this->headers = curl_slist_append(this->headers, "X-RapidAPI-Host: real-time-finance-data.p.rapidapi.com");
    this->headers = curl_slist_append(this->headers, "Content-Type: application/json");
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
}

HTTPRequest::~HTTPRequest()
{
    curl_slist_free_all(this->headers);
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}

string HTTPRequest::getStockPrice(const string &url)
{
    std::string responseString;

    if (curl && this->headers != NULL)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, this->headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseString);

        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            std::cerr << "cURL request failed: " << curl_easy_strerror(res) << std::endl;
        }
    }

    return responseString;
}

string HTTPRequest::getStockPrice(const string &url, const string stockName)
{
    if (!curl)
        return "";
    string jsonStockName = "{ stock : " + stockName + "}";
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStockName.c_str());

    string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK)
    {
        cerr << "POST request failed: " << curl_easy_strerror(res) << endl;
    }

    return response;
}

size_t HTTPRequest::WriteCallback(void *contents, size_t size, size_t nmemb, string *s)
{
    size_t totalSize = size * nmemb;
    s->append(static_cast<char *>(contents), totalSize);
    return totalSize;
}
