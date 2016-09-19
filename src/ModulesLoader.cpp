#include "includes/ModulesLoader.hpp"

using namespace std;


ModulesLoader::ModulesLoader(string modulesDir, string modulesPostFix, Ts3API &ts3) :
  modulesPostFix(modulesPostFix),
  modulesDir(modulesDir),
  ts3(ts3)
{
  DIR *link = opendir(("./" + modulesDir).c_str());
  struct dirent *file;
  smatch fileName;
  regex reg("(.*)\\." + modulesPostFix);

  //Deklaracja funckji pobierającej informacje o pluginie
  typedef PluginInterface *(*getPluginObjectT)(Ts3API);
  getPluginObjectT getPluginObject = NULL;


  void* dllBuff;

  if(link) {
    while((file = readdir(link)))
      if(regex_search(string(file->d_name), fileName, reg)) {
        this->modulesFiles.push_back(fileName[0]);
      }
  }else {
    cout << "[ERROR] Can't open folder " << modulesDir << endl;
  }

}

void ModulesLoader::loadAll() {
  //Jeżeli nie ma żadnych modułów w katalogu
  if (this->modulesFiles.size() < 1)
    return;

  ///Wskaźnik na uchwyty plków (dll)
  //void* modulesHandles[this->modulesFiles.size()];

  //Deklaracja typu funkcji pobierającej obiekt modułu
  typedef PluginInterface *(*getPluginObjectT)(Ts3API);
  getPluginObjectT getPluginObject = NULL;

  //Tymczasowy wsaźnik na obiekt modułu
  PluginInterface *pluginObj;

  //Wczytywanie modułów
  for(int i = 0; i < this->modulesFiles.size(); i++) {
    cout << "[INFO] Opening file: " << this->modulesFiles[i] << endl;;

    this->modulesHandles[this->modulesFiles[i]] = dlopen(string("./" + this->modulesDir + "/" + this->modulesFiles[i]).c_str(), RTLD_LAZY);
    if(!this->modulesHandles[this->modulesFiles[i]])  {
      cout << "[ERROR] Unable to open file " << this->modulesFiles[i] << endl;
      this->modulesHandles[this->modulesFiles[i]] = NULL;
      continue;
    }else {
      getPluginObject = (getPluginObjectT)dlsym(this->modulesHandles[this->modulesFiles[i]], "getPluginObject");

      if(!getPluginObject) {
        cout << "[ERROR] Unable to get plugin object handle. " << this->modulesFiles[i] << endl;
        getPluginObject = NULL;
        continue;
      }
    }

    pluginObj = getPluginObject(this->ts3);

    if(!pluginObj) {
      cout << "[ERROR] Unable to get plugin object. " << this->modulesFiles[i] << endl;
      pluginObj = NULL;
      getPluginObject = NULL;
      continue;
    }

    if(pluginObj->pluginPrefix != "Unnamed Plugin") {
      this->modulesObjects[pluginObj->pluginPrefix] = pluginObj;
    }else {
      cout << "[ERROR] Incorrect plugin prefix. " << this->modulesFiles[i] << endl;
    }

    pluginObj = NULL;
    getPluginObject = NULL;
    cout << "[SUCCESS] Loading " << this->modulesFiles[i] << " succesful" << endl;
  }
}

bool ModulesLoader::load(string moduleFile) {
  if(this->modulesHandles[moduleFile] != NULL)
    return false;

  //Deklaracja typu funkcji pobierającej obiekt modułu
  typedef PluginInterface *(*getPluginObjectT)(Ts3API);
  getPluginObjectT getPluginObject = NULL;

  //Tymczasowy wsaźnik na obiekt modułu
  PluginInterface *pluginObj;

  cout << "[INFO] Opening file: " << moduleFile << endl;;

  this->modulesHandles[moduleFile] = dlopen(string("./" + this->modulesDir + "/" + moduleFile).c_str(), RTLD_LAZY);
  if(!this->modulesHandles[moduleFile])  {
    cout << "[ERROR] Unable to open file " << moduleFile << endl;
    this->modulesHandles[moduleFile] = NULL;
    return false;
  }else {
    getPluginObject = (getPluginObjectT)dlsym(this->modulesHandles[moduleFile], "getPluginObject");

    if(!getPluginObject) {
      cout << "[ERROR] Unable to get plugin object handle. " << moduleFile << endl;
      return false;
    }
  }

  pluginObj = getPluginObject(this->ts3);

  if(!pluginObj) {
    cout << "[ERROR] Unable to get plugin object. " << moduleFile << endl;
    return false;
  }

  if(pluginObj->pluginPrefix != "Unnamed Plugin") {
    this->modulesObjects[pluginObj->pluginPrefix] = pluginObj;
  }else {
    cout << "[ERROR] Incorrect plugin prefix. " << moduleFile << endl;
  }

  cout << "[SUCCESS] Loading " << moduleFile << " succesful" << endl;
  return true;
}

bool ModulesLoader::unload(string moduleFile) {
  if(this->modulesHandles[moduleFile] == NULL)
    return true;

  //Deklaracja typu funkcji pobierającej obiekt modułu
  typedef PluginInterface *(*getPluginObjectT)(Ts3API);
  getPluginObjectT getPluginObject = NULL;

  //Tymczasowy wsaźnik na obiekt modułu
  PluginInterface *pluginObj;

  getPluginObject = (getPluginObjectT)dlsym(this->modulesHandles[moduleFile], "getPluginObject");
  if(!getPluginObject) {
    cout << "[ERROR] Unable to get plugin object handle. (unload) " << moduleFile << endl;
    return false;
  }

  pluginObj = getPluginObject(this->ts3);
  if(!pluginObj) {
    cout << "[ERROR] Unable to get plugin object. (unload) " << moduleFile << endl;
    return false;
  }

  if(this->modulesObjects[pluginObj->pluginPrefix]->stop()) {
    this->modulesObjects[pluginObj->pluginPrefix] = NULL;
    dlclose(this->modulesHandles[moduleFile]);
    this->modulesHandles[moduleFile] = NULL;
    return true;
  }else {
    return false;
  }
}
