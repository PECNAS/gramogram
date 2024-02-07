#ifndef CHAT_H
#define CHAT_H

#include "json/json.hpp"
#include <QTime>
#include <QMainWindow>
#include <QString>
using json = nlohmann::json;

class Chat : public QMainWindow
{
public:

    std::string reqdate(std::string sender, std::string receiver, std::string message);

private:
    QTime time;
};

#endif // CHAT_H
