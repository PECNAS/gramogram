#ifndef CHAT_H
#define CHAT_H

#include "json/json.hpp"
#include "curl/curl.h"
#include <QTime>
#include <QMainWindow>
#include <QString>

using json = nlohmann::json;

class Chat : public QMainWindow {
public:
    QString backData;
    std::string messdate(std::string sender, std::string receiver, std::string message);
    void sendPostRequest(const QString& url, const QByteArray& postData) {
        CURL *curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.toUtf8().constData());

            curl_easy_setopt(curl, CURLOPT_POST, 1L);

            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.constData());

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);

            CURLcode res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                qDebug() << "Failed to perform HTTP POST request: " << curl_easy_strerror(res);
            }

            // Освобождение ресурсов libcurl
            curl_easy_cleanup(curl);
        } else {
            qDebug() << "Failed to initialize libcurl";
        }
    }
    static size_t writeCallback(char* ptr, size_t size, size_t nmemb, void* userdata) {
        Chat data;
        Chat *request = static_cast<Chat*>(userdata);
        QString responseData = QString::fromUtf8(ptr, size * nmemb);
        data.callBackData(responseData);
        qDebug()<<responseData;
        return size * nmemb;
    }
    void callBackData(QString response) {
        backData=response;
    }
private:
    QTime time;
};

#endif // CHAT_H
