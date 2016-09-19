#include <iostream>
#include <string>
#include <PluginInterface.hpp>
#include <Ts3API.hpp>
#include <map>

using namespace std;

class WelcomeMessage: public PluginInterface {
public:
  Ts3API &ts3;

  WelcomeMessage(Ts3API &ts3) : ts3(ts3) {}

  bool start() {
    return true;
  }

  string executeCommand(string command) {
    return "tak";
  }

  bool stop() {
    return true;
  }

  string pluginPrefix = "wm";

};


extern "C" PluginInterface *getPluginObject(Ts3API &ts3) {
  return new WelcomeMessage(ts3);
}
