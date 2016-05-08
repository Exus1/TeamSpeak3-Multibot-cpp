#include "AntyVPN.hpp"

using namespace std;

AntyVPN::AntyVPN(Ts3API &api) : api(api) {
	if(!dirIsset("configs/functions/AntyVPN")) if(system("mkdir configs/functions/AntyVPN") == -1) logerAddWarrning("Nie udało się stworzyć folderu konfiguracyjnego funkcji AntyVPN");
	
	if(!fileIsset("configs/functions/AntyVPN/config.cfg")) createConfig();
}

int AntyVPN::writer(char *data, size_t size, size_t nmemb, string *buffer)  { 
  int result = 0;    
  if (buffer != NULL)  
  { 
    buffer->append(data, size * nmemb); 
    result = size * nmemb;  
  } 
  return result;  
} 

bool AntyVPN::isVPN(clientInfo &clInfo) {
    string wwwContent;
    if(getWebsiteContent("http://iphub.info/api.php?ip=" + clInfo["connection_client_ip"] + "&showtype=2&email=", wwwContent)) {
        wwwContent.erase(0, wwwContent.length()-1);
        if(wwwContent == "1")   return true;
        else                    return false;
    }else {
        return false;
    }
}


void AntyVPN::operator()() {
	
	map<string, clientInfo> clList;
	if(configFile["general_config"]["kick_from"].empty()) {
		logerAddWarrning("Nie ustawiono sposobu wyrzucania użytkowników. AntyVPN");
		return;
	}
    
	if(configFile["general_config"]["message"].empty()) {
		logerAddWarrning("Nie ustawino wiadomości porzegnalnej. AntyVPN");
		return;
	}
	
	vector<string> clientGroups;
	vector<string> ignoredGroups = configFile.explode(configFile["general_config"]["ignored_groups"], ",");
	bool breakLoop;
	
	while(true) {
		breakLoop = false;
		api.getServerClientList(clList, "auto", "-ip -groups");
		
		
		
		for(map<string, clientInfo>::iterator it = clList.begin(); it != clList.end(); it++) {
			// Ignorowanie grup
			clientGroups = configFile.explode(it->second["client_servergroups"], ",");
			for(size_t i = 0; i < clientGroups.size(); i++) {
				for(size_t i1 = 0; i1 < ignoredGroups.size(); i1++) {
					if(ignoredGroups[i1] == clientGroups[i]) {
						breakLoop = true;
						break;
					}
				}
				if(breakLoop) break;
			}
			if(breakLoop) continue;
			
			// Sprawdzanie czy używa VPN'a
			if(isVPN(it->second)) {
				if(configFile["general_config"]["kick_from"] == "server")   it->second.kickFromServer(configFile["general_config"]["message"]);
				else                                                        it->second.kickFromChannel(configFile["general_config"]["message"]);
			}
		}
		
		
		// Kończenie pętli
		if(loopEnd) {
			loopEnded = true;
			return;
		}
	}
}

bool AntyVPN::run() {
	th = new thread(bind(&startFunctionInThread, this));
	return (th != NULL)? true : false;
}

bool AntyVPN::stop() {
	if(isRuning() && !loopEnd) {
		loopEnd = true;
		for(int i = 0; i <10; i++) {
			if(loopEnded) {
				loopEnded = false;
				loopEnd = false;
				return true;
			}
			sleep(1);
		}
		return false;
	}else {
		return false;
	}	
}

string AntyVPN::status() {
	return "TEST";
}

bool AntyVPN::isRuning() {
	return (th != NULL)? true : false;
}

bool AntyVPN::isEnabled() {
	return (configFile["general_config"]["enable"] == "true")? true : false;
}

void AntyVPN::config() {
	while(true) {
		cout << COLOR_GREEN;
		cout << "Konfiguracja AntyVPN" << endl;
		cout << endl;
		cout << "Wybierz opcje której chcesz użyć:"<< endl;
		cout << COLOR_RESET;
        
		if(configFile["general_config"]["enable"] == "true")    cout << "1. Wyłącz" << endl;
		else                                                    cout << "1. Włącz" << endl;
        
		cout << "2. Wybierz sposób wyrzucania użytkownika" << endl;
		cout << "3. Ustaw wiadomość porzegnalną" << endl;
		cout << "4. Ustaw ignorowane grupy" << endl;
		
		cout << endl;
		cout << "0. Wstecz" << endl;
		
		unsigned short input;
		cin >> input;
		checkCinError();
		
		if(input > 3) {
			cout << COLOR_RED << "Nie ma takiej opcji" << COLOR_RESET << endl;
			sleep(3);
			if(system("clear") == -1) logerAddWarrning("Nie udało się wyczyścić terminala");
		}
		
		string chose, buffer;
		
		switch(input) {
			case 0: return; // Wyjście
			case 1: // Włącz/Wyłącz
			{
				if(configFile["general_config"]["enable"] == "true")    configFile["general_config"]["enable"] = "false";
				else                                                    configFile["general_config"]["enable"] = "true";
                
				configFile.save();
				break;
			}
			case 2: // Wybór kanału powitalnego
			{
				cout << "W jaki sposób chcesz wyrzucić użytkownika? " << endl;
				cout << "Wpisz server lub channel";
				cin >> chose;
				configFile["general_config"]["kick_from"] = chose;
				configFile.save();
				break;
			}
			case 3:
			{
				cout << "Wprowadź wiadomość porzegnalną:" << endl;
				cin >> chose;
				configFile["general_config"]["message"] = chose;
				configFile.save();
				break;
			}
			case 4:
			{
				buffer = "";
				while(true) {
					cout << "Wprowadź id grupy którą chcesz ignorować lub 0 jeżeli chcesz zakończyć konfigurację:" << endl;
					cin >> chose;
                    
					if(chose != "0")    buffer += chose + ",";
					else                break;
				}
				buffer.erase(buffer.length()-1, 1);
				configFile["general_config"]["ignored_groups"] = buffer;
				configFile.save();
				break;
			}
		}
		if(system("clear") == -1) logerAddWarrning("Nie udało się wyczyścić terminala");
	}
}

void AntyVPN::createConfig() {
	configFile["general_config"]["enable"] = "false";
	configFile["general_config"]["message"] = "Zostałeś wyrzucony z powodu używania VPN";
	configFile["general_config"]["# pomoc"] = "channel/server";
	configFile["general_config"]["kick_from"] = "server";
	configFile["general_config"]["ignored_groups"] = "1,2";
	
	configFile.save();
}