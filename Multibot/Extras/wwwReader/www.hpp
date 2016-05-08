#pragma once

#include <cstring>
#include <iostream>

#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

#include "Loger/Loger.hpp"

using namespace std;
 
bool getWebsiteContent(string website, string &websiteContent);