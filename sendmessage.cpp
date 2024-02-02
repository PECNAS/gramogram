#include "sendmessage.h"
#include "json.hpp"

using json = nlohmann::json;
SendMessage::SendMessage() {

}

json SendMessage::reqdate() {
    json reqdata = {
        {"sender",""},
        {"receiver",""},
        {"message",""},
        {"time",""}
    };
    return reqdata.dump();
}
