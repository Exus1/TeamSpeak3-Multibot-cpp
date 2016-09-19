#pragma once

#include <sqlite3.h>
#include <iostream>

#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <mutex>
#include <string>

#include <PluginInterface.hpp>
#include <map>
#include <vector>

#define BUFFLEN 512
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

#define COLOR_RESET "\x1b[0m"
#define BOLD_ON "\x1b[1m"
#define BOLD_OFF "\x1b[22m"
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_BLUE "\x1b[34m"


using namespace std;


class CommandLine {
    int sock = 0;
    mutex *mtx;

public:
    void operator()(map<string, int> &pluginsPrefixList, vector<string> modules, PluginInterface *pluginsTable[], int sock) {
      
    }
};
