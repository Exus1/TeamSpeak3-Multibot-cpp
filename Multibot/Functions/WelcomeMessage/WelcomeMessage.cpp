#include "WelcomeMessage.hpp"

using namespace std;

WelcomeMessage::WelcomeMessage(Ts3API &api) : api(api) 
{
	if(!dirIsset("configs/functions/WelcomeMessage")) {
		if(system("mkdir configs/functions/WelcomeMessage") == -1) logerAddWarrning("Nie udało sie stworzyć folderu konfiguracyjnego funkcji WelcomeMessage");
	}
	
	if(!fileIsset("configs/functions/WelcomeMessage/config.cfg") || !fileIsset("configs/functions/WelcomeMessage/welcomeMessage.txt")) {
		createConfig();
	}
	getWelcomeMessage();
	
}

bool WelcomeMessage::run() 
{
	th = new thread(bind(&startFunctionInThread, this));
	if(th != NULL)  return true;
	else            return false;
}

bool WelcomeMessage::stop() 
{
	if(isRuning() && !loopEnd) {
		loopEnd = true;
		for(int i = 0; i <10; i++) {
			if(loopEnded) {
				loopEnded = false;
				loopEnd = false;
				return true;
			}
			//sleep(1);
		}
		return false;
	}else {
		return false;
	}
}
	
string WelcomeMessage::status() 
{
	return "TEST";
}
	
bool WelcomeMessage::isRuning() 
{
	return (th != NULL)? true : false;
}
	
bool WelcomeMessage::isEnabled() 
{
	return (configFile["general_config"]["enable"] == "true")? true : false;
}

void WelcomeMessage::operator()() 
{
	map<string, clientInfo> clientList;
	map<string, clientInfo> clientListS;
	map<string, map<string, string>> testl;
	string message;
	while(true) {
		api.getServerClientList(clientList, "client_nickname", "-times -groups -info -country -ip -badges");
		for(map<string, clientInfo>::iterator it = clientList.begin(); it != clientList.end(); it++) {
			if(clientListS[it->first].empty()) {
				prepareMessage(message, it->second);
				it->second.sendMessage(message);
			}
		}
		
		clientListS.clear();
		clientListS = clientList;
		clientList.clear();
		
		
		if(loopEnd) {
			loopEnded = true;
			return;
		}
	}
}

void WelcomeMessage::getWelcomeMessage() 
{
	fstream file;
	
	file.open("configs/functions/WelcomeMessage/welcomeMessage.txt", ios::in);
	
	if(file.fail()) {
		logerAddWarrning("Nie udało się pobrać wiadomości powitalnej z pliku. WelcomeMessage");
		stop();
	}
	string buffer;
	while(getline(file, buffer)) message += buffer;
    
	file.close();
	return;
}

void WelcomeMessage::prepareMessage(string &returned, clientInfo &clInfo) 
{
	string zn[9] = { "client_nickname", "clid", "client_database_id", "client_unique_identifiter", "client_created", "client_lastconnected", "client_platform", "connection_client_ip", "client_totalconnections" };
	
	clientInfo clDInfo;
	int clid;
    
	if(api.trystoi(clInfo["clid"], clid)) api.getClientInfo(clDInfo, clid);
	
	returned = message;
	
	size_t pos;
	
	for(int i = 0; i < 9; i++) {
		while((pos = returned.find("{"+zn[i]+"}")) != string::npos) {
			returned.erase(pos, zn[i].length()+2);
			
			if(zn[i] == "client_created")       returned.insert(pos, clDInfo.getTimestampTime("client_created"));
			else if(zn[i] == "client_created")  returned.insert(pos, clDInfo.getTimestampTime("client_lastconnected"));
			else                                returned.insert(pos, clDInfo[zn[i]]);
		}
	}
	
	serverInfo svInfo;
	api.getServerInfo(svInfo);
	string zns[7] = { "virtualserver_name", "virtualserver_platform", "virtualserver_maxclients", "virtualserver_clientsonline", "virtualserver_channelsonline", "virtualserver_created", "virtualserver_uptime" };
	
	for(int i = 0; i < 7; i++) {
		while((pos = returned.find("{"+zns[i]+"}")) != string::npos) {
			returned.erase(pos, zns[i].length()+2);
			
			if(zns[i] == "virtualserver_uptime")        returned.insert(pos, svInfo.getStrTime("virtualserver_uptime"));
			else if(zns[i] == "virtualserver_created")  returned.insert(pos, svInfo.getTimestampTime("virtualserver_created"));
			else                                        returned.insert(pos, svInfo[zns[i]]);
		}
	}
}

void WelcomeMessage::config() 
{
	while(true) {
		cout << COLOR_GREEN;
		cout << "Konfiguracja WelcomeMessage" << endl;
		cout << endl;
		cout << "Wybierz opcje której chcesz użyć:"<< endl;
		cout << COLOR_RESET;
		
		if(configFile["general_config"]["enable"] == "true")    cout << "1. Wyłącz" << endl;
		else                                                    cout << "1. Włącz" << endl;
		
		cout << "2. Wybierz kanał powitalny" << endl;
		cout << endl;
		cout << "0. Wstecz" << endl;
		
		unsigned short input;
		cin >> input;
		checkCinError();
		
		if(input > 2) {
			cout << COLOR_RED << "Nie ma takiej opcji" << COLOR_RESET << endl;
			sleep(3);
			if(system("clear") == -1) logerAddWarrning("Nie udało się wyczyścić terminala");
		}
		
		string chose;
		
		switch(input) 
		{
			case 0: return; // Wyjście
			case 1: // Włącz/Wyłącz
			{
				if(configFile["general_config"]["enable"] == "true") {
					configFile["general_config"]["enable"] = "false";
				}else {
					configFile["general_config"]["enable"] = "true";
				}
				configFile.save();
				break;
			}
			case 2: // Wybór kanału powitalnego
			{
				cout << "Wprowadź numer kanału powitalnego: " << endl;
				cin >> chose;
				configFile["general_config"]["channel"] = chose;
				configFile.save();
			}
		}
		if(system("clear") == -1) logerAddWarrning("Nie udało się wyczyścić terminala");
	}
}

void WelcomeMessage::createConfig() 
{
	configFile["general_config"]["enable"] = "false";
	configFile["general_config"]["messageFile"] = "welcomeMessage.txt";
	configFile["general_config"]["channel"] = "1";
	configFile.save();
	
	fstream configFile;
	
	configFile.open("configs/functions/WelcomeMessage/welcomeMessage.txt", ios::trunc | ios::out);
	
	if(!configFile.good()) logerAddError("Nie udało się utworzyć pliku z wiadomością powitalną funkcji WelcomeMessage");
	
	configFile << "Witaj na serwerze TeamSpeak3. Oto przykładowa wiadomość powitalna. Możesz ją ustawić w pliku configs/functions/WelcomeMessage/welcomeMessage.txt";
	
	configFile.close();
}