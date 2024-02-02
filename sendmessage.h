#ifndef SENDMESSAGE_H
#define SENDMESSAGE_H

#include "json.hpp"
#include <QString>
using json = nlohmann::json;

class SendMessage
{
public:
    SendMessage();

    json reqdate();
};

#endif // SENDMESSAGE_H
