#include "chat.h"
#include "json.hpp"

#include <QTime>

using json = nlohmann::json;

std::string Chat::reqdate(std::string sender, std::string receiver, std::string message) {
    time = QTime::currentTime();
    json reqdata = {
        {"sender",sender},
        {"receiver",receiver},
        {"message",message},
        {"time",time.toString().toStdString()}
    };
    return reqdata.dump();
}
