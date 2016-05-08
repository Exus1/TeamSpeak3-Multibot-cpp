#pragma once

#include "TeamSpeak3_API/Ts3API.hpp"
#include "Functions/Function.hpp"
#include "Extras/Menu/Menu.hpp"

#define COLOR_RESET "\x1b[0m"
#define BOLD_ON "\x1b[1m"
#define BOLD_OFF "\x1b[22m"
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_BLUE "\x1b[34m"

using namespace std;


class ChannelCreator : public Function {
    
    ConfigFile& configFile = *(new ConfigFile("configs/functions/channelCreator/config.cfg"));
    
    Ts3API& api;
    
    ChannelCreator(Ts3API& api);
    
    virtual void operator()();
    
    virtual void config();
    
    virtual void createConfig();
    
    void configChannel(string id);
};