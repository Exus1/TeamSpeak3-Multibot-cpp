#pragma once

#include <string>
#include <Ts3API.hpp>

using namespace std;

class PluginInterface {
protected:
    const float APIVersion = 0.1;
public:
    float version = 0.0;
    string pluginName = "Unnamed Plugin";
    string pluginPrefix = "";
    //Ts3API &ts3; REQUIRED FOR CONSTRUCTOR!!

    //contructor(Ts3API &ts3) : ts3(ts3) {} REQUIRED!!

    virtual bool start()=0; //Include API Version check

    virtual string executeCommand(string command)=0;

    virtual bool stop()=0;
};
