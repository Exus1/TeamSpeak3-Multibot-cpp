#include "Ts3API.hpp"
#include "Loger/Loger.hpp"
#include "TeamSpeak3_API/Ts3API.hpp"
#include "Functions/Function.hpp"

#include <stdio.h>
#include <string>
#include <map>
#include <thread>
#include <time.h>

#include "Extras/Menu/Menu.hpp"
#include "Extras/wwwReader/www.hpp"

//#include <curl/curl.h>

// Functions Declaration
#include "Functions/WelcomeMessage/WelcomeMessage.hpp"
#include "Functions/AntyVPN/AntyVPN.hpp"
#include "Functions/PokeBot/PokeBot.hpp"

#define COLOR_RESET "\x1b[0m"
#define BOLD_ON "\x1b[1m"
#define BOLD_OFF "\x1b[22m"
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_BLUE "\x1b[34m"

using namespace std; 


int main(int argc, char **argv)
{
	//Foldery konfigurayjne
	if(!dirIsset("configs")) {
		logerAddInfo("Tworzenie folderów konfiguracyjnych");
		if(system("mkdir configs") == -1) logerAddWarrning("Wystąpił błąd przy tworzeniu folderu configs");
	
		if(system("mkdir configs/functions") == -1) logerAddWarrning("Wystąpił błąd przy tworzeniu folderu config/functions");
	}
    
	if(!dirIsset("configs/functions")) if(system("mkdir configs/functions") == -1) logerAddWarrning("Wystąpił błąd przy tworzeniu config/functions");
    
	if(!dirIsset("configs/functions")) logerAddError("Nie udało się utworzyć folderów konfiguracji");
    
	ConfigFile configcfg("configs/config.cfg");
	if(!fileIsset("configs/config.cfg")) {
		// Tworzenie głownego pliku konfiguracyjnego
		logerAddInfo("Tworzenie pliku głównej konfiguracji");
		configcfg["general_config"]["adress"] = "127.0.0.1";
		configcfg["general_config"]["serverPort"] = "9987";
		configcfg["general_config"]["queryPort"] = "10011";
		configcfg["general_config"]["login"] = "serveradmin";
		configcfg["general_config"]["password"] = "serveradminPassword";
		configcfg.save();
		
		// Konfigurator pierwszego uruchomienia
		string chose;
	
		cout << COLOR_GREEN << BOLD_ON;
		cout << "ExMultibot - Multibot dla serwerów TeamSpeak3" << endl;
		cout << BOLD_OFF;
		cout << "Konfiguracja podczas pierwszego uruchomienia" << endl;
		cout << endl;
		cout << COLOR_BLUE << "Podaj adres IP twojego serwera TeamSpeak3" << endl << COLOR_RESET;
		cin >> chose;
		configcfg["general_config"]["adress"] = chose;
		cout << COLOR_BLUE << "Podaj port twojego serwera TeamSpeak3" << endl << COLOR_RESET;
		cin >> chose;
		configcfg["general_config"]["serverPort"] = chose;
		cout << COLOR_BLUE << "Podaj port query twojego serwera TeamSpeak3" << endl << COLOR_RESET;
		cin >> chose;
		configcfg["general_config"]["queryPort"] = chose;
		cout << COLOR_BLUE << "Podaj login użytkownika query dla twojego serwera TeamSpeak3" << endl << COLOR_RESET;
		cin >> chose;
		configcfg["general_config"]["login"] = chose;
		cout << COLOR_BLUE << "Podaj hasło użytkownika query dla twojego serwera TeamSpeak3" << endl << COLOR_RESET;
		cin >> chose;
		configcfg["general_config"]["password"] = chose;
		cout << endl;
        cout << COLOR_BLUE << "Podaj nazwę bota" << endl << COLOR_RESET;
		cin >> chose;
		configcfg["general_config"]["nickname"] = chose;
		cout << endl;
		cout << COLOR_GREEN << "Utworzoną konfigurację możesz zmienić w pliku configs/config.cfg." << endl;
		configcfg.save();
		sleep(3);
		if(system("clear") == -1) logerAddWarrning("Czyszczenie interfejsu nie powiodło się");
	}
	
	// Konfiguracja połączenia
	serverConfig config;
	config.password = configcfg["general_config"]["password"]; //"4cFqJmSH63";
	config.ip = configcfg["general_config"]["adress"];
	config.login = configcfg["general_config"]["login"];
	config.password = configcfg["general_config"]["password"];
	config.query_port = configcfg["general_config"]["queryPort"];
	config.server_port = configcfg["general_config"]["serverPort"];
    config.nickname = configcfg["general_config"]["nickname"];

	
	Ts3API api(config);
    
    map<string, clientInfo> clientList;
	
    
	map<string, Function*> functionList;
	
	functionList["welcomemessage"] = new WelcomeMessage(api);
	functionList["antyvpn"] = new AntyVPN(api);
	functionList["pokebot"] = new PokeBot(api);

	// Tutaj uruchamia się menu
	Menu menu(functionList);

	//fstream testowy;
	//testowy.open("pliczek.txt", ios::out);
	// Tutaj wykonują się inne operacje dotyczące multibota. Np obsługa socketu interfejsu graficzneo
	while(true) {
		//testowy << "Lece" << endl;
		sleep(50);
	}
	
	
	
	
	int test;
	cin >> test;
	return 0;
}

