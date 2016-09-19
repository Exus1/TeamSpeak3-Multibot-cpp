#pragma once

#include <string>
#include <regex>
#include <vector>
#include <map>
#include <dirent.h>
#include <dlfcn.h>

#include <PluginInterface.hpp>
#include <Ts3API.hpp>

using namespace std;

class ModulesLoader {
private:
  string modulesDir;
  string modulesPostFix;
  Ts3API &ts3;

  vector<string> modulesFiles;
  map<string, PluginInterface*> modulesObjects;
  map<string, void*> modulesHandles;
public:
  ModulesLoader(string modulesDir, string modulesPostFix, Ts3API &ts3);

  void loadAll();

  bool load(string moduleFile);

  bool unload(string moduleFile);

  vector<string> getLoadedModules();

  vector<string> getUnloadedModules();

  bool startAll();

  bool status(string moduleName);

};
