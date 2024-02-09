#include "chat.h"
#include "json/json.hpp"
#include <QTime>

using json = nlohmann::json;

std::string Chat::messdate(std::string sender, std::string receiver, std::string message) {
    time = QTime::currentTime();
    json messagedata = {
        {"sender",sender},
        {"receiver",receiver},
        {"message",message},
        {"time",time.toString().toStdString()}
    };
    return messagedata.dump();
}



