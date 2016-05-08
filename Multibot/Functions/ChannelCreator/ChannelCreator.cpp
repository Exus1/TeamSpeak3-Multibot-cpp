#include "ChannelCreator.hpp"

using namespace std;

ChannelCreator::ChannelCreator(Ts3API& api) : api(api) {
    if(!dirIsset("configs/functions/channelCreator")) 
        if(system("mkdir configs/functions/channelCreator") == -1)
            logerAddError("Nie udało sie utworzyć folderu configs/functions/channelCreator");
    
    if(!fileIsset("configs/functions/channelCreator/config.cfg"))
        createConfig();
}

void ChannelCreator::operator()() {
    
}

void ChannelCreator::config() {
    while(true) {
        cout << COLOR_GREEN;
        cout << "Konfiguracja ChannelCreator" << endl;
        cout << endl;
        cout << "Wybierz opcje której chcesz użyć:"<< endl;
        cout << COLOR_RESET;
        
        if(configFile["general_config"]["enable"] == "true") cout << "1. Wyłącz" << endl;
        else                                                  cout << "1. Włącz" << endl;
    
        cout << "2. Dodaj nowy kanał" << endl;
        cout << "3. Usuń kanał" << endl;
        cout << "4. Konfiguruj wybrany kanał" << endl;
        cout << endl;
        cout << "0. wyjdź" << endl;
        cout << endl;
        cout << "Wybierz co chcesz zrobić" << endl;
    
        int chose;
        cin >> chose;
        checkCinError();
    
        if(chose > 4) {
            cout << "Nie ma takiej opcji!" << endl;
            sleep(3);
            continue;
        }
        
        switch(chose) 
        {
            case 0: return; break;
            case 1: 
            {
                if(configFile["general_config"]["enable"] == "true") {
                    configFile["general_config"]["enable"] = "false";
                    cout << COLOR_GREEN << "Włączono ChannelChecker" << endl;
                    sleep(2);
                }else {
                    configFile["general_config"]["enable"] == "true";
                    cout << COLOR_GREEN << "Wyłączono ChannelChecker" << endl;
                    sleep(2);
                }
                break;
            }
            case 2:
            {
                string inp;
                cout << COLOR_BLUE << "Wprowadź id kanału" << endl;
                cin >> inp;
                configChannel(inp);
                break;
            }
            case 3:
            {
                string inp;
                map<string, string> channelList = configFile.explodeToMap(configFile["general_config"]["channels"], ",");
                while(true) {
                    cout << COLOR_BLUE << "Wprowadź id kanału który chcesz usunąć" << COLOR_RESET << endl;
                    cin >> inp;
                    
                    if(channelList[inp].empty()) {
                        cout << "Nie ma kanłu o podanym id" << endl;
                        sleep(2);
                        continue;
                    }
                    
                    channelList.erase(inp);
                    configFile.erase("channel_"+inp);
                    
                    configFile["general_config"]["channels"].clear();
                    
                    for(map<string, string>::iterator it = channelList.begin(); it != channelList.end(); it++) {
                        if(configFile["general_config"]["channels"].empty()) 
                            configFile["general_config"]["channels"] = it->second;
                        else 
                            configFile["general_config"]["channels"] = "," + it->second;
                    }
                    configFile.save();
                    break;
                }
                case 4:
                {
                   string inp;
                    cout << COLOR_BLUE << "Wprowadź id kanału" << endl;
                    cin >> inp;
                    configChannel(inp);
                    break;
                }
            }
        }
    }
}

void ChannelCreator::createConfig() {
    configFile["general_config"]["enable"] = "true";
    configFile["general_config"]["channels"] = "0,0";
}

void ChannelCreator::configChannel(string id) {
    if(configFile["channel_"+id].empty()) {
        configFile["channel_"+id]["enable"] = "true";
        configFile["channel_"+id]["time_to_assgin"] = "15";
        configFile["channel_"+id]["groups_to_assgin"] = "0,0";
    }
}